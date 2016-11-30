#include "Bar.h"



Bar::Bar(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window):MovableGameObject(size, position, window)
{
	Init();
}

void Bar::Init()
{
	speed.x = 500;
	speed.y = 500;
	isMoving = true;
}

Bar::~Bar()
{
}

void Bar::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	//if (!isActive) return;

	Control();
	Move();
	Draw();
}

void Bar::Control()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		direction.x = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		direction.x = 1;
	}
	else
	{
		direction.x = 0;
	}
}

void Bar::Collided(sf::Vector2f point)
{

}
