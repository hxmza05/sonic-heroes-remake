#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;
class HUD
{
	int score;
	int ringsCollected;
	int lives;
	Clock timer;
public:
	HUD()
	{
		score = 0;
		ringsCollected = 0;
		lives = 100;
	}
	int&getScore()
	{
		return score;
	}
	int& getRings()
	{
		return ringsCollected;
	}
	int& getLives()
	{
		return lives;
	}
};