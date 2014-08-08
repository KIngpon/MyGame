#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

GameScene::GameScene(void)
{
	this->m_score = 0;
}


GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
   do
   {
	   CC_BREAK_IF(!Scene::init());

	   backgroundLayer = BackgroundLayer::create();
	   this->addChild(backgroundLayer);

	   weapon = Weapon::create();
	   this->addChild(weapon);

	   enemyLayer = EnemyLayer::create();
	   this->addChild(enemyLayer);

	   ufoLayer = UfoLayer::create();
	   this->addChild(ufoLayer);

	   controlLayer = ControlLayer::create();
	   this->addChild(controlLayer);

	   this->scheduleUpdate();

	   CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3", true);

	   return true;
   }while(0);
       return false;
}

/*void GameScene::preloadresource()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game.plist");

	//����ɻ�����
	Animation* heroAnimation = Animation::create();
	heroAnimation->setDelayPerUnit(0.2f);
	heroAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	heroAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
	AnimationCache::getInstance()->addAnimation(heroAnimation,"heroAnimation");

	//�л�3�ķ��ж���
	Animation* enemy3Animation = Animation::create();
	enemy3Animation->setDelayPerUnit(0.2f);
	enemy3Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
	enemy3Animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
	AnimationCache::getInstance()->addAnimation(enemy3Animation,"enemy3Animation");

	//Ӣ�۷ɻ��ı�ը����
	Animation* heroBlowupAnimation = Animation::create();
	heroBlowupAnimation->setDelayPerUnit(0.2f);
	heroBlowupAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png"));
	heroBlowupAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
	heroBlowupAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
	heroBlowupAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));
	AnimationCache::getInstance()->addAnimation(heroBlowupAnimation,"heroBlowupAnimation");
    
	//�л�1�ı�ը����
	Animation* enemy1DownAnimation = Animation::create();
	enemy1DownAnimation->setDelayPerUnit(0.05f);
	enemy1DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	enemy1DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	enemy1DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	enemy1DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));
	CCAnimationCache::getInstance()->addAnimation(enemy1DownAnimation, "enemy1DownAnimation");

	//�л�2�ı�ը����
	Animation* enemy2DownAnimation = Animation::create();
	enemy2DownAnimation->setDelayPerUnit(0.05f);
	enemy2DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
	enemy2DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
	enemy2DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
	enemy2DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));
	AnimationCache::getInstance()->addAnimation(enemy2DownAnimation, "enemy2DownAnimation"); 

	//�л�3�ı�ը����
	Animation* enemy3DownAnimation = Animation::create();
	enemy3DownAnimation->setDelayPerUnit(0.05f);
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png"));
	enemy3DownAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png"));
	AnimationCache::getInstance()->addAnimation(enemy3DownAnimation, "enemy3DownAnimation"); 

	//��ʼ�����涯��
	Animation* startAnimation = Animation::create();
	startAnimation->setDelayPerUnit(0.2);
	startAnimation->setLoops(2);
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));
	AnimationCache::sharedAnimationCache()->addAnimation(startAnimation, "startAnimation");
}*/

//ÿһ֡���һ����ײ
void GameScene::update(float dt)
{
   //����ÿһ֡�������һ�Σ��ڴ˴������ײ������
	checkHeroPlaneWithEnemyCollision();//���л���ɻ�����ײ
	checkBulletWithEnemyCollision(); //���л����ӵ�����ײ
	checkHeroPlaneWithUFOCollision(); //���ufo��ɻ�����ײ
}

//�����л����������ͷɻ�����Ƿ��غϣ�������Ӧ�Ĵ���
void GameScene::checkHeroPlaneWithEnemyCollision()
{
	Rect planeRect = weapon->getheroPlane()->getHero()->getBoundingBox();
	for(auto enemy : enemyLayer->getEnemy1Vector())
	{
		if(planeRect.intersectsRect(enemy->getBoundingBox()))
		{
			this->unscheduleUpdate();
			enemy->enemyBlowUp("enemy1DownAnimation");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy1_down.mp3");
			m_score += 2;
			controlLayer->updateScore(m_score);
			weapon->heroBlowUp();
		}
	}

	for(auto enemy : enemyLayer->getEnemy2Vector())
	{
		if(planeRect.intersectsRect(enemy->getBoundingBox()))
		{
			this->unscheduleUpdate();
			enemy->enemyBlowUp("enemy2DownAnimation");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy2_down.mp3");
			m_score += 5;
			controlLayer->updateScore(m_score);
			weapon->heroBlowUp();
		}
	}

	for(auto enemy : enemyLayer->getEnemy3Vector())
	{
		if(planeRect.intersectsRect(enemy->getBoundingBox()))
		{
			this->unscheduleUpdate();
			enemy->enemyBlowUp("enemy3DownAnimation");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy3_down.mp3");
			m_score += 10;
			controlLayer->updateScore(m_score);
		    weapon->heroBlowUp();
		}
	}
}

