#include "MovableGameObject.h"

MovableGameObject::MovableGameObject(sf::RenderWindow *window, sf::Texture texture):GameObject(window, texture)
{
	SetWalls(true, true, true, true);
}

MovableGameObject::MovableGameObject(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::RenderWindow *window, sf::Texture texture):GameObject(size, position, color, window, texture)
{
	SetWalls(true, true, true, true);
}

MovableGameObject::MovableGameObject(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture):GameObject(size, position, window, texture)
{
	SetWalls(true, true, true, true);
}

MovableGameObject::~MovableGameObject()
{
	SetWalls(true, true, true, true);
}


void MovableGameObject::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	if (!isActive) return;

	if (isMoving)
	{
		Move();
	}
	Draw();
}

void MovableGameObject::AddSpeed(float x, float y) {
	this->speed.x += x;
	this->speed.y += y;
}
void MovableGameObject::SetSpeed(float x, float y) {
	this->speed.x = x;
	this->speed.y = y;
}
sf::Vector2f MovableGameObject::GetSpeed() {
	return speed;
}
void MovableGameObject::Move(){
	
	if (topWall)
	{
		if (view.getPosition().y <= 0)
		{
			SetDirection(-2, 1);
			std::string soundFx = "bounce.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}
	if (rightWall)
	{
		if (view.getPosition().x + view.getSize().x >= window->getSize().x)
		{
			SetDirection(-1, -2);
			std::string soundFx = "bounce.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}
	if (bottomWall)
	{
		if (view.getPosition().y + view.getSize().y >= window->getSize().y)
		{
			SetDirection(-2, -1);
			std::string soundFx = "bounce.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}
	if (leftWall)
	{
		if (view.getPosition().x <= 0)
		{
			SetDirection(1, -2);
			std::string soundFx = "bounce.wav";
			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}

	//Automatically move object.
	sf::Vector2f distance(speed.x * direction.x * deltaTime, speed.y * direction.y * deltaTime);
	this->view.move(distance);

}
void MovableGameObject::MoveTo(float x, float y) {
	this->view.move(x, y);
}
void MovableGameObject::ChangeDirection(bool onX, bool onY) {
	
	if (onX)
	{
		this->direction.x *= -1;
	}
	if (onY)
	{
		this->direction.y *= -1;
	}
}
void MovableGameObject::SetDirection(float x, float y) {
	if(x > -2)
		this->direction.x = x;
	if(y > -2)
		this->direction.y = y;
}
void MovableGameObject::SetWalls(bool top, bool right, bool bottom, bool left){

	this->topWall = top;
	this->rightWall = right;
	this->bottomWall = bottom;
	this->leftWall = left;

}
void MovableGameObject::StartMoving() {
	isMoving = true;
}
void MovableGameObject::StopMoving() {
	isMoving = false;
}

bool MovableGameObject::CheckCollisionWith(GameObject *other)
{

	sf::Vector2f pointOfContact = GetPointOfContact(other);
	if (!inContact)
	{
		if (pointOfContact.x >= -1 && pointOfContact.x <= 1 && pointOfContact.y >= -1 && pointOfContact.y <= 1)
		{
			
			other->Collided(pointOfContact);
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

void MovableGameObject::Collided(sf::Vector2f point)
{
	int margin = 10;
	SetDirection(point.x, point.y);
	//this->MoveTo(margin * direction.x, margin * direction.y);
}
