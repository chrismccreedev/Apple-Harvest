#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include "Entity.hpp"

class MovingPlatform: public Entity
{
public:
	bool dir;
	MovingPlatform(AnimationManager &a, Level &lev,int x,int y,bool i_dir):Entity(a,x,y),dir(i_dir)
	{
		if(i_dir)
		{
			option("MovingPlatformX", 0.05, 0, "move");
			obj = lev.GetAllObjects();
		}
		else
		{
			option("MovingPlatformY", 0.05, 0, "move");
			obj = lev.GetAllObjects();
		}
	}

	void update(float time)
	{
		if(dir)
			x += dx*time;
		else
			y += dx*time;
		timer+=time;
		for(int i = 0; i<obj.size(); i++)
		{
			if(getRect().intersects(obj[i].rect))
			{
				if(obj[i].name=="solid" || obj[i].name=="staticPlatform" || timer>6000 || (dx<0 && y==obj[i].rect.top+obj[i].rect.height))
				{
					dx*=-1;
					timer = 0;
				}
			}
		}
		if(timer>6000)
		{
			dx*=-1;
			timer = 0;
		}
		anim.tick(time);
	}
};

#endif MOVINGPLATFORM_H
