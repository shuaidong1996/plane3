

#ifndef __Bullet_H__
#define __Bullet_H__

#include "Common.h"

class Bullet : public CCSprite
{
public:
	int _damage;//子弹的攻击力
	static Bullet* create(bool isEnemy, int damage,int id)
	{
		Bullet* b = new Bullet;
		b->init(isEnemy,damage,id);
		b->autorelease();
		return b;
	}
	bool init(bool isEnemy, int damage,int id)
	{
		_damage = damage;
		if (!isEnemy)//不是敌人
		{
			switch (id)
			{
			case 0:initWithFile(IMAGE_Bullet1);
				break;
			case 1:initWithFile(IMAGE_Bullet2);
				break;
			case 2:initWithFile(IMAGE_Bullet3);
				break;
			default:initWithFile(IMAGE_Bullet4);
				break;
			}
		}
		else
		{
			initWithFile(IMAGE_Bullet);
		}
		return true;
	}
};

#endif
