//copyright @mijitsu  :pog 
#pragma once
#include "MyObject.h";
#include "SFML/Audio.hpp"

class MySphere : public MyObject {
private:
	sf::CircleShape sphereRect;
	float angle;
	float speed;
	sf::Sound ballSound;
	sf::SoundBuffer ballSoundBuffer;
	Vector2f direction;
public:
	MySphere();
	~MySphere();
	virtual void Update() override;
	virtual void move(sf::Vector2f&) override;
	virtual void setPosition(float x, float y) override;
	void checkCollisionWithObject(std::shared_ptr<MyObject>& object) override;
	const sf::CircleShape &GetSphereRefRect() const & { return sphereRect; }
	sf::CircleShape GetSphereRefRect() && { return std::move(sphereRect); }
};