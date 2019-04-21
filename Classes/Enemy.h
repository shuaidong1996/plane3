

// Enemy�Ƿ�װ���˷ɻ�����

#ifndef __Enemy_H__
#define __Enemy_H__

#include "Common.h"
#include "shootBullets.h"
#include "BackMusic.h"

class Enemy : public CCSprite//��Heroһ������һ��������
{
public:
	enum TYPE{ SMALL, MIDDLE, BIG };

	int _hp;//Ѫ��
	TYPE _type;//�ɻ�����
	int _speed;//�����ٶ�
	int _damage;//������
	int _shootCD;//���ӵ��ٶ�
	int _curCD;//��ǰCD
	int _score;
	int rowCD;

	static Enemy* create(TYPE type)
	{
		Enemy* enemy = new Enemy;
		enemy->init(type);
		enemy->autorelease();
		return enemy;
	}

	bool init(TYPE type)
	{
		CCSprite::initWithFile(Util::format(type + 1, "Enemy", ".png"));

		_type = type;

		int hp[] = { 10, 30, 120 };
		_hp = hp[type];

		// ����С�ɻ�256����С�ɻ���5���ڴӴ����Ϸ�����  ���潫ÿ���½�256����  *5  ������Ļ�߶��� 1280
		int speed[] = { 256, 128, 50 };
		_speed = speed[type];

		int damage[] = { 20, 20, 20 };
		_damage = damage[type];

		_curCD = 0;
		int shootCD[] = { 60, 100, 30 };
		_shootCD = shootCD[type];

		int score[] = { 100, 500, 2000 };
		_score = score[type];

		rowCD = 0;

		// �˶��л�
		scheduleUpdate();

		return true;
	}
	
	//ÿ���½�  _speed ����
	void update(float dt)
	{
		setPositionY( getPositionY() - dt*_speed );
		if (_type != SMALL)
		{
			CCPoint delta;
			if (rowCD++ < 120)
				delta = ccp(dt*_speed, 0);
			else if (rowCD < 240)
				delta = ccp(-dt*_speed, 0);
			else
				rowCD = CCRANDOM_0_1()*300;

			if (!Util::isPartOutOfWindow(this, delta))
				setPosition(delta + getPosition());
		}
	}

	// �л������ӵ��Ľӿ�
	void shoot(CCArray* bullets)
	{
		if (canFire())
			shootBullets::create(_damage, _type, this, true, bullets);
	}
	//�����ӵ����� 
	bool canFire()
	{
		if (_hp <= 0 || _curCD++ != _shootCD)// �л�����  ���� CD��ȴʱ��û��  �Ͳ������ӵ�
			return false;
		_curCD = 0;
		return true;
	}

	void killed()
	{
		//��Ч
		BackMusic::enemyDownMusic();

		// ִ�б�ը������Ȼ��ɾ������
		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();//CCSpriteFrameCache��������
		cache->addSpriteFramesWithFile(ANI_PLIST_PFBoom);//���� plist File��������

		CCArray* frames = CCArray::create();//���� ֡ ����
		for (int i = 0; i < 18; ++i)
		{
			//�и�ͼƬ����ͨ���ļ����иplist�����ļ�����
			char* frameName = Util::format(i + 1, "Boom_", ".png");//����ļ���
			CCSpriteFrame* frame = cache->spriteFrameByName(frameName);//ͨ���ļ��� ��������֡
			frames->addObject(frame);//�Ѿ���֡���뵽  ֡������
		}
		// Animation  ����������; ����Ƭ����������Ƭ����; [Ӱ��] ����Ƭ;
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, .05f);//ͨ��֡���鴴�� CCAnimation
		//Animation ֻ�Ǵ���˶�����Ҫ��������Ϣ����ִ�ж���������Ҫ Animate��
		CCAnimate* animate = CCAnimate::create(animation);
		//ɾ��
		CCRemoveSelf* remove = CCRemoveSelf::create();

		this->runAction(CCSequence::create(animate, remove, NULL));
	}
};

#endif
