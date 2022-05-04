#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"


class PLAYER: public Entity
{
public:
	enum {stay,walk,jump} STATE; //состояния персонажа (стоять, идти, прыгать)
	bool shoot, hit; //флажки "стреляет" или "ударен"
	std::map<std::string,bool> key; //нажатая клавиша, воздействующая на персонажа

	PLAYER(AnimationManager &a, Level &lev,int x,int y):Entity(a,x,y)
	{
		option("Player",0,100,"stay");
        STATE = stay;
		hit = false;
		obj = lev.GetAllObjects();
	}

	PLAYER():Entity(AnimationManager(),0,0)
	{
	}

	void Keyboard()
	{
		if (key["L"]) //если нажали клавишу "влево" (стрелка влево либо А,
					  //в зависимости от настроек игры
		{
			dir = 1; //направление "1" - влево, "0" - вправо
			dx = -0.25; //придаем ускорение по оси Х
			if (STATE==stay) STATE = walk; //если до того "стояли", то "идем"
		}

		if (key["R"])
		{
			dir = 0;
			dx = 0.25;
			if (STATE==stay) STATE = walk;
		}

		if (key["Up"])
		{
			if (STATE==stay || STATE==walk)
			{
				dy = -0.6;
				STATE = jump;
				anim.play("jump");
			}
		}

		if (key["Space"])
		{
			shoot = true;
		}

		//если клавиша отпущена
		if (!(key["R"] || key["L"]))
		{
			dx=0;
			if (STATE==walk) STATE = stay;
		}
		if (!key["Up"])
		{
			dy = 0.3;
		}
		if (!key["Space"])
		{
			shoot = false;
		}

		key["R"]=key["L"]=key["Up"]=key["Down"]=key["Space"]=false;
	}

    void Animation(float time)
    {
 		if (STATE==stay) anim.set("stay");
		if (STATE==walk) anim.set("walk");
		if (STATE==jump) anim.set("jump");

        if (shoot)
		{
			anim.set("shoot");
		}

		if (hit)
		{
			timer+=time;
			if (timer>1000) //"мигаем" в течение 1 сек
			{
				hit = false;
				timer = 0;
			}
			anim.set("hit");
		}

		if (dir) anim.flip(); //отражаем анимацию по Х

		anim.tick(time); //проигрываем анимацию
    }

	void update(float time) //функция, обновляющая графику персонажа
	{
		Keyboard();

        Animation(time);

		dy+=0.001*time;

		x+=dx*time;
		Collision(0);

		y+=dy*time;
		Collision(1);
		//if(Health>100)
		//	Health = 100;
	}

	void Collision(int num) //функция, обрабатывающая столкновения персонажа
	{
		for (int i = 0;i<obj.size();i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name=="solid" || obj[i].name=="staticPlatform") //если это твердая поверхность или статическая платформа
				{
					if (dy>0 && num==1)
					{
						y = obj[i].rect.top - h;
						dy = 0; //останавливаем "падение вниз"
						STATE = stay; //и мы можем стоять
					}
					if (dy<0 && num==1)
					{
						y = obj[i].rect.top + obj[i].rect.height;
						dy = 0;
					}
					if (dx>0 && num==0)
					{
						x = obj[i].rect.left - w;
					}
					if (dx<0 && num==0)
					{
						x = obj[i].rect.left + obj[i].rect.width;
					}
				}

				if(obj[i].name=="getaway") //если это вода или ветки (препятствия)
				{
					if (dy>0 && num==1)
					{
						dy = 0; 
						y = obj[i].rect.top - obj[i].rect.height - h - 32;
						hit = true; //"ударяемся"
						Health-=5; //отнимаем 5 единиц здоровья
					}
					if(dx>0 && num==0)
					{
						x = obj[i].rect.left - w - 1;
						hit = true;
						Health-=5;
					}
					if(dx<0 && num==0)
					{
						x = obj[i].rect.left + obj[i].rect.width + 1;
						hit = true;
						Health-=5;
					}
				}
			}
	}

};


#endif PLAYER_H
