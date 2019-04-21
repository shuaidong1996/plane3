#include "SceneMenu.h"
#include "SceneStart.h"
#include "ScrollBackground.h"
#include "SceneGame.h"

bool SceneMenu::init()
{
	CCLayer::init();

	//��������
	BackMusic::backgroundMusic();

	// ���ӹ�������
	ScrollBackground* bg = ScrollBackground::create();
	addChild(bg);

	// ���½ǵķ��ذ�ť
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneMenu::Back));

	//����һ�仰�����˸�����֪���м��ܷɻ�
	CCSprite* sprite = CCSprite::create(IMAGE_xuanfeiji);
	sprite->setPosition(ccp(winSize.width / 2, winSize.height - 200));
	addChild(sprite);

	// ����һ�������㣬ѡ��ɻ�
	initScrollMenu();
	
	return true;
}

void SceneMenu::initScrollMenu()
{
	CCNode* node = CCNode::create();
	_node = node;
	// ���ӹ�������
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();//����֡����
	cache->addSpriteFramesWithFile("chooselevel.plist");//ͨ��Plist�ļ�������ͼƬ��������

	for (int i = 0; i < 5; ++i)//һ��5��ͼƬ
	{
		//һ��һ��ͼƬ���и�
		CCSprite* sprite = CCSprite::createWithSpriteFrameName(
			Util::format(i + 1, "ChooseLevel", ".png")
			);
		node->addChild(sprite);
		sprite->setPosition(ccp(winSize.width / 2+i*winSize.width, winSize.height / 2));
		sprite->setTag(i);
	}

	// ���ù�����ͼ
	CCScrollView* view = CCScrollView::create(winSize, node);
	addChild(view);
	view->setDirection(kCCScrollViewDirectionHorizontal);//���ú������
	view->setContentSize(CCSize(winSize.width*5, winSize.height));
	
	// ȥ������
	view->setBounceable(false);

	// ���ô���
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
}

void SceneMenu::ccTouchEnded(CCTouch* t, CCEvent*)
{
	if (Util::isClick(t))
	{
		// ���
		CCPoint ptInNode = _node->convertTouchToNodeSpace(t);//�Ѵ�����ת��Ϊ  �ڵ�����
		for (int i = 0; i < 5; ++i)
		{
			CCNode* sprite = _node->getChildByTag(i);
			if (sprite->boundingBox().containsPoint(ptInNode))//��������ڵ����꣬���Ƿ������ɻ�ͼƬ
			{
				switchScene(SceneGame, i);
				break;
			}
		}
	}
	else
	{
		// ����������һ����ʱ�����ö�ʱ��������ȥ����ScrollView��λ��
		scheduleOnce(schedule_selector(SceneMenu::adjustScrollView), .1f);
	}
}

void SceneMenu::adjustScrollView(float)
{
	int curPos = _node->getPositionX();//��ȡ��ǰλ��
	int minOff = 9999;
	int i;
	for (i = 0; i < 5; ++i)
	{
		int adjustPos = -i*winSize.width;
		int offset = abs(curPos - adjustPos);

		// ͨ���㷨������ӽ��ĵ���λ��
		if (offset < minOff) minOff = offset;
		else break;
	}

	int adjustPos = -(i - 1)*winSize.width;

	CCAction* action = CCMoveTo::create(.1f, ccp(adjustPos, _node->getPositionY()));
	_node->stopAllActions();
	_node->runAction(action);
}

void SceneMenu::Back(CCObject*)
{
	switchScene(SceneStart);
}
