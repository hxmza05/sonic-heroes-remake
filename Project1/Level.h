#pragma once
#include<iostream>
#include"Enemy.h"
#include"Collectibles.h"
#include"Obstacle.h"
#include"MoveablePlatform.h"
#include"FallingPlatform.h"
#include"HUD.h"

using namespace std;
#include"Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Level
{
protected:
	float levelEnd;
	//Collectible*** collectibles;
	//Obstacle** obstacles;
	const int endMark;
	Texture backgorund;
	Sprite bgSprite;
	char** lvl;

	int height;
	int width;
	float friction;

public:
	Level(char** level = nullptr) :endMark(0)
	{

	}
	virtual void designlvl(const char* filename) = 0;
	
	void drawLevel(RenderWindow& window, const int height, const int width, char** lvl, Sprite walls[], const int cell_size, int offset_x)
	{
		for (int i = 0; i < height; i += 1)
		{
			for (int j = 0; j < width; j += 1)
			{
				if (lvl[i][j] == 's')
					continue;
				else if (lvl[i][j] == 'w')
				{
					walls[0].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[0]);
				}
				else if (lvl[i][j] == 'q')
				{
					walls[1].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[1]);
				}
				else if (lvl[i][j] == 'e')
				{
					walls[2].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[2]);
				}
				else if (lvl[i][j] == 'p')
				{
					walls[3].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[3]);
				}
				else if (lvl[i][j] == 'i') 
				{
					walls[3].setScale(1.f, -1.f); 
					walls[3].setPosition(j * cell_size - offset_x, (i + 1) * cell_size);
					window.draw(walls[3]);
					walls[3].setScale(1.f, 1.f); 
				}
			}
		}
	}
	char** getLvl()
	{
		return lvl;
	}
	int getHeight()
	{
		return height;
	}
	int getWidth()
	{
		return width;
	}
	virtual MoveablePlatform* getMoveable()
	{
		return nullptr;
	}
	float& getFriction()
	{
		return friction;
	}
	virtual FallingPlatform**getFalling() = 0;
	//virtual void handleEnemies() = 0;
	virtual void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player,HUD& hud,bool& ) = 0;
	virtual void drawEnemies(RenderWindow& window, float offset_x) = 0;

	bool hasLevelEnded(float x)
	{
		if (x >= levelEnd)
			return true;
		return false;
	}




};

