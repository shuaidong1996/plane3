#include "AI.h"

bool AI::init()
{
	CCNode::init();

	//用于检测敌机是否已经飞出窗外
	scheduleUpdate();

	// 创建敌机的时间，可以将其写入配置文件，方便以后修改游戏逻辑
	schedule(schedule_selector(AI::genSmall), 1);//每1秒创建一个小飞机
	schedule(schedule_selector(AI::genMiddle), 5);//每5秒创建一个中飞机
	schedule(schedule_selector(AI::genBig), 30);//每30秒创建一个大飞机

	return true;
}
// 检测敌机是否已经飞出窗外
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
			e->shoot(_bullets);//没有飞出窗外就创建子弹并
		}
	}

	// 检测子弹是否飞出窗外
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

//创建 某种类型的 敌方飞机
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

//创建敌方飞机
void AI::genEnemy(Enemy::TYPE type)
{
	Enemy* e = Enemy::create(type);
	addChild(e);

	// 为敌机设置一个随机位置，随机值不是一个窗口宽度范围，而是窗口宽度减去飞机宽度范围
	float x = CCRANDOM_0_1() * (winSize.width - e->boundingBox().size.width) + e->boundingBox().size.width/2;
	float y = winSize.height;
	e->setPosition(ccp(x, y));

	// 创建一个敌方飞机，就加入到  AI 的飞机数组中
	_enemys->addObject(e);
}