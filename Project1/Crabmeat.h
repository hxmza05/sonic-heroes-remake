#pragma once
#include<iostream>
using namespace std;
using namespace sf;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>


class Crabmeat : public Enemy {

private:
	
	Texture moveRight;
	Texture moveLeft;
	Texture idle;
	Texture attackPlayer;
	bool attack;
	Clock clock;

public:

	Crabmeat() {

		this->hp = 4;
		this->speed = 2.0;
		Alive = true;
		Moving = true;
		attack = false;
		this->x = 0;
		this->y = 0;
		Start = 0;
		End = 0;

		totalAnimations = 4;
		indexAnimation = 0;


		idle.loadFromFile("Sprites/crabmeat.png");
		moveRight.loadFromFile("Sprites/crabmeat_right.png");
		moveLeft.loadFromFile("Sprites/crabmeat_left.png");
		attackPlayer.loadFromFile("Sprites/crabmeat_attack.png");

		states = new Animation * [totalAnimations];

		//  idle
		states[0] = new Animation(1);
		for (int i = 0; i < 1; i++) {
			states[0]->getSprites()[i].setTexture(idle);
			states[0]->getSprites()[i].setTextureRect(IntRect(0, 0, 120, 88));
			states[0]->getSprites()[i].setScale(0.5f, 0.5f);
		}


		// right 

		states[1] = new Animation(3);
		for (int i = 0, width = 0; i < 3; i++, width += 290 / 3) {
			states[1]->getSprites()[i].setTexture(moveRight);
			states[1]->getSprites()[i].setTextureRect(IntRect(width, 0, 290/3, 69));
			states[1]->getSprites()[i].setScale(0.620f, 0.637f);
		}

		// left 

		states[2] = new Animation(3);
		for (int i = 0, width = 0; i < 3; i++, width += 290 / 3) {
			states[2]->getSprites()[i].setTexture(moveLeft);
			states[2]->getSprites()[i].setTextureRect(IntRect(width, 0, 290/3, 70));
			states[2]->getSprites()[i].setScale(0.620f, 0.628f);
		}

		// attack 

		states[3] = new Animation(3);
		for (int i = 0, width = 0; i < 3; i++, width += 312 / 3) {
			states[3]->getSprites()[i].setTexture(attackPlayer);
			states[3]->getSprites()[i].setTextureRect(IntRect(width, 0, 312/3, 66));
			states[3]->getSprites()[i].setScale(0.577f, 0.666f);
		}


	}


	bool returnAttack() {
		return attack;
	}

	void setAttack() {
		attack = true;
		clock.restart();
	}


	void movement() {

		Moving ? x += speed : x -= speed;

		if(x>= End)
			Moving = false;

		if (x <= Start)
			Moving = true;


		if (attack) {

			if (clock.getElapsedTime().asSeconds() >= 0.3f) {
				attack = false;
				clock.restart();
			}

			indexAnimation = 3;
		}

		else {

			if (Moving && speed > 0)
				indexAnimation = 1;  // move right

			else if (!Moving)
				indexAnimation = 2;  // move left

			else
				indexAnimation = 0;  // idle 

		}

		states[indexAnimation]->RunAnimation();
		sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];

		sprite.setPosition(x, y);

	}

	static void draw_crabs(RenderWindow& window, Crabmeat crabs[], int& crabCount, int offset_x);

};

void Crabmeat::draw_crabs(RenderWindow& window, Crabmeat crabs[], int& crabCount, int offset_x)
{
	for (int i = 0; i < crabCount; i++) {

		crabs[i].movement();
		crabs[i].draw(window, offset_x);

	}
}


