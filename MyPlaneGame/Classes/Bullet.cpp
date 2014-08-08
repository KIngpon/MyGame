#include "Bullet.h"
#include "Weapon.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

const int END_Y = 875; //�ӵ��Ľ���λ�ã�������Ļ�߶�+�ӵ��߶ȼ��㣨852 + 21��
const int speed = 300; //�����ӵ����ٶ�

Bullet::Bullet(void)
{
}

Bullet::~Bullet(void)
{
}


Bullet* Bullet::createBullet(std::string frameName)
{
	Bullet* bullet = new Bullet();
	if(bullet)
	{
		bullet->initWithSpriteFrameName(frameName);
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void Bullet::initBulletWithFrameName(std::string frameName)
{
	this->initWithSpriteFrameName(frameName);
}

//�ӵ��ķ���
void Bullet::bulletMove(Point origin)
{
	//�����ӵ��ķ��еĲ���
	this->setPosition(origin);
	auto destination = Point(origin.x, END_Y);
	float duration = (END_Y - origin.y)/speed;

	//�����ƶ������Ͷ�����ɺ�Ļص�����
	auto moveTo = MoveTo::create(duration, destination);
	auto moveEnd = CallFunc::create(CC_CALLBACK_0(Bullet::moveEnd, this));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bullet.mp3");
	this->runAction(Sequence::create(moveTo, moveEnd, NULL));
}

//�ӵ������Ĵ���
void Bullet::moveEnd()
{
	Weapon* weapon = (Weapon*)this->getParent();
	weapon->removeBullet(this);
}


