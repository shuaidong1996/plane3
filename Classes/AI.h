
#ifndef __AI_H__
#define __AI_H__
#include "Common.h"
#include "Enemy.h"
#include "Bullet.h"

// ���Ƶл��Ĳ�������ʧ�����ǲ�������ײ
class AI : public CCNode
{
public:
	CREATE_FUNC(AI);
	bool init();

	// �������ел�������
	CCArray* _enemys;

	// �������ел����ӵ�
	CCArray* _bullets;

	// �����л��ͼ��л��Ƿ��Ѿ��ɵ�������
	void update(float);

	void onEnter()
	{
		CCNode::onEnter();
		_enemys = CCArray::create();//���� ���˷ɻ�������
		_enemys->retain();

		_bullets = CCArray::create();//���� �����ӵ�������
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

