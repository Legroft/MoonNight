#pragma once
#include "Card.h"
#include "statusBtn.h"
class Player {
public:

	int handMaxNum = 8;
	Card* handCards[8];				//手牌[数量上限]
	Card nullCard;					//空牌
	int handCardNums;				//手牌数目
	int getCardNum;					//抽牌数目
	void getCard(Card[], int, int);			//抽牌

	bool getCardState = false;					//玩家可否抽牌
	void randCardPool(Card[], int);			//抽卡池洗牌
	int cardSelect;					//与哪个卡牌正在交互

	Texture tNums[10];			//数字纹理
	int hp;						//血量
	int fullHp = 100;					//满血血量
	int mp = 5;						//蓝量
	int movePower = 1;				//行动力
	void drawState(RenderWindow*);			//更新状态
	int cardPoolNum;			//卡池中卡牌数量
	Sprite sMovePower;			//行动力
	Texture tHpBar;				//血量纹理
	Texture tMpBar;				//蓝量
	Sprite	hpBar;		//血量精灵
	Sprite  mpBar;		//蓝量
	void loadMedia();
	Player();

	Font textFont;			//文字的字体
	Text hpText, mpText, moveText;		//文字

	void updateHandCard();					//更新手牌状态
	void useCardTo(Card*, Player*);			//对某个敌人使用卡牌

	void disCard(Card*);					//弃牌

	bool isTurn = true;		//是否为该玩家回合

	int fireState = 0;		//火焰被动
	int poisonState = 0;			//毒被动
	int iceState = 0;			//寒冷被动
	int reduceGetCardNum = 0;		//减少的抽牌数
	int reduceDamageNum = 0;		//减少的伤害量

	bool humanPlayer = true;	//是否为人类玩家

	std::vector<int> playerStatus;				//玩家状态的数组
	void drawStatus(RenderWindow* window);		//绘制卡牌状态
	Texture tPlayerStatus[20];					//状态纹理
	statusBtn sPlayerStatus[20];					//状态精灵
	void statusUpdate(Player* enemy, int turn, int time);		//与状态进行交互

	bool addUpDamageAble = false;
	int addUpDamage = 0;
	int countDamage[2] = { 0,1 };

	void initData();			//初始化数据

	void cheat_getCard(Card[], int num);		//获得指定手牌

	int turnMagicUsedNum = 0;		//本回合使用咒术牌数量
	int turnInvalidCardNum = 0;		//回合牌失效次数
	int turnMagicAdd = 0;			//本回合咒术牌增加次数

	bool turnStart = true;		//回合开始

	int useCardNum;		//可以使用的卡牌数量
};

