#pragma once
#include <iostream>
#include<cmath>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Beebot : public Enemy {

private:

	int *BeebotStart;
	int *BeebotEnd;
	int *BeebotHeights;

	int beeCoordintes;
	int indexBee;
	int air_Row;

	const float bee_height = 37.5;
	const float bee_width = 88.5;

	float increase;
	float amplitude;
	float baseY;

public:

	Beebot() {

		hp = 5;
		increase = 0;
		speed = 0.8;
		amplitude = 20;
		baseY = 0;
		Alive = true;
		Moving = true;
		x = 0;
		y = 0;
		Start = 0;
		End = 0;

		beeCoordintes = 10;
		indexBee = 0;
		air_Row = 5;
		BeebotStart = new int[beeCoordintes];
		BeebotEnd = new int[beeCoordintes];
		BeebotHeights = new int[beeCoordintes];


		texture.loadFromFile("Sprites/beebot.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 118, 50));
		sprite.setPosition(x, y);
		sprite.setScale(0.75f, 0.75f);

	}

	void setBaseY(int baseY) {
		this->baseY = baseY;
	}

	float getbeeHeight() const {
		return bee_height;
	}

	float getbeeWidth() const {
		return bee_width;
	}

	void movement() {

		increase += 0.1;

		x += speed;

		if (x >= End) {
			speed = -abs(speed);
		}
		if (x <= Start) {
			speed = abs(speed);
		}

		y = baseY + amplitude * sin(increase);

		sprite.setPosition(x, y);

	}


	void getBeebotCoordinates(char** lvl, int height, int width);
	void draw_beebots(RenderWindow& window, Beebot beebots[], int& beeCount, int offset_x);
	void move_beebots(Beebot beebots[], int& beeIndex, int& beeCount, const int cell_size);

};



void Beebot::draw_beebots(RenderWindow& window, Beebot beebots[], int& beeCount, int offset_x)
{
	for (int i = 0; i < beeCount; i++) {

		beebots[i].movement();
		beebots[i].draw(window, offset_x);

	}
}

void Beebot::move_beebots(Beebot beebots[], int& beeIndex, int& beeCount, const int cell_size)
{
	for (int i = 0; i < beeCount; i++) {

		float patrolStart = BeebotStart[i] * cell_size;
		float beebot_End = BeebotEnd[i] * cell_size;
		float beebot_maxEnd = patrolStart + 10 * cell_size;
		float patrolEnd = (beebot_End > beebot_maxEnd) ? beebot_maxEnd : beebot_End;

		float bee_X = (patrolStart + patrolEnd) / 2.0f;
		float bee_Y = BeebotHeights[i] * cell_size + 10;

		beebots[beeIndex].setPosition(bee_X, bee_Y, patrolStart, patrolEnd);
		beebots[i].setBaseY(270);

		cout << "placed bee " << beeIndex << ": " << bee_X << ", " << bee_Y << endl;
		beeIndex++;
	}
	beeCount = beeIndex;
}

void Beebot::getBeebotCoordinates(char** lvl, int height, int width)
{
	for (int i = 2; i < height / 2 + 1; i++) {

		int j = 0;

		while (j < width - 1) {

			if (lvl[i][j] == 's' && lvl[i + 1][j] == 's' && lvl[i - 1][j] == 's') {

				int start = j;

				while (j < width && lvl[i][j] == 's' && lvl[i + 1][j] == 's' && lvl[i - 1][j] == 's') {
					j++;
				}

				int end = j - 1;

				if (end - start + 1 >= 4 && indexBee < beeCoordintes) {
					BeebotStart[indexBee] = start;
					BeebotEnd[indexBee] = end;
					BeebotHeights[indexBee] = i;
					indexBee++;

					cout << "Found air zone from tile " << start << " to " << end << " at row " << i << endl;
				}
			}

			else {
				j++;
			}
		}
	}
}