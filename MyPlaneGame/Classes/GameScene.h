#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "Weapon.h"
#include "EnemyLayer.h"
#include "UfoLayer.h"
#include "ControlLayer.h"
#include "GameOverLayer.h"

class GameScene : public cocos2d::Scene
{
public:
	GameScene(void);
	~GameScene(void);

	CREATE_FUNC(GameScene);
	bool init();
	void update(float dt);
	void eliminateAllEnemy();
	void pause();
	void resume();
	//CC_SYNTHESIZE_READONLY(int,m_score,Score);
	void gameOver();
	void changeLevel(float factor);

private:
	//void preloadresource();//ʵ�������ɾ��	
	void checkHeroPlaneWithEnemyCollision();//���л���ɻ�����ײ
	void checkBulletWithEnemyCollision(); //����ӵ���л�����ײ
	void checkHeroPlaneWithUFOCollision();//���ufo�ͷɻ�����ײ
	
	int m_score;
    
	BackgroundLayer* backgroundLayer;
	Weapon* weapon;
	EnemyLayer* enemyLayer;
	UfoLayer* ufoLayer;
	ControlLayer* controlLayer;
};

