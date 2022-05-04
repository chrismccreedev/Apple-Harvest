#ifndef _COIN_H_
#define _COIN_H_
#include "Entity.hpp"

class Coin: public Entity
{
public:

	Coin(AnimationManager &a,Level &lev,int x,int y):Entity(a,x,y)
	{
		option("Coin", 0.01, 10, "stay");
	}

	void update(float time)
	{
		anim.tick(time);
	}
};

#endif
