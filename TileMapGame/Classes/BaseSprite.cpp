#include "BaseSprite.h"
USING_NS_CC;

//��ʼ����������
BaseSprite::BaseSprite(void):
	m_pIdleAction(NULL),
	m_pWalkAction(NULL),
	m_pAttackAction(NULL),
	m_pHurtAction(NULL),
	m_pDeadAction(NULL),
	m_curActionState(ACTION_STATE_NONE)
{
}

//���ٵ�ʱ��Ҫ��retain�Ķ���release
BaseSprite::~BaseSprite(void)
{
	CC_SAFE_RELEASE_NULL(m_pIdleAction);
	CC_SAFE_RELEASE_NULL(m_pWalkAction);
	CC_SAFE_RELEASE_NULL(m_pAttackAction);
	CC_SAFE_RELEASE_NULL(m_pHurtAction);
	CC_SAFE_RELEASE_NULL(m_pDeadAction);
}

//ִ�����еĶ���
void BaseSprite::runIdleAction()
{
	if(changeState(ACTION_STATE_IDLE))
	{
		this->runAction(m_pIdleAction);
	}
}

//ִ�����ߵĶ���
void BaseSprite::runWalkAction()
{
	if(changeState(ACTION_STATE_WALK))
	{
		this->runAction(m_pWalkAction);
	}
}

//ִ���ܵ������Ķ���
void BaseSprite::runHurtAction()
{
	if(changeState(ACTION_STATE_HURT))
	{
		this->runAction(m_pHurtAction);
	}
}

//ִ�й����Ķ���
void BaseSprite::runAttactAction()
{
	if(changeState(ACTION_STATE_ATTACK))
	{
		this->runAction(m_pAttackAction);
	}
}

//ִ�������Ķ���
void BaseSprite::runDeadAction()
{
	if(changeState(ACTION_STATE_DEAD))
	{
		this->m_hp = 0;
		this->runAction(m_pDeadAction);
	}
}

//ɾ������
void BaseSprite::removeSprite()
{
	changeState(ACTION_STATE_REMOVE);
	log("BaseSprite::removeSprite m_curActionState = %d", m_curActionState);
}

//��������
Animation* BaseSprite::createAnimation(const char* formatStr, int frameCount, int fps)
{
	Vector<SpriteFrame*> pFrames(frameCount);
	for(int i = 0; i < frameCount; ++i)
	{
		const char* frameName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
		pFrames.pushBack(pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f/fps);
}

//������ص�����
CallFunc* BaseSprite::createDeadCallbackFunc()
{
	return CallFunc::create(CC_CALLBACK_0(BaseSprite::onDead, this));
}

//����״̬�Ļص�����
CallFunc* BaseSprite::createIdleCallbackFunc()
{
	return CallFunc::create(CC_CALLBACK_0(BaseSprite::runIdleAction, this));
}

//����
void BaseSprite::onDead()
{
    this->onDeadCallback();
}

//�жϽ�ɫ�Ƿ���
bool BaseSprite::isLive()
{
	if(this->m_curActionState >= ACTION_STATE_DEAD)
	{
	  return false;
	}else{
	  return true;
	}
}

//״̬�жϵĵ�һ��������||����Ĳ��ֲ�����⣬��ͷ��������������
bool BaseSprite::changeState(ActionState actionState)
{
	if((m_curActionState == ACTION_STATE_DEAD && actionState != ACTION_STATE_REMOVE) || m_curActionState == actionState)
	{
	   return false;
	}

	this->stopAllActions();
	this->m_curActionState = actionState;
	if(actionState == ACTION_STATE_REMOVE)
		 return false;
	else 
		 return true;

}

//����������صĽṹ���������rect,һ��������ײ��⣬�����½�Ϊԭ���actual.��һ��Ϊoriginal���������������½�Ϊԭ���rect
BoundingBox BaseSprite::createBoundingBox(Point origin, Size size)
{
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;
	boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
	boundingBox.actual.size = size;
	return boundingBox;
}

//���¹�����Χ�ͱ�������Χ
void BaseSprite::updateBoxes() {
	bool isFlippedX = this->isFlippedX();
	float x = 0.0f;
	if(isFlippedX) {
		x = this->getPosition().x - m_hitBox.original.origin.x;
	}else {
		x = this->getPosition().x + m_hitBox.original.origin.x;
	}
	m_hitBox.actual.origin = Point(x, this->getPosition().y + m_hitBox.original.origin.y);
    m_bodyBox.actual.origin = this->getPosition() + m_bodyBox.original.origin;
}

//���������λ�ã�������һ��updateBoxes();
void BaseSprite::setPosition(const Point &position)
{
	Sprite::setPosition(position);
	this->updateBoxes();
}