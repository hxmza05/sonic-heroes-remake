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

	int crabCount;
	int crab_start;
	int crab_end;
	Crabmeat* crab;

	int beeCount;
	int bee_start;
	int bee_end;
	bool* occupiedColumns;
	Beebot* beebot;

	int motobugCount;
	int motobug_start;
	int motobug_end;
	Motobug* motobugs;


	int batbrainCount;
	int batStart;
	int batEnd;
	Batbrain* bats;


	Enemy** enemies;
	int enemyCount;
	int j_start;
	int cell_size;

public:
	Level3(Audio* ad)
	{
		this->audio = ad;
		cell_size = 64;
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
		friction = 0.4;
		height = 14;
		width = 300;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}
		designlvl("lvl3.txt");

		enemyCount = 0;
		TotalEnemyCount = 18;
		enemies = new Enemy * [TotalEnemyCount];

		j_start = 5;
		crab_start = 5;
		crab_end = 9;
		crabCount = 5;

		for (int i = 0; i < crabCount; i++) {

			crab = new Crabmeat();
			crab->setAudio(audio);

			if (crab->getCrabCoordinates(lvl, height, width, crab_start, crab_end, j_start))
			{
				crab->move_crabs(cell_size);
				enemies[enemyCount++] = crab;
			}
		}


		j_start = 7;
		bee_start = 5;
		bee_end = 8;
		beeCount = 5;
		occupiedColumns = new bool[width]();

		for (int i = 0; i < beeCount; i++) {

			beebot = new Beebot();
			beebot->setAudio(audio);

			if (beebot->getBeebotCoordinates(lvl, height, width, bee_start, bee_end, j_start, occupiedColumns))
			{
				beebot->move_beebots(cell_size);
				enemies[enemyCount++] = beebot;
			}
		}


		j_start = 0;
		motobug_start = 8;
		motobug_end = 12;
		motobugCount = 4;


		for (int i = 0; i < motobugCount; i++) {

			motobugs = new Motobug();
			motobugs->setAudio(audio);

			if (motobugs->getMotobugCoordinates(lvl, height, width, motobug_start, motobug_end, j_start))
			{
				motobugs->move_motobugs(cell_size);
				enemies[enemyCount++] = motobugs;
			}

		}

		batbrainCount = 4;
		batStart = 0;
		batEnd = 0;

		for (int i = 0; i < batbrainCount; ++i) {

			bats = new Batbrain();
			bats->setAudio(audio);

			if (bats->getBatbrainCoordinates(lvl, height, width, batStart, batEnd, cell_size)) {
				enemies[enemyCount++] = bats;
			}

		}


		falling = new FallingPlatform * [fallingCount = 15];
		for (int i = 0, f = 64; i < fallingCount; i++, f++)
			falling[i] = new FallingPlatform(64 * f, 350);
		moveable = new MoveablePlatform(0, 0, 0, 0);
		levelEnd = (295 - 5) * 64;
		levelTimer = 150;
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

	void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player, HUD& hud, bool& gameOver) override
	{
		for (int i = 0; i < enemyCount; i++)
		{
			if (!enemies[i]->alive() && enemies[i]->deathDone())
				continue;

			enemies[i]->update(lvl, player, cell_size, hasKnockedBack, tempVelocity, onGround, indexAnimation, hud, gameOver);

			enemies[i]->drawExtra(window, offset_x);
		}
	}
	void drawEnemies(RenderWindow& window, float offset_x) override
	{

		for (int i = 0; i < enemyCount; i++)
		{
			if (!enemies[i]->deathDone())
				enemies[i]->draw(window, offset_x);
		}
	}
	bool hasLevelEnded(float x)
	{
		return true;
	}
	Eggstinger* getStinger() { return nullptr; }

	/*
	~Level3()
	{
		for (int i = 0; i < height; i++)
		{
			delete[] lvl[i];
		}
		delete[] lvl;

		for (int i = 0; i < enemyCount; i++)
		{
			delete enemies[i];
		}
		delete[] enemies;

		for (int i = 0; i < fallingCount; i++)
		{
			delete falling[i];
		}
		delete[] falling;

		delete[] occupiedColumns;

		delete moveable;
	}
	*/
};