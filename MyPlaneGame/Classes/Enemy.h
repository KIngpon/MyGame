#pragma once
#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
	Enemy(void);
	~Enemy(void);

	//�����л�����
	static Enemy* createEnemy();
	void initEnemyWithFrameName(std::string filename);

	//�����õл�����λ��
	cocos2d::Point getEnemyOriginPosition(cocos2d::Size enemySize);
	//�����ó�ʼ�ٶ�
	int getSpeed();
	//�л�����
	void enemyFly(cocos2d::Point pos);
	//�л�����
	void FlyEnd();
	//�л���ը
	void enemyBlowUp(std::string animationName);
	//��������ֵ
	void setLife(int life);
	//�ж��Ƿ�����
	bool isDead();
private:
	int m_life;
};

