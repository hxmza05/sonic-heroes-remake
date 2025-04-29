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

	Texture move_bee;
	//Texture wings;
	//Sprite wings_sprites;

	Clock moveClock;
	Clock attackClock;
	bool ZigZag;
	bool shotProjectile;
	bool attackingPlayer;
	float targetX, targetY;



public:

	Beebot() {

		hp = 5;
		speed = 1.2;
		Alive = true;
		Moving = true;
		x = 0;
		y = 0;
		Start = 0;
		End = 0;
		ZigZag = true;
		shotProjectile = false;
		attackingPlayer = false;
		targetX = 0, targetY = 0;
		moveClock.restart();
		attackClock.restart();

		beeCoordintes = 10;
		indexBee = 0;
		air_Row = 5;
		BeebotStart = new int[beeCoordintes];
		BeebotEnd = new int[beeCoordintes];
		BeebotHeights = new int[beeCoordintes];

		move_bee.loadFromFile("Sprites/beebot.png");
		//wings.loadFromFile("Sprites/bee_wings0.png");

		totalAnimations = 2;
		indexAnimation = 0;
		states = new Animation * [totalAnimations];

		states[0] = new Animation(1);

		for (int i = 0, height = 0; i < 1; i++) {
			states[0]->getSprites()[i].setTexture(move_bee);
			states[0]->getSprites()[i].setTextureRect(IntRect(0, 0, 118, 50));
			states[0]->getSprites()[i].setScale(0.75f, 0.75f);
		}

		/*states[7] = new Animation(3);

		for (int i = 0, height = 0; i < 3; i++, height += 33) {
			states[7]->getSprites()[i].setTexture(wings);
			states[7]->getSprites()[i].setTextureRect(IntRect(0, height, 150, 33));
			states[7]->getSprites()[i].setScale(0.35f, 0.75f);
		}*/

	}


	float getbeeHeight() const {
		return bee_height;
	}

	float getbeeWidth() const {
		return bee_width;
	}

	void movement(char** lvl, float player_x, float player_y, const int cell_size) {

		if (!attackingPlayer) {


			if (Moving) {

				x += speed;

				if (x >= End) {
					Moving = false;
				}
			}

			else {

				x -= speed;

				if (x <= Start) {
					Moving = true;
				}
			}

			if (moveClock.getElapsedTime().asMilliseconds() >= 500) {

				ZigZag = !ZigZag;
				moveClock.restart();
			}

			if (ZigZag) {

				y += 1.0f * speed;
			}

			else {

				y -= 1.0f * speed;
			}

			float dx = player_x - x;
			float dy = player_y - y;
			float distance = sqrt(dx * dx + dy * dy);

			if (distance < 150.0f)
			{
				attackingPlayer = true;
				//targetX = player_x + 40.0f;
				//targetY = player_y + 40.0f;
				attackClock.restart();     
			}

		}

		else {


			if (player_x > x + 80.0f)
			{
				x -= speed * 4.0f;

				if (x < -100.0f) {
					Alive = false;
					cout << "Bee leavng map after missing player" << endl;
				}
			}

			else {

				if (abs(x - (player_x + 70.0f)) > 5.0f) {

					if (x < player_x + 70.0f) {
						x += speed * 2.0f;
					}

					else {
						x -= speed * 2.0f;
					}
				}

				if (abs(y - player_y - 70.0f) > 5.0f) {

					if (y < player_y - 70.0f) {
						y += speed * 2.0f;
					}

					else {
						y -= speed * 2.0f;
					}
				}

				if (attackClock.getElapsedTime().asSeconds() > 5.0f) {
					shotProjectile = true;
					attackClock.restart();
					cout << "Bee shoots projectile at player!" << endl;
					// actuali spawn projectile here
				}
			}

		}



		states[indexAnimation]->RunAnimation();
		sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];

		//states[7]->RunAnimation();
		//wings_sprites = states[1]->getSprites()[states[1]->getIndex()];

		sprite.setPosition(x, y);
		//wings_sprites.setPosition(x + 15, y - 15);
	}


	void getBeebotCoordinates(char** lvl, int height, int width);
	//void draw_beebots(RenderWindow& window, Beebot beebots[], int& beeCount, int offset_x);
	void move_beebots(Beebot beebots[], int& beeIndex, int& beeCount, const int cell_size);

};


/*
void Beebot::draw_beebots(RenderWindow& window, Beebot beebots[], int& beeCount, int offset_x)
{
	for (int i = 0; i < beeCount; i++) {
			beebots[i].movement();
			beebots[i].draw(window, offset_x);
	}
}
*/
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

		cout << "placed bee " << beeIndex << ": " << bee_X << ", " << bee_Y << endl;
		beeIndex++;
	}
	beeCount = beeIndex;
}

void Beebot::getBeebotCoordinates(char** lvl, int height, int width)
{
	for (int i = 5; i < height / 2 + 1; i++) {

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