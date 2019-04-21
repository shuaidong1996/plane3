#include "Hero.h"
#include "shootBullets.h"

bool Hero::init(int id)
{
	//获取xml  里面英雄飞机的信息
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(CFG_planeinfo);

	//获取战斗力
	const CCString* value = dict->valueForKey(Util::format(id + 1, "planedamageamount"));
	_damage = value->intValue();

	//获取射击速度
	value = dict->valueForKey(Util::format(id + 1, "planeshootspeedrate"));
	_shootCD = value->intValue();

	//获取英雄机血量
	value = dict->valueForKey(Util::format(id + 1, "plane", "_hp"));
	_hp = value->intValue();

	//获取飞机图片,图片纹理
	value = dict->valueForKey(Util::format(id + 1, "plane"));
	CCSprite::initWithFile(value->getCString());
	//CCSprite::initWithFile("Player5.png");  其实就是初始化一张图片，等到下一帧再创建出来

	_curCD = 0;
	_id = id;

	// 专门发射子弹的定时器
	scheduleUpdate();

	return true;
}

void Hero::update(float)
{
	if (canFire())
	{
		shootBullets::create(_damage, _id, this, false, _bullets);
	}

	checkBullets();
}
//子弹有一个速度，只有达到一定值才能发射
bool Hero::canFire()
{
	// 子弹发射控制
	if (_curCD++ != _shootCD)
		return false;
	_curCD = 0;
	return true;
}
//用于回收子弹
void Hero::checkBullets()
{
	for (int i = 0; i < _bullets->count(); i++)
	{
		CCSprite* bullet = (CCSprite*)_bullets->objectAtIndex(i);
		if (Util::isAllOutOfWindow(bullet))
		{
			_bullets->removeObjectAtIndex(i);//从 子弹数组中移除
			bullet->removeFromParent();//把这颗子弹从父节点中移除
		}
	}
}