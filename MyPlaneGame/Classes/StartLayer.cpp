#include "StartLayer.h"
#include "GameScene.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

StartLayer::StartLayer(void)
{
}


StartLayer::~StartLayer(void)
{
}

Scene* StartLayer::scene()
{
   Scene* startScene = Scene::create();
   StartLayer* startLayer = StartLayer::create();
   startScene->addChild(startLayer);
   return startScene;
}

bool StartLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());

	   //Ԥ��������
	   preLoadResource();

	   //��Ӽ��ػ��汳��
	   Sprite* background = Sprite::createWithSpriteFrameName("background.png");
	   background->setAnchorPoint(Point::ZERO);
	   background->setPosition(Point::ZERO);
	   this->addChild(background);

	   auto winSize = Director::getInstance()->getWinSize();

	   //��Ӱ汾��Ϣ
	   auto copyRightSprite = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	   copyRightSprite->setPosition(winSize.width*0.5, winSize.height*0.6);
	   this->addChild(copyRightSprite);

	   //ִ�м��ض���
	   Sprite* start = Sprite::create();
	   auto animate = Animate::create(AnimationCache::getInstance()->getAnimation("startAnimation"));
	   auto callback = CallFunc::create(CC_CALLBACK_0(StartLayer::transition, this));
	   start->setPosition(winSize.width*0.5, winSize.height*0.4);
	   this->addChild(start);
	   start->runAction(Sequence::create(animate, callback, NULL));


	   return true;
   }while(0);
       
       return false;
}

void StartLayer::preLoadResource()
{
  	//֡�����ʼ��
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
	AnimationCache::getInstance()->addAnimation(enemy1DownAnimation, "enemy1DownAnimation");

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
	startAnimation->setDelayPerUnit(0.5);
	startAnimation->setLoops(2);
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
	startAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));
	AnimationCache::getInstance()->addAnimation(startAnimation, "startAnimation");

	//��ʼ���û����ݣ�����ֻ��һ����߼�¼
	UserData::getInstance()->saveUserData("beet_score", 0);

	//Ԥ���������ļ�
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_music.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bullet.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("big_spaceship_flying.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy1_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy2_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("enemy3_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("game_over.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("get_double_laser.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("use_bomb.mp3");
	//SimpleAudioEngine::getInstance()->preloadEffect("out.porp.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("button.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("achievement.mp3");
}

//����ת��
void StartLayer::transition()
{
	Scene* gameScene = TransitionSlideInR::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameScene);
}
