#pragma once
#include <iostream>
#include <cmath>
#include<ctime>
#include<cstdlib>
#include <SFML/Graphics.hpp>
#include "Beebot.h"
using namespace sf;
using namespace std;


class Batbrain : public Enemy {

private:

	bool chasingPlayer;   
	float StartX, StartY; 
	float range_chase;

	int* BatStart;
	int* BatEnd;
	int* BatHeights;

	int batCoordinates;
	int indexBat;

	const float Batheight = 95;
	const float BatWidth = 97;

public:

	Batbrain() {

		this->hp = 3;
		this->speed = 2.0f;
		Alive = true;
		Moving = true;
		chasingPlayer = false;
		range_chase = 300.0f;
		StartX = x;
		StartY = y;


		batCoordinates = 10;
		indexBat = 0;
		BatStart = new int[batCoordinates];
		BatEnd = new int[batCoordinates];
		BatHeights = new int[batCoordinates];
		

		texture.loadFromFile("Sprites/batbrain.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 97, 95));
		sprite.setPosition(x, y);
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

	float& getStartX() {
		return StartX;
	}

	float& getStartY() {
		return StartY;
	}

	void movement(char** lvl, float player_x, float player_y, const int cell_size);
	void getBatbrainCoordinates(char** lvl, int height, int width);
	void move_Batbrain(Batbrain batbrains[], int& batIndex, int& batCount, const int cell_size);

};


void Batbrain::movement(char** lvl, float player_x, float player_y, const int cell_size) {

	float bat_x = player_x - x;
	float bat_y = player_y - y;

	float distance = sqrt(bat_x * bat_x + bat_y * bat_y);

	if (distance < 250.0f) {
		chasingPlayer = true;
	}

	else {
		chasingPlayer = false;
	}

	if (chasingPlayer) {

		if (distance != 0) {

			bat_x /= distance;
			bat_y /= distance;

			float move_x = x + bat_x * speed;
			float move_y = y + bat_y * speed;

			if (!checkWallCollisionWithEnemy(lvl, move_x, move_y, cell_size)) {

				x = move_x;
				y = move_y;
			}
		}
	}

	else
	{

		x += speed;

		if (x >= End) {
			speed = -abs(speed);
		}
		if (x <= Start) {
			speed = abs(speed);
		}

	}

	sprite.setPosition(x, y);


}

void Batbrain::getBatbrainCoordinates(char** lvl, int height, int width) {

	srand(time(0)); // random seed once

	for (int i = 4; i < height / 2 + 1; i++) {

		int j = 0;

		while (j < width - 1) {

			if (lvl[i][j] == 's' && lvl[i + 1][j] == 's' && lvl[i - 1][j] == 's') {

				int start = j;

				while (j < width && lvl[i][j] == 's' && lvl[i + 1][j] == 's' && lvl[i - 1][j] == 's')
					j++;

				int end = j - 1;

				if(end-start >= 8)
					end = start + 8;

				if ((end - start + 1) >= 4 && indexBat < batCoordinates)
				{
					BatStart[indexBat] = start;
					BatEnd[indexBat] = end;
					BatHeights[indexBat] = i;
					indexBat++;
				}
			}
			else {
				j++;
			}
		}
	}
}


void Batbrain::move_Batbrain(Batbrain batbrains[], int& batIndex, int& batCount, const int cell_size) {

	for (int i = 0; i < batCount; i++) {

		float Start = BatStart[i] * cell_size;
		float End = BatEnd[i] * cell_size;

		float bat_X = (Start + End) / 2.0f;
		float bat_Y = (BatHeights[i]+1) * cell_size - Batheight / 2;

		batbrains[batIndex].setPosition(bat_X, bat_Y, Start, End);

		batIndex++;
	}

	batCount = batIndex;
}



