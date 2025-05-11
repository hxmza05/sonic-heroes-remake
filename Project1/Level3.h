#pragma once
#include<fstream>
#include"Level.h"
#include"Crabmeat.h"
#include"Beebot.h"
#include"Motobug.h"
#include"Batbrain.h"
#include"MoveablePlatform.h"
#include"HUD.h"

class Level3 : public Level
{
	MoveablePlatform* moveable;
	Crabmeat** crabs;
	Beebot** bees;
	Motobug** MotoBugs;
	Batbrain** bats;
public:
	Level3(Audio* ad)
	{
		this->audio = ad;
		backGround.loadFromFile("Data/lvl3Bg.jpeg");
		backGroundSprite.setTexture(backGround);
		unsigned int bgWidth = 626;
		unsigned int bgHeight = 357;
		scX = (float)1200 / bgWidth;
		scY = (float)900 / bgHeight;
		backGroundSprite.setScale(scX, scY);
		backGroundSprite.setScale(scX, scY);
		walls = new Sprite[4];
		wallText1.loadFromFile("Data/wallvl31.png");
		wallText2.loadFromFile("Data/wallvl32.png");
		wallText3.loadFromFile("Data/wallvl33.png");
		walls[0].setTexture(wallText1);
		walls[1].setTexture(wallText2);
		walls[2].setTexture(wallText3);
		walls[3].setTexture(wallText4);
		for (int i = 0;i < 3;i++)
		{
			walls[i].setScale(2, 2);
		}
		friction = 0.3;
		height = 14;
		width = 300;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}
		designlvl("lvl3.txt");

		crabs = new Crabmeat * [5];
		bees = new Beebot * [5];	
		MotoBugs = new Motobug * [5];
		bats = new Batbrain * [5];
		for (int i = 0; i < 5; i++)
		{
			crabs[i] = new Crabmeat();
			bees[i] = new Beebot();
			MotoBugs[i] = new Motobug();
			bats[i] = new Batbrain();
		}
		falling = new FallingPlatform * [fallingCount = 15];
		for (int i = 0, f = 64; i < fallingCount; i++, f++)
			falling[i] = new FallingPlatform(64 * f, 350);
		moveable = new MoveablePlatform(0, 0, 0, 0);
		levelEnd = (295 - 5) * 64;
	}
	char getMapValues(int val)
	{
		switch (val)
		{
		case 0:
			return 's';
		case 1:
			return 'q';
		case 2:
			return 'w';
		case 3:
			return 'e';
		case 4:
			return 'p';
		case 5:
			return 'r';
		case 6:
			return 'i';
		case 7:
			return 'j';
		case 8:
			return 'l';
		case 9:
			return 'b';

		default:
			return 's';
		}
	}
	void designlvl(const char* filename)
	{
		//cout << "\n\n\nIn desgin function for level 3\n\n\n";
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
	MoveablePlatform* getMoveable() override
	{
		return moveable;
	}
	virtual FallingPlatform** getFalling()
	{
		return nullptr;
	}
	void setAudio(Audio* a) override {
		audio = a;
		audio->playLevelMusicByIndex(audio->getLevel3Music());
	}

	virtual void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player,HUD&,bool&)
	{

	}
	void drawEnemies(RenderWindow& window, float offset_x)
	{
		for (int i = 0; i < enemyCount; ++i)
		{
			if (!enemies[i]->deathDone() && enemies[i]->deathDone())
				enemies[i]->draw(window, offset_x);
		}
	}
	bool hasLevelEnded(float x)
	{
		return true;
	}

};