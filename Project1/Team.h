#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include"Player.h"
#include"Sonic.h"
#include"TailedFox.h"
#include"Knuckles.h"
class Team
{
	Player** team;
	int playerIndex;
	//stores x and y coordinates of the leader
	int** leadersPath;
	int pathIndex;
public:
	Team()
	{
		team = new Player * [3];
		team[0] = new Sonic();
		team[1] = new TailedFox();
		team[2] = new Knuckles();
		playerIndex = 0;
		leadersPath = new int*[100];
		for (int i = 0;i < 100;i++)
		{
			leadersPath[i] = new int[2];
		}
		pathIndex = 0;
	}
	int getPlayerIndex()
	{
		return playerIndex;
	}
	void switchPlayer()
	{
		if (playerIndex == 2)
		{
			playerIndex = 0;
			return;
		}
		playerIndex++;

	}
	Player** getPlayer()
	{
		return team;
	}
	int** getLeadersPath()
	{
		return leadersPath;
	}
	int getPathIndex()
	{
		return pathIndex;
	}
	void switchLeader()
	{

	}
	void autoMoveFollowers()
	{
		for (int i = 0;i < 3;i++)
		{
			if (i == playerIndex)
				continue;
			if (team[i]->getHasStartedFollowing() == false)
			{
				team[i]->checkDelayNow(pathIndex);
			}
			else 
			
			{
				team[i]->updateDelay();
				cout << "Path index LEader's = " << pathIndex << "----- tailed fox's = " << team[1][0].getDelayinFollow() << "----- knuckel's = " << team[2][0].getDelayinFollow() << "\n";
				team[i][0].autoMove(leadersPath[team[i][0].getDelayinFollow()][0], leadersPath[team[i][0].getDelayinFollow()][1]);
			}
		}
	}
	/*void runAnimation()
	{
		for (int i = 0;i < 3;i++)
		{
			team[i].
		}
	}*/
	void draw(RenderWindow& window,int offsetx)
	{
		for (int i = 0;i < 3;i++)
		{
			team[i]->draw_player(window, team[i]->getStates()[0]->getSprites()[team[i]->getStates()[0]->getIndex()], offsetx);
		}
	}
	void storePath()
	{
		leadersPath[pathIndex][0] = team[playerIndex]->getx();
		leadersPath[pathIndex][1] = team[playerIndex]->gety();
		pathIndex++;
		if (pathIndex == 100)
		{
			pathIndex = 0;
		}

	}

	~Team()
	{
		for (int i = 0; i < 3; i++)
		{
			delete team[i];
		}
		delete[] team;
	}
};