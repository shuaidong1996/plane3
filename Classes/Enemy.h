

// Enemy是封装敌人飞机的类

#ifndef __Enemy_H__
#define __Enemy_H__

#include "Common.h"
#include "shootBullets.h"
#include "BackMusic.h"

class Enemy : public CCSprite//和Hero一样，是一个精灵类
{
public:
	enum TYPE{ SMALL, MIDDLE, BIG };

	int _hp;//血量
	TYPE _type;//飞机类型
	int _speed;//下落速度
	int _damage;//攻击力
	int _shootCD;//发子弹速度
	int _curCD;//当前CD
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

		// 设置小飞机256是让小飞机在5秒内从窗口上方落下  下面将每秒下降256距离  *5  就是屏幕高度了 1280
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

		// 运动敌机
		scheduleUpdate();

		return true;
	}
	
	//每秒下降  _speed 距离
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

	// 敌机发射子弹的接口
	void shoot(CCArray* bullets)
	{
		if (canFire())
			shootBullets::create(_damage, _type, this, true, bullets);
	}
	//控制子弹发射 
	bool canFire()
	{
		if (_hp <= 0 || _curCD++ != _shootCD)// 敌机死亡  或者 CD冷却时间没到  就不发射子弹
			return false;
		_curCD = 0;
		return true;
	}

	void killed()
	{
		//音效
		BackMusic::enemyDownMusic();

		// 执行爆炸动画，然后删除对象
		CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();//CCSpriteFrameCache创建缓存
		cache->addSpriteFramesWithFile(ANI_PLIST_PFBoom);//加载 plist File到缓存区

		CCArray* frames = CCArray::create();//创建 帧 数组
		for (int i = 0; i < 18; ++i)
		{
			//切割图片，，通过文件名切割（plist中有文件名）
			char* frameName = Util::format(i + 1, "Boom_", ".png");//获得文件名
			CCSpriteFrame* frame = cache->spriteFrameByName(frameName);//通过文件名 创建精灵帧
			frames->addObject(frame);//把精灵帧加入到  帧数组中
		}
		// Animation  生气，活泼; 动画片制作，动画片摄制; [影视] 动画片;
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(frames, .05f);//通过帧数组创建 CCAnimation
		//Animation 只是存放了动画需要的数据信息。而执行动画还是需要 Animate。
		CCAnimate* animate = CCAnimate::create(animation);
		//删除
		CCRemoveSelf* remove = CCRemoveSelf::create();

		this->runAction(CCSequence::create(animate, remove, NULL));
	}
};

#endif
