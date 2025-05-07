#pragma once
#include<fstream>
#include"Level.h"
#include"Crabmeat.h"
#include"Beebot.h"
#include"MoveablePlatform.h"
#include"FallingPlatform.h"

class Level1 : public Level
{
	FallingPlatform **falling;
	MoveablePlatform* moveable;
	Crabmeat** crabs;
	Beebot** bees;
public:
	Level1()
	{
		height = 14;
		width = 200;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}

		crabs = new Crabmeat * [5];
		bees = new Beebot * [5];
		for (int i = 0; i < 5; i++)
		{
			crabs[i] = new Crabmeat();
			bees[i] = new Beebot();
		}
		falling = new FallingPlatform * [8];
		for(int i = 0,f = 32;i < 8;i++,f++)
			falling[i] = new FallingPlatform(64 * f, 500);
		moveable = new MoveablePlatform(1000,450,850,1500);
		designlvl("lvl1.txt");

	}
	MoveablePlatform* getMoveable() override
	{
		return moveable;
	}
	virtual FallingPlatform** getFalling()
	{
		return falling;
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
		cout << "\n\n\nIn desgin function\n\n\n";
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
				cout << "lvl[" << i << "][" << j << "] = " << lvl[i][j] << endl;
			}
			cout << endl;
		}
		file.close();
	}
};