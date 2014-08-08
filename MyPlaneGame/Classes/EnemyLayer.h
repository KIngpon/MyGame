#pragma once
#include "cocos2d.h"
#include "Enemy.h"

class EnemyLayer : public cocos2d::Layer
{
public:
	EnemyLayer(void);
	~EnemyLayer(void);

	CREATE_FUNC(EnemyLayer);
	bool init();
	//����3�ֵл��Ĺ�������
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<Enemy*>, _enemy1Vector, Enemy1Vector);
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<Enemy*>, _enemy2Vector, Enemy2Vector);
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<Enemy*>, _enemy3Vector, Enemy3Vector);
	//��ӵл�
	void addEnemy1(float dt);
	void addEnemy2(float dt);
	void addEnemy3(float dt);
	//�Ƴ�ָ���л�
	void removeEnemy(Enemy* enemy);
	//������Ϸ�Ѷ�
	void setLevelFactor(float factor);
	//�����л�����
	void startEnemy(float factor);
	//ֹͣ�л�����
	void stopEnemy();
	//void removeAllEnemy();
};

