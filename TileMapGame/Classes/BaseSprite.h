#pragma once
#include "cocos2d.h"

//��Ϸ״̬
typedef enum
{
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_ATTACK,
	ACTION_STATE_HURT,
	ACTION_STATE_DEAD,
	ACTION_STATE_REMOVE,
}ActionState;

//��������Ĵ�С��Ϣ��actualΪ��ԭ���Rect,originalΪ�������С���½ǵ�Rect,������������ײ���
typedef struct _BoundingBox
{
   cocos2d::Rect actual;
   cocos2d::Rect original;
}BoundingBox;

class BaseSprite : public cocos2d::Sprite
{
public:
	BaseSprite(void);
	~BaseSprite(void);

	//�������в��ֲ�ͬ״̬�Ķ���
	void runIdleAction();
	void runWalkAction();
	void runAttactAction();
	void runHurtAction();
	void runDeadAction();
	//�Ƴ�����
	void removeSprite();

	//���嶯������
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pIdleAction, IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pWalkAction, WalkAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pAttackAction, AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pHurtAction, HurtAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, m_pDeadAction, DeadAction);

	//����״̬����
	CC_SYNTHESIZE(ActionState, m_curActionState, CurActionState);
	//��ɫ���ٶ�
	CC_SYNTHESIZE(cocos2d::Point, m_fVelocity, Velocity);
	//��ɫ��Ѫ��
	CC_SYNTHESIZE(unsigned int, m_hp, HP);
	//��ɫ�Ĺ�����
	CC_SYNTHESIZE(unsigned int, m_attack, Attack);
	//��ɫ���ܹ�����Χ
	CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
	//��ɫ�Ĺ�����Χ
	CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);

	//�����Զ���setPosition,�������ܹ����͹�����Χ
	virtual void setPosition(const cocos2d::Point &position);
	//��ɫ����
	virtual void onDead();
	//��ɫ�Ƿ���
	virtual bool isLive();

	//����������Ļص��¼�
	cocos2d::CallFunc* createDeadCallbackFunc();
	//��������״̬�µĻص��¼�
	cocos2d::CallFunc* createIdleCallbackFunc();

	//����һ���޷���ֵ�޲����ĺ���ģ�棬��ʵ�൱�ں���ָ��
	std::function<void(void)> onDeadCallback;
	//ͬ��
	std::function<void(void)> attack;

protected:
	//����һ������
	static cocos2d::Animation* createAnimation(const char* formatStr, int frameCount, int fps);
	//����һ��boundingbox�ṹ��
	BoundingBox createBoundingBox(cocos2d::Point origin, cocos2d::Size size);
	//���·�Χ
	void updateBoxes();

private:
	//�ı�״̬
	bool changeState(ActionState actionState);

};



