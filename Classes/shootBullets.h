#ifndef __shootBullets_H__
#define __shootBullets_H__

#include "Common.h"

class shootBullets : public CCSprite
{
	int _isEnermy;//敌机 -1  英雄机 1
	int _id;
	CCArray* _bullets;
public:
	int _damage;//子弹的攻击力
	CCSprite* _plane;

	static shootBullets* create(int damage, int id, CCSprite* s, bool isEnermu, CCArray* bullets);//id 子弹种类  s发子弹的 战机（用于取位置）

	bool init(int damage, int id, CCSprite* s, bool isEnermu, CCArray* bullets);
	void selectFire(int id);
	void fire0();
	void fire1();
	void fire2();
	void fire3();
	void fire4();

	void fire();
	void fire(const CCPoint& delta);
	void fire(int angle, const CCPoint& delta);
	CCSprite* gainBullet();
	void checkBullets();
	void moveFire();

};

#endif

