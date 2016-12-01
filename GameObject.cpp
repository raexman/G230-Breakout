#include "GameObject.h"

GameObject::GameObject(sf::RenderWindow *window, sf::Texture texture)
{
	isActive = true;
	this->window = window;
	this->view.setPosition(0,0);
	this->view.setSize(sf::Vector2f(100, 100));
	this->view.setFillColor(sf::Color::White);
	this->texture = texture;

	Init();
}

GameObject::GameObject(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::RenderWindow *window, sf::Texture texture)
{
	isActive = true;

	this->window = window;
	this->view.setPosition(position);
	this->view.setSize(size);
	this->view.setFillColor(color);
	this->texture = texture;

	Init();
}

GameObject::GameObject(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture)
{
	isActive = true;

	this->window = window;
	this->view.setPosition(position);
	this->view.setSize(size);
	this->view.setFillColor(sf::Color::White);
	this->texture = texture;

	Init();

}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
	HP = 1;
	this->view.setTexture(&texture);
	Draw();
}

void GameObject::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	
	if (!isActive) return;

	Draw();
}

void GameObject::Draw()
{
	window->draw(view);
}

bool GameObject::CheckCollisionWith(GameObject *other)
{

	sf::Vector2f pointOfContact = GetPointOfContact(other);
	if (pointOfContact.x >= -1 && pointOfContact.x <= 1)
	{
		return true;
	}
	
	return false;
}

sf::Vector2f GameObject::GetPointOfContact(GameObject *other)
{
	//The point of contact to be returned.
	sf::Vector2f pointOfContact(-2, -2);

	//Get this object'ss position.
	sf::Vector2f thisStartPosition(this->GetPosition());
	sf::Vector2f thisSize(this->GetSize());
	sf::Vector2f thisEndPosition(thisStartPosition.x + thisSize.x, thisStartPosition.y + thisSize.y);
	sf::Vector2f thisCenterPoint(thisStartPosition.x + thisSize.x * 0.5f, thisStartPosition.y + thisSize.y * 0.5f);

	//Get the other object's position.
	sf::Vector2f otherStartPosition(other->GetPosition());
	sf::Vector2f otherSize(other->GetSize());
	sf::Vector2f otherEndPosition(otherStartPosition.x + otherSize.x, otherStartPosition.y + otherSize.y);
	sf::Vector2f otherCenterPoint(otherStartPosition.x + otherSize.x * 0.5f, otherStartPosition.y + otherSize.y * 0.5f);

	//Check if current object envelopes colliding object.
	bool overlapTop = (thisStartPosition.y - otherEndPosition.y) < 0.0f && (thisStartPosition.y - otherEndPosition.y) > (otherSize.y * -1);
	bool overlapRight = (thisEndPosition.x - otherStartPosition.x) > 0.0f && (thisEndPosition.x - otherStartPosition.x) < otherSize.x;
	bool overlapBottom = (thisEndPosition.y - otherStartPosition.y) > 0.0f && (thisEndPosition.y - otherStartPosition.y) < otherSize.y;
	bool overlapLeft = (thisStartPosition.x - otherEndPosition.x) < 0.0f && (thisStartPosition.x - otherEndPosition.x) > (otherSize.x * -1);

	//It is.
	if ((overlapTop || overlapBottom) && (overlapLeft || overlapRight))
	{
		float verticalDistance = thisCenterPoint.y - otherCenterPoint.y;
		float horizontalDistance = thisCenterPoint.x - otherCenterPoint.x;

		sf::Vector2f base((thisSize.x + otherSize.x) * 0.5f, (thisSize.y + otherSize.y) * 0.5f);
		
		//There's a greater vertical distance.
		pointOfContact.x = horizontalDistance / base.x;
		pointOfContact.y = verticalDistance / base.y;
	}

	return pointOfContact;
}
void GameObject::Collided(sf::Vector2f point)
{

}
void GameObject::SetPosition(float x, float y)
{
	this->view.setPosition(x, y);
}

sf::Vector2f GameObject::GetPosition()
{
	return this->view.getPosition();
}
void GameObject::SetSize(float x, float y)
{
	this->view.setSize(sf::Vector2f(x, y));
}

sf::Vector2f GameObject::GetSize()
{
	return this->view.getSize();
}

bool GameObject::Dead()
{
	return HP < 1;
}