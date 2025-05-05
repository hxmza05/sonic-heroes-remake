#pragma once
#include<fstream>
#include"Level.h"
class BossLevel : public Level
{
public:
	BossLevel(char** level = nullptr, Enemy*** e = nullptr)
	{
		height = 14;
		width = 110;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}
	}
	void designlvl(const char* filename)
	{
		ifstream file("lvl4.txt");
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
};