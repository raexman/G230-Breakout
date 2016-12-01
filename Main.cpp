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
void PlayLevel(int level = 0);
void Victory();
void Exit();
void CreateLevel1Bricks();
void CreateLevel2Bricks();
void CreateLevel3Bricks();
void CreateLevel4Bricks();
void CheckBrickCollisions(Ball *ball);

using namespace std;

vector<unique_ptr<Brick>> bricks;
float deltaTime;
bool isPlaying;
bool isWon;
bool isMenu;
int matchMode;
float maxScore = 4;
const int numOfPlayers = 2;

sf::Font font;
sf::RenderWindow *window;
sf::Sprite background;
sf::Texture bgTexture;
sf::Texture barTexture;
sf::Texture ballTexture;
sf::Texture brickTexture;
sf::Vector2f speed(200, 200);

sf::SoundBuffer buffer;
sf::Sound sound;

int margin = 10;
int rows = 4;
int cols = 8;
int score = 0;
int rounds = 0;
int unbreakable = 0;

int WinMain()
{
	font.loadFromFile("AmericanCaptain.ttf");

	window = new sf::RenderWindow(sf::VideoMode(800, 600), "WRECK-OUT!");
	bgTexture.loadFromFile("background2.jpg");
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
		title.setString("WRECK-OUT!");
		title.setCharacterSize(125);
		title.setFillColor(sf::Color::Yellow);
		title.setOutlineColor(sf::Color::Black);
		title.setOutlineThickness(10);
		title.setPosition((window->getSize().x - title.getLocalBounds().width) * 0.5, 150);

		sf::Text menu;
		menu.setFont(font);
		menu.setString("PRESS SPACE TO PLAY");
		menu.setCharacterSize(48);
		menu.setFillColor(sf::Color::White);
		menu.setOutlineColor(sf::Color::Black);
		menu.setOutlineThickness(10);
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			mode = 1;
			optionChosen = true;
		}
	}
	switch (mode)
	{
		case 0: Exit();
		case 1: PlayLevel(); break;
		default:break;
	}
}
void CreateLevel1Bricks()
{

	int brickWidth = (window->getSize().x * 0.80f) / cols;
	int brickHeight = brickWidth * 0.4;

	for (int i = 0; i < rows*cols; i++)
	{
		Brick *go;
		brickTexture.loadFromFile("brick_destroyed.png");
		go = new Brick(1, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color::White, window, brickTexture);
		bricks.push_back(unique_ptr<Brick>(go));
	}
}
void CreateLevel2Bricks()
{

	int brickWidth = (window->getSize().x * 0.80f) / cols;
	int brickHeight = brickWidth * 0.4;

	for (int i = 0; i < rows*cols; i++)
	{
		Brick *go;
		if (i / cols >= 0 && i / cols <= 1)
		{
			brickTexture.loadFromFile("brick_damaged.png");
			go = new Brick(2, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color::Blue, window, brickTexture);
		}
		else
		{
			brickTexture.loadFromFile("brick_destroyed.png");
			go = new Brick(1, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color::White, window, brickTexture);
		}

		bricks.push_back(unique_ptr<Brick>(go));
	}
}
void CreateLevel3Bricks()
{

	int brickWidth = (window->getSize().x * 0.80f) / cols;
	int brickHeight = brickWidth * 0.4;

	for (int i = 0; i < rows*cols; i++)
	{
		Brick *go;
		if (i / cols >= 0 && i / cols <= 1)
		{
			brickTexture.loadFromFile("brick.png");
			go = new Brick(3, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color::Green, window, brickTexture);
		}
		else if (i/cols >= 2 && i/cols <= 3)
		{
			brickTexture.loadFromFile("brick_damaged.png");
			go = new Brick(2, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color::Blue, window, brickTexture);
		}
		else
		{
			brickTexture.loadFromFile("brick_destroyed.png");
			go = new Brick(1, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i /cols) * (brickHeight + margin) + margin ), sf::Color::White, window, brickTexture);
		}

		bricks.push_back(unique_ptr<Brick>(go));
	}
}

void CreateLevel4Bricks()
{
	unbreakable = 0;
	int brickWidth = (window->getSize().x * 0.80f) / cols;
	int brickHeight = brickWidth * 0.4;

	for (int i = 0; i < rows*cols; i++)
	{
		Brick *go;
		
		int type = rand() % int(cols*rows*0.5);

		switch (type)
		{
			case 0:
			case 1:
				brickTexture.loadFromFile("brick.png");
				go = new Brick(1, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color::Magenta, window, brickTexture);
				go->PowerUp = "drill";
				break;
			case 2:
				brickTexture.loadFromFile("brick.png");
				go = new Brick(1, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color::Blue, window, brickTexture);
				go->PowerUp = "slowmo";
				break;
			case 3:
			case 4:
			case 5:
				brickTexture.loadFromFile("brick.png");
				go = new Brick(3, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color(100, 100, 100, 255), window, brickTexture);
				go->isInvincible = true;
				unbreakable++;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
				brickTexture.loadFromFile("brick_damaged.png");
				go = new Brick(1, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color(0, 200, 80, 255) , window, brickTexture);
				go->isInvisible = true;
				break;
			default:
				brickTexture.loadFromFile("brick_destroyed.png");
				go = new Brick(1, sf::Vector2f(brickWidth - margin, brickHeight), sf::Vector2f(i%cols * brickWidth + window->getSize().x * 0.1f, (i / cols) * (brickHeight + margin) + margin), sf::Color::White, window, brickTexture);
				break;
		}

		bricks.push_back(unique_ptr<Brick>(go));
	}
}

