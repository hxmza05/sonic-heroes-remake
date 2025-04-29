#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Animation
{
	Clock animationClk;
	Sprite* sprites;
	int index = 0;
	const int totalSprites;
public:
	Animation(int totalSprites): totalSprites(totalSprites)
	{
		sprites = new Sprite[totalSprites];
	}
	Sprite* getSprites()
	{
		return sprites;
	}
	int getIndex()
	{
		return index;
	}
	void RunAnimation()
	{
		if (index == totalSprites - 1 && animationClk.getElapsedTime().asMilliseconds() > 50)
		{
			index = 0;
			animationClk.restart();

		}
		else if(animationClk.getElapsedTime().asMilliseconds() > 50)
		{
			index++;
			animationClk.restart();

		}
	}
	~Animation()
	{
		delete[] sprites;
	}
};