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
	CCArray* _bullets;//���ڴ���ӵ�������

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

	void onEnter()//Ӣ�۷ɻ�һ���������ϳ�ʼ��  �ӵ����飬���ڴ����ӵ�
	{
		CCSprite::onEnter();
		_bullets = CCArray::create();
		_bullets->retain();//�������鲻������
	}

	void onExit()
	{
		CCSprite::onExit();
		_bullets->release();
	}
};

#endif
