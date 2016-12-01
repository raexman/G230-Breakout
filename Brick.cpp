#include "Brick.h"
#include <SFML\Graphics.hpp>


Brick::Brick(int HP, sf::RenderWindow *window, sf::Texture texture) :GameObject(window, texture)
{
	this->HP = HP;
	Init();
}

Brick::Brick(int HP, sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::RenderWindow *window, sf::Texture texture) : GameObject(size, position, color, window, texture)
{
	this->HP = HP;
	Init();
}

Brick::Brick(int HP, sf::Vector2f size, sf::Vector2f position, sf::RenderWindow *window, sf::Texture texture) : GameObject(size, position, window, texture)
{
	this->HP = HP;
	Init();
}

Brick::~Brick()
{
}

void Brick::Init()
{
	sf::Texture destroyed;
	sf::Texture damaged;

	destroyed.loadFromFile("brick_destroyed.png");
	damaged.loadFromFile("brick_damaged.png");

	textures.push_back(destroyed);
	textures.push_back(destroyed);
	textures.push_back(texture);

	view.setOutlineColor(sf::Color::Black);
	view.setOutlineThickness(2);
}
void Brick::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	if (!isActive || isInvisible) return;

	Draw();
}
void Brick::Collided(sf::Vector2f point)
{
	//std::cout << "Collided!" << std::endl;
	if(!isInvincible)
		Hurt();
}

void Brick::Hurt(int damage)
{
	HP-=damage;

	view.setTexture(&textures[HP]);
	view.setFillColor(sf::Color::Red);

	//view.setTextureRect(sf::IntRect(100, 100, view.getSize().x * 20, view.getSize().y * 20));
}

bool Brick::Dead()
{
	return HP < 1;
}