void CheckBrickCollisions(Ball *ball)
{
	for (int i = 0; i < bricks.size(); i++)
	{
		Brick *br = bricks[i].get();
		bool hasCollided = ball->CheckCollisionWith(br, true);
		if (hasCollided)
		{
			std::string soundFx = "hit.wav";
			score++;

			if (bricks[i]->PowerUp == "drill")
			{
				soundFx = "powerup.wav";
				ball->isDrilling = true;
			}
			else if (bricks[i]->PowerUp == "slowmo")
			{
				soundFx = "powerup.wav";
				ball->SetSpeed(100, 100);
				ball->isDrilling = false;
			}
			
			if (br->Dead())
			{
				soundFx = "explosion.wav";
				buffer.loadFromFile(soundFx);
				sound.setBuffer(buffer);
				sound.play();
				bricks.erase(bricks.begin() + i);
				continue;
			}

			buffer.loadFromFile(soundFx);
			sound.setBuffer(buffer);
			sound.play();
		}
	}
}
void PlayLevel(int level)
{
	barTexture.loadFromFile("paddle.jpg");
	ballTexture.loadFromFile("ball.png");

	Bar bar(sf::Vector2f(100, 30), sf::Vector2f((window->getSize().x - 50) * 0.5f, window->getSize().y - 80), window, barTexture);
	Ball ball(speed, 3, sf::Vector2f(20,20), sf::Vector2f(0,0), window, ballTexture);

	level = level % 4 + 1;

	switch (level)
	{
		case 1:
			CreateLevel1Bricks();
			break;
		case 2:
			CreateLevel2Bricks();
			break;
		case 3:
			CreateLevel3Bricks();
			break;
		case 4:
			CreateLevel4Bricks();
			break;
		default:
			CreateLevel1Bricks();
			break;
	}

	

	sf::Text title;
	title.setFont(font);
	title.setString("Lives: " + to_string(ball.GetLives()));
	title.setCharacterSize(21);
	title.setFillColor(sf::Color::Yellow);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2);
	title.setPosition(window->getSize().x - title.getLocalBounds().width - margin* 2, window->getSize().y - title.getLocalBounds().height - margin * 2);

	sf::Text scoreLabel;
	scoreLabel.setFont(font);
	scoreLabel.setString("Score: " + to_string(score));
	scoreLabel.setCharacterSize(21);
	scoreLabel.setFillColor(sf::Color::Yellow);
	scoreLabel.setOutlineColor(sf::Color::Black);
	scoreLabel.setOutlineThickness(2);
	scoreLabel.setPosition(margin * 2, window->getSize().y - scoreLabel.getLocalBounds().height - margin * 2);

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
		
		//Draw title.
		title.setString("Lives: " + to_string(ball.GetLives()));
		scoreLabel.setString("Score: " + to_string(score));
		window->draw(title);
		window->draw(scoreLabel);

		bar.Update(deltaTime);
		
		//Draw ball.
		//Check ball status.
		if (ball.isResting)
		{
			//Keep ball
			float ballX = bar.GetPosition().x + (bar.GetSize().x - ball.GetSize().x) * 0.5f;
			float ballY = bar.GetPosition().y - ball.GetSize().y;
			ball.SetPosition(ballX, ballY);
		}
		ball.Update(deltaTime);
		
		//Draw bricks.
		for (int i = 0; i < bricks.size(); i++)
		{
			bricks[i]->Update(deltaTime);
		}


		
		//Check collisions.
		CheckBrickCollisions(&ball);
		ball.CheckCollisionWith(&bar, false);
		
		//Display scene.
		window->display();

		if (ball.Dead())
		{
			isPlaying = false;
		}

		if ((bricks.size() - unbreakable) == 0)
		{
			isPlaying = false;
			isWon = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			isPlaying = false;
			level = -1;
			isWon = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			isPlaying = false;
			level = 0;
			isWon = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		{
			isPlaying = false;
			level = 1;
			isWon = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		{
			isPlaying = false;
			level = 2;
			isWon = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J))
		{
			ball.AddSpeed(1, 1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
		{
			ball.AddSpeed(-1, -1);
		}


	}

	bricks.erase(bricks.begin(), bricks.end());
	speed = ball.GetSpeed();

	if (!isWon)
		Victory();
	else
	{
		std::string soundFx = "cheers.wav";
		buffer.loadFromFile(soundFx);
		sound.setBuffer(buffer);
		sound.play();
		isWon = false;
		PlayLevel(level + 1);
	}

}


void Victory()
{
	std::string soundFx = "denied.wav";
	buffer.loadFromFile(soundFx);
	sound.setBuffer(buffer);
	sound.play();

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