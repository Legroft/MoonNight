#include "hintText.h"
#include <iostream>
hintText::hintText() {
	textFont.loadFromFile("./data/font/simsun.ttc");
}
void hintText::setText(int type) {				//根据传入参数不同输出不同的文本
	hint.setFont(textFont);
	hint.setCharacterSize(40);
	switch (type) {
		case 0:
			hint.setString(L"魔力不足！");
			break;
		case 1:
			hint.setString(L"行动力不足！");
			break;
	}
	hint.setPosition(750, 400);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	hint.setFillColor(color);
	isShow = true;
	clock.restart();
}
void hintText::showHint(RenderWindow* window) {						//慢慢变透明
	if (isShow) {
		if (clock.getElapsedTime().asMilliseconds() > 500) {
			color.a = 255 - (clock.getElapsedTime().asMilliseconds() - 500) / 10;
			hint.setFillColor(color);
		}
		if (clock.getElapsedTime().asMilliseconds() < 3050) {
			window->draw(hint);
		} else {
			isShow = false;
		}
	}
}