#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "Level.hpp"
#include "Animation.hpp"
#include "GameMain.h"
#include "Entity.hpp"
#include "AppleShot.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Hunter.hpp"
#include "MovingPlatform.hpp"
#include "Buttons.h"
#include "Chicken.hpp"
#include "Coin.hpp"
#include "Apple.hpp"
#include "InterfaceIcons.hpp"
#include <sstream>

using namespace sf;
using namespace std;

enum EndGameVariants //возможные варианты окончания игры
{
	Exit,
	Win,
	Lose,
	Replay
};

enum Controls //управление
{
	up,
	down,
	left,
	right,
	shoot
};

bool showHints = false, showStats = false;

EndGameVariants RunGame(std::string clevel, RenderWindow* window, int& sc, int& coins, int& apps, int& he, Buttons& bList) //в этой функции собственно запускается игра
{
	int score = sc; //баллы
	int pickedCoins = coins; //собранные монеты
	int pickedApples = apps; //количество собранных яблок
	int hl = he; //здоровье

	Texture* loadtex;
	RectangleShape loadScreen;
	loadtex = new Texture;
	loadtex->loadFromFile("img/empty.png");
	loadScreen.setPosition(0,0);
	loadScreen.setTexture(loadtex);
	window->draw(loadScreen);
	drawText("Загрузка, пожалуйста подождите...",Vector2f(window->getSize().x/2,window->getSize().y/2),window);
	window->display();
	//инициализация
	bool gPause = false;
	bool GEP = false, endGame = false, ShootFixer = true;

	bool isWolfDestroyed = false, isHunterDestroyed = false;
	bool isAppleTaken = false, isCoinTaken = false, isChickenTaken = false;

	Font SystemFont;
	SystemFont.loadFromFile("etc/EuropeB.otf");
	Font ThinFont;
	ThinFont.loadFromFile("etc/EuropeN.ttf");
	Text Title("",SystemFont,30);
	Title.setStyle(Text::Regular);

	View view(FloatRect(0, 0, 1024, 600)); //создали вид окна (1024х600)

	Level lvl; //создали объект "Уровень"
	lvl.LoadFromFile(clevel); //загрузили из файла

	Texture enemy_t,enemyH_t, moveplatform_t, player_t, apple_t, shoot_t, chicken_t, coin_t,bg; //текстуры для объектов
	bg.loadFromFile("img/bg.png");
	enemy_t.loadFromFile("img/wolf.png");
	enemyH_t.loadFromFile("img/hunter.png");
	moveplatform_t.loadFromFile("img/movingPlatform.png");
	player_t.loadFromFile("img/fox.png");
	apple_t.loadFromFile("img/apple.png");
	shoot_t.loadFromFile("img/apple_shot.png");
	chicken_t.loadFromFile("img/chicken.png");
	coin_t.loadFromFile("img/coin.png");


	AnimationManager anim; //создаем объект менеджера анимаций
	anim.loadFromXML("anims/fox.xml",player_t); //загружаем из файла анимацию
	anim.animList["jump"].loop = 0; //показатель зацикленной анимации равен 0

	AnimationManager anim2; //анимация для яблока (стрельба)
	anim2.create("move",shoot_t,7,7,8,8,1,0);
	anim2.create("explode",shoot_t,81,2,22,22,1,0.02,29,false);

	AnimationManager anim3; //анимация для волка
	anim3.loadFromXML("anims/wolf.xml", enemy_t);
	anim3.create("move",enemy_t,103,14,83,95,2,0.1,0.05);
	anim3.animList["move"].loop = 0;

	AnimationManager anim3_1;
	anim3_1.loadFromXML("anims/hunter.xml", enemyH_t); //анимация для охотника
	anim3_1.animList["move"].loop = 1;

	AnimationManager anim4;
	anim4.create("move",moveplatform_t,0,0,95,22,1,0);

	AnimationManager anim5;
	anim5.create("stay",chicken_t,0,0,53,32,1,0); //это жареный цыпленок, которого подбирает персонаж

	AnimationManager anim6;
	anim6.create("stay",coin_t,0,0,32,32,1,0); //это монета, которую подбирает персонаж

	AnimationManager anim7;
	anim7.create("stay",apple_t,0,0,32,32,1,0); //это яблоко, которое подбирает персонаж

    Sprite background(bg);
    background.setOrigin(bg.getSize().x/2,bg.getSize().y/2);

	std::list<Entity*> entities; //создали список указателей на объекты
	std::list<Entity*>::iterator it; //манипулируем объектами с помощью итератора

	std::vector<Object> e = lvl.GetObjects("enemy"); //объектов-врагов загружаем в вектор
	for (int i=0;i < e.size();i++)
		entities.push_back(new Enemy(anim3, lvl, e[i].rect.left, e[i].rect.top,100)); //извлекаем из списка

	e = lvl.GetObjects("enemyH");
	for (int i=0;i < e.size();i++)
		entities.push_back(new Hunter(anim3_1, lvl, e[i].rect.left, e[i].rect.top,100));

	e = lvl.GetObjects("MovingPlatformX");
	for (int i=0;i < e.size();i++)
		entities.push_back(new MovingPlatform(anim4, lvl, e[i].rect.left, e[i].rect.top,true));
	e = lvl.GetObjects("MovingPlatformY");
	for (int i=0;i < e.size();i++)
		entities.push_back(new MovingPlatform(anim4, lvl, e[i].rect.left, e[i].rect.top,false));

	e = lvl.GetObjects("Chicken");	
	for (int i=0;i < e.size();i++)
	{
		entities.push_back(new Chicken(anim5, lvl, e[i].rect.left, e[i].rect.top));
	}

	e = lvl.GetObjects("Coin");	
	for (int i=0;i < e.size();i++)
	{
		entities.push_back(new Coin(anim6, lvl, e[i].rect.left, e[i].rect.top-32));
	}

	e = lvl.GetObjects("Apple");
	for(int i = 0; i<e.size(); i++)
	{
		entities.push_back(new Apple(anim7, lvl, e[i].rect.left, e[i].rect.top-32));
	}

	for(it = entities.begin();it!=entities.end();it++)
	{
		Entity *b = *it;
		if(b->Name=="Enemy")
			b->update(0);
	}

	Object pl = lvl.GetObject("player");
	PLAYER Fox(anim, lvl, pl.rect.left, pl.rect.top);
	Fox.option("Player",0,hl,"stay");

	InterfaceIcon CoinsIcon("img/coin_icon.png", 64, 64, 64, 64, pickedCoins);
	//это иконка монеты, возле которой выводим количество собранных монеток
	InterfaceIcon ApplesIcon("img/apple_icon.png", 212,64, 64, 64, pickedApples);
	//это иконка яблока, возле которой выводим количество собранных яблок
	InterfaceIcon HealthIcon("img/health_icon.png", 350, 64, 64, 64, Fox.getHealth());

	InterfaceIcon ScoreIcon("img/score.png", 518, 64, 100, 60, score);

	RectangleShape EGD;
	Texture* egdtex = new Texture;
	egdtex->loadFromFile("img/empty.png");
	EGD.setTexture(egdtex);
	EGD.setPosition(0,0);
	EGD.setSize(Vector2f(1024,0));

	Clock clock; //таймер игрового времени

	//Это основа игры
	while (window->isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/600;  

		if (time > 40) time = 40; //урезаем "время", для того чтобы
		//оно примерно соответствовало жизненному

		Event event;
		while (window->pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
				if ((event.key.code==Keyboard::Space)&&ShootFixer&&(pickedApples!=0))
		        {
					entities.push_back(new AppleShot(anim2,lvl,Fox.x+44,Fox.y+40,Fox.dir));
					ShootFixer = false;
					pickedApples--;
				}
				if((event.type == Event::KeyReleased)&&(event.key.code==Keyboard::Space)&&!ShootFixer)
					ShootFixer = true;
				if(event.type == Event::Closed && !gPause) //если хотим закрыть окно во время игры,
				{
					gPause = true; //то ставим на паузу
				}
		}
		if(!endGame)
		{
			if (Keyboard::isKeyPressed(getHotKey(Controls::left))) Fox.key["L"]=true;
			if (Keyboard::isKeyPressed(getHotKey(Controls::right))) Fox.key["R"]=true;
			if (Keyboard::isKeyPressed(getHotKey(Controls::up))) Fox.key["Up"]=true;
			if (Keyboard::isKeyPressed(getHotKey(Controls::down))) Fox.key["Down"]=true;
			if (Keyboard::isKeyPressed(getHotKey(Controls::shoot))) Fox.key["Space"]=true;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				if(!gPause)
					gPause = true;
				else gPause = false;
			if(!gPause)
			{
				CoinsIcon.update(pickedCoins);
				CoinsIcon.DrawIcon(*window);
				ApplesIcon.update(pickedApples);
				ApplesIcon.DrawIcon(*window);
				for(it=entities.begin();it!=entities.end();)
				{
					Entity *b = *it;
					if(
						((b->Name=="Enemy")&&(b->y>Fox.getRect().top-350)&&(b->y<Fox.getRect().top+350)
						&&(b->x>Fox.getRect().left-450)&&(b->x<Fox.getRect().left+450))
						||
						((b->Name!="Enemy"))
						)
						b->update(time);
					if (b->life==false) //если враг умер
					{
						it  = entities.erase(it); //удалили из вектора
						delete b; //удалили указатель
					}
					else it++;
				}
				Fox.update(time);
				HealthIcon.update(Fox.getHealth());
				if(Fox.getHealth()<=0)
				{
					gPause = true;
					GEP = true;
				}
				for(it=entities.begin();it!=entities.end();it++)
				{
					//1. волки
					if ((*it)->Name=="Enemy")
					{
						Entity *enemy = *it;

						if (enemy->Health<=0) continue;

						if  (Fox.getRect().intersects(enemy->getRect()))
								if (!Fox.hit)
								{
									Fox.Health-=20;
									Fox.hit = true;
									if(Fox.dir)
										Fox.x+=10;
									else Fox.x-=10;
								}

							for (std::list<Entity*>::iterator it2=entities.begin(); it2!=entities.end(); it2++)
							{
								Entity *bullet = *it2;
								if(bullet->Name=="AppleShot")
									if(bullet->Health>0)
										if(bullet->getRect().intersects(enemy->getRect()))
										{
											enemy->Health = 0;
											bullet->Health = 0;
											score+=30;
											ScoreIcon.update(score);
											isWolfDestroyed = true;
										}
							}
					}
					//охотники
					if ((*it)->Name=="EnemyH")
					{
						Entity *enemy = *it;

						if (enemy->Health<=0) continue;

						if  (Fox.getRect().intersects(enemy->getRect()))
							if (Fox.dy>0) //если прыгнули сверху на голову
								{
									enemy->dx = 0;
									Fox.dy = -0.2;
									enemy->Health = 0;
									score+=50;
									ScoreIcon.update(score);
									isHunterDestroyed = true;
								}
							else
								if (!Fox.hit)
								{
									Fox.Health-=25;
									Fox.hit = true;
									if(Fox.dir)
										Fox.x+=10;
									else Fox.x-=10;
								}
					}

					//2. движущиеся платформы
					if ((*it)->Name=="MovingPlatformX")
					{
						Entity *movPlat = *it;
						if  (Fox.getRect().intersects(movPlat->getRect()))
							if (Fox.dy>0)
								if (Fox.y+Fox.h<movPlat->y+movPlat->h)
								{
									Fox.y = movPlat->y - Fox.h + 3;
									Fox.x+=movPlat->dx*time;
									Fox.dy = 0;
									Fox.STATE = PLAYER::stay;
								}
					}
					if ((*it)->Name=="MovingPlatformY")
					{
						Entity *movPlat = *it;
						if  (Fox.getRect().intersects(movPlat->getRect()))
							if (Fox.dy>0)
								if (Fox.y+Fox.h<movPlat->y+movPlat->h)
								{
									Fox.y = movPlat->y - Fox.h + 3;
									Fox.dy = 0;
									Fox.STATE = PLAYER::stay;
								}
					}
					//3. Жареные цыплята
					if ((*it)->Name=="Chicken")
					{
						Entity *mc = *it;

						if  (Fox.getRect().intersects(mc->getRect()) && mc->life)
						{
							Fox.Health+=20;
							mc->life = false;
							isChickenTaken = true;
						}
					}
					//4. Монеты
					if ((*it)->Name=="Coin")
					{
						Entity *Coin = *it;

						if  (Fox.getRect().intersects(Coin->getRect()) && Coin->life)
						{
							Coin->life = false;
							pickedCoins++; //увеличили кол-во собранных монет
							score+=5;
							ScoreIcon.update(score);
							isCoinTaken = true;
						}
					}
					//5. Яблоки
					if((*it)->Name=="Apple")
					{
						Entity *Apple = *it;
						if(Fox.getRect().intersects(Apple->getRect()) && Apple->life)
						{
							Apple->life=false;
							pickedApples++;
							score+=10;
							ApplesIcon.update(pickedApples);
							ScoreIcon.update(score);
							isAppleTaken = true;
						}
					}
				}
			}
			Object exit = lvl.GetObject("exit");
			if(Fox.getRect().intersects(exit.rect))
			{
				gPause = true;
				GEP = true;
			}

			window->clear();
			view.setCenter(Fox.x,Fox.y);
			window->setView(view);

			background.setPosition(view.getCenter());
			window->draw(background);

			lvl.Draw(*window);

			for(it = entities.begin();it!=entities.end();it++)
				(*it)->draw(*window);

			Fox.draw(*window);
			std::ostringstream updStr;
			updStr<<pickedApples;
			ApplesIcon.data.setString(updStr.str());
			CoinsIcon.DrawIcon(*window); //рисуем иконку монеты + выводим количество
			drawText(CoinsIcon.data.getString(),Vector2f(Fox.getRect().left-window->getSize().x/2 + 160,Fox.getRect().top-window->getSize().y/2 + 100),SystemFont,Title,window);
			ApplesIcon.DrawIcon(*window);
			drawText(ApplesIcon.data.getString(),Vector2f(Fox.getRect().left-window->getSize().x/2 + 300,Fox.getRect().top-window->getSize().y/2 + 100),SystemFont,Title,window);
			HealthIcon.DrawIcon(*window);
			drawText(HealthIcon.data.getString(),Vector2f(Fox.getRect().left-window->getSize().x/2 + 440,Fox.getRect().top-window->getSize().y/2 + 100),SystemFont,Title,window);
			ScoreIcon.DrawIcon(*window);
			//рисуем текст, отображающий количество набранных баллов (вместе с дополнительными (за яблоки))
			drawText(ScoreIcon.data.getString(),Vector2f(Fox.getRect().left-window->getSize().x/2+700,Fox.getRect().top-window->getSize().y/2 + 100),SystemFont,Title,window);

			if(Keyboard::isKeyPressed(Keyboard::H) && !gPause)
			{
				if(!showHints)
				{
					showHints = true;
					showStats = false;
				}
				else showHints = false;
			}

			if(showHints)
			{
				wchar_t* ifWASD = L"Прыжок: W\tВправо: D\tВлево: A\t\nБросить яблоко: Space\tПомощь: H\tСтатистика: I";
				wchar_t* ifNoWASD = L"Вверх: клавиша ↑\tВправо: клавиша →\tВлево: клавиша ←\t\nБросить яблоко: Space\tПомощь: H\tСтатистика: I";
				Text txt("",ThinFont,30);
				if(!getWASDcontrol())
				{
					drawText(ifNoWASD,Vector2f(Fox.getRect().left+window->getSize().x/2-20,Fox.getRect().top+window->getSize().y/2-50), ThinFont,txt,window);
					Texture* arrows_t = new Texture[3];
					arrows_t[0].loadFromFile("img/up.png");
					arrows_t[1].loadFromFile("img/left.png");
					arrows_t[2].loadFromFile("img/right.png");
					Sprite* arrows = new Sprite[3];
					for(int i = 0; i<3; i++)
						arrows[i].setTexture(arrows_t[i]);
					arrows[0].setPosition(Vector2f(Fox.getRect().left+window->getSize().x/2-670,Fox.getRect().top+window->getSize().y/2-60));
					arrows[1].setPosition(Vector2f(Fox.getRect().left+window->getSize().x/2-80,Fox.getRect().top+window->getSize().y/2-60));
					arrows[2].setPosition(Vector2f(Fox.getRect().left+window->getSize().x/2-365,Fox.getRect().top+window->getSize().y/2-60));
					for(int i = 0; i<3; i++)
						window->draw(arrows[i]);
					delete [] arrows_t, arrows;
				}
				else
					drawText(ifWASD,Vector2f(Fox.getRect().left+window->getSize().x/2-200,Fox.getRect().top+window->getSize().y/2-50), ThinFont,txt,window);
			}

			if(Keyboard::isKeyPressed(Keyboard::I) && !gPause)
			{
				if(!showStats)
				{
					showStats = true;
					showHints = false;
				}
				else showStats = false;
			}

			if(showStats)
			{
				short movPlats = lvl.GetObjects("MovingPlatformX").size() + lvl.GetObjects("MovingPlatformY").size();
				short stPlats = lvl.GetObjects("staticPlatform").size()-1;
				short wolves = lvl.GetObjects("enemy").size();
				short hunters = lvl.GetObjects("enemyH").size();
				short traps = lvl.GetObjects("getaway").size();
				std::ostringstream os1, os2, os3, os4, os5;
				os1<<stPlats; os2<<movPlats; os3<<wolves; os4<<hunters; os5<<traps;
				String stats = "Неподвижных платформ: "+os1.str()+"\tПодвижных платформ: "+os2.str()+"\tВолков: "+os3.str()+"\nОхотников: "+os4.str()+"\tПрепятствий: "+os5.str();
				Text txt(stats,ThinFont,30);
				drawText(stats,Vector2f(Fox.getRect().left+window->getSize().x/2-230,Fox.getRect().top+window->getSize().y/2-50), ThinFont,txt,window);
			}

			if(isWolfDestroyed)
			{
				Font fnt(SystemFont);
				Text text("+ 30 баллов!", fnt, 40);
				text.setColor(Color(255,201,14));
				text.setPosition(
					Vector2f(Fox.getRect().left-window->getSize().x/2+350,
					Fox.getRect().top-window->getSize().y/2+270));
				Clock clk;
				clk.restart();
				do
					window->draw(text);
					while(clk.getElapsedTime().asMilliseconds()==6000);
				isWolfDestroyed = false;
			}
			if(isHunterDestroyed)
			{
				Font fnt(SystemFont);
				Text text("+ 50 баллов!", fnt, 40);
				text.setColor(Color(255,201,14));
				text.setPosition(
					Vector2f(Fox.getRect().left-window->getSize().x/2+350,
					Fox.getRect().top-window->getSize().y/2+270));
				Clock clk;
				clk.restart();
				do
					window->draw(text);
					while(clk.getElapsedTime().asMilliseconds()==6000);
				isHunterDestroyed = false;
			}
			if(isAppleTaken)
			{
				Font fnt(SystemFont);
				Text text("+ 10 баллов!", fnt, 40);
				text.setColor(Color(113,225,3));
				text.setPosition(
					Vector2f(Fox.getRect().left-window->getSize().x/2+350,
					Fox.getRect().top-window->getSize().y/2+270));
				Clock clk;
				clk.restart();
				do
					window->draw(text);
					while(clk.getElapsedTime().asMilliseconds()==6000);
				isAppleTaken = false;
			}
			if(isCoinTaken)
			{
				Font fnt(SystemFont);
				Text text("+ 5 баллов!", fnt, 40);
				text.setColor(Color(0,162,232));
				text.setPosition(
					Vector2f(Fox.getRect().left-window->getSize().x/2+350,
					Fox.getRect().top-window->getSize().y/2+270));
				Clock clk;
				clk.restart();
				do
					window->draw(text);
					while(clk.getElapsedTime().asMilliseconds()==6000);
				isCoinTaken = false;
			}
			if(isChickenTaken)
			{
				Font fnt(SystemFont);
				Text text("Здоровье + 20", fnt, 40);
				text.setColor(Color(255,128,192));
				text.setPosition(
					Vector2f(Fox.getRect().left-window->getSize().x/2+350,
					Fox.getRect().top-window->getSize().y/2+270));
				Clock clk;
				clk.restart();
				do
					window->draw(text);
					while(clk.getElapsedTime().asMilliseconds()==6000);
				isChickenTaken = false;
			}
			if(pickedApples<=0)
			{
				Font fnt(SystemFont);
				Text text("У вас нет яблок, чтобы стрелять!", fnt, 40);
				text.setColor(Color(255,0,0));
				text.setPosition(Vector2f(Fox.getRect().left-window->getSize().x/2+180, Fox.getRect().top-window->getSize().y/2+270));
				if(Keyboard::isKeyPressed(Keyboard::Space) && !gPause)
				{
					window->draw(text);
				}
			}
			if(gPause)
			{
				window->setView(View(FloatRect(0, 0, 1024, 600)));
				RectangleShape pauseRect;
				pauseRect.setFillColor(Color::Color(0,0,0,100));
				pauseRect.setSize(Vector2f(1024,600));
				pauseRect.setPosition(0,0);
				window->draw(pauseRect);
				if(GEP)
				{
					if(EGD.getSize().y>=600)
						endGame = true;
					else
					{
						EGD.setSize(Vector2f(1024,EGD.getSize().y+30));
					}
				}
				else
				{
					bList.update(window);
					bList.draw(window);
					drawText("ПАУЗА",Vector2f(500,200),window);
					switch(bList.getClick())
					{
					case 0:
						gPause = false;
						break;
					case 1: //кнопка "Выйти..."
						{
							if(getAutoSave())
							{
								FILE* fp = fopen("userdata.usd","wb");
								char* tmp = new char[clevel.size()+1];
								for(int i = 0; i<clevel.size(); i++)
									tmp[i] = clevel[i];
								tmp[clevel.size()] = '\0';
								int h = Fox.getHealth();
								fprintf(fp,"%s %d %d %d %d",tmp,score,pickedCoins,pickedApples,h);
								fclose(fp);
								delete tmp;
							}
							return Exit;
						}
					case 2: //кнопка "Сохранить игру" (активна в случае отключенного AutoSave)
						{
							//Сохранение в файл
							FILE* fp = fopen("userdata.usd","wb");
							char* tmp;
							tmp = new char[clevel.size()+1];
							for(int i = 0; i<clevel.size(); i++)
								tmp[i] = clevel[i];
							tmp[clevel.size()] = '\0';
							int h = Fox.getHealth();
							fprintf(fp,"%s %d %d %d %d", tmp, score, pickedCoins, pickedApples, h);
							fclose(fp);
							delete tmp;
							break;
						}
					case 3:
						{
							return Replay;
						}
						break;
					}
				}
			}
			window->draw(EGD);
			window->display();
		}
		else
		{
			if(Fox.getHealth()<=0)
				return Lose;
			sc = score;
			apps = pickedApples;
			coins = pickedCoins;
			return Win;
		}
	}
	delete egdtex, loadtex;
}