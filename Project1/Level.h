#pragma once
#include<iostream>
#include"Enemy.h"
#include"Collectibles.h"
#include"Obstacle.h"
#include"MoveablePlatform.h"
#include"FallingPlatform.h"

using namespace std;
#include"Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Level
{
protected:
	//Collectible*** collectibles;
	//Obstacle** obstacles;
	const int endMark;
	Texture backgorund;
	Sprite bgSprite;
	char** lvl;
	 int height;
	 int width;
	//Enemy*** enemies;
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
	virtual FallingPlatform**getFalling() = 0;
	//virtual void handleEnemies() = 0;
	virtual void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player) = 0;

	//{
	//	for (int i = 0; i < height; i += 1)
	//	{
	//		for (int j = 0; j < width; j += 1)
	//		{
	//			if (lvl[i][j] == 's')
	//				continue;
	//			else if (lvl[i][j] == 'w')
	//			{
	//				bgSprite.setPosition(j * cell_size - offset_x, i * cell_size);
	//				window.draw(bgSprite);
	//			}
	//		}
	//	}
	//}

	//Level2(Texture T,Sprite S,)
	//{
	//	enemies = new * Enemy[3];
	//	enemies[0][0] = new 
	//}
};

