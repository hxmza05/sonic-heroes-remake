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
#include"Audio.h"

class StateManager
{
	Audio audio;
	Menu *menu;
	Game* game;
	Clock leaderBoardClk;
	int stateIndex;
	RenderWindow& window;
	Leaderboard* leaderboard;
	int screen_x ;
	int screen_y ;
	bool showLeaderBoard;
	Clock segaclock;
	//bool showLeaderBoard;
	Music menuMusic;
	bool menuBeingPlayed;
	Texture leaderBoard;
	Sprite leaderBoardSp;
	Text windowClose;
	Font font;
	bool nameAdded;
public:
	StateManager(Leaderboard* leaderboard, RenderWindow& w) :window(w)
	{
		nameAdded =0;
		showLeaderBoard = false;
		this->leaderboard = leaderboard;
		audio.loadAllSounds();
		//window = w;
		screen_x = 1200;
		screen_y = 900;
		
		stateIndex = 0;
		//menu = new Menu(screen_x, screen_y, &leaderboard);
		menu = new Menu(screen_x, screen_y, leaderboard);
		menu->setAudio(&audio);
		game = new Game(&audio);
		menuMusic.openFromFile("Audio/sonicMenuSong.ogg");
		menuBeingPlayed = false;
		leaderBoard.loadFromFile("Data/levelTransition.png");
		leaderBoardSp.setTexture(leaderBoard);
		leaderBoardSp.setPosition(0, 0);
		int scX = (float)1200 / leaderBoard.getSize().x;
		int scY = (float)900 / leaderBoard.getSize().y;
		leaderBoardSp.setScale(scX, 3.75);
		font.loadFromFile("Fonts/NiseSegaSonic.ttf");

		windowClose.setFont(font);
		windowClose.setString("Window Closing in : ");
		windowClose.setCharacterSize(24);
		windowClose.setFillColor(Color::Blue);
		windowClose.setPosition(700, 15);
		windowClose.setOutlineColor(sf::Color::Black);
		windowClose.setOutlineThickness(4);



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
				 if (stateIndex == 1)
				{
					game->handleInput(event);
				}
			}
			window.clear();
			if (!stateIndex)
			{
		
				menu->work(window,event,game);
				//if (audio.getCurrentlyPlayingMusic() != audio.getBossMusic() && segaclock.getElapsedTime().asSeconds() > 10/*&& menu->getSegaMusicPlayed()*/)
				//{
					//audio.playLevelMusicByIndex(audio.getBossMusic());
				//}
				if (menu->isMenuFullyReady() && !menuBeingPlayed)
				{
					cout << "HERE";
					menuMusic.play();
					menuMusic.setLoop(true);
					menuMusic.setVolume(audio.getMusicVolume());
					menuBeingPlayed = true;
				}
				if (menuBeingPlayed)
				{
					menuMusic.setVolume(audio.getMusicVolume());
				}
				if (menu->isGameStateActive())
				{
					stateIndex = 1;
					//audio.playLevelMusicByIndex(game->getLevelIndex());
				}
			}
			//cout << "State Index : " << stateIndex << endl;
			if (stateIndex == 1)
			{
				menuBeingPlayed = false;
				menuMusic.stop();
				if (game->play(window))
				{
					if (game->WantToReturnToMenu())
					{
						stateIndex = 0;
						menu->returnToMenuFromGame();
						menu->setAudio(&audio);
						//audio.playLevelMusicByIndex(audio.getBossMusic());
						game->resetReturnToMenuFlag(); 
						continue;
					}
					else
					{
						showLeaderBoard = true;
						stateIndex = 2;
						leaderBoardClk.restart();
						window.clear();
					}
				}

			}
			if (stateIndex == 2)
			{
				if(!nameAdded)
				{
					leaderboard->addNewScore(menu->getPlayerName(), game->getHUD().getScore());
					nameAdded = 1;
				}
				menuBeingPlayed = false;
				if (leaderBoardClk.getElapsedTime().asMilliseconds() < 9000)
				{
					int rem = 9 - leaderBoardClk.getElapsedTime().asSeconds();
					windowClose.setString("Window Closing in : " + to_string(rem));
					window.draw(leaderBoardSp);
					window.draw(windowClose);
					leaderboard->draw(window);
					
				}
				else
				{
					game->saveGame(menu->getRefToPlayerName());
					window.close();
				}
			}
			window.display();
		}
	}
	/*
	~StateManager()
	{
		delete menu;
		delete game;
	}
	*/
};
