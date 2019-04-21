#include "Hero.h"
#include "shootBullets.h"

bool Hero::init(int id)
{
	//��ȡxml  ����Ӣ�۷ɻ�����Ϣ
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(CFG_planeinfo);

	//��ȡս����
	const CCString* value = dict->valueForKey(Util::format(id + 1, "planedamageamount"));
	_damage = value->intValue();

	//��ȡ����ٶ�
	value = dict->valueForKey(Util::format(id + 1, "planeshootspeedrate"));
	_shootCD = value->intValue();

	//��ȡӢ�ۻ�Ѫ��
	value = dict->valueForKey(Util::format(id + 1, "plane", "_hp"));
	_hp = value->intValue();

	//��ȡ�ɻ�ͼƬ,ͼƬ����
	value = dict->valueForKey(Util::format(id + 1, "plane"));
	CCSprite::initWithFile(value->getCString());
	//CCSprite::initWithFile("Player5.png");  ��ʵ���ǳ�ʼ��һ��ͼƬ���ȵ���һ֡�ٴ�������

	_curCD = 0;
	_id = id;

	// ר�ŷ����ӵ��Ķ�ʱ��
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
//�ӵ���һ���ٶȣ�ֻ�дﵽһ��ֵ���ܷ���
bool Hero::canFire()
{
	// �ӵ��������
	if (_curCD++ != _shootCD)
		return false;
	_curCD = 0;
	return true;
}
//���ڻ����ӵ�
void Hero::checkBullets()
{
	for (int i = 0; i < _bullets->count(); i++)
	{
		CCSprite* bullet = (CCSprite*)_bullets->objectAtIndex(i);
		if (Util::isAllOutOfWindow(bullet))
		{
			_bullets->removeObjectAtIndex(i);//�� �ӵ��������Ƴ�
			bullet->removeFromParent();//������ӵ��Ӹ��ڵ����Ƴ�
		}
	}
}