#pragma once
#include "GameObject.h"
class Brick :
	public GameObject
{
public:
	Brick(sf::RenderWindow *window);
	Brick(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window);
	Brick(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::RenderWindow *window);
	~Brick();
	void Collided(sf::Vector2f point);
	void Init();
	bool Dead();
	void Hurt();
};

