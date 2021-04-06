#include "Enemy.h"
#include <iostream>
#include <sstream>
using namespace std;
void Enemy::initData() {
	fullHp = 30;
	cardShow.cardState = null;

	isTurn = false;				//敌人后出牌

	useCardNum = getCardNum;				//记得修改

	humanPlayer = false;
	handCardNums = 0;
	getCardNum = 4;
	movePower = 2;

	mp = 3;

	hp = fullHp;		//设定为初始血量
	for (int i = 0; i < handMaxNum; i++) {						//初始化敌人手牌
		handCards[i] = &nullCard;
	}

	turnStart = false;

	playerStatus.clear();				//清空状态数组

	addUpDamage = 0;		//造成总伤害为0
	countDamage[0] = 0;		//计数
	countDamage[1] = 1;		//计数

	turnMagicUsedNum = 0;	//本回合使用咒术牌为0
	turnMagicAdd = 0;		//本回合咒术牌增加次数

	fireState = 0;
	iceState = 0;
	reduceDamageNum = 0;
	reduceGetCardNum = 0;

}
Enemy::Enemy() {
	hpText.setCharacterSize(18);
	hpText.setPosition(785, 328);
	mpText.setCharacterSize(15);
	mpText.setPosition(785, 348);
	moveText.setPosition(895, 343);

	hpBar.setPosition(913, 334);
	mpBar.setPosition(867, 354);

	cardPosition.x = 400;
	cardPosition.y = 100;

	initData();

}
void Enemy::loadMedia() {
	tHpBar.loadFromFile("./data/ui/blong.png");	//设定贴图
	tMpBar.loadFromFile("./data/ui/bshort.png");
	for (int i = 0; i < 10; i++) {
		stringstream ss;
		ss << "./data/ui/" << i << ".png";
		tNums[i].loadFromFile(ss.str());
	}
	hpBar.setTexture(tHpBar);
	mpBar.setTexture(tMpBar);
	sMovePower.setTexture(tNums[1]);

	for (int i = 0; i < 20; i++) {
		stringstream ss;
		ss << "./data/status/card" << i << ".png";
		tPlayerStatus[i].loadFromFile(ss.str());
		sPlayerStatus[i].setTexture(tPlayerStatus[i]);
		sPlayerStatus[i].setScale(0.3f, 0.3f);
	}
}
void Enemy::setName(int num) {
	name = num;
	switch (name) {
		case carpente:
			tShape.loadFromFile("./data/enemy/carpente.png");
			shape.setTexture(tShape);
			break;
		case prisone:
			tShape.loadFromFile("./data/enemy/prisone.png");
			shape.setTexture(tShape);
			break;
		default:
			break;
	}
}
bool Enemy::checkMouse(Vector2i mouse) {
	return ((mouse.x > shape.getPosition().x && mouse.x < shape.getPosition().x + shape.getTexture()->getSize().x) &&
		(mouse.y > shape.getPosition().y && mouse.y < shape.getPosition().y + shape.getTexture()->getSize().y)) ? true : false;
}
void Enemy::getCard(Card cards[], int getNum, int length) {
	Player::getCard(cards, getNum, length);
	cardShow = nullCard;			//回合开始时出牌为null
	useCardTimer.restart();			//启动计时器
}
int Enemy::showCard(RenderWindow* window, Player* player, cardManager* cm) {
	useCardNum = 0;
	for (int i = 0; i < handMaxNum; i++) {
		if (handCards[i]->cardState != handCards[i]->null) {
			if (cm->cardUsable(this, handCards[i])) {
				useCardNum++;
			};
		}
	}
	if (useCardNum == 0 && handCardNums == handMaxNum) {
		for (int i = 0; i < handMaxNum; i++) {
			handCards[i]->cardState = handCards[i]->disCardPool;
			handCards[i] = &nullCard;
			handCardNums--;
		}
		return 0;
	}
	if (useCardNum > 0) {
		if (useCardTimer.getElapsedTime().asMilliseconds() > 800) {		//大于800 ms
			for (int i = 0; i < handMaxNum; i++) {
				if (handCards[i]->cardState != handCards[i]->null) {		//如果手牌不为空

					//useCardTo(handCards[i], player);									//弃牌
					//useCardTo(handCards[i], player);

					Card tempCardShow = *handCards[i];								//展示该卡牌
					int cardNum = handCardNums;
					int num = cm->useCard(this, handCards[i], i, player);

					useCardNum += handCardNums - cardNum;

					//if (handCardNums == 0) {
					//	useCardNum = 0;
					//} else {
					//	if (handCardNums < cardNum) {
					//		useCardNum -= 1;
					//	}
					//}
					//cardShow = tempCardShow;
					//useCardTimer.restart();									//重启计时器

					//return i;													//退出循环


					switch (num) {				//是否可用
						/*case 2:
						case 3:
							return -1;*/
						case -2:
						case -1:
							useCardNum--;
							//handCards[i] = &nullCard;								//手牌数组位置为null
							cardShow = tempCardShow;
							useCardTimer.restart();									//重启计时器

							return i;													//退出循环
							break;
					}

				}
			}
		}
	}
	return -2;
}
void Enemy::drawStatus(RenderWindow* window) {
	for (int i = 0; i < playerStatus.size(); i++) {
		sPlayerStatus[playerStatus[i]].setPosition(625 + i * 60.f, 400);
		window->draw(sPlayerStatus[playerStatus[i]]);
	}
}
