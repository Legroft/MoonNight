#pragma once
#include "Button.h"
class Card : public Button {
public:
	enum e_cardType {
		attack, mp, magic, movePower, fightBack, equip //红色攻击牌，法力牌，咒术牌，行动力牌，反制牌，装备牌
	};
	enum e_cardState {
		cardPool, handPool, disCardPool, noPool, null			//卡牌的状态，卡池，手牌区，弃牌区，被移除,空
	};
	enum e_special {
		potion
	};
	enum e_potionType {
		fire, ice, dark, thunder,
	};
	int playerStatus = -1;		//赋予玩家的特殊状态
	int getCardType = -1;		//抽牌种类
	int reduceEnemyGetNum = 0;	//减少敌人抽牌数
	int attackTimes = 1;	//攻击次数
	int potionType = -1;
	int failNum = 0;		//使敌人出牌失效次数
	bool removeGame = false;//是否移出游戏
	int useTimes = 1;		//触发次数
	int cardSpecial = -1;	//特殊卡牌
	int getStrong = 0;		//获得“强效”		
	int cost = 0;			//消耗点数
	int damage = 0;			//物理伤害
	int fireDamage = 0;		//火焰伤害
	int iceDamage = 0;		//寒冷伤害
	int poisonDamage = 0;	//毒伤害
	int getMp = 0;			//获得魔法
	//int reduceMagic = 0;	//消耗魔法
	int getMovePower = 0;	//获得行动力
	int getHp = 0;			//加血
	int superHp = 0;		//血量上限
	bool destory = false;		//是否“移除”卡牌
	//bool getCard = 0;		//抽牌
	int getCardNum = 0;		//抽牌数
	int cardType = 0;		//卡牌种类
	int cardState = cardPool;	//卡牌状态 哪个池子里
	bool discard = false;		//是否可弃牌

	void move(Vector2i);		//卡牌移动
	Vector2f originPosition;	//初始位置
	Vector2i originMouse;		//初始鼠标位置



};

