#pragma once
#include "GameObject.h"
class Brick :
	public GameObject
{
protected:
	std::vector<sf::Texture> textures;
public:
	bool isInvincible;
	bool isInvisible;
	std::string PowerUp;
	Brick(int HP, sf::RenderWindow *window, sf::Texture texture);
	Brick(int HP, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture);
	Brick(int HP, sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::RenderWindow *window, sf::Texture texture);
	~Brick();
	void Collided(sf::Vector2f point);
	void Init();
	void Update(float deltaTime);
	bool Dead();
	void Hurt(int damage = 1);
};

