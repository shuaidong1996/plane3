#include "ScrollBackground.h"


bool ScrollBackground::init()
{
//	CCLayer::init();

	//����һ�����������飬�����뵽����
	CCSprite* bg = Util::addBackground(IMAGE_background, this);

	// �ñ���ͼƬ�ʹ����±߶���
	bg->setPositionY(bg->getPositionY() + winSize.height/2);

	CCMoveBy* move = CCMoveBy::create(8, ccp(0, -winSize.height));//�����ƶ�  ����ͼ
	CCPlace* place = CCPlace::create(bg->getPosition());//Ȼ��ָ���ԭλ��

	bg->runAction(
		CCRepeatForever::create(CCSequence::create(move, place, NULL))//ͼƬ������
		);


	return true;
}
