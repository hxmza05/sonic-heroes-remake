#pragma once
#include<iostream>
using namespace std;
using namespace sf;
#include"Animation.h"
#include "HUD.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class Enemy 
{

protected:

	float x, y, speed;
	float hp;
	bool Alive, Moving, Attack;
	float Start, End;

	Texture texture;
	Sprite sprite;
	Animation** states;
	int indexAnimation;
	int totalAnimations;



	Animation* deathAnim;     // Pointer to smoke death animation
	Texture smoke0;
	Texture smoke1;
	bool isDying = false;     // Flag to start death animation
	bool deathFinished = false; // Flag when animation ends
	Clock deathClock;         // To time last frame and delay deletion

	Clock deathFrameClock;        // Controls delay between death frames



public:

	Enemy() {

		x = 0, y = 0, speed = 0;
		hp = 0;
		Alive = false, Moving = false;
		Start = 0, End = 0;
		indexAnimation = 0, totalAnimations = 0;


		smoke0.loadFromFile("Sprites/death0.png");
		smoke1.loadFromFile("Sprites/death1.png");

		deathAnim = new Animation(5); // 2 frames from smoke0, 3 from smoke1

		int i = 0;
		// First 2 frames from smoke0 (104x51  52x51 each)
		for (int x = 0; x < 2; ++x, ++i) {
			deathAnim->getSprites()[i].setTexture(smoke0);
			deathAnim->getSprites()[i].setTextureRect(IntRect(x * 52, 0, 52, 51));
			deathAnim->getSprites()[i].setScale(1.5f, 1.5f);
		}

		deathAnim->getSprites()[i].setTexture(smoke1);
		deathAnim->getSprites()[i++].setTextureRect(IntRect(0, 0, 33, 31));   // Frame 1

		deathAnim->getSprites()[i].setTexture(smoke1);
		deathAnim->getSprites()[i++].setTextureRect(IntRect(33, 0, 30, 31));  // Frame 2

		deathAnim->getSprites()[i].setTexture(smoke1);
		deathAnim->getSprites()[i++].setTextureRect(IntRect(63, 0, 21, 31));  // Frame 3
		
		for (int j = i - 3; j < i; ++j)
			deathAnim->getSprites()[j].setScale(2.f, 2.f);



		
	}

	
	float& getX() {

		return x;
	}

	float& getY() {

		return y;
	}

	float& getHp() {

		return hp;
	}

	bool& alive() {

		return Alive;
	}

	void setHp(float x) {

		if (hp == 0)
		{
			Alive = false;
			hp = 0;
		}

		hp = x;
	}

	void setAlive(bool status) { 
		this->Alive = status; 
	}

	void setAnimation(int animationIndex) {
		indexAnimation = animationIndex;
	}
	
	void RunNewAnimation() {
		states[indexAnimation]->RunAnimation();
		sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];
	}


	void setPosition(float startX, float startY, float Start, float End) {

		x = startX;
		y = startY;
		this->Start = Start;
		this->End = End;
		sprite.setPosition(x, y);

	}

	void draw(RenderWindow& window, float offset_x)
	{

		sprite.setPosition(x - offset_x, y);
		window.draw(sprite);

	}


	Sprite& getSprite() {
		return sprite;
	}


	bool checkWallCollisionWithEnemy(char** lvl, float enemy_x, float enemy_y, const int cell_size = 64) {

		return !(lvl[(int)(enemy_y) / cell_size][(int)(enemy_x) / cell_size] == 's');
	}

	virtual void update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver) = 0;
	virtual void drawExtra(RenderWindow& window, float offset_x) {}
	virtual ~Enemy() {}


	void triggerDeath() {

		if (!isDying) {
			isDying = true;
			deathAnim->reset();
			deathFrameClock.restart();
		}
	}

	bool playDeathAnimation(RenderWindow& window, float offset_x) {

		if (!isDying) 
			return false;

		if (deathFrameClock.getElapsedTime().asMilliseconds() >= 800) {

			if (deathAnim->getIndex() < deathAnim->getLength() - 1) {
				deathAnim->RunAnimation(); 
				deathFrameClock.restart();
			}

			else {
				deathFinished = true;
				return true;
			}
		}

		Sprite& frame = deathAnim->getSprites()[deathAnim->getIndex()];
		frame.setPosition(x - offset_x, y);
		window.draw(frame);
		return false;

	}

	bool hasDeathFinished() {
		return deathFinished;
	}


};
