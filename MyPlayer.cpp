#include "MyPlayer.h"

MyPlayer::MyPlayer()
{
	initSprite("player.png");
	speed = 10.f;
	id = "player";
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::Update()
{
	auto offset = Vector2f(speed, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && fRect.left >= 0) {
		offset.x *= -1;
		move(offset);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (fRect.left + fRect.width)  <= 1024) {
		move(offset);
	}
}
