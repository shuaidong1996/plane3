//�ɱ������(variadic macros)���ݿɱ������
/*
C99��������׼���ڸı������־��棬����������Զ���ɱ������(variadic macros)��������Ϳ���ʹ��ӵ�п��Ա仯�Ĳ�����ĺꡣ�ɱ�������������������ӣ�
#define debug(��) printf(__VA_ARGS__)*/
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
	//�������ַ�����һ������  �ϲ�
	static char* format(int value, const char* prefix = "", const char* suffix = "")
	{
		static char buf[1024];
		sprintf(buf, "%s%d%s", prefix, value, suffix);
		return buf;
	}
	//��һ���������ǵ���������ƶ�
	static bool isClick(CCTouch* t)
	{
		return t->getLocation().getDistanceSq(t->getStartLocation()) < 25;//�жϴ��� ���ڵ�λ�� �� �����λ�ã�֮������ƽ���Ƿ�С��25
	}
	//����λ�ƣ��ƶ�һ���ڵ�
	static void moveNode(CCNode* node, const CCPoint& delta)
	{
		node->setPosition(node->getPosition() + delta);
	}
	// �ж�node�����ƶ�delta�ľ�����ǲ����ܵ���������ȥ��
	static bool isPartOutOfWindow(CCNode* node, const CCPoint& delta = ccp(0, 0))
	{
		CCRect rcNode = node->boundingBox();
		CCPoint pt[4];
		//��ȡ�ڵ�  ���ε��ĸ���  ������
		pt[0] = ccp(rcNode.getMinX(), rcNode.getMinY());
		pt[1] = ccp(rcNode.getMinX(), rcNode.getMaxY());
		pt[2] = ccp(rcNode.getMaxX(), rcNode.getMaxY());
		pt[3] = ccp(rcNode.getMaxX(), rcNode.getMinY());

		//��ȡ�����������
		CCRect rcWin(0, 0, winSize.width, winSize.height);

		//�����ж� �ƶ��� ���ε��ĸ��� �Ƿ��ڴ�����
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
		//�ƶ��ӵ�λ�ã���������Ϊû�б�Ҫ����������һ֡�ܵ�����ȥҲ����ν���������������´��ٻ���Ҳһ��
		//CCRect rcNode = node->boundingBox();
		//rcNode.origin = rcNode.origin + delta;
		if (rcWin.intersectsRect(node->boundingBox()))//�ж�����������û�н���
		{
			return false;
		}
		return true;
	}
	//�ı�Label��ֵ
	static void modifyLabel(CCLabelAtlas* label, int change)
	{
		const char* sValue = label->getString();//��ȡ���ڵ�Labelֵ
		int value = atoi(sValue);//���ַ���  תΪ ����
		value += change;//�ı�����ֵ
		label->setString(format(value));//�ı�Labelֵ
	}
};

#endif