#include "Brick.h"
#include <SFML\Graphics.hpp>


Brick::Brick(sf::RenderWindow *window) :GameObject(window)
{
	HP = 2;
}

Brick::Brick(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::RenderWindow *window) : GameObject(size, position, color, window)
{
	HP = 2;
}

Brick::Brick(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window) : GameObject(size, position, window)
{
	HP = 2;
}

Brick::~Brick()
{

}

void Brick::Init()
{
}

void Brick::Collided(sf::Vector2f point)
{
	Hurt();
}

void Brick::Hurt()
{
	HP--;
	view.setFillColor(sf::Color(view.getFillColor().toInteger()/2));
}

bool Brick::Dead()
{
	return HP < 1;
}