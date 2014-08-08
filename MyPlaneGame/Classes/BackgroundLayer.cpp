#include "BackgroundLayer.h"
USING_NS_CC;

BackgroundLayer::BackgroundLayer(void)
{
}


BackgroundLayer::~BackgroundLayer(void)
{
}

bool BackgroundLayer::init()
{
   do
   {
	   CC_BREAK_IF(!Layer::init());

	   background1 = Sprite::createWithSpriteFrameName("background.png");
	   background1->setAnchorPoint(Point::ZERO);
	   background1->setPosition(Point::ZERO);
	   //ԭ�����ֵİױ����ڽ���ˣ����ǵ�������һ����뽫������Ƭ����Ϊ�޾��
	   background1->getTexture()->setAliasTexParameters();
	   this->addChild(background1);

	   background2 = Sprite::createWithSpriteFrameName("background.png");
	   background2->setAnchorPoint(Point::ZERO);
	   background2->setPosition(Point(0, background2->getContentSize().height - 2.0f));
	   background2->getTexture()->setAliasTexParameters();
	   this->addChild(background2);

	   this->schedule(schedule_selector(BackgroundLayer::backgroundMove),0.01f);

      return true;
   }while(0);
      return false;
}

//��������ͼƬ�Ĺ���ģ��ɻ����˶�
void BackgroundLayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2.0f);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2.0f);
	if(0 == background2->getPositionY())
	{
		background1->setPositionY(0);
	}
}
