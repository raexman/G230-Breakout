#pragma once
#include "GameObject.h"
class MovableGameObject :
	public GameObject
{
protected:
	sf::Vector2f speed;
	sf::Vector2f direction;
	bool topWall;
	bool rightWall;
	bool bottomWall;
	bool leftWall;
	bool isMoving;

public:
	MovableGameObject(sf::RenderWindow *window, sf::Texture texture);
	MovableGameObject(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture);
	MovableGameObject(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::RenderWindow *window, sf::Texture texture);
	~MovableGameObject();
	virtual void Update(float deltaTime);
	virtual void Collided(sf::Vector2f point);

	virtual void AddSpeed(float x, float y);
	virtual void SetSpeed(float x, float y);
	virtual sf::Vector2f GetSpeed();

	virtual void StartMoving();
	virtual void StopMoving();
	virtual void Move();
	virtual void MoveTo(float x, float y);

	virtual void ChangeDirection(bool onX, bool onY);
	virtual void SetDirection(float x, float y);
	
	virtual void SetWalls(bool top, bool right, bool bottom, bool left);

	virtual bool CheckCollisionWith(GameObject *other);

};

