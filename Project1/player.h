//#pragma once
#include<iostream>
using namespace std;
#include"Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
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
	Texture playerTexture;
	Sprite playerSprite;
	Animation** states;
	int indexAnimation;
	int totalAnimations;
public:
	Player()
	{
		x = 150;
		y = 150;
		hasCollided = false;
		hasKnockedBack = false;
		max_speed = 15;
		velocityX = 0;
		velocityY = 9.8;
		//spacePressed = false;// our own defined
		collisionDetectedOffGround = false;
		jumpStrength = -20; // Initial jump velocity
		gravity = 1;        // Gravity acceleration
		tempTerminalVelocityY = 15;
		tempVelocityY = -7;
		tempGravity = 0.6;
		onGround = false;
		acceleration = 0.2;
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
	

};
void Player::draw_player(RenderWindow& window, Sprite& LstillSprite, float offset_x)
{  
   LstillSprite.setPosition(x - offset_x, y);  
   window.draw(LstillSprite);  
}
void Player:: player_gravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed)
{
	offset_y = y;
	offset_y += velocityY;

	int headY = (int)(y + hit_box_factor_y) / cell_size;
	int tileLeftX = (int)(x + hit_box_factor_x) / cell_size;
	int tileRightX = (int)(x + hit_box_factor_x + Pwidth - 1) / cell_size;

	bool hitsTopRow = (headY == 0 || headY == 1);
	bool leftHit = (lvl[headY][tileLeftX] == 'w' || lvl[headY][tileLeftX] == 'q' || lvl[headY][tileLeftX] == 'e');
	bool rightHit = (lvl[headY][tileRightX] == 'w' || lvl[headY][tileRightX] == 'q' || lvl[headY][tileRightX] == 'e');

	if (velocityY < 0 && hitsTopRow && (leftHit || rightHit))
	{
		velocityY = 0;
	}
	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];

	char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];
	bool forLeft = topLeft == 's';
	bool forMiddle = topMiddle == 's';
	bool forRight = topRight == 's';


	if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' || bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' || bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') && velocityY > 0 && (forLeft || forMiddle || forRight))
	{
		onGround = true;
		/*y = ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size) * cell_size - hit_box_factor_y - Pheight;*/
		velocityY = 0;
		spacePressed = false;
	}
	else
	{
		y = offset_y;
		onGround = false;
	}
	if (!onGround)
	{
		velocityY += gravity;
		cout << "Gravity being added correctly \n";
		if (velocityY >= terminal_Velocity)
			velocityY = terminal_Velocity;
	}
	else
	{
		velocityY = 0;
		spacePressed = false;
	}
}
void Player::playerVirtualGravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed)
{
	offset_y = y;
	offset_y += tempVelocityY;
	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];

	char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];
	bool forLeft = topLeft == 's';
	bool forMiddle = topMiddle == 's';
	bool forRight = topRight == 's';


	if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' || bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' || bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') && tempVelocityY > 0 && (forLeft || forMiddle || forRight))
	{
		onGround = true;
		/*y = ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size) * cell_size - hit_box_factor_y - Pheight;*/
		tempVelocityY = 0;
		spacePressed = false;
	}
	else
	{
		y = offset_y;
		tempVelocityY += tempGravity;
		onGround = false;
	}
}
