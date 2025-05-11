#pragma once
#include<iostream>
using namespace std;
#include"Animation.h"
#include "Audio.h"
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
#define STILL 12
#define GLIDEL 13
#define GLIDER 14
#define HANG

#define AJUMP 0
//#define 

class Player
{
	int callCount;
	bool hasCollided;
	bool hasKnockedBack;
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

	float terminal_Velocity;
	////////////////////////////
	int Pheight;
	int Pwidth;
	// only to adjust the player's hitbox
	int hit_box_factor_x;
	int hit_box_factor_y;
	bool knockedByProjectile;
	Clock haveBeenPutDown;
	float hitBox_x;
	float hitBox_y;
	Texture hitBoxTex;
	Texture hitBoxTexJump;
	Sprite HitBoxSprite;

protected:
	Clock coolDown;
	bool specialAbilityUsed;
	Clock specialAbiltyClock;
	float tailed_x;
	float tailed_y;
	float acceleration;
	float velocityX;
	bool direction;
	float x;
	float y;
	bool hasDetectedItself;
	float max_speed;
	float velocityY;
	bool onGround;
	float scale_x = 2.5;
	float scale_y = 2.5;
	Animation** states;

	int indexAnimation;
	int totalAnimations;
	int* trail;
	virtual void followLeader(const int const** pathToFollow) = 0;
	int delayInFollow;
	bool hasStartedFollowing;
	bool isEven;
	float dummyGravity;
	bool figuringOut;
	bool tempOnground;
	bool invincible;
	double flyingTime;
	int idxPl;

	Audio* audio;

public:
	Player()
	{
		invincible = false;
		callCount = 0;
		tempOnground = true;
		tailed_x = -999;
		tailed_y = -999;
		haveBeenPutDown.restart();
		direction = 1;

		figuringOut = false;
		dummyGravity = 0.8;
		isEven = 0;
		x = 150;
		y = 150;
		hitBox_x = x;
		hitBox_y = y;
		hasCollided = false;
		hasKnockedBack = false;
		max_speed = 12;
		velocityX = 0.5;
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
		trail = new int[20];
		delayInFollow = 0;
		hasStartedFollowing = false;
		knockedByProjectile = false;
		hasDetectedItself = false;
		hitBoxTex.loadFromFile("Data/hitBox.png");
		hitBoxTexJump.loadFromFile("Data/hitBoxJump.png");
		HitBoxSprite.setScale(2.5, 2.5);
	}
	int getIdxPl()
	{
			return idxPl;
}
	bool getInvincible()
	{
		return invincible;
	}
	double getFlyingTime()
	{
		return flyingTime;
	}
	void setFlyingTime(double b)
	{
		flyingTime = b;
	}
	void setInvincible(bool b)
	{
		invincible = b;
	}
	void decelerate(char** lvl, int w,float friction);
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
	Clock& getHaveBeenPutDown()
	{
		return haveBeenPutDown;
	}
	int& getAnimationIndex()
	{
		return indexAnimation;
	}
	int &getDelayinFollow()
	{
		return delayInFollow;
	}
	void setDelayInFollow(int d)
	{
		delayInFollow = d;
	}
	bool getHasStartedFollowing()
	{
		return hasStartedFollowing;
	}
	void setHasStartedFollowing(bool b)
	{
		hasStartedFollowing = b;
	}
	Animation** getStates()
	{
		return states;
	}
	bool& getHasKnockedByProjectile()
	{
		return knockedByProjectile;
	}
	void setHitBoxX(float x)
	{
		hitBox_x = x;
	}
	void setHitBoxY(float y)
	{
		hitBox_y = y;
	}
	float getHitBoxX()
	{
		return hitBox_x;
	}
	float getHitBoxY()
	{
		return hitBox_y;
	}
	void updateDelay()
	{
		delayInFollow++;

		if (delayInFollow == 100)
		{
			delayInFollow = 0;
			return;
		}
	}
	void setAccelration(float a)
	{
		acceleration = a;
	}
	void setVelcotiyX(float a)
	{
		velocityX = a;
	}
	void setAudio(Audio* a) 
	{ 
		audio = a; 
	}
	void decelerateRight(char** lvl, int width, float friction);
	void player_dummy_gravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed,int,int);
	void autoMove(int x_coord,int y_coord,char**,int h,int w);
	void draw_player(RenderWindow& window, Sprite& LstillSprite,float offset_x);
	void player_gravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed,int,int,bool&);
	void playerVirtualGravity(char** lvl, float& offset_y, float& offset_x, const int cell_size,bool& spacePressed,int,int,bool&);
	void moveLeft(char**lvl,int w,float friction);
	void moveRight(char** llvl,int w,float friction);
	virtual void moveUp(bool,int&) = 0;
	virtual void useSpecialAbilty(char**,int h,int w) = 0;
	void checkDelayNow(int idx);
	bool checkFeet(char** lvl,int h,int w);
	bool teleportToTailed();
	bool& getTempOnGround()
	{
		return tempOnground;
	}
	void setx(float _x)
	{
		x = _x;
	}
	void sety(float _y)
	{
		y = _y;
	}
	void setTailedCoords(float _x, float _y)
	{
		tailed_x = _x;
		tailed_y = _y;
		cout << "tailed_X = " << tailed_x << "   tailed_y = " << tailed_y <<" in  stter" << endl;
		tempOnground = true;
	}
	//void detectYourself();
	void figureItOutYourself(float,char**,float,int);
	void executePushingLeft()
	{
		indexAnimation = PUSHLEFT;
		states[indexAnimation][0].RunAnimation();
		//cout << "\n\n\nPushing left executed \n\n\n";
	}
	void executePushingRight()
	{
		indexAnimation = PUSHRIGHT;
		states[indexAnimation][0].RunAnimation();
		//cout << "\n\n\nPushing right executed\n\n\n";
	}
	void drawHitBox(RenderWindow& window)
	{
		callCount++;
		cout << "Call : " << callCount << "\n";
		if (!onGround)
		{
			cout << "Drawing in jump\n\n";
			HitBoxSprite.setTexture(hitBoxTexJump);
			HitBoxSprite.setScale(1,1);
			HitBoxSprite.setPosition(x + hit_box_factor_x - 1, y + hit_box_factor_y + 5);
		}
		else 
		{
			cout << "Not drawing in jump\n\n";
			HitBoxSprite.setTexture(hitBoxTex);
			HitBoxSprite.setScale(2.5, 2.5);
			HitBoxSprite.setPosition(x + hit_box_factor_x - 1, y + hit_box_factor_y + 5);

		}
		window.draw(HitBoxSprite);


		//HitBoxSprite.setPosition(x + hit_box_factor_x, y + hit_box_factor_y);
	}
	bool &getSpecialAbiltyUsed()
	{
		return specialAbilityUsed;
	}
	virtual void spinDash(char** lvl, float w, float f)
	{
		cout << "LVL wala spindash\n";
	}
};