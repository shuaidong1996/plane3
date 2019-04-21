#ifndef __SceneGame_H__
#define __SceneGame_H__

#include "Common.h"
#include "Hero.h"
#include "AI.h"

class SceneGame : public CCLayer
{
	const char* _name;
	CCEditBox* _box;
public:
	static SceneGame* create(int planeID)
	{
		SceneGame* game = new SceneGame();
		game->init(planeID);
		game->autorelease();
		return game;
	}

	bool init(int planeID);

	void Back(CCObject*);
	void addHeroPlane(int id);
	void createEnemyAI();
	void addLabels();
	void inputName();
	void checkName(float);

	Hero* _hero;
	AI* _ai;

	CCLabelAtlas* _score;
	CCLabelAtlas* _hp;

	bool ccTouchBegan(CCTouch* t, CCEvent*)
	{
		// 点中飞机才能移动
		//return _hero->boundingBox().containsPoint(t->getLocation());
		return true;
	}
	void ccTouchMoved(CCTouch* t, CCEvent*);

	void update(float dt);
	void EnemyImpactCheck();
	void EnemyBulletImpactCheck();
	void gameOver();
};

#endif