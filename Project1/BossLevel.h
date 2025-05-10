#pragma once
#include<fstream>
#include"Level.h"
#include"MoveablePlatform.h"

class BossLevel : public Level
{
	//MoveablePlatform* moveable;
	//Enemy** enemies;
	//Collectibles** collectibles;
	//Obstacle** obstacles;
	//int height;
	//int width;

	FallingPlatform** falling;
	MoveablePlatform* moveable;

	Enemy** enemies;
	int enemyCount;
	int TotalEnemyCount;
	int cell_size;

	Eggstinger* stinger;

public:
	BossLevel()
	{
		friction = 0.3;
		cell_size = 64;
		height = 14;
		width = 24;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}

		moveable = nullptr;
		falling = nullptr;


		designlvl("bosslvl.txt");

		enemyCount = 0;
		TotalEnemyCount = 1;
		enemies = new Enemy * [TotalEnemyCount];
		
		stinger = new Eggstinger();
		stinger->setPosition(12 * cell_size, 2 * cell_size, 0, 0);
	    enemies[enemyCount++] = stinger;
		

	}

	char  getMapValues(int val)
	{
		switch (val)
		{
			case 0: return 's';
			case 1: return 'q';
			case 2: return 'w';
			case 3: return 'e';
			case 4: return 'p';
			case 5: return 'r';
			case 6: return 'p';
			case 9: return 'b';
			default: return 's';
		}
	}
	void designlvl(const char* filename)
	{
		//cout << "\n\n\nIn desgin function of boss\n\n\n";
		ifstream file(filename);
		if (!file.is_open())
		{
			cerr << "Error opening file: " << filename << endl;
			return;
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int wall;
				file >> wall;
				lvl[i][j] = getMapValues(wall);
				//cout << "lvl[" << i << "][" << j << "] = " << lvl[i][j] << endl;
			}
			//cout << endl;
		}
		file.close();
	}

	virtual FallingPlatform** getFalling()
	{
		return nullptr;
	}
	MoveablePlatform* getMoveable() override
	{
		return moveable;
	}
	void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player, HUD& hud, bool& gameOver) override
	{
		for (int i = 0; i < enemyCount; ++i)
		{
			if (!enemies[i]->alive())
				continue;  

			enemies[i]->update(lvl, player, cell_size, hasKnockedBack, tempVelocity, onGround, indexAnimation, hud, gameOver);

			enemies[i]->drawExtra(window, offset_x);
		}
	}

	void drawEnemies(RenderWindow& window, float offset_x) override
	{
		for (int i = 0; i < enemyCount; ++i)
		{		
			if (enemies[i]->alive())
				enemies[i]->draw(window, offset_x);
		}
	}

	bool hasLevelEnded(float x) { return true; }

};