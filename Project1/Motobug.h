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

		MotoBugCoordinates = 10;
		indexMotoBug = 0;

		MotoBugStart = new int[MotoBugCoordinates];
		MotoBugEnd = new int[MotoBugCoordinates];
		MotoBugWalls = new int[MotoBugCoordinates];


		texture.loadFromFile("Sprites/motobug.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 102, 72));
		sprite.setScale(0.75f, 0.75f);

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


	void movement(float player_x, float player_y);
	void move_motobugs(Motobug** motobugs, int& motobugIndex, int& motobugCount, const int cell_size);
	void getMotobugCoordinates(char** lvl, int height, int width);


};


void Motobug::movement(float player_x, float player_y) {

	if (attack && clock.getElapsedTime().asSeconds() >= 0.3f) {
		attack = false;
		clock.restart();
	}

	if ((player_x >= Start && player_x <= End) && (abs(player_y - y) < 64)) {
		setAttack(); 

		if (player_x > x) {
			x += speed;
		}

		else if (player_x < x) {
			x -= speed;
		}
	}

	else {

		if (Moving) {
			x += speed;
		}

		else {
			x -= speed;
		}

		if (x >= End) {
			Moving = false;
		}

		else if (x <= Start) {
			Moving = true;
		}

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


void Motobug::getMotobugCoordinates(char** lvl, int height, int width)
{
	for (int i = 10; i < height - 2; i++) { //////////// add variables for start and end range in loop conditions

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



