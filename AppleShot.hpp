#ifndef _APPLESHOT_H_
#define _APPLESHOT_H_

#include "Entity.hpp"


class AppleShot: public Entity
{
public:

	AppleShot(AnimationManager &a, Level &lev,int x,int y,bool dir):Entity(a,x,y)
	{
		option("AppleShot", 0.3, 10, "move");

		if (dir) dx = -0.3;
   		obj = lev.GetObjects("solid");
	}

	void update(float time)
	{
		x+=dx*time;

		for (int i=0;i<obj.size();i++)
			if (getRect().intersects(obj[i].rect)) //���� ������������ � �������� ������,
		        Health = 0; //�� ���������� ������

		if (Health<=0) {anim.set("explode"); 
						dx = 0;
		                if (anim.isPlaying()==false) life = false; //���� ��������� ��������, �� ���������� ������
		                }

		anim.tick(time);
	}

};

#endif
