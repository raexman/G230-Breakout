#pragma once
#include "MovableGameObject.h"
class Bar :
	public MovableGameObject
{
public:
	Bar(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window);
	~Bar();
	void Update(float deltaTime);
	void Control();
	void Init();
	void Collided(sf::Vector2f point);
};

