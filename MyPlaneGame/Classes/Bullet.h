#pragma once
#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
public:
	Bullet(void);
	~Bullet(void);
	//����дcreate��initWithFrameName,��Ȼ����ʹ��Sprite�еĳ�ʼ������
	static Bullet* createBullet(std::string frameName);
	void initBulletWithFrameName(std::string frameName);

	//�ӵ��ƶ�
	void bulletMove(cocos2d::Point origin);
	//�ƶ���������
	void moveEnd();
	
};