//�����л������������ӵ���������������������������غϣ��������ֵ���в���������Ҫ��ı�ը����
void GameScene::checkBulletWithEnemyCollision()
{
	for(auto bullet : weapon->getbulletVector())
	{
		auto pos = bullet->getPosition();

	   for(auto enemy : enemyLayer->getEnemy1Vector())
	     {
		    auto rect = enemy->getBoundingBox();
			if(rect.containsPoint(pos))
			{
				weapon->removeBullet(bullet);
				if(enemy->isDead())
				{
				   enemy->enemyBlowUp("enemy1DownAnimation");
				   m_score += 2;
				   controlLayer->updateScore(m_score);
				}
				break;
			}
	     }

	    for(auto enemy : enemyLayer->getEnemy2Vector())
	     {
		    auto rect = enemy->getBoundingBox();
			if(rect.containsPoint(pos))
			{
				weapon->removeBullet(bullet);
				if(enemy->isDead())
				{
				   enemy->enemyBlowUp("enemy2DownAnimation");
				   m_score += 5;
				   controlLayer->updateScore(m_score);
				}
				break;
			}
	     }
	
		for(auto enemy : enemyLayer->getEnemy3Vector())
	     {
		    auto rect = enemy->getBoundingBox();
			if(rect.containsPoint(pos))
			{
				weapon->removeBullet(bullet);
				if(enemy->isDead())
				{
				   enemy->enemyBlowUp("enemy3DownAnimation");
				   m_score += 10;
				   controlLayer->updateScore(m_score);
				}
				break;
			}
	     }
	}
}

//ufo��ɻ�����ײ��������bomb����ӻ���˫���ӵ����л�
void GameScene::checkHeroPlaneWithUFOCollision()
{
	 for(auto ufo : ufoLayer->getufoVector())
	 {
		 Rect planeRect = weapon->getheroPlane()->getHero()->getBoundingBox();

		 if(planeRect.intersectsRect(ufo->getBoundingBox()))
		 {
			 if(ufo->getTag() == 1)
			 {
				 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_double_laser.mp3");
				 weapon->changeBullet();
			 }
			 else
			 {
				 CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("get_bomb.mp3");
				 ufoLayer->addBombNum();
			 }
			 ufoLayer->collision(ufo);
			 //��Ӹı�Ĵ���
			 break;
		 }
	 }
}

//�������ел�
void GameScene::eliminateAllEnemy()
{
	    for(auto enemy : enemyLayer->getEnemy1Vector())
	     {
			 enemy->enemyBlowUp("enemy1DownAnimation");
			 m_score += 2;
			 controlLayer->updateScore(m_score);
	     }
		enemyLayer->getEnemy2Vector().clear();

	    for(auto enemy :enemyLayer->getEnemy2Vector())
	     {
	       enemy->enemyBlowUp("enemy2DownAnimation");
		   m_score += 5;
		   controlLayer->updateScore(m_score);
	     }	
		enemyLayer->getEnemy2Vector().clear();

		for(auto enemy : enemyLayer->getEnemy3Vector())
	     {
		   enemy->enemyBlowUp("enemy3DownAnimation");
		   m_score += 10;
		   controlLayer->updateScore(m_score);
	     }
		enemyLayer->getEnemy3Vector().clear();
}

//��Ϸ��ͣ
void GameScene::pause()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
	weapon->pauseTouch();
	Director::getInstance()->pause();
}

//��Ϸ�ָ�
void GameScene::resume()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
	weapon->resumeTouch();
	Director::getInstance()->resume();
}

//��Ϸ����
void GameScene::gameOver()
{
	/*this->unscheduleAllSelectors();
	enemyLayer->unscheduleAllSelectors();
	ufoLayer->unscheduleAllSelectors();*/
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	Scene* gameOveScene = TransitionCrossFade::create(1.0f, GameOverLayer::scene(m_score));
	Director::getInstance()->replaceScene(gameOveScene);
}

void GameScene::changeLevel(float factor)
{
	enemyLayer->setLevelFactor(factor);
}
