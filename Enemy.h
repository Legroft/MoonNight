#pragma once
#include "Player.h"
#include "cardManager.h"
using namespace sf;
class Enemy :public Player {
public:
	enum eName {					//敌人的名字
		null, carpente, prisone
	};

	int name = 0;						//名字
	Texture tShape;					//敌人纹理
	Sprite shape;					//敌人精灵s
	void setName(int);				//设定名字
	void loadMedia();
	Enemy();

	bool checkMouse(Vector2i);	//检测鼠标是否在敌人身上

	void getCard(Card[], int, int);			//抽牌
	int showCard(RenderWindow*, Player*, cardManager*);		//把敌人用过的卡牌展示在屏幕上
	Card cardShow;			//展示的卡牌
	Vector2f cardPosition;		//敌人卡牌的绘制位置
	Clock useCardTimer;			//出牌定时器

	Clock lastCardClock;			//敌人出最后一张牌的延时

	void initData();
	void drawStatus(RenderWindow* window);
};

