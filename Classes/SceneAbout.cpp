#include "SceneAbout.h"
#include "SceneStart.h"

bool SceneAbout::init()
{
	CCLayer::init();

	// ����һ������ͼƬ
	Util::addBackground(IMAGE_background, this);

	//����һ�����ذ�ť�����½�
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneAbout::Back));

	//���About��Ϣ
	setInfo();

	return true;
}
void SceneAbout::Back(CCObject*)
{
	switchScene(SceneStart);
}
void SceneAbout::setInfo()
{
	//��ȡxml�е��ļ� createWithContentsOfFile
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(CFG_about);
	CCPoint margin(10, 50);
	float space = 120;
	for (int i = 0; i < 5; ++i)
	{
		//ͨ����ֵ����ȡ����  
		const CCString* value = dict->valueForKey(Util::format(i + 1, "people"));
		
		//�ѻ�ȡ�����ַ�����ӡ����
		CCLabelTTF* label = CCLabelTTF::create(value->getCString(), "Arial", 80);
		addChild(label);

		// label��ê�㣬����Ӱ��setPosition����ָ�������ֵĶ��뷽ʽ(Ĭ�Ͼ��У������������)
		label->setAnchorPoint(ccp(0, 1));
		label->setPosition(ccp(0 + margin.x, winSize.height - i*space - margin.y));

		label->setColor(ccc3(0, 0, 255));
	}
}

