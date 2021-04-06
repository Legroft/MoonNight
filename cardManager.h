#pragma once
#include "Player.h"
#include <iostream>
#include <vector>
using namespace std;
class cardManager {
public:
	int playerCardPoolNum = 72, enemyCardPoolNum = 72;							//卡池中卡牌数量
	int playerCardLength = 72, enemyCardLength = 72;
	Card playerCards[72], enemyCards[72];										//卡牌数组
	Texture tCard1[3][72], tEnemyCard[72];										//卡牌纹理数组
	void initCards();															//初始化卡牌数据
	int useCard(Player*, Card*, int i, Player*);										//使用卡牌
	void getCard(Player*, Card[], int, int, int);								//抽牌 玩家，卡组 抽牌数 卡组数量 抽牌种类
	bool cardUsable(Player*, Card*);												//手牌是否可用
	int getCardPoolNum(Player*, Card[], int);				//获取卡池中牌的数量
	vector<int> searchCard(Player*, Card[], int, int, int);					//搜寻卡牌 长度 卡池 种类 消耗 

	void drawCardPoolNum(RenderWindow*);				//绘制卡池剩余卡牌

	Text textCardPoolNum;		//抽卡池剩余卡牌
	Font textFont;				//字体

	int playerStatus(Player*, Card*, Player*);
};