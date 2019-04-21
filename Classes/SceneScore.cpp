#include "SceneScore.h"
#include "SceneMenu.h"
#include <string>
#include <vector>
using namespace std;

bool SceneScore::init(int score, const char* name)
{
	CCLayer::init();

	//设置一个背景图片
	Util::addBackground(IMAGE_background, this);

	//增加一个返回按钮
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneScore::Back));

	//打印一条等待消息
	uploadwait();

	//把分数上传到服务器，并从服务器获得分数的前十名
	uploadScore(score, name);

	//创建15个CCLabelTTF
	CCLabelTTF* ttf = CCLabelTTF::create("Ranking List", "", 80);
	addChild(ttf);
	ttf->setPosition(ccp(winSize.width / 2, winSize.height - 50));
	for (int i = 0; i < 15; i++)
	{
		CCLabelTTF* ttf = CCLabelTTF::create("No People", "", 80);
		addChild(ttf);
		ttf->setTag(i + 1000);
		ttf->setPosition(ccp(winSize.width / 5, winSize.height - i * 120 - 150));//Dimensions 面积
		// label的锚点，除了影响setPosition，还指定了文字的对齐方式(默认居中，现在是左对齐)
		ttf->setAnchorPoint(ccp(0, 1));
	}

	return true;
}
void SceneScore::Back(CCObject*)
{
	switchScene(SceneMenu);
}
void SceneScore::uploadScore(int score, const char* name)
{
	char data[100];
	sprintf(data, "name=%s&score=%d", name, score);

	//二：post请求
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl("http://139.199.26.222:8080/plane_server_game/servlet/Server");//设置url
	//request->setUrl("http://localhost:8080/plane_server_game/servlet/Server");//设置url
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setRequestData(data, strlen(data));
	request->setResponseCallback(this, httpresponse_selector(SceneScore::Response));//设置请求回调函数
	//request->setTag("Post_My_Data");
	CCHttpClient::getInstance()->send(request);
	request->release();
}
void SceneScore::Response(CCHttpClient* client, CCHttpResponse* resp)
{
	// 错误处理
	if (!resp->isSucceed())
	{
		uploadFalse();
		CCLog("Response Error: %s", resp->getErrorBuffer());
		return;
	}

	// 正确的处理，先只是打印服务器返回的内容
	std::vector<char>* data = resp->getResponseData();
	std::string str;

	for (std::vector<char>::iterator it = data->begin(); it != data->end(); it++)
	{
		char ch = *it;
		str += ch;
	}
	//CCLog("resp: %s", str.c_str());


	char* name;
	char* score;
	char* p = new char[str.size() + 1];
	strcpy(p, str.c_str());
	strtok(p, "|");
	for (int i = 0; i<15; i++)
	{
		name = strtok(NULL, "|");
		if (name == NULL)
			break;
		score = strtok(NULL, "|");

		CCLabelTTF* ttf = (CCLabelTTF*)getChildByTag(1000 + i);
		char show[1024];
		sprintf(show, "%s:\t%s", name, score);
		ttf->setString(show);
	}

	waitSprite->setVisible(false);

	delete p;
}
void SceneScore::uploadwait()
{
	CCSprite* s = CCSprite::create(IMAGE_shangchuan);
	addChild(s);
	s->setScale(1.5);
	s->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	waitSprite = s;
}
void SceneScore::uploadFalse()
{
	CCSprite* s = CCSprite::create(IMAGE_lianjieshibai);
	addChild(s);
	s->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	waitSprite->setVisible(false);
}