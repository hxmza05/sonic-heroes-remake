#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;

#define LEFT 0
#define RIGHT 1
#define UPL 2
#define UPR 3
#define EDGEL 4
#define EDGER 5
#define LEFTRUN 6
#define RIGHTRUN 7
#define PUSHLEFT 8
#define PUSHRIGHT 9
#define JUMPL 10
#define JUMPR 11
#define STILL 12
#define GLIDEL 13
#define GLIDER 14


#define SPIND 15
#define BREAKL 16
#define GLIDEL 13
#define GLIDER 14
#define AJUMP 0

class Sonic :public Player
{
	//bool specialAbi
	bool directionSpecial;
	bool restarted;
	Texture jogLeft;
	Texture jogRight;
	Texture upLeft;
	Texture upRight;
	Texture edgeLeft;
	Texture edgeRight;
	Texture leftRun;
	Texture rightRun;
	Texture pushLeft;
	Texture pushRight;
	Texture jumpLeft;
	Texture jumpRight;
	Texture still;
	Texture glideLeft;
	Texture glideRight;
	Texture spinDsh;
public:
	Sonic()
	{
		idxPl = 0;
		//isGliding = false;
		states = new Animation*[16];
		indexAnimation = 0;
		totalAnimations = 15;
		jogLeft.loadFromFile("Data/0jog_left.png");
		states[LEFT] = new Animation(10);
		for (int i = 0,width = 0;i < 10;i++,width+=40)
		{
			states[LEFT]->getSprites()[i].setTexture(jogLeft);
			states[LEFT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[LEFT]->getSprites()[i].setScale(2, 2);

		}
		jogRight.loadFromFile("Data/0jog_right.png");
		states[RIGHT] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 40)
		{
			states[RIGHT]->getSprites()[i].setTexture(jogRight);
			states[RIGHT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[RIGHT]->getSprites()[i].setScale(2, 2);
		}
		upLeft.loadFromFile("Data/0upL.png");
		states[UPL] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 40)
		{
			states[UPL]->getSprites()[i].setTexture(upLeft);
			states[UPL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[UPL]->getSprites()[i].setScale(2, 2);

		}
		upRight.loadFromFile("Data/0upR.png");
		states[UPR] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 40)
		{
			states[UPR]->getSprites()[i].setTexture(upRight);
			states[UPR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[UPR]->getSprites()[i].setScale(2, 2);

		}
		edgeLeft.loadFromFile("Data/0edgeL.png");
		states[EDGEL] = new Animation(7);
		for (int i = 0, width = 0;i < 7;i++, width += 40)
		{
			states[EDGEL]->getSprites()[i].setTexture(edgeLeft);
			states[EDGEL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[EDGEL]->getSprites()[i].setScale(2, 2);

		}
		edgeRight.loadFromFile("Data/0edgeR.png");
		states[EDGER] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 40)
		{
			states[EDGER]->getSprites()[i].setTexture(edgeRight);
			states[EDGER]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[EDGER]->getSprites()[i].setScale(2, 2);

		}
		leftRun.loadFromFile("Data/0left_run.png");
		states[LEFTRUN] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 40)
		{
			states[LEFTRUN]->getSprites()[i].setTexture(leftRun);
			states[LEFTRUN]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[LEFTRUN]->getSprites()[i].setScale(2, 2);

		}
		rightRun.loadFromFile("Data/0right_run.png");
		states[RIGHTRUN] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 40)
		{
			states[RIGHTRUN]->getSprites()[i].setTexture(rightRun);
			states[RIGHTRUN]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[RIGHTRUN]->getSprites()[i].setScale(2, 2);

		}
		pushLeft.loadFromFile("Data/0pushL.png");
		states[PUSHLEFT] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 40)
		{
			states[PUSHLEFT]->getSprites()[i].setTexture(pushLeft);
			states[PUSHLEFT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[PUSHLEFT]->getSprites()[i].setScale(2, 2);

		}
		pushRight.loadFromFile("Data/0pushR.png");
		states[PUSHRIGHT] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 40)
		{
			states[PUSHRIGHT]->getSprites()[i].setTexture(pushRight);
			states[PUSHRIGHT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[PUSHRIGHT]->getSprites()[i].setScale(2, 2);

		}
		jumpLeft.loadFromFile("Data/0upL.png");
		states[JUMPL] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 40)
		{
			states[JUMPL]->getSprites()[i].setTexture(jumpLeft);
			states[JUMPL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[JUMPL]->getSprites()[i].setScale(2, 2);

		}
		jumpRight.loadFromFile("Data/0upR.png");
		states[JUMPR] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 40)
		{
			states[JUMPR]->getSprites()[i].setTexture(jumpRight);
			states[JUMPR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[JUMPR]->getSprites()[i].setScale(2, 2);

		}
		still.loadFromFile("Data/0still.png");
		states[STILL] = new Animation(11);
		for (int i = 0, width = 0;i < 11;i++, width += 49)
		{
			states[STILL]->getSprites()[i].setTexture(still);
			states[STILL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[STILL]->getSprites()[i].setScale(2, 2);
		}
		glideLeft.loadFromFile("Data/0edgeL.png");
		states[GLIDEL] = new Animation(7);
		for (int i = 0, width = 0;i < 7;i++, width += 40)
		{
			states[GLIDEL]->getSprites()[i].setTexture(glideLeft);
			states[GLIDEL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[GLIDEL]->getSprites()[i].setScale(2, 2);
		}
		glideRight.loadFromFile("Data/sonic_hang.png");
		states[GLIDER] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 49)
		{
			states[GLIDER]->getSprites()[i].setTexture(glideRight);
			states[GLIDER]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 49, 50));
			states[GLIDER]->getSprites()[i].setScale(2, 2);
		}
		spinDsh.loadFromFile("Data/spinDash.png");
		states[SPIND] = new Animation(6);
		for (int i = 0, width = 0;i < 6;i++, width += 36.33)
		{
			states[SPIND]->getSprites()[i].setTexture(spinDsh);
			states[SPIND]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 36.33, 50));
			states[SPIND]->getSprites()[i].setScale(2.5, 2.5);
		}
		delayInFollow = 15;
		max_speed = 15;
		specialAbilityUsed = false;
		restarted = false;
		isSpecial = false;
		spinDashed = false;
	}

	virtual void followLeader(const int const **pathToFollow)
	{
		
	}
	virtual void moveUp(bool spacePressed,int &unsedHere)
	{
		if(!spacePressed)
		{
			velocityY = -19.5;
			onGround = false;
		}
	}
	void useSpecialAbilty(char**lvl,int h,int w)
	{
		if(!specialAbilityUsed && coolDown.getElapsedTime().asSeconds() > 3)
		{
			specialAbilityUsed = true;
			spinDashed = true;
			specialAbiltyClock.restart();
			directionSpecial = direction;
			if (direction)
			{
				velocityX = 5;
			}
			else velocityX = -5;
			acceleration = 1;
		}
	}
	void spinDash(char**lvl,float width,float friction)
	{
		if (specialAbiltyClock.getElapsedTime().asMilliseconds() > 500)
		{
			if(!restarted)
			{
				coolDown.restart();
				restarted = true;
			}
			spinDashed = false;
			specialAbilityUsed = false;
			acceleration = 0.2;
			velocityX = 0;
			return;
		}
		restarted = false;
		if (directionSpecial)
		{
			moveRight(lvl, width, 0.1);
		}
		if (!directionSpecial)
		{
			moveLeft(lvl, width, 0.1);
		}
		indexAnimation = SPIND;
	}
};