#pragma once
#include "cocos2d.h"

class UfoLayer : public cocos2d::Layer
{
public:
	UfoLayer(void);
	~UfoLayer(void);
	CREATE_FUNC(UfoLayer);
	bool init();
	//���ufo
	void addUfo(float dt);
	//������λ��
	cocos2d::Point getRandomPosition(cocos2d::Size size);
	//����ufo��������
	CC_SYNTHESIZE_READONLY(cocos2d::Vector<cocos2d::Sprite*>, _ufoVector, ufoVector);
	//ufo����
	void ufoMove(cocos2d::Sprite* ufo, cocos2d::Point pos);
	//���н���
	void moveEnd(cocos2d::Sprite* ufo);
	//��ײ����
	void collision(cocos2d::Sprite* ufo);
	//���bomb�ı�־
	void addBombItem();
	//���ٵ�ǰ���ел�
	void destroyAllEnemy();
	//����bomb��Ŀ
	void updateBombNum();
	//����bomb
	void addBombNum();
	//����bomb
	void subBombNum();
private:
	int m_bombNum;
	cocos2d::Label* bombCount;
};

