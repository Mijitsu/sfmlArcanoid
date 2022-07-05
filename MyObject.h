//copyright @mijitsu  :pog 
#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class MyObject {	
protected:
	enum LifeState {
		NORMAL,
		DEAD
	};
	Texture texture;
	Sprite sprite;
	LifeState state;
	void initSprite(std::string aFile);
	FloatRect fRect;
	Vector2f position;
	std::string id;
public:
	enum Object_ID {
		Ball,
		Brick,
		Player
	};
	static std::shared_ptr<MyObject> createObject(Object_ID id);

	MyObject();
	MyObject(std::string path);
	virtual ~MyObject();

	virtual void Update();
	virtual void move(Vector2f& offset);
	virtual void setPosition(Vector2f& pos);
	virtual void setPosition(float x, float y);
	virtual void checkCollisionWithObject(std::shared_ptr<MyObject>& object);

	void Draw(RenderWindow& window);
	void changeState(LifeState pState) { state = pState;}
	const LifeState &getState() const & { return state; };
	LifeState getState()&& { return std::move(state); }

	const Sprite& getSprite() const& { return sprite; }
	Sprite getSprite()&& { return std::move(sprite); }

	const std::string& getId() const& { return id; }
	std::string getId()&& { return std::move(id); }
	
	const FloatRect &getFRect() const & { return fRect; }
	FloatRect getFRect()&& { return std::move(fRect); }
};