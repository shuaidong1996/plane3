#include "shootBullets.h"
#include "Bullet.h"

shootBullets* shootBullets::create(int damage, int id, CCSprite* s, bool isEnermy, CCArray* bullets)
{
	shootBullets* b = new shootBullets;
	b->init(damage, id, s, isEnermy,bullets);
	b->autorelease();
	return b;
}
bool shootBullets::init(int damage, int id, CCSprite* s, bool isEnermy, CCArray* bullets)
{
	_isEnermy = 1;//默认不是敌机
	if (isEnermy)
		_isEnermy = -1;

	_plane = s;
	_bullets = bullets;
	_damage = damage;//赋予攻击力
	_id = id;
	selectFire(id);//选择子弹种类
	return true;
}
//不同飞机，发不同的子弹
void shootBullets::selectFire(int id)
{
	switch (id)
	{
	case 0:
		fire0();
		break;
	case 1:
		fire1();
		break;
	case 2:
		fire2();
		break;
	case 3:
		fire3();
		break;
	case 4:
		fire4();
		break;
	}
}

void shootBullets::fire0()
{
	fire();
}
void shootBullets::fire1()
{
	fire();
	fire(ccp(_plane->getContentSize().width / 4, -_isEnermy *_plane->getContentSize().height / 3));
	fire(ccp(-_plane->getContentSize().width / 4, -_isEnermy *_plane->getContentSize().height / 3));
}
void shootBullets::fire2()
{
	fire();
	if (_isEnermy == -1)
	{
		fire(30, ccp(-30, 10));
		fire(-30, ccp(30, 10));
		fire(40, ccp(-50, 0));
		fire(-40, ccp(50, 0));
		return;
	}

	fire(30, ccp(_plane->getContentSize().width / 6, -_plane->getContentSize().height / 3));
	fire(-30, ccp(-_plane->getContentSize().width / 6, -_plane->getContentSize().height / 3));
}
void shootBullets::fire3()
{
	CCPoint ptDelta = ccp(0, -_plane->getContentSize().height / 2);

	fire();
	fire(90, ptDelta + ccp(_plane->getContentSize().width / 2, 0));
	fire(180, ptDelta + ptDelta);
	fire(270, ptDelta + ccp(-_plane->getContentSize().width / 2, 0));
}

void shootBullets::fire4()
{
	CCPoint ptDelta = ccp(0, -_plane->getContentSize().height / 2);
	float off = _plane->getContentSize().height / 4;

	fire();
	fire(180, ptDelta * 2);
	fire(45, ptDelta + ccp(off, off));
	fire(135, ptDelta + ccp(off, -off));
	fire(225, ptDelta + ccp(-off, -off));
	fire(315, ptDelta + ccp(-off, off));
}
//下面函数可以用一个函数，但是为了节约内存，我用重载的形式
void shootBullets::fire()
{
	// 子弹初始位置
	CCSprite* bullet = gainBullet();
	bullet->setPosition(_plane->getPosition() + ccp(0, _isEnermy * _plane->getContentSize().height / 2));
	setPosition(_plane->getPosition() + ccp(0, _isEnermy * _plane->getContentSize().height / 2));
		//让子弹动起来
	bullet->runAction(CCMoveBy::create(4, ccp(0, _isEnermy * 2500)));
}
void shootBullets::fire(const CCPoint& delta)
{
	// 子弹初始位置
	CCSprite* bullet = gainBullet();
	bullet->setPosition(_plane->getPosition() + ccp(0, _isEnermy * _plane->getContentSize().height / 2) + delta);

	//让子弹动起来
	bullet->runAction(CCMoveBy::create(4, ccp(0, _isEnermy * 2500)));
}
//设置子弹发射角度，和偏移位置
void shootBullets::fire(int angle, const CCPoint& delta)
{
	float diagonal_line = sqrt(winSize.height * winSize.height + winSize.width * winSize.width);//对角线长度
	float offX = sinf(angle*M_PI / 180)*diagonal_line * _isEnermy;
	float offY = cosf(angle*M_PI / 180)*diagonal_line * _isEnermy;

	// 子弹初始位置
	CCSprite* bullet = gainBullet();
	bullet->setPosition(_plane->getPosition() + ccp(0, _isEnermy * _plane->getContentSize().height / 2) + delta);

	//让子弹动起来
	bullet->runAction(CCMoveBy::create(4, ccp(offX, offY)));
	bullet->setRotation(angle);//子弹也有方向，旋转子弹
}
//创建子弹
CCSprite* shootBullets::gainBullet()
{
	Bullet* bullet;
	if (_isEnermy == 1)
		bullet = Bullet::create(false, _damage, _id);
	else
		bullet = Bullet::create(true, _damage, _id);

	_plane->getParent()->addChild(bullet);//把子弹加入到 父节点中，也就是SceneGame场景中(子弹，不算做飞机的子类)
	_bullets->addObject(bullet);

	return bullet;
}


