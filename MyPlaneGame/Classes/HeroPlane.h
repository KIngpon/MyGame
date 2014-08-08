#pragma once
#include "cocos2d.h"


class HeroPlane : public cocos2d::Node
{
public:
	HeroPlane(void);
	~HeroPlane(void);

	//��Ӣ�۷ɻ����ó�Ϊ����
	static HeroPlane* getInstance();
	//���ٵ���
	void destroyInstance();
	bool init();
	//�ɻ���ը
	void blowUp();
	//��ը���ز���
	void callBack();
	//����һ��ֻ������
	CC_SYNTHESIZE_READONLY(cocos2d::Sprite* , _hero, Hero);

	//��ȡӢ�۷ɻ���Ч�Ĵ��㷶Χ
	//cocos2d::Rect getHeroPlaneTouchRect();

};

