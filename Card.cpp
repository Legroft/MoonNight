#include "Card.h"
#include<iostream>
using namespace std;
void Card::move(Vector2i mouse) {
	setPosition(originPosition.x + mouse.x - originMouse.x, originPosition.y + mouse.y - originMouse.y);
}
