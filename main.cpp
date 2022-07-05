//copyright @mijitsu  :pog 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyObject.h"
#include <cmath>
#include <ctime>
#include <vector>
#include <list>
#include <memory>
using namespace sf; 


void createBricks(std::list<std::shared_ptr<MyObject>>& list, int bricksCount);
int main()
{
	enum { NORMAL, DEAD };
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	bool isPlaying = false;

	ContextSettings settings;
	settings.antialiasingLevel = 8;
	const int gameWidth = 1024;
	const int gameHeight = 768;
	RenderWindow window(VideoMode(gameWidth, gameHeight, 32), "2D Sumulation", Style::Titlebar | Style::Close, settings);
	window.setVerticalSyncEnabled(true); //или таймер ...https://habr.com/ru/post/442528/ 
	window.setFramerateLimit(60);
	auto bg = std::make_unique<MyObject>("bg.jpg");
	bg->setPosition(0, 0);
	std::list<std::shared_ptr<MyObject>> objects;

	auto player = MyObject::createObject(MyObject::Object_ID::Player);
	player->setPosition(gameWidth/2 - player->getSprite().getTextureRect().width/2, gameHeight - 100);
	objects.push_back(player);

	auto ball = MyObject::createObject(MyObject::Object_ID::Ball);
	ball->setPosition(gameWidth / 2 - ball->getSprite().getTextureRect().width / 2, gameHeight / 2 - ball->getSprite().getTextureRect().height / 2);
	objects.push_back(ball);
	
	int bricksCount = 30;
	createBricks(objects, bricksCount);

	while (window.isOpen()) {
		sf::Event event;		
			while (window.pollEvent(event)) {
				if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
					window.close();
					break;
				}
			}
			window.clear(sf::Color(0, 0, 0));
			bg->Draw(window);
			auto remove = objects.end();
			for (auto it = objects.begin(); it != objects.end(); ++it) {
				if ((*it)->getState() == DEAD) {
					remove = it;
				}
				else {
					(*it)->Draw(window);
					(*it)->Update();
					ball->checkCollisionWithObject(*it);					
				}
				if (ball->getState() == DEAD) {
					window.close();
				}
			}
			if (remove != objects.end())
				objects.erase(remove);
			window.display();
	}
	return EXIT_SUCCESS;	
}


void createBricks(std::list<std::shared_ptr<MyObject>>& list, int bricksCount)
{
	float gapX = 85;
	float gapY = 30;
	for (int i = 0, k = 0; i < bricksCount; ++i, ++k) {
		auto cube = MyObject::createObject(MyObject::Brick);
		if (k >= 10) {
			gapY += 45;
			k = 0;
		}
		cube->setPosition(100 + gapX*k, gapY);
		list.push_back(move(cube));
	}
}