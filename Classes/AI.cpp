#include "AI.h"

bool AI::init()
{
	CCNode::init();

	//���ڼ��л��Ƿ��Ѿ��ɳ�����
	scheduleUpdate();

	// �����л���ʱ�䣬���Խ���д�������ļ��������Ժ��޸���Ϸ�߼�
	schedule(schedule_selector(AI::genSmall), 1);//ÿ1�봴��һ��С�ɻ�
	schedule(schedule_selector(AI::genMiddle), 5);//ÿ5�봴��һ���зɻ�
	schedule(schedule_selector(AI::genBig), 30);//ÿ30�봴��һ����ɻ�

	return true;
}
// ���л��Ƿ��Ѿ��ɳ�����
void AI::update(float)
{
	int count = _enemys->count();
	for (int i = count - 1; i >= 0; --i)
	{
		Enemy* e = (Enemy*)_enemys->objectAtIndex(i);
		if (Util::isAllOutOfWindow(e))
		{
			e->removeFromParent();
			_enemys->removeObject(e);
		}
		else
		{
			e->shoot(_bullets);//û�зɳ�����ʹ����ӵ���
		}
	}

	// ����ӵ��Ƿ�ɳ�����
	count = _bullets->count();
	for (int i = count - 1; i >= 0; --i)
	{
		Bullet* b = (Bullet*)_bullets->objectAtIndex(i);
		if (Util::isAllOutOfWindow(b))
		{
			b->removeFromParent();
			_bullets->removeObject(b);
		}
	}
}

//���� ĳ�����͵� �з��ɻ�
void AI::genSmall(float)
{
	genEnemy(Enemy::SMALL);
}
void AI::genMiddle(float)
{
	genEnemy(Enemy::MIDDLE);
}
void AI::genBig(float)
{
	genEnemy(Enemy::BIG);
}

//�����з��ɻ�
void AI::genEnemy(Enemy::TYPE type)
{
	Enemy* e = Enemy::create(type);
	addChild(e);

	// Ϊ�л�����һ�����λ�ã����ֵ����һ�����ڿ�ȷ�Χ�����Ǵ��ڿ�ȼ�ȥ�ɻ���ȷ�Χ
	float x = CCRANDOM_0_1() * (winSize.width - e->boundingBox().size.width) + e->boundingBox().size.width/2;
	float y = winSize.height;
	e->setPosition(ccp(x, y));

	// ����һ���з��ɻ����ͼ��뵽  AI �ķɻ�������
	_enemys->addObject(e);
}