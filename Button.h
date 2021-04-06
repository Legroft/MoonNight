#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button :public Sprite {   //继承SFML的Sprite类
public:
	Texture tNormal;			//三种不同状态的纹理
	Texture tHover;
	Texture tClick;
	bool hoverSd = true;				//是否播放音效
	bool pressSd = true;

	enum BtnState {
		NORMAL, HOVER, CLICK, RELEASE
	};
	int btnState = NORMAL;										//按钮状态
	int checkMouse(Vector2i, Event);					//检查鼠标状态
	void setTextures(Texture, Texture);					//加载纹理，两种状态
	void setTextures(Texture, Texture, Texture);		//加载纹理，三种状态
	void setState(int);									//设置按钮状态
	void offset(float, float);
	bool mouseContain(Vector2i);						//检测鼠标是否在精灵内
	bool mouseContain(Vector2i, int, int);						//检测鼠标是否在精灵内
	bool mouseContainf(Vector2f, float, float);						//检测鼠标是否在精灵内
	int checkMouse(Vector2i, Event, int, int);					//检查鼠标状态
};