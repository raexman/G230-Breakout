// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <memory>
#include "Ball.h"
#include "MovableGameObject.h"
#include "Brick.h"
#include "Bar.h"

void PlayMusic();
void LoadBackground();
void Init();
void Menu();
void PlayerVsCPUMatch();
void PlayerVsPlayerMatch();
void FourWayMatch();
void Victory();
void Exit();

using namespace std;

vector<unique_ptr<GameObject>> bricks;
float deltaTime;
bool isPlaying;
bool isMenu;
int matchMode;
float maxScore = 4;
const int numOfPlayers = 2;

sf::Font font;
sf::RenderWindow *window;
sf::Sprite background;
sf::Texture bgTexture;

int margin = 10;
int rows = 6;
int cols = 8;

int main()
{
	font.loadFromFile("AmericanCaptain.ttf");

	window = new sf::RenderWindow(sf::VideoMode(800, 600), "PingPong!");
	bgTexture.loadFromFile("background.jpg");
	background.setTexture(bgTexture);

	Init();

	Exit();
	system("pause");
	return 0;

}
void Init()
{

	Menu();

}

void Menu()
{
	bool optionChosen = false;
	int mode = 0;

	while (window->isOpen() && !optionChosen)
	{
		sf::Text title;
		title.setFont(font);
		title.setString("ULTRA PONG 20XX");
		title.setCharacterSize(125);
		title.setFillColor(sf::Color::White);
		title.setPosition((window->getSize().x - title.getLocalBounds().width) * 0.5, 100);

		sf::Text menu;
		menu.setFont(font);
		menu.setString("[1] Player vs CPU \n[2] Player vs Player\n[3] 4-Player Game");
		menu.setCharacterSize(48);
		menu.setFillColor(sf::Color::White);
		menu.setPosition((window->getSize().x - menu.getLocalBounds().width) * 0.5, title.getPosition().y + title.getGlobalBounds().height + 50);

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return;
			}
		}

		window->clear();
		window->draw(background);
		window->draw(menu);
		window->draw(title);
		window->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			mode = 1;
			optionChosen = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			mode = 2;
			optionChosen = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		{
			mode = 3;
			optionChosen = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		{
			mode = 4;
			optionChosen = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			mode = 0;
			optionChosen = true;
		}
	}
	switch (mode)
	{
		case 0: Exit();
		case 1: PlayerVsCPUMatch(); break;
		default:break;
	}
}

void CreateBricks()
{
	int brickWidth = (window->getSize().x - margin * (cols + 1)) / cols;
	int brickHeight = brickWidth * 0.4;

	for (int i = 0; i < rows*cols; i++)
	{
		Brick *go = new Brick(sf::Vector2f(brickWidth, brickHeight), sf::Vector2f(i%cols * (brickWidth + margin) + margin, (i /cols) * (brickHeight + margin) + margin ), sf::Color::Blue, window);
		bricks.push_back(unique_ptr<GameObject>(go));
	}
}
void CheckCollisions(GameObject *go)
{
	for (int i = 0; i < bricks.size(); i++)
	{
		GameObject *br = bricks[i].get();
		bool hasCollided = go->CheckCollisionWith(br);
		if (hasCollided && br->Dead())
		{
			bricks.erase(bricks.begin() + i);
			continue;
		}
	}
}
void PlayerVsCPUMatch()
{
	/*
	MovableGameObject mover(sf::Vector2f(100, 100), sf::Vector2f((window->getSize().x - 50)*0.5f, (window->getSize().y - 50)*0.5f), sf::Color::Yellow, window);
	mover.StartMoving();
	mover.SetSpeed(660, 660);
	mover.SetDirection(1, 1);

	MovableGameObject mover2(sf::Vector2f(20, 20), sf::Vector2f(0, (window->getSize().y - 50)*0.5f), sf::Color::Magenta, window);
	mover2.StartMoving();
	mover2.SetSpeed(500, 500);
	mover2.SetDirection(-1, -1);
	*/
	
	Bar bar(sf::Vector2f(100, 40), sf::Vector2f((window->getSize().x - 50) * 0.5f, window->getSize().y - 80), window);
	Ball ball(sf::Vector2f(20,20), sf::Vector2f(0,0), window);
	CreateBricks();

	sf::Clock clock;
	isPlaying = true;
	
	while (window->isOpen() && isPlaying)
	{
		window->setActive(true);
		deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return;
			}
		}

		//Draw scene.
		window->clear();
		
		//Draw window graphics.
		window->draw(background);
		
		//Draw object graphics.
		//mover.Update(deltaTime);
		//mover2.Update(deltaTime);
		bar.Update(deltaTime);

		//Check ball status.
		if (ball.isResting)
		{
			//Keep ball
			float ballX = bar.GetPosition().x + (bar.GetSize().x - ball.GetSize().x) * 0.5f;
			float ballY = bar.GetPosition().y - ball.GetSize().y;
			ball.SetPosition(ballX, ballY);
		}

		ball.Update(deltaTime);
		
		for (int i = 0; i < bricks.size(); i++)
		{
			bricks[i]->Update(deltaTime);
		}


		
		//Check collisions.
		CheckCollisions(&ball);
		ball.CheckCollisionWith(&bar);
		//Display scene.
		window->display();
	}

	Victory();

}


void Victory()
{
	bool optionChosen = false;
	while (window->isOpen() && !optionChosen)
	{
		sf::Text menu;
		menu.setFont(font);
		menu.setString("GAME OVER!");
		menu.setCharacterSize(96);
		menu.setFillColor(sf::Color::White);
		menu.setPosition((window->getSize().x - menu.getLocalBounds().width) * 0.5, (window->getSize().y - menu.getLocalBounds().height) * 0.5);

		sf::Text subtitle;
		subtitle.setFont(font);
		subtitle.setString("Press [SPACEBAR] to go to Menu");
		subtitle.setCharacterSize(48);
		subtitle.setFillColor(sf::Color::White);
		subtitle.setPosition((window->getSize().x - subtitle.getLocalBounds().width) * 0.5, menu.getPosition().y + menu.getLocalBounds().height + 50);

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				return;
			}
		}

		window->clear();
		window->draw(background);
		window->draw(menu);
		window->draw(subtitle);
		window->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			optionChosen = true;
		}
	}

	Menu();
}

void PlayMusic()
{

}

void LoadBackground()
{

}

void Exit()
{
}