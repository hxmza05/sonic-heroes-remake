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
	Level3(char** level = nullptr, Enemy*** e = nullptr)
	{
		height = 14;
		width = 300;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}
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
		moveable = new MoveablePlatform(0, 0, 0, 0);
		designlvl("lvl3.txt");
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
		default: return 's';
		}
	}
	void designlvl(const char* filename)
	{
		cout << "\n\n\nIn desgin function for level 3\n\n\n";
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
			cout << endl;
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

	virtual void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player,HUD&)
	{

	}

};