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
public:
	BossLevel(char** level = nullptr)
	{
		//moveable = new MoveablePlatform(0,0,0,0) ;
		height = 14;
		width = 60;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}

		designlvl("bosslvl.txt");

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

	virtual FallingPlatform** getFalling()
	{
		return nullptr;
	}
	/*MoveablePlatform* getMoveable() override
	{
		return moveable;
	}*/
};