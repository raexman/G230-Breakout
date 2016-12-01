#include "Bar.h"



Bar::Bar(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture):MovableGameObject(size, position, window, texture)
{
	Init();
}

void Bar::Init()
{
	speed.x = 500;
	speed.y = 500;
	isMoving = true;
	view.setOutlineColor(sf::Color::Black);
	view.setOutlineThickness(2);
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
	buffer.loadFromFile("bumper.wav");
	sound.setBuffer(buffer);
	sound.play();
}
