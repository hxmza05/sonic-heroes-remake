#pragma once
#include"player.h"
#include"GlobalFunctions.h"

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

#define BREAKR 15
#define BREAKL 16

#define AJUMP 0
class SpecialCharacter :public Player
{
	// AKA MARIO 
	int GlideCount = 0;
	int idxPl;




	bool hasCooleddown;
	double flyingTime;
	Clock fliyingClock;





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

public:
	SpecialCharacter()
	{
		//isGliding = false;
		states = new Animation * [15];
		indexAnimation = 0;
		totalAnimations = 15;
		jogLeft.loadFromFile("Data/marioWalkL.png");
		states[LEFT] = new Animation(3);
		for (int i = 0, width = 0;i < 3;i++, width += 14.3)
		{
			states[LEFT]->getSprites()[i].setTexture(jogLeft);
			states[LEFT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.3, 50));
			states[LEFT]->getSprites()[i].setScale(3.9, 3.9);

		}
		jogRight.loadFromFile("Data/marioWalkR.png");
		states[RIGHT] = new Animation(3);
		for (int i = 0, width = 0;i < 3;i++, width += 14.3)
		{
			states[RIGHT]->getSprites()[i].setTexture(jogRight);
			states[RIGHT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.3, 50));
			states[RIGHT]->getSprites()[i].setScale(3.9, 3.9);
		}
		upLeft.loadFromFile("Data/marioJumpL.png");
		states[UPL] = new Animation(1);
		for (int i = 0, width = 0;i < 1;i++, width += 40)
		{
			states[UPL]->getSprites()[i].setTexture(upLeft);
			states[UPL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[UPL]->getSprites()[i].setScale(4, 4);

		}
		upRight.loadFromFile("Data/marioJumpR.png");
		states[UPR] = new Animation(1);
		for (int i = 0, width = 0;i < 1;i++, width += 40)
		{
			states[UPR]->getSprites()[i].setTexture(upRight);
			states[UPR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[UPR]->getSprites()[i].setScale(4, 4);

		}
		edgeLeft.loadFromFile("Data/marioWalkR.png");
		states[EDGEL] = new Animation(3);
		for (int i = 0, width = 0;i < 3;i++, width += 14.3)
		{
			states[EDGEL]->getSprites()[i].setTexture(edgeLeft);
			states[EDGEL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.3, 50));
			states[EDGEL]->getSprites()[i].setScale(3.9, 3.9);

		}
		edgeRight.loadFromFile("Data/marioWalkL.png");
		states[EDGER] = new Animation(3);
		for (int i = 0, width = 0;i < 3;i++, width += 14.3)
		{
			states[EDGER]->getSprites()[i].setTexture(edgeRight);
			states[EDGER]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.3, 50));
			states[EDGER]->getSprites()[i].setScale(3.9, 3.9);

		}
		leftRun.loadFromFile("Data/marioWalkL.png");
		states[LEFTRUN] = new Animation(3);
		for (int i = 0, width = 0;i < 3;i++, width += 14.3)
		{
			states[LEFTRUN]->getSprites()[i].setTexture(jogLeft);
			states[LEFTRUN]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.3, 50));
			states[LEFTRUN]->getSprites()[i].setScale(3.9, 3.9);

		}
		rightRun.loadFromFile("Data/marioWalkR.png");
		states[RIGHTRUN] = new Animation(3);
		for (int i = 0, width = 0;i < 3;i++, width += 14.3)
		{
			states[RIGHTRUN]->getSprites()[i].setTexture(jogRight);
			states[RIGHTRUN]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.3, 50));
			states[RIGHTRUN]->getSprites()[i].setScale(3.9, 3.9);
		}
		pushLeft.loadFromFile("Data/marioStillO.png");
		states[PUSHLEFT] = new Animation(18);
		for (int i = 0, width = 0;i < 18;i++)
		{
			if (i != 0 && i % 6 == 0)
				width += 14.33333;
			states[PUSHLEFT]->getSprites()[i].setTexture(still);
			states[PUSHLEFT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.33333, 50));
			states[PUSHLEFT]->getSprites()[i].setScale(3.7, 3.7);
		}
		pushRight.loadFromFile("Data/marioStillO.png");
		states[PUSHRIGHT] = new Animation(18);
		for (int i = 0, width = 0;i < 18;i++)
		{
			if (i != 0 && i % 6 == 0)
				width += 14.33333;
			states[PUSHRIGHT]->getSprites()[i].setTexture(still);
			states[PUSHRIGHT]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.33333, 50));
			states[PUSHRIGHT]->getSprites()[i].setScale(3.7, 3.7);
		}
		jumpLeft.loadFromFile("Data/marioFlyL.png");
		states[JUMPL] = new Animation(6);
		for (int i = 0, width = 0;i < 6;i++, width += 18.1666666)
		{
			states[JUMPL]->getSprites()[i].setTexture(jumpLeft);
			states[JUMPL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 18.1666666, 50));
			states[JUMPL]->getSprites()[i].setScale(3.4, 3.2);

		}
		jumpRight.loadFromFile("Data/marioFlyR.png");
		states[JUMPR] = new Animation(6);
		for (int i = 0, width = 0;i < 6;i++, width += 18.1666666)
		{
			states[JUMPR]->getSprites()[i].setTexture(jumpRight);
			states[JUMPR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 18.1666666, 50));
			states[JUMPR]->getSprites()[i].setScale(3.4, 3.2);

		}
		still.loadFromFile("Data/marioStillO.png");
		states[STILL] = new Animation(18);
		for (int i = 0, width = 0;i < 18;i++)
		{
			if (i != 0 && i % 6 == 0)
				width += 14.33333;
			states[STILL]->getSprites()[i].setTexture(still);
			states[STILL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 14.33333, 50));
			states[STILL]->getSprites()[i].setScale(3.7, 3.7);
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
		delayInFollow = 0;
		max_speed = 15;
		specialAbilityUsed = false;
		restarted = false;
		flyingTime = 20;
		hasCooleddown = false;
		isSpecial = true;
		spinDashed = false;
	}
	void spinDash(char** lvl, float width, float friction)
	{
		if (specialAbiltyClock.getElapsedTime().asMilliseconds() > 1000)
		{
			cout << "Spin Dash Mario dectivated!!!!\n";
			if (!restarted)
			{
				coolDown.restart();
				restarted = true;
			}
			specialAbilityUsed = false;
			spinDashed = false;
			acceleration = 0.2;
			velocityX = 0;
			return;
		}
		Break(lvl, 14, width);
		restarted = false;
		if (directionSpecial)
		{
			cout << "\nmoving rightttt!!!";
			moveRight(lvl, width, 0.1);
		}
		if (!directionSpecial)
		{
			moveLeft(lvl, width, 0.1);
		}
	}
	virtual void moveUp(bool spacePressed, int& spaceCount)
	{
		if (spaceCount > 9 && ((!restarted) || (restarted && fliyingClock.getElapsedTime().asSeconds() < flyingTime)))
		{
			if (audio) 
			{

				if (audio->isSoundPlaying(audio->getJump())) {
					audio->stopSound(audio->getJump());
				}

				if (!audio->isSoundPlaying(audio->getFlying())) {
					audio->stopSound(audio->getJump());
					audio->playSound(audio->getFlying());
				}
			}
			hasCooleddown = false;
			if (y - 2 >= 64)
				velocityY = -2;
			else velocityY = 0.01;
			indexAnimation = direction == 1? JUMPR : JUMPL;
			onGround = false;
			if (!restarted)
			{
				fliyingClock.restart();
				restarted = true;
			}
		}
		else if (fliyingClock.getElapsedTime().asSeconds() >= flyingTime && restarted && spaceCount > 9)
		{
			if (audio) 
			{
				audio->playSound(audio->getTired());
			}
			spaceCount = 0;
			return;
		}
		if (!spacePressed)
		{
			cout << "\n\nISSUE HERE!!!!!\n\n";
			velocityY = -19.5;
			onGround = false;
			if (direction == 1)
				indexAnimation = UPR;
			else indexAnimation = UPL;
			restarted = false;
		}
	}
	void Break(char** lvl, int height, int width)
	{
		cout << "Break has been called in direction :"<< direction <<"\n";
		float glidePixels = velocityX;
		cout << "Glide pixels : " << velocityX <<"-------";
		int checkX = (direction == 1) ? x + getPwidth() + glidePixels : x - glidePixels;
		int checkY = y + getPheight() / 2; // Middle of player vertically for more accurate collision
		int tileX = checkX / 64;
		int tileY = checkY / 64;
		cout << "TILEX = " << tileX << "----- TILEY = " << tileY << "\n";
		//  checking bounds here firstxly
		if (tileX < 0 || tileY < 0 || tileY >= 14)
			return;
		if (checkCollisionSpikes(lvl, checkX, checkY, height, width))
		{
			cout << "Retrjning!!!!\n";
			return;
		}
		// If block is breakable
		if (checkCollisionExceptSpikes(lvl, checkX, checkY, height, width))
		{
			if (audio)
			{
				audio->playSound(audio->getGlassSmash());
			}
			cout << "BROKEN!!!\n";
			lvl[tileY][tileX] = 's'; // Mark it as emptyspace pwnow
			//cout << "Collision Detected and Block Broken\n";
		}
		else cout << "NOt BROKENNNN 1111111111-----------";
		checkY = y - 5;
		tileY = checkY / 64;
		if (checkCollisionExceptSpikes(lvl, checkX, checkY, height, width))
		{
			cout << "BROKENNN!!!!";
			if (audio) 
			{
				audio->playSound(audio->getGlassSmash());
			}
			lvl[tileY][tileX] = 's'; // Mark it as emptyspace pwnow
			//cout << "Collision Detected and Block Broken\n";
		}
		else cout << "NOT BROKENN2222222222222222222222!!!!";
		// Glide movement
		if (indexAnimation == BREAKR)
			x += glidePixels;
		else
			x -= glidePixels;
		GlideCount++;
	}
	virtual void followLeader(const int const** pathToFollow)
	{

	}
	void useSpecialAbilty(char** lvl, int h, int w)
	{
		
		//Break(lvl, 14, w);
		if (!specialAbilityUsed && coolDown.getElapsedTime().asSeconds() > 3)
		{
			spinDashed = true;
			cout << "Special Ability mario has bveen activated !!! \n";
			specialAbilityUsed = true;
			specialAbiltyClock.restart();
			directionSpecial = direction;
			if (direction)
			{
				velocityX = 5;
			}
			else velocityX = -5;
			acceleration = 1;
			indexAnimation = JUMPR;
		}
	}

};