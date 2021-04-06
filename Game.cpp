#include "Game.h"
#include <iostream>
#include <thread>
using namespace std;

Game::Game() {
	windowWidth = 1600;								//窗口宽度
	windowHeight = 900;								//窗口高度
	window.create(VideoMode(windowWidth, windowHeight), L"月圆之夜", windowStyle);			//建立一个xx宽xx高，标题为xxx的窗口，L表示双字节
	gameSceneState = SCENE_LOADING;					//初始默认游戏场景
	initLoading();

}
void Game::Initial() {
	window.setFramerateLimit(60);					//刷新帧数
	gameOver = gameQuit = false;
	fightMusicState = true;
	startMusicState = true;
	drawPosition();
}
void Game::initFightData() {
	whosTurn = ePlayerTurn;
	for (int i = 0; i < sizeof(cardManage.playerCards) / sizeof(cardManage.playerCards[0]); i++) {			//初始化玩家卡池
		cardManage.playerCards[i].cardState = cardManage.playerCards[i].cardPool;
		cardManage.playerCards[i].discard = true;
	}


	for (int i = 0; i < humanPlayer.handMaxNum; i++) {			//填充玩家手牌数组
		humanPlayer.handCards[i] = &humanPlayer.nullCard;
	}
	humanPlayer.initData();
	enemyCarpente.initData();
	gameLose = false;			//游戏没有输

	for (int i = 0; i < sizeof(cardManage.enemyCards) / sizeof(cardManage.enemyCards[0]); i++) {		//初始化敌人卡池
		cardManage.enemyCards[i].cardState = cardManage.enemyCards[i].cardPool;
		cardManage.enemyCards[i].discard = true;
	}


	enemyCarpente.initData();
}
void Game::loadMediaData() {
	//加载贴图纹理
	tGameStartBK.loadFromFile("./data/bg/bg1.png");
	tStartBtnNormal.loadFromFile("./data/button/start.png");
	tStartBtnHover.loadFromFile("./data/button/startHover.png");
	tStartBtnClick.loadFromFile("./data/button/startClick.png");
	tGameFightBK.loadFromFile("./data/bg/bg2.png");
	tbackToMenuNormal.loadFromFile("./data/button/backNormal.png");
	tbackToMenuHover.loadFromFile("./data/button/backHover.png");
	tbackToMenuClick.loadFromFile("./data/button/backClick.png");

	tPlayUI.loadFromFile("./data/ui/playerUI.png");
	tEnemyUI.loadFromFile("./data/ui/enemyUI.png");
	tDialog.loadFromFile("./data/ui/dialog.png");
	tTurn.loadFromFile("./data/ui/yourTurn.png");

	sPlayUI.setTexture(tPlayUI);
	sEnemyUI.setTexture(tEnemyUI);
	sDialog.setTexture(tDialog);
	sTurn.setTexture(tTurn);

	//精灵绑定纹理
	sGameStartBK.setTexture(tGameStartBK);
	startBtn.setTextures(tStartBtnNormal, tStartBtnHover, tStartBtnClick);
	sGameFightBK.setTexture(tGameFightBK);
	backToMenuBtn.setTextures(tbackToMenuNormal, tbackToMenuHover, tbackToMenuClick);

	tDisCardBtn.loadFromFile("./data/button/delete.png");
	tDisCardBtnHover.loadFromFile("./data/button/deleteHover.png");
	disCardBtn.setTextures(tDisCardBtn, tDisCardBtnHover, tDisCardBtnHover);

	//加载音频
	gameStartMusic.openFromFile("./data/music/game.ogg");
	fightMusic.openFromFile("./data/music/fight.ogg");

	victorSb.loadFromFile("./data/sound/victor.ogg");
	defeatSb.loadFromFile("./data/sound/defeat.ogg");
	attackSb.loadFromFile("./data/sound/attack.ogg");
	hoverSb.loadFromFile("./data/sound/hover.ogg");
	pressSb.loadFromFile("./data/sound/press.ogg");
	releaseSb.loadFromFile("./data/sound/release.ogg");

	victorSd.setBuffer(victorSb);
	defeatSd.setBuffer(defeatSb);
	attackSd.setBuffer(attackSb);
	hoverSd.setBuffer(hoverSb);
	pressSd.setBuffer(pressSb);
	releaseSd.setBuffer(releaseSb);

	turnEndNormal.loadFromFile("./data/button/endNormal.png");
	turnEndHover.loadFromFile("./data/button/endHover.png");
	turnEndCllick.loadFromFile("./data/button/endClick.png");
	turnEnd.setTextures(turnEndNormal, turnEndHover, turnEndCllick);

	tYesNormal.loadFromFile("./data/button/yes.png");
	tYesHover.loadFromFile("./data/button/yesHover.png");
	tYesClick.loadFromFile("./data/button/yesClick.png");
	tNoNormal.loadFromFile("./data/button/no.png");
	tNoHover.loadFromFile("./data/button/noHover.png");
	tNoClick.loadFromFile("./data/button/noClick.png");

	yesBtn.setTextures(tYesNormal, tYesHover, tYesClick);
	noBtn.setTextures(tNoNormal, tNoHover, tNoClick);


	tgameWinDialog.loadFromFile("./data/ui/youWin.png");						//输赢的对话框
	tgameLoseDialog.loadFromFile("./data/ui/youLose.png");
	tgmOverToMenuBtn.loadFromFile("./data/button/toMenu.png");					//加载游戏结束时的按钮	
	tgmOverToMenuBtnHover.loadFromFile("./data/button/toMenuHover.png");		//返回主界面
	tgmOverToMenuBtnClick.loadFromFile("./data/button/toMenuClick.png");
	tgmOverReplayBtn.loadFromFile("./data/button/replay.png");
	tgmOverReplayBtnHover.loadFromFile("./data/button/replayHover.png");
	tgmOverReplayBtnClick.loadFromFile("./data/button/replayClick.png");

	gmOverReplayBtn.setTextures(tgmOverReplayBtn, tgmOverReplayBtnHover, tgmOverReplayBtnClick);
	gmOvertoMenuBtn.setTextures(tgmOverToMenuBtn, tgmOverToMenuBtnHover, tgmOverToMenuBtnClick);
	gmWinDialog.setTexture(tgameWinDialog);
	gmLoseDialog.setTexture(tgameLoseDialog);

	loadCards();
	gameSceneState = SCENE_START;
	initMusic();
	humanPlayer.loadMedia();
	loadEnemy();

}
void Game::initMusic() {
	gameStartMusic.setLoop(true);			////背景音乐循环
	fightMusic.setLoop(true);
	gameStartMusic.play();
}
void Game::loadMusic() {
	switch (gameSceneState) {
		case SCENE_START:
			fightMusic.stop();
			if (startMusicState) {			//音乐开关
				gameStartMusic.play();
			} else {
				gameStartMusic.stop();
			}break;
		case SCENE_FIGHT:
			gameStartMusic.stop();
			if (fightMusicState) {			//音乐开关
				fightMusic.play();
			} else {
				fightMusic.stop();
			}break;
		default:
			break;
	}
}
void Game::loadCards() {
	cardManage.initCards();
}
void Game::loadEnemy() {
	enemyCarpente.setName(1);
	enemyCarpente.loadMedia();
}
void Game::Input() {
	Event event;
	Vector2i mousePosition = Mouse::getPosition(window);
	while (window.pollEvent(event)) {				//接受事件
		if (event.type == Event::Closed) {
			window.close();							//关闭键关闭窗口
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape) {
			window.close();							//按esc键关闭窗口
			gameQuit = true;
		}
		switch (gameSceneState) {
			case SCENE_START:
				startInput(mousePosition, event); break;
			case SCENE_FIGHT:
				fightInput(mousePosition, event); break;
			default:
				break;
		}
	}
}
void Game::startInput(Vector2i mousePosition, Event event) {
	backToMenuBtn.setState(0);
	switch (startBtn.checkMouse(mousePosition, event)) {
		case 1:
			break;
		case 3:														//如果RELEASE状态
			releaseSd.play();
			gameSceneState = SCENE_FIGHT;							//切换场景
			loadMusic();											//加载音乐
			initFightData();										//加载战斗数据
		default:
			break;
	}
}
void Game::fightInput(Vector2i mousePosition, Event event) {

	if (gameWin) {
		if (event.type == Event::EventType::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
			gameSceneState = SCENE_START;				//切换场景
			gameWin = false;							//
		}
	} else if (gameLose) {
		switch (gmOverReplayBtn.checkMouse(mousePosition, event)) {
			case 3:
				initFightData();
				gmOverReplayBtn.setState(gmOverReplayBtn.NORMAL);
		}
		switch (gmOvertoMenuBtn.checkMouse(mousePosition, event)) {
			case 3:
				gameLose = false;
				gameSceneState = SCENE_START;									//切换场景
				gmOvertoMenuBtn.setState(gmOvertoMenuBtn.NORMAL);				//设定为普通状态
				loadMusic();													//切换音乐
		}
	} else {

		startBtn.setState(0);
		switch (backToMenuBtn.btnState) {
			case 1:
			case 2:
				backToMenuBtn.offset(-5, -5);						//设定偏移量
				break;
		}
		switch (backToMenuBtn.checkMouse(mousePosition, event)) {
			case 1:
				break;
			case 3:
				releaseSd.play();										//释放按钮的声音
				showBackDialog = true;									//显示对话框
				break;
		}
		if (showBackDialog) {
			switch (yesBtn.checkMouse(mousePosition, event)) {
				case 3:
					gameSceneState = SCENE_START;							//切换场景
					loadMusic();											//加载音乐
					showBackDialog = false;								//不显示对话框
					yesBtn.setState(0);									//设定按钮为普通状态
					break;
			}
			switch (noBtn.checkMouse(mousePosition, event)) {
				case 3:
					showBackDialog = false;
					break;
			}
		}
		if (whosTurn == ePlayerTurn) {
			switch (turnEnd.checkMouse(mousePosition, event, 0, 0)) {
				case 1:
					hoverSd.play();
					break;
				case 3:

					//humanPlayer.cheat_getCard(cardManage.playerCards, 18);		//去掉
					//humanPlayer.cheat_getCard(cardManage.playerCards, 23);		//去掉

					releaseSd.play();

					whosTurn = eEnemyTurn;									//敌人回合
					enemyCarpente.getCardState = true;						//可摸牌
					enemyCarpente.turnStart = true;					//敌人回合开始
					turnEnd.setState(turnEnd.NORMAL);
					break;
			}
			int cardPos = 0;											//当前卡牌是手牌中的第几张
			for (int i = 0; i < humanPlayer.handMaxNum; i++) {
				if (humanPlayer.handCards[i]->cardState != humanPlayer.handCards[i]->null) {
					cardPos++;
					if (cardPos != humanPlayer.handCardNums) {	//如果不是最后一张手牌（在最上面）
						cardOffset.x = 80;
						cardOffset.y = 0;
					} else {
						cardOffset.x = 0;
						cardOffset.y = 0;
					}
					if (humanPlayer.handCards[i]->mouseContain(mousePosition, cardOffset.x, cardOffset.y)) {
						humanPlayer.cardSelect = i;								//与第i张卡牌进行交互
					}
					switch (humanPlayer.handCards[i]->checkMouse(mousePosition, event, cardOffset.x, cardOffset.y)) {		//卡片事件
						case 0:
							humanPlayer.handCards[i]->hoverSd = true;					//如果卡片为普通状态 比如 鼠标移到卡牌外 原地释放卡牌
							humanPlayer.handCards[i]->pressSd = true;
							if (humanPlayer.cardSelect != -1) {							//如果鼠标在与卡牌进行交互

							} else if (mousePosition.x > (300 + (humanPlayer.handCardNums - 1) * 150 + 200) || mousePosition.x < 300 || mousePosition.y>800 || mousePosition.y < 500) {		//鼠标在手牌区外
								pressSd.stop();											//按下时的音效
								hoverSd.stop();											//悬浮时的音效
							}
							break;
						case 1:
							pressSd.stop();
							if (humanPlayer.handCards[i]->hoverSd) {					//如果悬浮音效可播放
								hoverSd.play();											//播放悬浮音效
								humanPlayer.handCards[i]->hoverSd = false;				//不可播放悬浮音效
							}
							break;
						case 2:
							hoverSd.stop();
							if (humanPlayer.handCards[i]->pressSd) {
								pressSd.play();
								humanPlayer.handCards[i]->pressSd = false;
							}
							disCardBtn.setState(disCardBtn.HOVER);
							break;
						case 3:
							pressSd.stop();
							releaseSd.play();
							if (enemyCarpente.checkMouse(mousePosition)) {
								switch (cardManage.useCard(&humanPlayer, humanPlayer.handCards[i], i, &enemyCarpente)) {		//是否可出牌
									case 2:
										hint.setText(0);
										break;
									case 3:
										hint.setText(1);
										break;
									case -1:
										attackSd.play();													//播放攻击音乐
										//humanPlayer.useCardTo(humanPlayer.handCards[i], &enemyCarpente);	//对敌人使用卡牌

										//humanPlayer.handCards[i] = &humanPlayer.nullCard;					//设定使用后的手牌为null
										break;
									case -2:			//无效了一张牌

										break;
								}
							} else {
								if (humanPlayer.handCards[i]->mouseContainf(disCardBtn.getPosition(), 30, -30)) {
									humanPlayer.disCard(humanPlayer.handCards[i]);
									humanPlayer.handCards[i] = &humanPlayer.nullCard;					//设定使用后的手牌为null
								} else
									humanPlayer.handCards[i]->setState(humanPlayer.handCards[i]->NORMAL);		//释放后设定为普通状态
							}
							disCardBtn.setState(disCardBtn.NORMAL);
							humanPlayer.cardSelect = -1;								//没有在与卡牌进行交互
							humanPlayer.handCards[i]->hoverSd = true;					//释放卡牌，音效可播放
							humanPlayer.handCards[i]->pressSd = true;
							break;

					}
				}

			}
		}
	}
}
void Game::drawPosition() {

	sGameStartBK.setPosition(0, 0);			//设置绘制位置
	startBtn.setPosition(windowWidth * 0.7f, windowHeight * 0.3f);

	sGameFightBK.setPosition(0, 0);			//设定背景图位置

	sTurn.setPosition(540, 400);
	sPlayUI.setPosition(0, 700);

	turnEnd.setPosition(1275, 785);
	disCardBtn.setPosition(80, 840);

	//敌人
	enemyCarpente.shape.setPosition(680, 10);
	sEnemyUI.setPosition(635, 300);

	//对话框
	sDialog.setPosition(635, 200);
	yesBtn.setPosition(700, 350);
	noBtn.setPosition(875, 350);

	//输赢对话库
	gmOverReplayBtn.setPosition(830, 580);
	gmOvertoMenuBtn.setPosition(440, 580);
	gmLoseDialog.setPosition(420, 20);
	gmWinDialog.setPosition(420, 20);

}
void Game::Draw() {
	Vector2u size;
	size.x = windowWidth;
	size.y = windowHeight;
	window.setSize(size);
	switch (gameSceneState) {		//场景判断
		case SCENE_START:
			drawStart();
			break;
		case SCENE_FIGHT:
			drawFight();
			break;
		case SCENE_LOADING:
			drawLoading();
			break;
		default:
			break;
	}
}
void Game::initLoading() {
	tLoadBk.loadFromFile("./data/bg/loading.png");		//加载背景
	stringstream ss;
	for (int i = 0; i < 40; i++) {						//加载动画序列
		ss << "./data/anime/loading/load" << i << ".png";
		tLoads[i].loadFromFile(ss.str());
		ss.str("");
	}
	sLoadBk.setTexture(tLoadBk);
	anLoading.bindFrames(tLoads, sizeof(tLoads) / sizeof(tLoads[0]));	//绑定动画序列
	anLoading.setScale(0.5, 0.5);										//缩放
}
void Game::drawLoading() {
	sLoadBk.setPosition(0, 0);
	window.draw(sLoadBk);
	anLoading.setPosition(800, 400);
	anLoading.play();						//播放当前帧
	window.draw(anLoading);
	window.display();
}
void Game::drawStart() {					//初始场景
	window.clear();							//清屏
	window.draw(sGameStartBK);				//绘制
	window.draw(startBtn);
	window.display();
}
void Game::drawFight() {					//战斗场景
	window.clear();							//清屏
	window.draw(sGameFightBK);				//绘制背景图

	backToMenuBtn.setPosition(windowWidth * 0.9f, windowHeight * 0.05f);	//按百分比绘制	不要写到别的函数里去
	window.draw(backToMenuBtn);
	drawPlayer();
	drawEnemy();
	//绘制
	drawCard();
	drawDialog();

	window.display();						//展示屏幕
}
void Game::drawCard() {
	int pos = 0;					//记录绘制位置
	for (int i = 0; i < humanPlayer.handMaxNum; i++) {
		if (humanPlayer.handCards[i]->cardState != humanPlayer.handCards[i]->null) {
			//cout << "is " << i << endl;
			if (humanPlayer.handCards[i]->btnState == humanPlayer.handCards[i]->CLICK) {				//如果为按下的状态
				humanPlayer.handCards[i]->move(Mouse::getPosition(window));								//卡牌移动事件
			} else {
				humanPlayer.handCards[i]->setPosition((float)(700 + (pos - humanPlayer.handCardNums / 2) * 120), (float)480);								//默认位置
				humanPlayer.handCards[i]->originPosition = humanPlayer.handCards[i]->getPosition();		//设置默认位置
				humanPlayer.handCards[i]->originMouse = Mouse::getPosition(window);						//设定按下鼠标前鼠标的位置
			}
			window.draw(*humanPlayer.handCards[i]);
			if (pos < humanPlayer.handCardNums) {
				pos++;
			}
		}
	}
}
void Game::drawPlayer() {
	window.draw(sPlayUI);
	humanPlayer.drawState(&window);			//绘制人物属性
	humanPlayer.drawStatus(&window);			//绘制人物状态
	window.draw(turnEnd);
	window.draw(disCardBtn);
	cardManage.drawCardPoolNum(&window);
}
void Game::drawEnemy() {
	window.draw(enemyCarpente.shape);
	window.draw(sEnemyUI);
	enemyCarpente.drawState(&window);
	if (whosTurn == eEnemyTurn && !gameLose) {

		//int i = enemyCarpente.showCard(&window, &humanPlayer);
		//cardManage.useCard(&enemyCarpente, enemyCarpente.handCards[i], i, &humanPlayer);

		int j = enemyCarpente.showCard(&window, &humanPlayer, &cardManage);

		if (enemyCarpente.cardShow.cardState != enemyCarpente.cardShow.null) {
			enemyCarpente.cardShow.setPosition(enemyCarpente.cardPosition);
			window.draw(enemyCarpente.cardShow);
		}

		//cout << enemyCarpente.handCardNums;
	}
	enemyCarpente.drawStatus(&window);


}
void Game::drawDialog() {
	if (showBackDialog) {
		window.draw(sDialog);
		window.draw(yesBtn);
		window.draw(noBtn);
	}
	if (gameLose) {
		window.draw(gmLoseDialog);
		window.draw(gmOverReplayBtn);
		window.draw(gmOvertoMenuBtn);
	}
	if (gameWin) {
		window.draw(gmWinDialog);
	}
	hint.showHint(&window);
}

