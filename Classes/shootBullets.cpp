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
	_isEnermy = 1;//Ĭ�ϲ��ǵл�
	if (isEnermy)
		_isEnermy = -1;

	_plane = s;
	_bullets = bullets;
	_damage = damage;//���蹥����
	_id = id;
	selectFire(id);//ѡ���ӵ�����
	return true;
}
//��ͬ�ɻ�������ͬ���ӵ�
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
//���溯��������һ������������Ϊ�˽�Լ�ڴ棬�������ص���ʽ
void shootBullets::fire()
{
	// �ӵ���ʼλ��
	CCSprite* bullet = gainBullet();
	bullet->setPosition(_plane->getPosition() + ccp(0, _isEnermy * _plane->getContentSize().height / 2));
	setPosition(_plane->getPosition() + ccp(0, _isEnermy * _plane->getContentSize().height / 2));
		//���ӵ�������
	bullet->runAction(CCMoveBy::create(4, ccp(0, _isEnermy * 2500)));
}
void shootBullets::fire(const CCPoint& delta)
{
	// �ӵ���ʼλ��
	CCSprite* bullet = gainBullet();
	bullet->setPosition(_plane->getPosition() + ccp(0, _isEnermy * _plane->getContentSize().height / 2) + delta);

	//���ӵ�������
	bullet->runAction(CCMoveBy::create(4, ccp(0, _isEnermy * 2500)));
}
//�����ӵ�����Ƕȣ���ƫ��λ��
void shootBullets::fire(int angle, const CCPoint& delta)
{
	float diagonal_line = sqrt(winSize.height * winSize.height + winSize.width * winSize.width);//�Խ��߳���
	float offX = sinf(angle*M_PI / 180)*diagonal_line * _isEnermy;
	float offY = cosf(angle*M_PI / 180)*diagonal_line * _isEnermy;

	// �ӵ���ʼλ��
	CCSprite* bullet = gainBullet();
	bullet->setPosition(_plane->getPosition() + ccp(0, _isEnermy * _plane->getContentSize().height / 2) + delta);

	//���ӵ�������
	bullet->runAction(CCMoveBy::create(4, ccp(offX, offY)));
	bullet->setRotation(angle);//�ӵ�Ҳ�з�����ת�ӵ�
}
//�����ӵ�
CCSprite* shootBullets::gainBullet()
{
	Bullet* bullet;
	if (_isEnermy == 1)
		bullet = Bullet::create(false, _damage, _id);
	else
		bullet = Bullet::create(true, _damage, _id);

	_plane->getParent()->addChild(bullet);//���ӵ����뵽 ���ڵ��У�Ҳ����SceneGame������(�ӵ����������ɻ�������)
	_bullets->addObject(bullet);

	return bullet;
}


