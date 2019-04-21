#include "SceneGame.h"
#include "ScrollBackground.h"
#include "SceneMenu.h"
#include "SceneScore.h"
#include "QuitDialog.h"
#include "BackMusic.h"

bool SceneGame::init(int planeID)
{
	//	CCLayer::init();

	// 滚动背景
	ScrollBackground* bg = ScrollBackground::create();
	addChild(bg);

	// 右下角的返回按钮
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneGame::Back));

	// 创建英雄飞机
	addHeroPlane(planeID);

	// 使能touch
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	// 创建敌机AI
	createEnemyAI();

	// 碰撞检测
	scheduleUpdate();

	// 增加Label显示信息
	addLabels();

	return true;
}

void SceneGame::addLabels()
{
	_hp = CCLabelAtlas::create(Util::format(_hero->_hp), IMAGE_FONT_labelatlasimg, 24, 32, '0');
	_score = CCLabelAtlas::create("0", IMAGE_FONT_labelatlasimg, 24, 32, '0');

	addChild(_hp);
	addChild(_score);

	_hp->setScale(2);
	_score->setScale(2);

	_hp->setAnchorPoint(ccp(1, 1));
	_hp->setPosition(ccp(winSize.width, winSize.height - 30));

	_score->setAnchorPoint(ccp(0, 1));
	_score->setPosition(ccp(0, winSize.height -30));
}

void SceneGame::update(float)
{
	// 碰撞检测
	EnemyImpactCheck();
	EnemyBulletImpactCheck();
}
// 敌机 的 碰撞检测
void SceneGame::EnemyImpactCheck()
{
	int count = _ai->_enemys->count();
	for (int i = count - 1; i >= 0; --i)
	{
		Enemy* e = (Enemy*)_ai->_enemys->objectAtIndex(i);
		// 敌机 和 英雄战机 是否有交集
		if (e->boundingBox().intersectsRect(_hero->boundingBox()))
		{
			// 英雄战机少血
			_hero->_hp -= e->_hp;

			//如果英雄死去
			if (_hero->_hp <= 0)
			{
				gameOver();
				unscheduleUpdate();
				return;
			}

			// 注意避免显示负数的_hp
			Util::modifyLabel(_hp, -e->_hp);// 现在的hp  -  敌机的hp

			// 敌机从数组里删除，从数组删除意味着这个敌机不再参与碰撞检测 // 也不再发射子弹
			_ai->_enemys->removeObjectAtIndex(i);

			// 敌机死亡的动画，以及敌机从渲染树中删除
			e->killed();

			//增加分数
			Util::modifyLabel(_score, e->_score);

			continue;
		}

		// 敌机 和 我方子弹 做碰撞检测
		int bulletCount = _hero->_bullets->count();
		for (int j = bulletCount - 1; j >= 0; --j)
		{
			CCSprite* sprite = (CCSprite*)_hero->_bullets->objectAtIndex(j);
			if (sprite->boundingBox().intersectsRect(e->boundingBox()))
			{
				// 敌机的血要减少
				e->_hp -= _hero->_damage;

				// 子弹要消失
				_hero->_bullets->removeObject(sprite);//从数组中移除
				sprite->removeFromParent();//从父节点中移除

				// 判断敌机是否已经死亡
				if (e->_hp <= 0)
				{
					_ai->_enemys->removeObjectAtIndex(i);// 敌机从数组里删除，从数组删除意味着这个敌机不再参与碰撞检测
					Util::modifyLabel(_score, e->_score);//增加分数
					e->killed();
					break;
				}
			}
		}
	}
}
// 敌机子弹的碰撞检测
void SceneGame::EnemyBulletImpactCheck()
{
	int count = _ai->_bullets->count();
	//敌机子弹 和 英雄战机  碰撞检测
	for (int i = count - 1; i >= 0; --i)
	{
		Bullet* eb = (Bullet*)_ai->_bullets->objectAtIndex(i);
		if (eb->boundingBox().intersectsRect(_hero->boundingBox()))
		{
			//减血
			_hero->_hp -= eb->_damage;

			//死
			if (_hero->_hp <= 0)
			{
				gameOver();
				unscheduleUpdate();
				return;
			}

			//标记 血 下降
			Util::modifyLabel(_hp, -eb->_damage);

			//地方子弹 kill
			_ai->_bullets->removeObject(eb);
			eb->removeFromParent();
			continue;  // 注意检测完成就不需要执行后续的代码了
		}

		// 敌机子弹 和 我方子弹  做碰撞检测
		//int bulletCount = _hero->_bullets->count();
		//for (int j = bulletCount - 1; j >= 0; --j)
		//{
		//	CCSprite* sprite = (CCSprite*)_hero->_bullets->objectAtIndex(j);
		//	CCRect rc1 = sprite->boundingBox();
		//	CCLog("......... %d", _ai->_bullets->count());
		//	CCRect rc2 = eb->boundingBox();
		//	if (rc1.intersectsRect(rc2))
		//	{
		//		// 敌机子弹消失
		//		_ai->_bullets->removeObject(eb);
		//		eb->removeFromParent();

		//		// 我方子弹要消失
		//		_hero->_bullets->removeObject(sprite);
		//		sprite->removeFromParent();

		//		// 当一个我军子弹和敌军子弹碰撞检测之后，这个敌军子弹就不需要和另外的我军子弹进行碰撞检测
		//		break;
		//	}
		//}
	}
}
void SceneGame::gameOver()
{
	_hero->removeFromParent();
	inputName();
	schedule(schedule_selector(SceneGame::checkName));
}
void SceneGame::inputName()
{
	CCEditBox* box = CCEditBox::create(CCSize(1050, 120), CCScale9Sprite::create(IMAGE_editBox));
	addChild(box);
	box->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	//增加提示
	box->setPlaceHolder("Please leave your BigName");
	//设置提示字体
	box->setFont("Arial", 82);
	//设置输入的字体颜色
	box->setFontColor(ccc3(255, 0, 0));
	//设置可以输入的长度
	box->setMaxLength(8);
	//设置输入的形式  密码形式等等
	//box->setInputFlag(kEditBoxInputFlagInitialCapsAllCharacters);//好像除了密码形式，其他形式都不管用
	//设置键盘弹出为数字键盘或其他
	//box->setInputMode(kEditBoxInputModePhoneNumber);
	_box = box;
	setTouchEnabled(false);
}
void SceneGame::checkName(float)
{
	_name = _box->getText();
	if (strcmp(_name,""))
	{
		switchScene(SceneScore, atoi(_score->getString()),_name);
	}
}

void SceneGame::createEnemyAI()
{
	_ai = AI::create();
	addChild(_ai);
}

void SceneGame::addHeroPlane(int id)
{
	_hero = Hero::create(id);
	addChild(_hero);
	_hero->setPosition(ccp(winSize.width / 2, _hero->getContentSize().height));
}

void SceneGame::Back(CCObject*)
{
	addChild(QuitDialog::create(false));//这里注意，，必须加入渲染树中，不然不能调用onEnter
}

void SceneGame::ccTouchMoved(CCTouch* t, CCEvent*)
{
	if (Util::isPartOutOfWindow(_hero, t->getDelta()))
		return;

	Util::moveNode(_hero, t->getDelta());
	//_hero->setPosition(_hero->getPosition() + t->getDelta());
}