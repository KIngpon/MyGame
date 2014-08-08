#include "HeroPlane.h"
#include "GameScene.h"

USING_NS_CC;
static HeroPlane* _heroPlane = NULL;

HeroPlane::HeroPlane(void)
{
}


HeroPlane::~HeroPlane(void)
{
}

HeroPlane* HeroPlane::getInstance()
{
   if(NULL == _heroPlane)
   {
      _heroPlane = new HeroPlane();
	  _heroPlane->init();
   }
   
   return _heroPlane;
}

bool HeroPlane::init()
{
   do
   {
	   //��ӷɻ�����
	   auto winSize = Director::getInstance()->getWinSize();
	   _hero = Sprite::createWithSpriteFrameName("hero1.png");
	   _hero->setPosition(Point(winSize.width*0.5, _hero->getContentSize().height));
	   this->addChild(_hero,6);

	   //������ʼ����˸����
	   auto blink = Blink::create(1.0f, 3);
	   //�����ɻ����ж���
	   auto planeAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("heroAnimation"));
	   
	   _hero->runAction(blink);
	   _hero->runAction(RepeatForever::create(planeAnimate));

	   return true;
   }while(0);

       return false;
}

//�ɻ���ը����
void HeroPlane::blowUp()
{
	auto blowup = Animate::create(AnimationCache::getInstance()->getAnimation("heroBlowupAnimation"));
	auto hide = Hide::create();
	auto callback = CallFunc::create(CC_CALLBACK_0(HeroPlane::callBack, this));
    _hero->stopAllActions();
	_hero->runAction(Sequence::create(blowup, hide, callback, NULL));
}

//�л���ը֮��ķ��ش���������Ҫ�ǽ���gameover�Ĵ���
void HeroPlane::callBack()
{
	_hero->stopAllActions();
	_hero->removeFromParentAndCleanup(true);
	this->destroyInstance();
	GameScene* gameScene = (GameScene*)(this->getParent()->getParent());
	gameScene->gameOver();
}

//�������ٵ���
void HeroPlane::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_heroPlane);
}
