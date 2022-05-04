#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity.hpp"


class Enemy: public Entity
{
public:

	Enemy(AnimationManager &a,Level &lev,int x,int y,int hp):Entity(a,x,y)
	{
		option("Enemy", 0.1, hp, "move");
		obj = lev.GetAllObjects();
	}

	void update(float time)
	{
		x+=dx*time;
		Collision(dx, 0);
		timer+=time;
		if (Health<=0)
		{
			anim.set("dead");
			dx = 0;
			timer_end+=time;
		    if (timer_end>800)
				life = false;
		}
		if(dx<0)
			anim.flip(false);
		else
			anim.flip(true);
		anim.tick(time);
	}
	void Collision(float Dx, float Dy)
	{
		for(int i = 0; i<obj.size(); i++)
		{
			if(getRect().intersects(obj[i].rect))
			{
				if(obj[i].name=="staticPlatform")
				{
					//if(y<obj[i].rect.top-h)
					{
						if(x<=obj[i].rect.left && dx<0)
						{
							x = obj[i].rect.left;
							dx = 0.1;
							anim.flip(false);
						}
						if(x>=obj[i].rect.left+obj[i].rect.width-w && dx>0)
						{
							x = obj[i].rect.left+obj[i].rect.width-w;
							dx = -0.1;
							anim.flip(true);
						}
					}
				}
				if(obj[i].name=="solid")
				{
					if(Dy>0)
					{
						y = obj[i].rect.top - h;
						dy = 0;
					}
					if(Dy<0)
					{
						y = obj[i].rect.top + obj[i].rect.height;
						dy = 0;
					}
					if(Dx>0)
					{
						x = obj[i].rect.left - w;
						dx = -0.1;
						anim.flip(true);
					}
					if(Dx<0)
					{
						x = obj[i].rect.left + obj[i].rect.width;
						dx = 0.1;
						anim.flip(false);
					}
				}
			}
		}
	}
};

#endif
