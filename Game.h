#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <sstream>
#include "Button.h"
#include "Card.h"
#include "Animation.h"
#include "Enemy.h"
#include "cardManager.h"
#include "hintText.h"
#include "playerManager.h"
using namespace sf;
enum gameSceneState {		//不同的游戏场景
	SCENE_START, SCENE_FIGHT, SCENE_LOADING
};
enum enemyName {					//敌人的名字
	null, carpente, prisone
};
enum e_whosTurn {					//谁的回合
	ePlayerTurn, eEnemyTurn
};
class Game {
public:
	sf::RenderWindow window;    //定义游戏窗口
	Uint32 windowStyle = Style::Close | Style::Titlebar;
	Game();
	int windowWidth, windowHeight;						//场景宽，高
	int gameSceneState;									//场景状态
	bool gameOver, gameQuit;
	bool startMusicState, fightMusicState;						//音乐播放状态
	Texture tGameStartBK, tGameFightBK, tStartBtnNormal, tStartBtnHover, tStartBtnClick;		//加载纹理
	Texture tbackToMenuNormal, tbackToMenuHover, tbackToMenuClick;
	Sprite sGameStartBK, sGameFightBK, sStartBtn;		//精灵
	Music gameStartMusic, fightMusic;								//音乐
	SoundBuffer victorSb, defeatSb, attackSb, hoverSb, pressSb, releaseSb;  //音效缓冲
	Sound victorSd, defeatSd, attackSd, hoverSd, pressSd, releaseSd;		//音效
	Button startBtn, backToMenuBtn;									//自定义button类

	Player humanPlayer;									//人类玩家

	int enemyName;							//存放敌人序号
	Enemy enemyCarpente, enemyPrisone;						//初始化敌人

	Texture tLoadBk, tLoads[40];				//加载界面背景，加载动画序列
	Animation anLoading;						//加载动画
	Sprite sLoadBk;								//加载界面背景

	Texture tPlayUI, tEnemy[30], tEnemyUI, tNums[10], tDialog, tTurn;
	Sprite sPlayUI, sEnemy[30], sEnemyUI, sNums[10], sDialog, sTurn;
	Vector2i cardOffset;					//设定卡牌偏移量

	Button turnEnd, disCardBtn;					//回合结束按钮,弃牌按钮
	Texture turnEndNormal, turnEndHover, turnEndCllick, tDisCardBtn, tDisCardBtnHover;	//回合

	Texture tYesNormal, tYesHover, tYesClick, tNoNormal, tNoHover, tNoClick;		// 是 否
	Button yesBtn, noBtn;
	bool showBackDialog = false;				//是否显示返回主界面对话框

	int whosTurn = 0;				//默认玩家回合

	Sprite gmLoseDialog, gmWinDialog;
	Texture tgmOverToMenuBtn, tgmOverToMenuBtnHover, tgmOverToMenuBtnClick;
	Texture tgmOverReplayBtn, tgmOverReplayBtnHover, tgmOverReplayBtnClick;
	Texture tgameLoseDialog, tgameWinDialog;
	Button gmOvertoMenuBtn, gmOverReplayBtn;
	bool gameLose = false, gameWin = false;

	hintText hint;			//提示信息
	bool showHint = false;			//是否提示

	cardManager cardManage;			//卡牌管理
	playerManager playerManager;	//玩家管理

	void Run();				//游戏运行

	void Initial();			//初始化
	void initFightData();	//初始化战斗数据
	void initMusic();		//初始化音乐
	void initLoading();	//初始化加载界面

	void loadMediaData();	//加载媒体
	void loadMusic();		//加载音乐
	void loadCards();		//加载卡牌
	void loadEnemy();		//加载敌人

	void Input();			//交互
	void startInput(Vector2i, Event);		//初始场景的交互
	void fightInput(Vector2i, Event);		//战斗场景的交互

	void Draw();			//绘制不同的内容
	void drawPosition();	//设置绘制位置
	void drawStart();		//初始场景
	void drawFight();		//战斗场景
	void drawLoading();     //游戏加载界面
	void drawCard();
	void drawPlayer();		//玩家UI绘制
	void drawEnemy();       //敌人UI绘制
	void drawDialog();		//是否绘制对话框

	void Logic();

};