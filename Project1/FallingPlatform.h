#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class FallingPlatform
{
	Texture* fallingTexture;
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
		width = 64 ;
		height = 64 ;
		//fallingTexture.loadFromFile("Data/brick1.png");
		fallingTexture = new Texture[3];
		fallingTexture[0].loadFromFile("Data/brick1.png");
		fallingTexture[1].loadFromFile("Data/snowTiles.jpg");
		fallingTexture[2].loadFromFile("Data/wallvl31.png");

		//fallingSprite.setTexture(fallingTexture);
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
		int scY, scX;
		fallingSprite.setTexture(fallingTexture[levelIndex]);
		switch (levelIndex)
		{
		case 0:

			fallingSprite.setScale(0.66, 0.67);

			break;
		case 1:

			fallingSprite.setScale(1.18, 1.18);
			break;
		case 2:

			fallingSprite.setScale(1.88, 1.88);
			break;
		}
		fallingSprite.setPosition(x-offset_x, y);
		window.draw(fallingSprite);
	}
	
};
