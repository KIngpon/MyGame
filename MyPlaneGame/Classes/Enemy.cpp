#include "Enemy.h"
#include "EnemyLayer.h"
USING_NS_CC;

static const Size Enemy1Size = Size(57,43);
static const Size Enemy2Size = Size(69,99);
static const Size Enemy3Size = Size(169,258);
static const int ENDY = -150;

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

Enemy* Enemy::createEnemy()
{
	Enemy* enemy = new Enemy();
	if(enemy)
	{
		enemy->initWithTexture(nullptr, Rect::ZERO);
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

void Enemy::initEnemyWithFrameName(std::string filename)
{
	this->initWithSpriteFrameName(filename);
}


//�����ȡ��ʼλ�á������и����⡣����������ʱֱ��ȥget Size ����ֱ�Ӷ��峣�����أ�
Point Enemy::getEnemyOriginPosition(Size enemySize)
{
	auto winSize = Director::getInstance()->getWinSize();
	float posX = (float)(rand()%(int(winSize.width - enemySize.width)) + enemySize.width*0.5);
	float posY = winSize.height + enemySize.height;
	return Point(posX, posY);
}

//����㶨��
int Enemy::getSpeed()
{
    return rand()%200+100;
}

//�л�����
void Enemy::enemyFly(Point pos)
{
	this->setPosition(pos);
	Point destination = Point(pos.x, ENDY);
	float duration = (pos.y - ENDY)/(getSpeed());
	auto moveTo = MoveTo::create(duration, destination);
	auto flyEnd = CallFunc::create(CC_CALLBACK_0(Enemy::FlyEnd, this));
	this->runAction(Sequence::create(moveTo, flyEnd, NULL));
}

//�л����н���֮��Ĵ���
void Enemy::FlyEnd()
{
	EnemyLayer* enemylayer = (EnemyLayer*)this->getParent();
	enemylayer->removeEnemy(this);
	this->removeFromParentAndCleanup(true);
}

//�л���ը������Ĳ���Ϊ��ը����������
void Enemy::enemyBlowUp(std::string animationName)
{
	auto animate = Animate::create(AnimationCache::getInstance()->getAnimation(animationName));
	auto hide = Hide::create();
	auto callback = CallFunc::create(CC_CALLBACK_0(Enemy::FlyEnd, this));
	this->stopAllActions();
	this->runAction(Sequence::create(animate, hide, callback, NULL));
}

//��������ֵ
void Enemy::setLife(int life)
{
   this->m_life = life;
}

//�жϵл��Ƿ��Ѿ�����
bool Enemy::isDead()
{
	m_life--;
	if(m_life)
		return false;
	else
		return true;
}