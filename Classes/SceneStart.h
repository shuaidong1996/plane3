#ifndef __SCENESTART_H__
#define __SCENESTART_H__

#include "Common.h"

class SceneStart:public CCLayer
{
public:
	CREATE_FUNC(SceneStart);
	bool init();

	void Start(CCObject* sender);
	void About(CCObject* sender);
	void Quit(CCObject* sender);
	void createMenu();
};

#endif