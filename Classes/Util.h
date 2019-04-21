//可变参数宏(variadic macros)传递可变参数表
/*
C99编译器标准终于改变了这种局面，它允许你可以定义可变参数宏(variadic macros)，这样你就可以使用拥有可以变化的参数表的宏。可变参数宏就像下面这个样子：
#define debug(…) printf(__VA_ARGS__)*/
#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define winSize CCDirector::sharedDirector()->getWinSize()
#define switchScene(__layer_name__, ...) CCDirector::sharedDirector()->replaceScene(Util::scene(__layer_name__::create(__VA_ARGS__)))


class Util
{
public:
	static CCScene* scene(CCLayer* layer)
	{
		CCScene* scene = CCScene::create();
		scene->addChild(layer);
		return scene;
	}
	static CCSprite* addBackground(const char* picFile, CCNode* parent)
	{
		CCSprite* sprite = CCSprite::create(picFile);
		parent->addChild(sprite);
		sprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		return sprite;
	}
	static CCMenuItem* addMenuItemImageRB(const char* picFile1, const char* picFile2, CCNode* parent)
	{
		CCMenuItem* item = CCMenuItemImage::create(picFile1, picFile2);
		CCMenu* menu = CCMenu::createWithItem(item);
		parent->addChild(menu);
		moveMenuItemRB(item);
		return item;
	}
	static void moveMenuItemRB(CCMenuItem* node)
	{
		node->setPosition(ccp(winSize.width / 2 - node->getContentSize().width / 2, node->getContentSize().height / 2 - winSize.height / 2));
	}
	//把两个字符串和一个数字  合并
	static char* format(int value, const char* prefix = "", const char* suffix = "")
	{
		static char buf[1024];
		sprintf(buf, "%s%d%s", prefix, value, suffix);
		return buf;
	}
	//看一个动作，是点击，还是移动
	static bool isClick(CCTouch* t)
	{
		return t->getLocation().getDistanceSq(t->getStartLocation()) < 25;//判断触摸 现在的位置 和 点击的位置，之间距离的平方是否小于25
	}
	//根据位移，移动一个节点
	static void moveNode(CCNode* node, const CCPoint& delta)
	{
		node->setPosition(node->getPosition() + delta);
	}
	// 判断node经过移动delta的距离后，是不是跑到窗口外面去了
	static bool isPartOutOfWindow(CCNode* node, const CCPoint& delta = ccp(0, 0))
	{
		CCRect rcNode = node->boundingBox();
		CCPoint pt[4];
		//获取节点  矩形的四个角  的坐标
		pt[0] = ccp(rcNode.getMinX(), rcNode.getMinY());
		pt[1] = ccp(rcNode.getMinX(), rcNode.getMaxY());
		pt[2] = ccp(rcNode.getMaxX(), rcNode.getMaxY());
		pt[3] = ccp(rcNode.getMaxX(), rcNode.getMinY());

		//获取窗口这个矩形
		CCRect rcWin(0, 0, winSize.width, winSize.height);

		//依次判断 移动后 矩形的四个角 是否在窗口内
		for (int i = 0; i < 4; i++)
		{
			if (!rcWin.containsPoint(pt[i] + delta))
				return true;
		}
		return false;
	}
	static bool isAllOutOfWindow(CCNode* node, const CCPoint& delta = ccp(0, 0))
	{
		CCRect rcWin(0, 0, winSize.width, winSize.height);
		//移动子弹位置（），我认为没有必要，就算这下一帧跑到外面去也无所谓，反正看不见，下次再回收也一样
		//CCRect rcNode = node->boundingBox();
		//rcNode.origin = rcNode.origin + delta;
		if (rcWin.intersectsRect(node->boundingBox()))//判断两个矩形有没有交集
		{
			return false;
		}
		return true;
	}
	//改变Label的值
	static void modifyLabel(CCLabelAtlas* label, int change)
	{
		const char* sValue = label->getString();//获取现在的Label值
		int value = atoi(sValue);//把字符串  转为 整形
		value += change;//改变整形值
		label->setString(format(value));//改变Label值
	}
};

#endif