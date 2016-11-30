#pragma once
#include "MovableGameObject.h"
class Ball :
	public MovableGameObject
{
public:
	bool isResting;
	Ball(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window);
	~Ball();
	void Init();
	void Update(float deltaTime);
	void Collided(sf::Vector2f point);
};

