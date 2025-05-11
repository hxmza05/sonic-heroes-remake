#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
//////////////////////////////
#include"Player.h"
#include"Sonic.h"
#include"Collectibles.h"
#include"Rings.h"
#include"Motobug.h"
#include"Enemy.h"
#include"Crabmeat.h"
#include"Beebot.h"
#include"Batbrain.h"
#include"Eggstinger.h"
#include"Menu.h"
#include"Knuckles.h"
#include"TailedFox.h"
#include"Team.h"
#include"Game.h"
#include"StateManager.h"

class StateManager
{
	Menu *menu;
	Game* game;
	int stateIndex;
	RenderWindow& window;
	Leaderboard* leaderboard;
	Audio audio;
	int screen_x ;
	int screen_y ;

public:
	StateManager(Leaderboard* leaderboard, RenderWindow& w) :window(w)
	{
		this->leaderboard = leaderboard;
		audio.loadAllSounds();
		//window = w;
		screen_x = 1200;
		screen_y = 900;
		
		stateIndex = 1;
		//menu = new Menu(screen_x, screen_y, &leaderboard);
		menu = new Menu(screen_x, screen_y, leaderboard, &audio);
		game = new Game();
	}
	int getStateIndex()
	{
		return stateIndex;
	}
	void setStateIndex(int index)
	{
		stateIndex = index;
	}
	
	void run()
	{
		Event event;
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					leaderboard->addNewScore(menu->getPlayerName(),game->getHUD().getScore());
					game->saveGame(menu->getRefToPlayerName());
					window.close();
				}
				if (!menu->isGameStateActive())
				{
					menu->update(window, event);
				}
				else break;
			}
			window.clear();
			if (!stateIndex)
			{
				menu->work(window,event,game);
				if (menu->isGameStateActive())
				{
					stateIndex = 1;
				}
			}
			//cout << "State Index : " << stateIndex << endl;
			if (stateIndex == 1)
			{
				game->play(window);
			}
			window.display();
		}

	}
};
