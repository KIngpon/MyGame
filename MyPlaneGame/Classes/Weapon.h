#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "HeroPlane.h"

typedef enum
{
   Bullet1 = 0,
   Bullet2
}BulletType;

class Weapon : public cocos2d::Layer
{
public:
	Weapon(void);
	~Weapon(void);

	CC_SYNTHESIZE_READONLY(HeroPlane*, _heroPlane, heroPlane);
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<Bullet*>, _bulletVector, bulletVector);

	CREATE_FUNC(Weapon);
	bool init();

	//����ӵ�
	void addBullet(float dt);
	//���˫���ӵ�
	void addMultiBullet(float dt);
	//�Ƴ��ӵ�
	void removeBullet(Bullet* bullet);
	//��ȡ�ӵ�����λ��
	cocos2d::Point getShootPostion();
	//�ɻ���ը
	void heroBlowUp();
	//���������ӵ�����
	void startBullet1Shoot(float dt);
	//ֹͣ�����ӵ�����
	void stopBullet1Shoot();
	//����˫���ӵ�����
	void startBullet2Shoot();
	//ֹͣ˫���ӵ�����
	void stopBullet2Shoot();
	//�ı��ӵ�����
	void changeBullet();
	//��ͣ����
	void pauseTouch();
	//�ָ�����
	void resumeTouch();

	//��Ӵ����¼�
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	cocos2d::EventListenerTouchOneByOne* touchListener;
	BulletType bulletType;

};



