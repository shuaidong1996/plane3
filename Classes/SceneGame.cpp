#include "SceneGame.h"
#include "ScrollBackground.h"
#include "SceneMenu.h"
#include "SceneScore.h"
#include "QuitDialog.h"
#include "BackMusic.h"

bool SceneGame::init(int planeID)
{
	//	CCLayer::init();

	// ��������
	ScrollBackground* bg = ScrollBackground::create();
	addChild(bg);

	// ���½ǵķ��ذ�ť
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneGame::Back));

	// ����Ӣ�۷ɻ�
	addHeroPlane(planeID);

	// ʹ��touch
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	// �����л�AI
	createEnemyAI();

	// ��ײ���
	scheduleUpdate();

	// ����Label��ʾ��Ϣ
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
	// ��ײ���
	EnemyImpactCheck();
	EnemyBulletImpactCheck();
}
// �л� �� ��ײ���
void SceneGame::EnemyImpactCheck()
{
	int count = _ai->_enemys->count();
	for (int i = count - 1; i >= 0; --i)
	{
		Enemy* e = (Enemy*)_ai->_enemys->objectAtIndex(i);
		// �л� �� Ӣ��ս�� �Ƿ��н���
		if (e->boundingBox().intersectsRect(_hero->boundingBox()))
		{
			// Ӣ��ս����Ѫ
			_hero->_hp -= e->_hp;

			//���Ӣ����ȥ
			if (_hero->_hp <= 0)
			{
				gameOver();
				unscheduleUpdate();
				return;
			}

			// ע�������ʾ������_hp
			Util::modifyLabel(_hp, -e->_hp);// ���ڵ�hp  -  �л���hp

			// �л���������ɾ����������ɾ����ζ������л����ٲ�����ײ��� // Ҳ���ٷ����ӵ�
			_ai->_enemys->removeObjectAtIndex(i);

			// �л������Ķ������Լ��л�����Ⱦ����ɾ��
			e->killed();

			//���ӷ���
			Util::modifyLabel(_score, e->_score);

			continue;
		}

		// �л� �� �ҷ��ӵ� ����ײ���
		int bulletCount = _hero->_bullets->count();
		for (int j = bulletCount - 1; j >= 0; --j)
		{
			CCSprite* sprite = (CCSprite*)_hero->_bullets->objectAtIndex(j);
			if (sprite->boundingBox().intersectsRect(e->boundingBox()))
			{
				// �л���ѪҪ����
				e->_hp -= _hero->_damage;

				// �ӵ�Ҫ��ʧ
				_hero->_bullets->removeObject(sprite);//���������Ƴ�
				sprite->removeFromParent();//�Ӹ��ڵ����Ƴ�

				// �жϵл��Ƿ��Ѿ�����
				if (e->_hp <= 0)
				{
					_ai->_enemys->removeObjectAtIndex(i);// �л���������ɾ����������ɾ����ζ������л����ٲ�����ײ���
					Util::modifyLabel(_score, e->_score);//���ӷ���
					e->killed();
					break;
				}
			}
		}
	}
}
// �л��ӵ�����ײ���
void SceneGame::EnemyBulletImpactCheck()
{
	int count = _ai->_bullets->count();
	//�л��ӵ� �� Ӣ��ս��  ��ײ���
	for (int i = count - 1; i >= 0; --i)
	{
		Bullet* eb = (Bullet*)_ai->_bullets->objectAtIndex(i);
		if (eb->boundingBox().intersectsRect(_hero->boundingBox()))
		{
			//��Ѫ
			_hero->_hp -= eb->_damage;

			//��
			if (_hero->_hp <= 0)
			{
				gameOver();
				unscheduleUpdate();
				return;
			}

			//��� Ѫ �½�
			Util::modifyLabel(_hp, -eb->_damage);

			//�ط��ӵ� kill
			_ai->_bullets->removeObject(eb);
			eb->removeFromParent();
			continue;  // ע������ɾͲ���Ҫִ�к����Ĵ�����
		}

		// �л��ӵ� �� �ҷ��ӵ�  ����ײ���
		//int bulletCount = _hero->_bullets->count();
		//for (int j = bulletCount - 1; j >= 0; --j)
		//{
		//	CCSprite* sprite = (CCSprite*)_hero->_bullets->objectAtIndex(j);
		//	CCRect rc1 = sprite->boundingBox();
		//	CCLog("......... %d", _ai->_bullets->count());
		//	CCRect rc2 = eb->boundingBox();
		//	if (rc1.intersectsRect(rc2))
		//	{
		//		// �л��ӵ���ʧ
		//		_ai->_bullets->removeObject(eb);
		//		eb->removeFromParent();

		//		// �ҷ��ӵ�Ҫ��ʧ
		//		_hero->_bullets->removeObject(sprite);
		//		sprite->removeFromParent();

		//		// ��һ���Ҿ��ӵ��͵о��ӵ���ײ���֮������о��ӵ��Ͳ���Ҫ��������Ҿ��ӵ�������ײ���
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

	//������ʾ
	box->setPlaceHolder("Please leave your BigName");
	//������ʾ����
	box->setFont("Arial", 82);
	//���������������ɫ
	box->setFontColor(ccc3(255, 0, 0));
	//���ÿ�������ĳ���
	box->setMaxLength(8);
	//�����������ʽ  ������ʽ�ȵ�
	//box->setInputFlag(kEditBoxInputFlagInitialCapsAllCharacters);//�������������ʽ��������ʽ��������
	//���ü��̵���Ϊ���ּ��̻�����
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
	addChild(QuitDialog::create(false));//����ע�⣬�����������Ⱦ���У���Ȼ���ܵ���onEnter
}

void SceneGame::ccTouchMoved(CCTouch* t, CCEvent*)
{
	if (Util::isPartOutOfWindow(_hero, t->getDelta()))
		return;

	Util::moveNode(_hero, t->getDelta());
	//_hero->setPosition(_hero->getPosition() + t->getDelta());
}