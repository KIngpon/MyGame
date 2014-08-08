#pragma once
#include "cocos2d.h"

class GameOverLayer : public cocos2d::Layer
{
public:
	GameOverLayer(void);
	~GameOverLayer(void);

	static cocos2d::Scene* scene(int score);
	static GameOverLayer* create(int score);
	bool init();
	//���¿�ʼ��Ϸ
	void reset();
	//��ʾ��ǰ����
	void showCurrentScore();
	//��ʾ��ߵ÷�
	void showBestScore();
	//����¼ʱ��ʾ��־
	void showBestSprite();
	//��ʾ�˵���
	void showMenu();
private:
	int finalScore;
	bool getRecord;
	cocos2d::Label* scoreLabel;


};

