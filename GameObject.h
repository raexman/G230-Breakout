#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <stdio.h>
#include <string>

class GameObject
{
protected:
	//Variables.
	float deltaTime;
	sf::RenderWindow *window;
	sf::RectangleShape view;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Texture texture;
	bool isActive;
	int HP;

public:
	//Variables.
	bool inContact;

	//Functions.
	GameObject(sf::RenderWindow *window, sf::Texture texture);
	GameObject(sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture);
	GameObject(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::RenderWindow *window, sf::Texture texture);
	~GameObject();
	//States.
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void Collided(sf::Vector2f point);
	virtual bool Dead();
	//Collision.
	virtual bool CheckCollisionWith(GameObject *other);
	virtual sf::Vector2f GetPointOfContact(GameObject *other);
	//Getters/Setters
	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition();
	virtual void SetSize(float x, float y);
	virtual sf::Vector2f GetSize();
};

