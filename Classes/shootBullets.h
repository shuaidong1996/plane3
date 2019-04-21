#ifndef __shootBullets_H__
#define __shootBullets_H__

#include "Common.h"

class shootBullets : public CCSprite
{
	int _isEnermy;//�л� -1  Ӣ�ۻ� 1
	int _id;
	CCArray* _bullets;
public:
	int _damage;//�ӵ��Ĺ�����
	CCSprite* _plane;

	static shootBullets* create(int damage, int id, CCSprite* s, bool isEnermu, CCArray* bullets);//id �ӵ�����  s���ӵ��� ս��������ȡλ�ã�

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

