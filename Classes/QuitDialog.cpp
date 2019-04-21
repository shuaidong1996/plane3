#include "QuitDialog.h"

bool QuitDialog::init(bool isQuitGame)
{
	CCLayer::init();

	_isQuitGame = isQuitGame;

	CCMenu* menu = CCMenu::create();
	addChild(menu);
	_menu = menu;

	CCMenuItem* itemYes = CCMenuItemImage::create(IMAGE_quit, IMAGE_quit);
	CCMenuItem* itemNo = CCMenuItemImage::create(IMAGE_continue, IMAGE_continue);

	menu->addChild(itemYes);
	menu->addChild(itemNo);

	itemYes->setPosition(ccp(-200, 0));
	itemNo->setPosition(ccp(200, 0));

	itemYes->setTarget(this, menu_selector(QuitDialog::Yes));
	itemNo->setTarget(this, menu_selector(QuitDialog::No));

	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);
	setTouchPriority(-130);

	return true;
}
void QuitDialog::Yes(CCObject*)
{
	if (_isQuitGame)
		exit(0);

	switchScene(SceneMenu);
}
void QuitDialog::No(CCObject*)
{
	removeFromParent();
}
bool QuitDialog::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	_menuClick = _menu->ccTouchBegan(pTouch, pEvent);//ֻ����_menu����˵��� �������_menu�еĶ����ͷ��� true
	return true;
}
void QuitDialog::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if (_menuClick)  _menu->ccTouchMoved(pTouch, pEvent);//ֻ�е���ˣ�������
}
void QuitDialog::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (_menuClick)  _menu->ccTouchEnded(pTouch, pEvent);
}
void QuitDialog::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	if (_menuClick)  _menu->ccTouchCancelled(pTouch, pEvent);
}