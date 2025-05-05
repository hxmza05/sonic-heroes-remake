#pragma once
#include <iostream>
#include "Enemy.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Motobug : public Enemy
{

private:

	bool attack;
	Clock clock;

	int* MotoBugStart;
	int* MotoBugEnd;
	int* MotoBugWalls;
	int MotoBugCoordinates;
	int indexMotoBug;

	const float MotobugHeight;
	const float MotobugWidth;

	Texture movebug;
	Texture bugattack;
	Texture flip0;
	Texture flip1;


	bool flipStarted;
	bool flipCompleted;
	bool facingRight;
	Clock flipClock;




public:

	Motobug() : MotobugHeight(54.0), MotobugWidth(76.5) {

		this->hp = 2;
		this->speed = 2.5;
		this->x = 0;
		this->y = 0;
		Moving = true;
		Alive = true;
		attack = false;
		Start = 0;
		End = 0;
		clock.restart();
		totalAnimations = 4;
		indexAnimation = 0;

		MotoBugCoordinates = 10;
		indexMotoBug = 0;

		MotoBugStart = new int[MotoBugCoordinates];
		MotoBugEnd = new int[MotoBugCoordinates];
		MotoBugWalls = new int[MotoBugCoordinates];

		flipStarted = false;
		flipCompleted = false;
		facingRight = false; 
		flipClock.restart();


		movebug.loadFromFile("Sprites/bug_move.png");
		bugattack.loadFromFile("Sprites/bug_attack.png");
		flip0.loadFromFile("Sprites/bug_switchdir0.png");
		flip1.loadFromFile("Sprites/bug_switchdir1.png");


		states = new Animation * [totalAnimations];

		//moving

		states[0] = new Animation(5);

		for (int i = 0, width = 2.0f; i < 5; i++, width += 169.f) {
			states[0]->getSprites()[i].setTexture(movebug);
			states[0]->getSprites()[i].setTextureRect(IntRect(width, 0, 167.f, 125.f));
			states[0]->getSprites()[i].setScale(0.452f, 0.432f);
		}

		states[1] = new Animation(3); // attack

		for (int i = 0, width = 0; i < 3; i++, width += 169.6f) {
			states[1]->getSprites()[i].setTexture(bugattack);
			states[1]->getSprites()[i].setTextureRect(IntRect(width, 0, 169.6f, 126.f));
			states[1]->getSprites()[i].setScale(0.451f, 0.428f);
		}


		/*

		// flip direction 0
		states[1] = new Animation(2);

		for (int i = 0, width = 0; i < 2; i++, width += 157.f) {
			states[1]->getSprites()[i].setTexture(flip0);
			states[1]->getSprites()[i].setTextureRect(IntRect(width, 0, 157.f, 118.f));
			states[1]->getSprites()[i].setScale(0.487f, 0.457f);
		}


		// flip direction 1 

		states[2] = new Animation(3);

		for (int i = 0, height = 0; i < 3; i++, height += 120.6f) {
			states[2]->getSprites()[i].setTexture(flip1);
			states[2]->getSprites()[i].setTextureRect(IntRect(0, height, 161.f, 120.6f));
			states[2]->getSprites()[i].setScale(0.475f, 0.447f);
		}

		*/




	}

	float getX() {

		return x;
	}

	float getY() {

		return y;
	}

	int getHp() {

		return hp;
	}

	bool alive() {

		return Alive;
	}

	bool returnAttack() {
		return attack;
	}

	void setAttack() {
		attack = true;
		clock.restart();
	}

	float getMotobugHeight() const {
		return MotobugHeight;
	}

	float getMotobugWidth() const {
		return MotobugWidth;
	}

	bool isFacingRight() const {
		return facingRight;
	}


	void movement(float player_x, float player_y);
	void move_motobugs(Motobug** motobugs, int& motobugIndex, int& motobugCount, const int cell_size);
	void getMotobugCoordinates(char** lvl, int height, int width, int start_x, int end_x);
	bool PlayerBugCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight);

};


void Motobug::movement(float player_x, float player_y) {

	float offset = 10.0f;

	if (attack) {

		indexAnimation = 1;

		if (player_x > x + offset && x + speed < End) {
			x += speed; 
		}

		else if (player_x < x - offset && x - speed > Start) {
			x -= speed;
		}

		if (clock.getElapsedTime().asSeconds() >= 1.5f) {
			attack = false;
			clock.restart();
		}
	}

	else if ((player_x >= Start && player_x <= End) && (abs(player_y - y) < 64)) {

		setAttack(); 

		indexAnimation = 1;

		if (player_x > x + offset) {
			facingRight = true;
		}

		else if (player_x < x - offset) {
			facingRight = false;
		}
	}

	else {

		indexAnimation = 0;

		if (Moving) {
			x += speed;
			facingRight = true;
			if (x >= End) Moving = false;
		}

		else {
			x -= speed;
			facingRight = false;
			if (x <= Start) Moving = true;
		}
	}

	states[indexAnimation]->RunAnimation();
	sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];

	if (indexAnimation == 0) {
		sprite.setScale(facingRight ? -0.452f : 0.452f, 0.432f);
	}

	else {
		sprite.setScale(facingRight ? -0.451f : 0.451f, 0.428f);
	}

	sprite.setPosition(x, y);
}


void Motobug::move_motobugs(Motobug** motobugs, int& motobugIndex, int& motobugCount, const int cell_size)
{
	for (int i = 0; i < motobugCount; i++) {

		float Start = MotoBugStart[i] * cell_size;
		float motobug_End = MotoBugEnd[i] * cell_size;
		float motobug_maxEnd = Start + 10 * cell_size;
		float End = (motobug_End > motobug_maxEnd) ? motobug_maxEnd : motobug_End;

		float bug_X = (Start + End) / 2.0f;
		float bug_Y = (MotoBugWalls[i] + 1) * cell_size - MotobugHeight;

		motobugs[i]->setPosition(bug_X, bug_Y, Start, End);

		cout << "placed bug " << motobugIndex << ": " << bug_X << ", " << bug_Y << endl;
		motobugIndex++;
	}

	motobugCount = motobugIndex;
}


void Motobug::getMotobugCoordinates(char** lvl, int height, int width, int start_x, int end_x)
{
	for (int i = start_x; i < end_x; i++) { 

		int j = 0;

		while (j < width - 1) {

			if (lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q')) {

				int start = j;

				while (j < width && lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q')) {
					j++;
				}

				int end = j - 1;

				if (end - start + 1 >= 4 && indexMotoBug < MotoBugCoordinates) {
					MotoBugStart[indexMotoBug] = start;
					MotoBugEnd[indexMotoBug] = end;
					MotoBugWalls[indexMotoBug] = i;
					indexMotoBug++;

					cout << "Found bug zone from tile " << start << " to " << end << " at row " << i << endl;
				}
			}

			else {
				j++;
			}
		}
	}
}


bool Motobug::PlayerBugCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
{
	return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
}

