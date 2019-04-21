#include "SceneMenu.h"
#include "SceneStart.h"
#include "ScrollBackground.h"
#include "SceneGame.h"

bool SceneMenu::init()
{
	CCLayer::init();

	//背景音乐
	BackMusic::backgroundMusic();

	// 增加滚动背景
	ScrollBackground* bg = ScrollBackground::create();
	addChild(bg);

	// 右下角的返回按钮
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneMenu::Back));

	//增加一句话。别人根本不知道有几架飞机
	CCSprite* sprite = CCSprite::create(IMAGE_xuanfeiji);
	sprite->setPosition(ccp(winSize.width / 2, winSize.height - 200));
	addChild(sprite);

	// 增加一个滚动层，选择飞机
	initScrollMenu();
	
	return true;
}

void SceneMenu::initScrollMenu()
{
	CCNode* node = CCNode::create();
	_node = node;
	// 增加滚动内容
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();//创建帧缓存
	cache->addSpriteFramesWithFile("chooselevel.plist");//通过Plist文件，加载图片到缓存中

	for (int i = 0; i < 5; ++i)//一共5张图片
	{
		//一张一张图片的切割
		CCSprite* sprite = CCSprite::createWithSpriteFrameName(
			Util::format(i + 1, "ChooseLevel", ".png")
			);
		node->addChild(sprite);
		sprite->setPosition(ccp(winSize.width / 2+i*winSize.width, winSize.height / 2));
		sprite->setTag(i);
	}

	// 设置滚动视图
	CCScrollView* view = CCScrollView::create(winSize, node);
	addChild(view);
	view->setDirection(kCCScrollViewDirectionHorizontal);//设置横向滚动
	view->setContentSize(CCSize(winSize.width*5, winSize.height));
	
	// 去掉弹性
	view->setBounceable(false);

	// 设置触摸
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
}

void SceneMenu::ccTouchEnded(CCTouch* t, CCEvent*)
{
	if (Util::isClick(t))
	{
		// 点击
		CCPoint ptInNode = _node->convertTouchToNodeSpace(t);//把触摸点转换为  节点坐标
		for (int i = 0; i < 5; ++i)
		{
			CCNode* sprite = _node->getChildByTag(i);
			if (sprite->boundingBox().containsPoint(ptInNode))//看触摸点节点坐标，，是否点击到飞机图片
			{
				switchScene(SceneGame, i);
				break;
			}
		}
	}
	else
	{
		// 滑动：启动一个定时器，让定时器处理函数去矫正ScrollView的位置
		scheduleOnce(schedule_selector(SceneMenu::adjustScrollView), .1f);
	}
}

void SceneMenu::adjustScrollView(float)
{
	int curPos = _node->getPositionX();//获取当前位置
	int minOff = 9999;
	int i;
	for (i = 0; i < 5; ++i)
	{
		int adjustPos = -i*winSize.width;
		int offset = abs(curPos - adjustPos);

		// 通过算法查找最接近的调整位置
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
