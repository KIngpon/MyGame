#pragma once
#include "cocos2d.h"

class ControlLayer : public cocos2d::Layer
{
public:
	ControlLayer(void);
	~ControlLayer(void);
	CREATE_FUNC(ControlLayer);
	bool init();
	//��Ϸ��ͣ��ť�����¼�
	void pauseCallBack();
	//���·���
	void updateScore(int score);
	//���õȼ�
	void setLevel(int score);
private:
	cocos2d::MenuItemSprite* pauseItem;
	cocos2d::Label* scoreLabel;
	int level;
	float levelfactor;
	int levelscore;
};

