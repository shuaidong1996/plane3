#ifndef __Hero_H__
#define __Hero_H__

#include "Common.h"
#include "Bullet.h"

class Hero : public CCSprite
{
	int _shootCD;
	int _curCD;
	int _id;
public:
	int _hp;
	int _damage;
	CCArray* _bullets;//用于存放子弹的数组

	static Hero* create(int id)
	{
		Hero* h = new Hero;
		h->init(id);
		h->autorelease();
		return h;
	}
	bool init(int id);

	void update(float);
	bool canFire();
	void checkBullets();

	void onEnter()//英雄飞机一创建，马上初始化  子弹数组，用于创建子弹
	{
		CCSprite::onEnter();
		_bullets = CCArray::create();
		_bullets->retain();//保存数组不被回收
	}

	void onExit()
	{
		CCSprite::onExit();
		_bullets->release();
	}
};

#endif
