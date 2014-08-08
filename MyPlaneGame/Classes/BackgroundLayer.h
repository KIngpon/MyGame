#pragma once
#include "cocos2d.h"

class BackgroundLayer : public cocos2d::Layer
{
public:
	BackgroundLayer(void);
	~BackgroundLayer(void);
	CREATE_FUNC(BackgroundLayer);
	bool init();

private:
	//ͼƬ����
	void backgroundMove(float dt);
	//����������������
	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
};

