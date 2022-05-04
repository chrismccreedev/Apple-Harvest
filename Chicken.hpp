#ifndef _CHICKEN_H_
#define _CHICKEN_H_

#include "Entity.hpp"


class Chicken: public Entity
{
public:

	Chicken(AnimationManager &a,Level &lev,int x,int y):Entity(a,x,y)
	{
		option("Chicken", 0.01, 15, "stay");
	}

	void update(float time)
	{
		anim.tick(time);
	}
};

#endif
