#pragma once
//#include"Player.h"
using namespace sf;


class Knuckles :public Player
{
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
public:
	Knuckles()
	{
		states = new Animation * [13];
		indexAnimation = 0;
		totalAnimations = 13;
		jogLeft.loadFromFile("Data/KLeftWalk.png");
		states[LEFT] = new Animation(12);
		for (int i = 0,  width = 0;i < 12;i++,  width += 49)
		{
			states[LEFT]->getSprites()[i].setTexture(jogLeft);
			states[LEFT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[LEFT]->getSprites()[i].setScale(2, 2);

		}
		jogRight.loadFromFile("Data/KRightWalk.png");
		states[RIGHT] = new Animation(12);
		for (int i = 0,  width = 0;i < 12;i++,  width += 49)
		{
			states[RIGHT]->getSprites()[i].setTexture(jogRight);
			states[RIGHT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[RIGHT]->getSprites()[i].setScale(2, 2);
		}
		upLeft.loadFromFile("Data/KJumpL.png");
		states[UPL] = new Animation(14);
		for (int i = 0,  width = 0;i < 14;i++, width += 49)
		{
			states[UPL]->getSprites()[i].setTexture(upLeft);
			states[UPL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[UPL]->getSprites()[i].setScale(2, 2);

		}
		upRight.loadFromFile("Data/KJumpR.png");
		states[UPR] = new Animation(14);
		for (int i = 0,  width = 0;i < 14;i++, width += 49)
		{
			states[UPR]->getSprites()[i].setTexture(upRight);
			states[UPR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[UPR]->getSprites()[i].setScale(2, 2);

		}
		edgeLeft.loadFromFile("Data/KEdgeL.png");
		states[EDGEL] = new Animation(6);
		for (int i = 0,  width = 0;i < 6;i++, width += 49)
		{
			states[EDGEL]->getSprites()[i].setTexture(edgeLeft);
			states[EDGEL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[EDGEL]->getSprites()[i].setScale(2, 2);

		}
		edgeRight.loadFromFile("Data/KEdgeR.png");
		states[EDGER] = new Animation(6);
		for (int i = 0,  width = 0;i < 6;i++, width += 49)
		{
			states[EDGER]->getSprites()[i].setTexture(edgeRight);
			states[EDGER]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[EDGER]->getSprites()[i].setScale(2, 2);

		}
		leftRun.loadFromFile("Data/KLeftJog.png");
		states[LEFTRUN] = new Animation(12);
		for (int i = 0,  width = 0;i < 12;i++, width += 49)
		{
			states[LEFTRUN]->getSprites()[i].setTexture(leftRun);
			states[LEFTRUN]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[LEFTRUN]->getSprites()[i].setScale(2, 2);

		}
		rightRun.loadFromFile("Data/KRightJog.png");
		states[RIGHTRUN] = new Animation(12);
		for (int i = 0,  width = 0;i < 12;i++, width += 49)
		{
			states[RIGHTRUN]->getSprites()[i].setTexture(rightRun);
			states[RIGHTRUN]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[RIGHTRUN]->getSprites()[i].setScale(2, 2);

		}
		pushLeft.loadFromFile("Data/KPushL.png");
		states[PUSHLEFT] = new Animation(10);
		for (int i = 0,  width = 0;i < 10;i++, width += 49)
		{
			states[PUSHLEFT]->getSprites()[i].setTexture(pushLeft);
			states[PUSHLEFT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[PUSHLEFT]->getSprites()[i].setScale(2, 2);

		}
		pushRight.loadFromFile("Data/KPushR.png");
		states[PUSHRIGHT] = new Animation(10);
		for (int i = 0,  width = 0;i < 10;i++, width += 49)
		{
			states[PUSHRIGHT]->getSprites()[i].setTexture(pushRight);
			states[PUSHRIGHT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[PUSHRIGHT]->getSprites()[i].setScale(2, 2);

		}
		jumpLeft.loadFromFile("Data/KJumpL.png");
		states[JUMPL] = new Animation(14);
		for (int i = 0,  width = 0;i < 14;i++, width += 49)
		{
			states[JUMPL]->getSprites()[i].setTexture(jumpLeft);
			states[JUMPL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[JUMPL]->getSprites()[i].setScale(2, 2);

		}
		jumpRight.loadFromFile("Data/KJumpR.png");
		states[JUMPR] = new Animation(14);
		for (int i = 0,  width = 0;i < 14;i++, width += 49)
		{
			states[JUMPR]->getSprites()[i].setTexture(jumpRight);
			states[JUMPR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[JUMPR]->getSprites()[i].setScale(2, 2);

		}
		still.loadFromFile("Data/knucklesStill.png");
		states[STILL] = new Animation(12);
		for (int i = 0,  width = 0;i < 12;i++, width += 49)
		{
			states[STILL]->getSprites()[i].setTexture(still);
			states[STILL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[STILL]->getSprites()[i].setScale(2, 2);
		}
		delayInFollow = 20;
	}
	virtual void followLeader(const int const** pathToFollow)
	{
		
	}
};