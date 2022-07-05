#include "MyObject.h"
#include "MySphere.h"
#include "MyCube.h"
#include "MyPlayer.h"
#include <memory>
#include <cassert>
void MyObject::initSprite(std::string aFile)
{
	if (!texture.loadFromFile("images/" + aFile))
		return;
	sprite.setTexture(texture);
}



std::shared_ptr<MyObject> MyObject::createObject(Object_ID id)
{
	std::shared_ptr<MyObject> p = nullptr;
	switch (id)
	{
	case MyObject::Ball:
		p = std::make_shared<MySphere>();
		break;
	case MyObject::Brick:
		p = std::make_shared<MyCube>();
		break;
	case MyObject::Player:
		p = std::make_shared<MyPlayer>();
		break;
	default:
		assert(false && "id nevalidnoe");
	}
	return p;
}

void MyObject::Update()
{
}

void MyObject::move(Vector2f& offset)
{
	sprite.move(offset);
	fRect.left += offset.x;
	fRect.top += offset.y;	
}

void MyObject::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void MyObject::setPosition(Vector2f& pos)
{
	sprite.setPosition(pos);
	fRect = FloatRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getTextureRect().width, sprite.getTextureRect().height);
}

void MyObject::setPosition(float x, float y)
{
	sprite.setPosition(x , y);
	fRect = FloatRect(sprite.getPosition().x, sprite.getPosition().y, sprite.getTextureRect().width, sprite.getTextureRect().height);
}

void MyObject::checkCollisionWithObject(std::shared_ptr<MyObject>& object)
{

}

MyObject::MyObject() : position(Vector2f(0.f, 0.f)), state(LifeState::NORMAL), fRect(FloatRect()) {}

MyObject::MyObject(std::string path)
{
	initSprite(std::move(path));
}

MyObject::~MyObject()
{
}

