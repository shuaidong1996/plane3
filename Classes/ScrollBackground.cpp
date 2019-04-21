#include "ScrollBackground.h"


bool ScrollBackground::init()
{
//	CCLayer::init();

	//创建一个背景，精灵，并加入到此类
	CCSprite* bg = Util::addBackground(IMAGE_background, this);

	// 让背景图片和窗口下边对其
	bg->setPositionY(bg->getPositionY() + winSize.height/2);

	CCMoveBy* move = CCMoveBy::create(8, ccp(0, -winSize.height));//向下移动  半张图
	CCPlace* place = CCPlace::create(bg->getPosition());//然后恢复到原位置

	bg->runAction(
		CCRepeatForever::create(CCSequence::create(move, place, NULL))//图片动起来
		);


	return true;
}
