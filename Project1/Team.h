//#pragma once
//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Window.hpp>
//#include <iostream>
//#include"Player.h"
//#include"Sonic.h"
//#include"TailedFox.h"
//#include"Knuckles.h"
//class Team
//{
//	Player** team;
//	int playerIndex;
//public:
//	Team()
//	{
//		team = new Player * [3];
//		team[0] = new Sonic();
//		team[1] = new TailedFox();
//		team[2] = new Knuckles();
//		playerIndex = 0;
//	}
//	int& getPlayerIndex()
//	{
//		return playerIndex;
//	}
//	Player* getPlayer()
//	{
//		return team[playerIndex];
//	}
//	~Team()
//	{
//		for (int i = 0; i < 3; i++)
//		{
//			delete team[i];
//		}
//		delete[] team;
//	}
//};