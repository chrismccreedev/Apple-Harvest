#ifndef APPLE_H
#define APPLE_H
#include "Entity.hpp"

class Apple: public Entity
{
public:
	Apple(AnimationManager &a,Level &lev,int x,int y): Entity(a,x,y)
	{
		option("Apple", 0.01, 10, "stay");
	}
	void update(float time)
	{
		anim.tick(time);
	}
};

#endif APPLE_H