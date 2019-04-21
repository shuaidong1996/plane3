#include "BackMusic.h"
#include "SimpleAudioEngine.h"

CCScene* BackMusic::scene()
{
	CCScene* scene = CCScene::create();
	BackMusic* layer = BackMusic::create();
	scene->addChild(layer);
	return scene;
}
bool BackMusic::init()
{
	CCLayer::init();

	// 预加载
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MP3_background);//加载到内存中去，但不会执行
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MP3_enemydown);//加载到内存中去，但不会执行

	return true;
}
void BackMusic::backgroundMusic()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MP3_background,true);
}
void BackMusic::enemyDownMusic()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(MP3_enemydown);
	
}
