#include "Weapon.h"
USING_NS_CC;

static const int PlaneWidth = 102;
static const int PlaneHeight = 126;

Weapon::Weapon(void)
{
}


Weapon::~Weapon(void)
{
}

bool Weapon::init()
{
   do
   {
	   //��ӷɻ�
	   _heroPlane = HeroPlane::getInstance();
	   this->addChild(_heroPlane);

	   //�ӳ�2�뷢���ӵ�
	   startBullet1Shoot(2.0f);

	   //��Ӵ����¼�������ӵ��ַ�����ȥ
	   touchListener = EventListenerTouchOneByOne::create();
	   touchListener->setSwallowTouches(true);
	   touchListener->onTouchBegan = CC_CALLBACK_2(Weapon::onTouchBegan, this);
	   touchListener->onTouchMoved = CC_CALLBACK_2(Weapon::onTouchMoved, this);
	   _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, _heroPlane);

	   return true;
   }while(0);

   return false;
}

//����ӵ�
void Weapon::addBullet(float dt)
{
	Bullet* bullet = Bullet::createBullet("bullet1.png"); //�������ʹ��������Ⱦ����������
	this->addChild(bullet, 1);
	//��ӵ��ӵ���������
	_bulletVector.pushBack(bullet);
	//��ó�ʼλ����
	bullet->bulletMove(getShootPostion());
}

//���˫�ӵ����䣬ͬ���ӵ�����һ�����������������ӵ�
void Weapon::addMultiBullet(float dt)
{

	Bullet* bulletLeft = Bullet::createBullet("bullet2.png");
	Bullet* bulletRight = Bullet::createBullet("bullet2.png");
	this->addChild(bulletLeft,1);
	this->addChild(bulletRight,1);
	_bulletVector.pushBack(bulletLeft);
	_bulletVector.pushBack(bulletRight);
	bulletLeft->bulletMove(ccpSub(getShootPostion(), Point(7, 0)));
	bulletRight->bulletMove(ccpAdd(getShootPostion(), Point(7, 0)));
}

//��÷���λ�ã����Ƿ��طɻ�ͷ��λ��
Point Weapon::getShootPostion()
{
	auto pos = _heroPlane->getHero()->getPosition();
	auto shootPos = Point(pos.x, pos.y+PlaneHeight/2);
	return shootPos;
}

//�Ƴ��ӵ�����Ҫע����ӵ����������г�ȥ
void Weapon::removeBullet(Bullet* bullet)
{
	_bulletVector.eraseObject(bullet);
	this->removeChild(bullet, true);
}

//�ɻ���ը
void Weapon::heroBlowUp()
{
	this->unscheduleAllSelectors();//ֹͣ�ӵ�����
	_eventDispatcher->removeEventListener(touchListener);//ֹͣ��������
	_heroPlane->blowUp();//�ɻ���ը
}

//�����ӵ��ķ��䣬�ö�ʱ��ʵ�֣��������Ϊ�ӳ�ʱ��dt
void Weapon::startBullet1Shoot(float dt)
{
	this->bulletType = Bullet1;
	this->schedule(schedule_selector(Weapon::addBullet), 0.3f, kRepeatForever, dt);
}

//�����ӵ���ֹͣ���䣬ֹͣ������
void Weapon::stopBullet1Shoot()
{
	this->unschedule(schedule_selector(Weapon::addBullet));
}

//˫���ӵ��ķ���
void Weapon::startBullet2Shoot()
{
    this->bulletType = Bullet2;
	this->schedule(schedule_selector(Weapon::addMultiBullet), 0.3f, 20, 0);
}

//˫���ӵ���ֹͣ����
void Weapon::stopBullet2Shoot()
{
	this->unschedule(schedule_selector(Weapon::addMultiBullet));
}

//�ı��ӵ������ͣ����ڻ��˫���ӵ�ufo��ʱ������л�
//��ֹͣ���ŵķ��䣬Ȼ����ʱ�������ŵķ��䣬��ִ���д������Ƶ�˫�ŷ���
//���ﻹҪע�⵽˫���ӵ�����������ֻ��˫���ӵ���ʱ��Ĵ���
void Weapon::changeBullet()
{
	this->stopBullet1Shoot(); 
	if(this->bulletType == Bullet2)
	{
	  this->stopBullet2Shoot();
	}
	this->startBullet1Shoot(6.5f);
	this->startBullet2Shoot();
	
}

//������ʼ�¼�
bool Weapon::onTouchBegan(Touch* touch, Event* event)
{
	//��÷ɻ��Ĵ�����Χ
	auto node = dynamic_cast<HeroPlane*>(event->getCurrentTarget());
	Rect rect = node->getHero()->getBoundingBox();
	//��������ķ�Χ
	Rect touchRect = Rect(rect.origin.x-5, rect.origin.y-5, rect.size.width+10, rect.size.height+10);
	Point point = touch->getLocation();
	//�жϴ������Ƿ��ڴ�������Χ��
	if(touchRect.containsPoint(point))
	{
	   return true;
	}
	return false;
}

//�����ƶ��¼�
void Weapon::onTouchMoved(Touch* touch, Event* event)
{
    auto node = dynamic_cast<HeroPlane*>(event->getCurrentTarget());
	Size winSize = CCDirector::getInstance()->getWinSize();

	//���÷�Χ
	auto point = node->getHero()->getPosition()+touch->getDelta();
	point.x = MAX(point.x , PlaneWidth*0.4);
	point.x = MIN(point.x , (winSize.width - PlaneWidth*0.4));
	point.y = MAX(point.y , PlaneHeight*0.4);
	point.y = MIN(point.y , (winSize.height - PlaneHeight*0.4));

	node->getHero()->setPosition(point);
}

//��ͣ����,���ڿ�����Ϸ��ͣ
void Weapon::pauseTouch()
{
   _eventDispatcher->pauseEventListenersForTarget(_heroPlane);
}

//�ָ����������ڿ��ƻָ���Ϸ
void Weapon::resumeTouch()
{
	_eventDispatcher->resumeEventListenersForTarget(_heroPlane);
}

