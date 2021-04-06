#include<iostream>
#include"Game.h"
#include <thread>
using namespace std;
Game game;
int main() {
	thread thLoad(&Game::loadMediaData, &game);			//创建一个线程加载游戏素材
	thLoad.detach();									//独立于主线程运行
	game.Run();
	return 0;
}