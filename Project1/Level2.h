#pragma once
#include<fstream>
#include"Level.h"
#include"Crabmeat.h"
#include"Beebot.h"
#include"Motobug.h"
#include"MoveablePlatform.h"
class Level2 : public Level
{
	MoveablePlatform* moveable;
	Crabmeat** crabs;
	Beebot** bees;
	Motobug** MotoBugs;

public:
	Level2(char** level = nullptr, Enemy*** e = nullptr) 
	{
		height = 14;
		width = 110;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}
		crabs = new Crabmeat * [5];
		bees = new Beebot * [5];
		MotoBugs = new Motobug * [5];
		for (int i = 0; i < 5; i++)
		{
			crabs[i] = new Crabmeat();
			bees[i] = new Beebot();
			MotoBugs[i] = new Motobug();
		}
		moveable = new MoveablePlatform(0,0,0,0);
		designlvl("lvl2.txt");
	}
	void designlvl(const char* filename)
	{
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
				file >> lvl[i][j];
			}
		}
		file.close();
	}
	MoveablePlatform* getMoveable() override
	{
		return moveable;
	}
};