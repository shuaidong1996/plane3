#ifndef __SceneScore_H__
#define __SceneScore_H__

#include "Common.h"

class SceneScore : public CCLayer
{
	CCSprite* waitSprite;
public:
	static SceneScore* create(int score,const char* name)
	{
		SceneScore* s = new SceneScore();
		s->init(score,name);
		s->autorelease();
		return s;
	}
	bool init(int score,const char* name);

	void Back(CCObject*);

	void uploadScore(int score, const char* username);//�ϴ�����
	void Response(CCHttpClient* client, CCHttpResponse* resp);//��������Ӧ����

	void uploadwait();
	void uploadFalse();
};

#endif
