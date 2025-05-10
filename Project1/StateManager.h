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
	int screen_x ;
	int screen_y ;
public:
	StateManager(Leaderboard* leaderboard, RenderWindow& w) :window(w)
	{
		//window = w;
		screen_x = 1200;
		screen_y = 900;
		
		stateIndex = 1;
		//menu = new Menu(screen_x, screen_y, &leaderboard);
		menu = new Menu(screen_x, screen_y, leaderboard);
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
					window.close();
				}
				if (!menu->isGameStateActive()) 
				{
					menu->update(window, event);
				}
			}
			/*if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}*/
			window.clear();
			if (!stateIndex)
			{
				menu->work(window,event);
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
	//{
	//	screen_x = 1200;
	//	screen_y = 900;
	//	menu(1200, 900, &leaderboard);
	//	window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog", Style::Close | Style::Resize | Style::Close);
	//	window.setVerticalSyncEnabled(true);
	//	window.setFramerateLimit(60);
	//
	//}
};
