#ifndef _HUNTER_H_
#define _HUNTER_H_

#include "Enemy.hpp"

class Hunter: public Enemy
{
public:
	Hunter(AnimationManager &a,Level &lev,int x,int y,int hp):Enemy(a,lev,x,y,hp)
	{
		option("EnemyH",0.1,hp,"move");
	}
	void update(float time)
	{
		x+=dx*time;
		Collision(dx, 0);
		timer+=time;
		if (timer>2500)
		{
			anim.set("stop");
			dx = 0;
			timer_end+=time;
			if(timer_end>800)
			{
				timer_end = 0;
				anim.set("move");
				dx = 0.1;
				timer = 0;
				timer+=time;
			}
		}
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
};

#endif