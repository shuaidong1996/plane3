#ifndef __QUITDIALOG_H__
#define __QUITDIALOG_H__
#include "Common.h"
#include "SceneMenu.h"

class QuitDialog :public CCLayer
{
	CCMenu* _menu;
	bool _menuClick;
	bool _isQuitGame;
public:
	static QuitDialog* create(bool isQuitGame)
	{
		QuitDialog* q = new QuitDialog;
		q->init(isQuitGame);
		q->autorelease();
		return q;
	}
	bool init(bool isQuitGame);

	void Yes(CCObject*);
	void No(CCObject*);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void onEnter()
	{
		CCLayer::onEnter();
		// ��ģ̬�Ի��򵯳�ʱ����ϷӦ����ͣ
		CCDirector::sharedDirector()->pause();
	}

	void onExit()
	{
		CCLayer::onExit();
		CCDirector::sharedDirector()->resume();
	}
};

#endif