void Game::Logic() {
	switch (gameSceneState) {
		case SCENE_FIGHT:
			if (humanPlayer.hp <= 0) {
				gameLose = true;
				enemyCarpente.cardShow = enemyCarpente.nullCard;
			}
			if (enemyCarpente.hp <= 0) {
				gameWin = true;
			}
			humanPlayer.statusUpdate(&enemyCarpente, whosTurn, -1);
			enemyCarpente.statusUpdate(&humanPlayer, whosTurn, -1);
			//cout << enemyCarpente.getCardState << "and" << enemyCarpente.isTurn;
			if (whosTurn == eEnemyTurn) {
				humanPlayer.statusUpdate(&enemyCarpente, whosTurn, 1);
				if (enemyCarpente.getCardState) {
					if (cardManage.enemyCardPoolNum == 0) {
						for (int i = 0; i < sizeof(cardManage.enemyCards) / sizeof(cardManage.enemyCards[0]); i++) {			//遍历
							if (cardManage.enemyCards[i].cardState == cardManage.enemyCards[i].disCardPool) {					//如果是在弃牌堆就转移到抽牌堆中
								cardManage.enemyCards[i].cardState = cardManage.enemyCards[i].cardPool;
							}
						}
					}
					if (enemyCarpente.movePower < 2) {
						enemyCarpente.movePower = 2;
					}

					cardManage.getCard(&enemyCarpente, cardManage.enemyCards, enemyCarpente.getCardNum, sizeof(cardManage.enemyCards) / sizeof(cardManage.enemyCards[0]), -1);
					if (enemyCarpente.reduceGetCardNum > 0) {			//回复减少抽牌数
						enemyCarpente.getCardNum += enemyCarpente.reduceGetCardNum;
						enemyCarpente.reduceGetCardNum = 0;

					}
					//enemyCarpente.getCard(cardManage.enemyCards, enemyCarpente.getCardNum, sizeof(cardManage.enemyCards) / sizeof(cardManage.enemyCards[0]));				//抽牌  获取抽牌数量

					enemyCarpente.getCardState = false;
				}
				if (enemyCarpente.turnStart) {
					enemyCarpente.useCardNum = enemyCarpente.handCardNums;	//敌人可用牌数量
					enemyCarpente.turnStart = false;
				}
				if (enemyCarpente.useCardNum == 1) {
					enemyCarpente.lastCardClock.restart();													//启动计时器
				}
				if (enemyCarpente.useCardNum == 0) {
					if (enemyCarpente.lastCardClock.getElapsedTime().asMilliseconds() > 1600) {				//获取最后一张牌展示时间
						whosTurn = ePlayerTurn;																//玩家回合
						humanPlayer.getCardState = true;													//玩家可抽牌
						enemyCarpente.cardShow = enemyCarpente.nullCard;									//设定展示卡牌为null
						humanPlayer.turnStart = true;														//玩家回合开始
					}
				}

			} else if (whosTurn == ePlayerTurn && !gameLose) {

				enemyCarpente.statusUpdate(&humanPlayer, whosTurn, 1);
				if (humanPlayer.getCardState) {
					if (cardManage.playerCardPoolNum == 0) {																	//如果卡池抽完了
						for (int i = 0; i < sizeof(cardManage.playerCards) / sizeof(cardManage.playerCards[0]); i++) {			//遍历
							if (cardManage.playerCards[i].cardState == cardManage.playerCards[i].disCardPool) {					//如果是在弃牌堆就转移到抽牌堆中
								cardManage.playerCards[i].cardState = cardManage.playerCards[i].cardPool;
							}
						}
					}
					humanPlayer.mp /= 2;					//每回合魔法减半
					if (humanPlayer.movePower == 0) {		//每回合回复一点行动力
						humanPlayer.movePower = 1;
					}
					cardManage.getCard(&humanPlayer, cardManage.playerCards, humanPlayer.getCardNum, sizeof(cardManage.playerCards) / sizeof(cardManage.playerCards[0]), -1);
					if (humanPlayer.reduceGetCardNum > 0) {			//回复减少抽牌数
						humanPlayer.getCardNum += humanPlayer.reduceGetCardNum;
						humanPlayer.reduceGetCardNum = 0;
					}
					//humanPlayer.getCard(cardManage.playerCards, humanPlayer.getCardNum, sizeof(cardManage.playerCards) / sizeof(cardManage.playerCards[0]));				//抽牌  获取抽牌数量
					humanPlayer.getCardState = false;
					for (int i = 0; i < humanPlayer.handCardNums; i++) {
						humanPlayer.handCards[i]->setState(0);		//设置贴图为普通状态
					}
				}
				if (humanPlayer.turnStart) {
					humanPlayer.turnStart = false;
				}
			}

			break;
	}
}

void Game::Run() {
	Initial();
	while (window.isOpen()) {
		Input();
		Draw();
		Logic();
	}
}
