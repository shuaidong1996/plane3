
#ifndef __AI_H__
#define __AI_H__
#include "Common.h"
#include "Enemy.h"
#include "Bullet.h"

// 控制敌机的产生和消失，但是不负责碰撞
class AI : public CCNode
{
public:
	CREATE_FUNC(AI);
	bool init();

	// 保存所有敌机的数组
	CCArray* _enemys;

	// 保存所有敌机的子弹
	CCArray* _bullets;

	// 产生敌机和检测敌机是否已经飞到窗口外
	void update(float);

	void onEnter()
	{
		CCNode::onEnter();
		_enemys = CCArray::create();//保存 敌人飞机的数组
		_enemys->retain();

		_bullets = CCArray::create();//保存 敌人子弹的数组
		_bullets->retain();
	}

	void onExit()
	{
		CCNode::onExit();
		_enemys->release();
		_bullets->release();
	}

	void genSmall(float);
	void genMiddle(float);
	void genBig(float);
	void genEnemy(Enemy::TYPE type);
};

#endif

