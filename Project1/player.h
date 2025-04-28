#pragma once
#include<iostream>
using namespace std;
#include"Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
#define LEFT 0
#define RIGHT 1
#define UPL 2
#define UPR 3
#define EDGEL 4
#define EDGER 5
#define LEFTRUN 6
#define RIGHTRUN 7
#define PUSHLEFT 8
#define PUSHRIGHT 9
#define JUMPL 10
#define JUMPR 11

class Player
{
	float x;
	float y;
	bool hasCollided;
	bool hasKnockedBack;
	float max_speed;
	float velocityX;
	float velocityY;
	bool spacePressed;// our own defined
	bool collisionDetectedOffGround;
	float jumpStrength; // Initial jump velocity
	float gravity;        // Gravity acceleration
	///////////////////////////////////////
	/// for knockBack parabolic Trajecotry/
	///////////////////////////////////////
	float tempTerminalVelocityY;
	float tempVelocityY;
	float tempGravity;

	bool onGround;
	float terminal_Velocity;
	float acceleration;
	////////////////////////////
	int Pheight;
	int Pwidth;
	// only to adjust the player's hitbox
	int hit_box_factor_x;
	int hit_box_factor_y;
protected:
	float scale_x = 2.5;
	float scale_y = 2.5;
	Animation** states;
	int indexAnimation;
	int totalAnimations;
	int* trail;
public:
	Player()
	{
		x = 150;
		y = 150;
		hasCollided = false;
		hasKnockedBack = false;
		max_speed = 20;
		velocityX = 1;
		velocityY = 9.8;
		//spacePressed = false;// our own defined
		collisionDetectedOffGround = false;
		jumpStrength = -20; // Initial jump velocity
		gravity = 1;        // Gravity acceleration
		tempTerminalVelocityY = 15;
		tempVelocityY = -7;
		tempGravity = 0.6;
		onGround = false;
		acceleration = 1;
		Pheight = 35 * 2.5;
		Pwidth = 24 * 2.5;
		hit_box_factor_x = 8 * 2.5;
		hit_box_factor_y = 5 * 2.5;
		states = nullptr;
		scale_x = 2.5;
		scale_y = 2.5;
		indexAnimation = 0;
		totalAnimations = 0;
		terminal_Velocity = 20;
		trail = new int[20];
	}
	float& getx()
	{
		return x;
	}
	float& gety()
	{
		return y;
	}
	float& getVelocityX()
	{
		return velocityX;
	}
	float& getVelocityY()
	{
		return velocityY;
	}
	float& getJumpStrength()
	{
		return jumpStrength;
	}
	float& getGravity()
	{
		return gravity;
	}
	float& getTempTerminalVelocityY()
	{
		return tempTerminalVelocityY;
	}
	float& getTempVelocityY()
	{
		return tempVelocityY;
	}
	float& getTempGravity()
	{
		return tempGravity;
	}
	float& getTerminalVelocity()
	{
		return terminal_Velocity;
	}
	float& getAcceleration()
	{
		return acceleration;
	}
	float& getScaleX()
	{
		return scale_x;
	}
	float& getScaleY()
	{
		return scale_y;
	}
	int& getPheight()
	{
		return Pheight;
	}
	int& getPwidth()
	{
		return Pwidth;
	}
	int& getHitBoxFactorX()
	{
		return hit_box_factor_x;
	}
	int& getHitBoxFactorY()
	{
		return hit_box_factor_y;
	}
	bool& getHasCollided()
	{
		return hasCollided;
	}
	bool& getHasKnockedBack()
	{
		return hasKnockedBack;
	}
	int getMaxSpeed()
	{
		return max_speed;
	}
	//bool& getSpacePressed()
	//{
	//	return spacePressed;
	//}
	bool& getCollisionDetectedOffGround()
	{
		return collisionDetectedOffGround;
	}
	bool& getOnGround()
	{
		return onGround;
	}
	int& getAnimationIndex()
	{
		return indexAnimation;
	}
	Animation** getStates()
	{
		return states;
	}
	void draw_player(RenderWindow& window, Sprite& LstillSprite,float offset_x);
	void player_gravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed);
	void playerVirtualGravity(char** lvl, float& offset_y, float& offset_x, const int cell_size,bool& spacePressed);
	void moveLeft();
	void moveRight();
	

};