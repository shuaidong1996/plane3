#include "SceneScore.h"
#include "SceneMenu.h"
#include <string>
#include <vector>
using namespace std;

bool SceneScore::init(int score, const char* name)
{
	CCLayer::init();

	//����һ������ͼƬ
	Util::addBackground(IMAGE_background, this);

	//����һ�����ذ�ť
	CCMenuItem* item = Util::addMenuItemImageRB(IMAGE_btn_back_normal, IMAGE_btn_back_press, this);
	item->setTarget(this, menu_selector(SceneScore::Back));

	//��ӡһ���ȴ���Ϣ
	uploadwait();

	//�ѷ����ϴ��������������ӷ�������÷�����ǰʮ��
	uploadScore(score, name);

	//����15��CCLabelTTF
	CCLabelTTF* ttf = CCLabelTTF::create("Ranking List", "", 80);
	addChild(ttf);
	ttf->setPosition(ccp(winSize.width / 2, winSize.height - 50));
	for (int i = 0; i < 15; i++)
	{
		CCLabelTTF* ttf = CCLabelTTF::create("No People", "", 80);
		addChild(ttf);
		ttf->setTag(i + 1000);
		ttf->setPosition(ccp(winSize.width / 5, winSize.height - i * 120 - 150));//Dimensions ���
		// label��ê�㣬����Ӱ��setPosition����ָ�������ֵĶ��뷽ʽ(Ĭ�Ͼ��У������������)
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

	//����post����
	CCHttpRequest* request = new CCHttpRequest();
	request->setUrl("http://139.199.26.222:8080/plane_server_game/servlet/Server");//����url
	//request->setUrl("http://localhost:8080/plane_server_game/servlet/Server");//����url
	request->setRequestType(CCHttpRequest::kHttpPost);
	request->setRequestData(data, strlen(data));
	request->setResponseCallback(this, httpresponse_selector(SceneScore::Response));//��������ص�����
	//request->setTag("Post_My_Data");
	CCHttpClient::getInstance()->send(request);
	request->release();
}
void SceneScore::Response(CCHttpClient* client, CCHttpResponse* resp)
{
	// ������
	if (!resp->isSucceed())
	{
		uploadFalse();
		CCLog("Response Error: %s", resp->getErrorBuffer());
		return;
	}

	// ��ȷ�Ĵ�����ֻ�Ǵ�ӡ���������ص�����
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