#pragma once
//#include"Player.h"
#include"GlobalFunctions.h"
using namespace sf;
#define BREAKR 15
#define BREAKL 16

#define AJUMP 0
#include "Audio.h"

class Knuckles :public Player
{
	int GlideCount;
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
	Texture breakR;
	Texture breakL;
public:
	Knuckles()
	{
		 GlideCount = 0;
		 idxPl = 2;
		//isGliding = false;
		states = new Animation * [15];
		indexAnimation = 0;
		totalAnimations = 17;
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

		glideLeft.loadFromFile("Data/KEdgeL.png");
		states[GLIDEL] = new Animation(6);
		for (int i = 0, width = 0;i < 6;i++, width += 49)
		{
			states[GLIDEL]->getSprites()[i].setTexture(edgeLeft);
			states[GLIDEL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[GLIDEL]->getSprites()[i].setScale(2, 2);

		}
		glideRight.loadFromFile("Data/KEdgeR.png");
		states[GLIDER] = new Animation(6);
		for (int i = 0, width = 0;i < 6;i++, width += 49)
		{
			states[GLIDER]->getSprites()[i].setTexture(edgeRight);
			states[GLIDER]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[GLIDER]->getSprites()[i].setScale(2, 2);
		}
		breakL.loadFromFile("Data/KBreakL.png");
		states[BREAKL] = new Animation(5);
		for (int i = 0, width = 0;i <5;i++, width += 49)
		{
			states[BREAKL]->getSprites()[i].setTexture(breakL);
			states[BREAKL]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[BREAKL]->getSprites()[i].setScale(2, 2);
		}
		breakR.loadFromFile("Data/KBreakR.png");
		states[BREAKR] = new Animation(5);
		for (int i = 0, width = 0;i < 5;i++, width += 49)
		{
			states[BREAKR]->getSprites()[i].setTexture(breakR);
			states[BREAKR]->getSprites()[i].setTextureRect(sf::IntRect(width, 0, 40, 50));
			states[BREAKR]->getSprites()[i].setScale(2, 2);
		}

		invincible = false;
		coolDown.restart();
		delayInFollow = 30;
	}

	virtual void followLeader(const int const** pathToFollow)
	{
		
	}
	virtual void moveUp(bool spacePressed,int& unusedHere)
	{
		if(!spacePressed)
		{

			velocityY = -19.5;
			onGround = false;
		}
	}
	void glideAndFollowTails()
	{

	}
	void coolingDownCount()
	{
		if (GlideCount >= 11 && coolDown.getElapsedTime().asSeconds()>1)
		{
			GlideCount = 0;
			coolDown.restart();
		}
	}
	void useSpecialAbilty(char**lvl,int height,int width)
	{
		cout << coolDown.getElapsedTime().asSeconds()<<"\n";
		if(GlideCount <=10)
		{
			cout << "inside";
				if (direction == 1)
			{
				indexAnimation = BREAKR;
			}
			if (direction == 0)
			{
				indexAnimation = BREAKL;
			}
			cout << "BreakCalled";
			Break(lvl,14,width);
			if (audio && GlideCount == 0) {
				audio->playSound(audio->getSpecialWarp());
			}
			//coolDown.restart();
		}
		states[indexAnimation]->RunAnimation();
		coolingDownCount();
	}
	void Break(char**lvl,int height,int width)
	{
		int glidePixels = 5;
		int checkX = (indexAnimation == BREAKR) ? x + getPwidth() + glidePixels : x - glidePixels;
		int checkY = y + getPheight() / 2; // Middle of player vertically for more accurate collision
		int tileX = checkX / 64;
		int tileY = checkY / 64;

		//  checking bounds here firstxly
		if (tileX < 0  || tileY < 0 || tileY >= 14)
			return;
		if (checkCollisionSpikes(lvl, checkX, checkY,height,width))
		{
			return;
		}
		// If block is breakable
		if (checkCollisionExceptSpikes(lvl, checkX, checkY,height,width))
		{
			if (audio) {
				audio->playSound(audio->getGlassSmash());
			}

			lvl[tileY][tileX] = 's'; // Mark it as emptyspace pwnow
			cout << "Collision Detected and Block Broken\n";
		}
		checkY = y - 5;
		tileY = checkY / 64;
		if (checkCollisionExceptSpikes(lvl, checkX, checkY,height,width))
		{

			if (audio) {
				audio->playSound(audio->getGlassSmash());
			}

			lvl[tileY][tileX] = 's'; // Mark it as emptyspace pwnow
			cout << "Collision Detected and Block Broken\n";
		}
		// Glide movement
		if (indexAnimation == BREAKR)
			x += glidePixels;
		else
			x -= glidePixels;
		GlideCount++;
	}
	void moveLeft()
	{
		if(indexAnimation != BREAKL && indexAnimation != BREAKR)
		{
			if (velocityX > 0)
			{
				//velocityX-=

			}
			{
				x += velocityX;
				if (velocityX - acceleration > -max_speed)
				{
					velocityX -= acceleration;
				}
				if (velocityX > -10)
				{
					indexAnimation = LEFT;
					states[LEFT][0].RunAnimation();/*&& topLeft != 'q' && topLeft != 'e';*/
				}
				else
				{
					indexAnimation = LEFTRUN;
					states[LEFTRUN][0].RunAnimation();
				}
			}
			direction = 0;
		}
	}
	void moveRight()
	{
		if(indexAnimation != BREAKL && indexAnimation != BREAKR)
		{
			x += velocityX;
			if (velocityX + acceleration < max_speed)
			{
				velocityX += acceleration;
			}
			if (velocityX < 10)
			{
				indexAnimation = RIGHT;
				states[RIGHT][0].RunAnimation();/*&& topLeft != 'q' && topLeft != 'e';*/
				//cout<<"right  animation running";
			}
			else
			{
				indexAnimation = RIGHTRUN;
				states[RIGHTRUN][0].RunAnimation();
			}
			direction = 1;
		}
	}
};