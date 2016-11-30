#include "Ball.h"



Ball::Ball(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window):MovableGameObject(size, position, window)
{
	SetWalls(true, true, false, true);
	Init();
}
void Ball::Init()
{
	isResting = true;
}

void Ball::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	if (!isActive) return;

	if (isMoving)
	{
		Move();
	}
	if (GetPosition().y > window->getSize().y)
	{
		//Reset ball;
		isResting = true;
	}

	if (isResting)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			isResting = false;
			isMoving = true;
			speed.x = 200;
			speed.y = 200;
			direction.x = 0;
			direction.y = -1;
		}
	}
	Draw();

}

Ball::~Ball()
{
}

void Ball::Collided(sf::Vector2f point)
{
	int margin = 10;
	SetDirection(point.x, point.y);
	AddSpeed(10 * abs(point.x), 10 * abs(point.y));
	this->MoveTo(margin * direction.x, margin * direction.y);

	std::cout << "SPEED X: " << speed.x << " | Y: " << speed.y << std::endl;
}

