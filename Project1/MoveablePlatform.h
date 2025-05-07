#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class MoveablePlatform
{
	Texture moveableTexture;
	Sprite moveableSprite;
	float x;
	float y;
	float rangeLeft;
	float rangeRight;
	int direction;
	int widthPlatform;
public:
	MoveablePlatform(float x = 0, float y= 0,float rL = 0,float rR = 0)
	{
		this->x = x;
		this->y = y;
		this->widthPlatform = 144;
		rangeLeft= rL;
		rangeRight = rR;
		direction = 0;
		moveableTexture.loadFromFile("Data/moveable.png");
		moveableSprite.setScale(3.5, 3.5);
		moveableSprite.setTexture(moveableTexture);
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	int getWidth()
	{
		return widthPlatform;
	}
	void setX(float x)
	{
		this->x = x;
	}
	void setY(float y)
	{
		this->y = y;
	}
	void setWidth(int widthPlatform)
	{
		this->widthPlatform = widthPlatform;
	}
	bool move(float&player_x,float&player_y,int player_width,int&playerheight,bool &onGround)
	{
		bool movePlayerAsWell = checkCollisionWithPlayer( player_x,  player_y,  player_width,  playerheight);
		bool returnState = false;
		if (movePlayerAsWell)
		{
			player_y = y - playerheight - 10;
			returnState = true;
			onGround = true;
			
			cout << "player on the moveable wall now\n\n";
		}
		if (x <= rangeLeft && direction == 0)
		{
			direction = 1;
		}
		else if (x >= rangeRight && direction == 1)
		{
			direction = 0;
		}
		if (direction == 1)
		{
			x += 3;
			if (movePlayerAsWell)
				player_x += 3;
		}
		else if (direction == 0)
		{
			x -= 3;
			if (movePlayerAsWell)
				player_x -= 3;
		}
		return returnState;
	}
	bool checkCollisionWithPlayer(float player_x, float player_y, int player_width, int playerheight)
	{
		return ((player_x + player_width > x && player_x < x + widthPlatform) && ((player_y + playerheight >= y - 10)&&(player_y + playerheight <= y + 10)));
	}
	void draw(RenderWindow& window,float offset_x)
	{
		cout << "Drawing moveable at  "<<x-offset_x<<"and "<<y<<"\n";

		moveableSprite.setPosition(x - offset_x, y);
		window.draw(moveableSprite);
	}
};