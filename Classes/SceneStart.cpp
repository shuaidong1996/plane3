#include "SceneStart.h"
#include "SceneAbout.h"
#include "SceneMenu.h"
#include "QuitDialog.h"

bool SceneStart::init()
{
	CCLayer::init();

	// 设置一个背景图片
	Util::addBackground(IMAGE_background2, this);
	
	// 加三个菜单按钮
	createMenu();

	return true;
}
void SceneStart::Start(CCObject*)
{
	switchScene(SceneMenu);
}

void SceneStart::About(CCObject*)
{
	//switchScene(SceneAbout);
	CCDirector::sharedDirector()->replaceScene(Util::scene(SceneAbout::create()));
}
void SceneStart::createMenu()
{
	CCMenuItem* start = CCMenuItemImage::create(IMAGE_start_1, IMAGE_start_2);
	CCMenuItem* about = CCMenuItemImage::create(IMAGE_about_1, IMAGE_about_2);
	CCMenuItem* quit = CCMenuItemImage::create(IMAGE_quit_1, IMAGE_quit_2);
	CCMenu* menu = CCMenu::create(start, about, quit, NULL);
	addChild(menu);

	// 自定义空格的对其
	menu->alignItemsVerticallyWithPadding(50);

	//动起来
	CCArray* allItems = menu->getChildren();
	for (int i = 0; i < allItems->count(); i++)
	{
		CCMenuItem* item = (CCMenuItem*)allItems->objectAtIndex(i);
		CCPoint dest = item->getPosition();
		item->setPosition(ccp(dest.x - winSize.width, dest.y));

		CCDelayTime* delay = CCDelayTime::create(i);//延迟出来

		CCMoveTo* move = CCMoveTo::create(1, dest);
		//让菜单有弹动的效果
		CCEaseElasticOut* ease = CCEaseElasticOut::create(move);
		CCSequence* seq = CCSequence::create(delay, ease, NULL);

		item->runAction(seq);
	}

	// 三个按钮增加回调函数
	start->setTarget(this, menu_selector(SceneStart::Start));
	about->setTarget(this, menu_selector(SceneStart::About));
	quit->setTarget(this, menu_selector(SceneStart::Quit));
}

void SceneStart::Quit(CCObject*)
{
	addChild(QuitDialog::create(true));
}
