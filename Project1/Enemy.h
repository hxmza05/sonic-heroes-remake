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

public:

	Enemy() {

		x = 0, y = 0, speed = 0;
		hp = 0;
		Alive = false, Moving = false;
		Start = 0, End = 0;
		indexAnimation = 0, totalAnimations = 0;
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


};
