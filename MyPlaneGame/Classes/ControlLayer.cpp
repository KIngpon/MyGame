#include "ControlLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static const Size size = Size(60, 45);

ControlLayer::ControlLayer(void)
{
	level = 1;
	levelfactor = 1;
	levelscore = 50;
}


ControlLayer::~ControlLayer(void)
{
}

bool ControlLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());
	   auto winSize = Director::getInstance()->getWinSize();

	   //�����ͣ�˵���ť
	   pauseItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("game_pause_nor.png"),Sprite::createWithSpriteFrameName("game_pause_pressed.png"),CC_CALLBACK_0(ControlLayer::pauseCallBack, this));   
	   auto menu = Menu::create(pauseItem, NULL);
	   menu->setPosition(size.width*0.6, winSize.height-size.height*0.6);
	   this->addChild(menu);

	   //��ӷ�����ʾ��ǩ
	   scoreLabel = Label::createWithBMFont("font.fnt", "0");
	   scoreLabel->setPosition(winSize.width-50, winSize.height-20);
	   this->addChild(scoreLabel);

	   return true;
   }while(0);

   return false;
}

//��ͣ�����¼�
void ControlLayer::pauseCallBack()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button.mp3");
	//����δ��ͣ״̬��ִ����ͣ����
	if(!Director::getInstance()->isPaused())
	{
		//�˴������ͣ�������

		//����ͣ��ǩ��ť����Ϊ�ָ���Ϸ����ʽ
		pauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_resume_nor.png")); 
		pauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_resume_pressed.png"));
		//ִ����ͣ
		GameScene* gameScene = (GameScene*)this->getParent();
		gameScene->pause();
	}
	else//���Ѿ���ͣ���ٴε����ť��ִ�лָ���Ϸ����
	{
	    //�ѻָ���ǩ����Ϊ��ͣ��Ϸ����ʽ
		pauseItem->setNormalImage(Sprite::createWithSpriteFrameName("game_pause_nor.png")); 
		pauseItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_pause_pressed.png"));
		//ִ�лָ�
		GameScene* gameScene = (GameScene*)this->getParent();
		gameScene->resume();
	}
}

//���·�������Ҫ��label��setString��ʵ��
void ControlLayer::updateScore(int score)
{
	String* scoreString = String::createWithFormat("%d", score);
	scoreLabel->setString(scoreString->getCString());
	if(level < 4)
	{
		setLevel(score);
	}
}

void ControlLayer::setLevel(int score)
{
	if(score > levelscore)
	{
	  level++;
	  levelfactor -= 0.3;
	  levelscore += 50;
	  GameScene* gameScene = (GameScene*)this->getParent();
	  gameScene->changeLevel(levelfactor);
	}
}

