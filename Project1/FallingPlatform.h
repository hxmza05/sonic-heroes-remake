#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class FallingPlatform
{
	Texture fallingTexture;
	Sprite fallingSprite;
	float x;
	float y;
	bool activated;
	int width;
	int height;
public:
	FallingPlatform(float _x = 0, float _y = 0)
	{
		x = _x;
		y = _y;
		activated = false;
		width = 64 * 3;
		height = 64 * 4;
		fallingTexture.loadFromFile("Data/brick1.png");
		fallingSprite.setTexture(fallingTexture);
		//fallingSprite.setScale(11, 5);
	}
	float& getx()
	{
		return x;
	}
	float& gety()
	{
		return y;
	}
	int getWidth()
	{
		return width;
	}
	int getHeight()
	{
		return height;
	}
	bool& getActivated()
	{
		return activated;
	}
	void shouldItActivate(float playerx)
	{
		if (playerx + 64*4 >= x)
		{
			activated = true;
		}
	}
	void fall()
	{
		if(y < 900)
			y += 5;
	}
	void draw(RenderWindow& window,float offset_x,int levelIndex)
	{
		switch (levelIndex)
		{
		case 0:
			fallingTexture.loadFromFile("Data/brick2.png");
			fallingSprite.setScale(1.03, 1.03);

			break;
		case 1:
			fallingTexture.loadFromFile("Data/snowTiles.jpg");
			fallingSprite.setScale(1.5, 1.5);
			break;
		case 2:
			fallingTexture.loadFromFile("Data/wallvl31.png");
			fallingSprite.setScale(2, 2);
			break;
		}
		fallingSprite.setPosition(x-offset_x, y);
		window.draw(fallingSprite);
	}
	
};
