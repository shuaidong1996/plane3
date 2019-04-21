#include "SceneAbout.h"
#include "SceneStart.h"

bool SceneAbout::init()
{
	CCLayer::init();

	// 设置一个背景图片
	Util::addBackground(IMAGE_background, this);

	//增加一个返回按钮在右下角
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneAbout::Back));

	//添加About信息
	setInfo();

	return true;
}
void SceneAbout::Back(CCObject*)
{
	switchScene(SceneStart);
}
void SceneAbout::setInfo()
{
	//获取xml中的文件 createWithContentsOfFile
	CCDictionary* dict = CCDictionary::createWithContentsOfFile(CFG_about);
	CCPoint margin(10, 50);
	float space = 120;
	for (int i = 0; i < 5; ++i)
	{
		//通过键值，获取内容  
		const CCString* value = dict->valueForKey(Util::format(i + 1, "people"));
		
		//把获取到的字符串打印出来
		CCLabelTTF* label = CCLabelTTF::create(value->getCString(), "Arial", 80);
		addChild(label);

		// label的锚点，除了影响setPosition，还指定了文字的对齐方式(默认居中，现在是左对齐)
		label->setAnchorPoint(ccp(0, 1));
		label->setPosition(ccp(0 + margin.x, winSize.height - i*space - margin.y));

		label->setColor(ccc3(0, 0, 255));
	}
}

