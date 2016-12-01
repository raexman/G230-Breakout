#include "Ball.h"



Ball::Ball(sf::Vector2f speed, int lives, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture):MovableGameObject(size, position, window, texture)
{
	this->speed = speed;
	this->HP = lives;
	SetWalls(true, true, false, true);
	Init();
}
void Ball::Init()
{
	isResting = true;
	this->view.setTexture(&texture);
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
		Hurt();
		if (Dead()){
			//End game.
			isActive = false;
		}
		else
		{
			std::string soundFx = "falling.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}

	if (isResting)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			isResting = false;
			isMoving = true;
			direction.x = 0;
			direction.y = -1;
		}
	}
	Draw();

}

void Ball::Hurt(int damage)
{
	HP -= damage;
}

Ball::~Ball()
{
}
bool Ball::CheckCollisionWith(GameObject *other, bool drillable)
{

	sf::Vector2f pointOfContact = GetPointOfContact(other);
	if (!inContact)
	{
		if (pointOfContact.x >= -1 && pointOfContact.x <= 1 && pointOfContact.y >= -1 && pointOfContact.y <= 1)
		{

			other->Collided(pointOfContact);
			if (!drillable || !isDrilling) 
				this->Collided(pointOfContact);
			inContact = true;

			return true;
		}
	}
	else
	{
		if (pointOfContact.x < -1 || pointOfContact.x > 1 || pointOfContact.y < -1 || pointOfContact.y > 1)
		{
			inContact = false;
		}
	}

	return false;
}

void Ball::Collided(sf::Vector2f point)
{
	int margin = 10;
	SetDirection(point.x, point.y);
	AddSpeed(5 * abs(point.x), 5 * abs(point.y));
	this->MoveTo(margin * direction.x, margin * direction.y);

	std::cout << "SPEED X: " << speed.x << " | Y: " << speed.y << std::endl;

}

int Ball::GetLives()
{
	return HP;
}