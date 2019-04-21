#ifndef __BACKMUSIC_H__
#define __BACKMUSIC_H__
#include "Common.h"

class BackMusic:CCLayer
{
public:
	static CCScene* scene();
	CREATE_FUNC(BackMusic);
	bool init();

	static void backgroundMusic();
	static void enemyDownMusic();
};

#endif