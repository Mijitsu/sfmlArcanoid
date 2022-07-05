#include "MySphere.h"
#include <SFML/Audio.hpp>
#include <cmath>
using namespace sf;
MySphere::MySphere()
{
	initSprite("sphere.png");
	float sphereRadius = 12.5f;
	sphereRect = CircleShape(sphereRadius);
	const float pi = 3.14159f;
	sphereRect.setOrigin(sphereRadius / 2, sphereRadius / 2);
	sprite.setTextureRect(IntRect(0, 0, sphereRadius*2, sphereRadius*2));
	sprite.setOrigin(sphereRect.getOrigin());
	angle = rand() % 2 ? -0.9 : -2.3;
	speed = 4;
	direction = Vector2f(1, 1);	
	if (ballSoundBuffer.loadFromFile("resources/ball.wav")) {
		ballSound = Sound(ballSoundBuffer);
	}	
	id = "ball";
}

MySphere::~MySphere()
{

}

void MySphere::Update()
{
	auto offset = Vector2f(std::cos(angle) * speed * direction.x, std::sin(angle) * speed * direction.y);
	move(offset);
	if (sphereRect.getPosition().x + sphereRect.getRadius() >= 1024) {		
		ballSound.play();
		direction.x*= -1;		
	}
	if (sphereRect.getPosition().x <= 0) {
		ballSound.play();
		direction.x *= -1;
	}
	if (sphereRect.getPosition().y <= 0) {
		ballSound.play();
		direction.y *= -1;
	}
	if (sphereRect.getPosition().y + sphereRect.getRadius() >= 768) {
		state = MyObject::LifeState::DEAD;
	}

}


void MySphere::move(sf::Vector2f& offset)
{
	sprite.move(offset);
	sphereRect.move(offset);
}

void MySphere::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
	sphereRect.setPosition(x, y);
}

void MySphere::checkCollisionWithObject(std::shared_ptr<MyObject>& object)
{
	if (object->getId() == "player") {
		if (sphereRect.getGlobalBounds().intersects(object->getFRect())) {
			direction.y *= -1;
			ballSound.play();
		}
	}
	if (object->getId() == "brick") {
		if (sphereRect.getGlobalBounds().intersects(object->getFRect())) {
			direction.y *= -1;
			ballSound.play();
			object->changeState(MyObject::LifeState::DEAD);
		}
	}
}
