#pragma once
//#include"Player.h"
using namespace sf;


class TailedFox :public Player
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
	TailedFox()
	{
		states = new Animation * [13];
		indexAnimation = 0;
		totalAnimations = 13;
		jogLeft.loadFromFile("Data/TJogL.png");
		states[LEFT] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 49)
		{
			states[LEFT]->getSprites()[i].setTexture(jogLeft);
			states[LEFT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 49, 50));
			states[LEFT]->getSprites()[i].setScale(2, 2);

		}
		jogRight.loadFromFile("Data/TJogR.png");
		states[RIGHT] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 49)
		{
			states[RIGHT]->getSprites()[i].setTexture(jogRight);
			states[RIGHT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 49, 50));
			states[RIGHT]->getSprites()[i].setScale(2, 2);
		}
		upLeft.loadFromFile("Data/TJump.png");
		states[UPL] = new Animation(6);
		for (int i = 0, width = 0;i < 6;i++, width += 49)
		{
			states[UPL]->getSprites()[i].setTexture(upLeft);
			states[UPL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[UPL]->getSprites()[i].setScale(2, 2);

		}
		upRight.loadFromFile("Data/TJump.png");
		states[UPR] = new Animation(6);
		for (int i = 0, width = 0;i < 6;i++, width += 49)
		{
			states[UPR]->getSprites()[i].setTexture(upRight);
			states[UPR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[UPR]->getSprites()[i].setScale(2, 2);

		}
		edgeLeft.loadFromFile("Data/TEdgeL.png");
		states[EDGEL] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 49)
		{
			states[EDGEL]->getSprites()[i].setTexture(edgeLeft);
			states[EDGEL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[EDGEL]->getSprites()[i].setScale(2, 2);

		}
		edgeRight.loadFromFile("Data/TEdgeR.png");
		states[EDGER] = new Animation(8);
		for (int i = 0, width = 0;i < 8;i++, width += 56)
		{
			states[EDGER]->getSprites()[i].setTexture(edgeRight);
			states[EDGER]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[EDGER]->getSprites()[i].setScale(2, 2);

		}
		leftRun.loadFromFile("Data/TJogL.png");
		states[LEFTRUN] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 49)
		{
			states[LEFTRUN]->getSprites()[i].setTexture(leftRun);
			states[LEFTRUN]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 49, 50));
			states[LEFTRUN]->getSprites()[i].setScale(2, 2);

		}
		rightRun.loadFromFile("Data/TJogR.png");
		states[RIGHTRUN] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 49)
		{
			states[RIGHTRUN]->getSprites()[i].setTexture(rightRun);
			states[RIGHTRUN]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 49 , 50));
			states[RIGHTRUN]->getSprites()[i].setScale(2, 2);

		}
		pushLeft.loadFromFile("Data/TPushL.png");
		states[PUSHLEFT] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 49)
		{
			states[PUSHLEFT]->getSprites()[i].setTexture(pushLeft);
			states[PUSHLEFT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[PUSHLEFT]->getSprites()[i].setScale(2, 2);

		}
		pushRight.loadFromFile("Data/TPushR.png");
		states[PUSHRIGHT] = new Animation(10);
		for (int i = 0, width = 0;i < 10;i++, width += 49)
		{
			states[PUSHRIGHT]->getSprites()[i].setTexture(pushRight);
			states[PUSHRIGHT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[PUSHRIGHT]->getSprites()[i].setScale(2, 2);

		}
		jumpLeft.loadFromFile("Data/TFlyL.png");
		states[JUMPL] = new Animation(4);
		for (int i = 0, width = 0;i < 4;i++, width += 54)
		{
			states[JUMPL]->getSprites()[i].setTexture(jumpLeft);
			states[JUMPL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[JUMPL]->getSprites()[i].setScale(2, 2);

		}
		jumpRight.loadFromFile("Data/TFlyR.png");
		states[JUMPR] = new Animation(4);
		for (int i = 0, width = 0;i < 4;i++, width += 54)
		{
			states[JUMPR]->getSprites()[i].setTexture(jumpRight);
			states[JUMPR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 54, 50));
			states[JUMPR]->getSprites()[i].setScale(2, 2);

		}
		still.loadFromFile("Data/TIdle.png");
		states[STILL] = new Animation(24);
		for (int i = 0, width = 0;i < 24;i++, width += 49)
		{
			states[STILL]->getSprites()[i].setTexture(still);
			states[STILL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[STILL]->getSprites()[i].setScale(2, 2);
		}
		delayInFollow = 30;
	}
	virtual void followLeader(const int const** pathToFollow)
	{

	}
	void Fly()
	{

	}
	
};