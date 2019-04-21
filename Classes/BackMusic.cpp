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

	// Ԥ����
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MP3_background);//���ص��ڴ���ȥ��������ִ��
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MP3_enemydown);//���ص��ڴ���ȥ��������ִ��

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
