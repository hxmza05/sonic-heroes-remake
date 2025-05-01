#pragma once
#include <iostream>
#include<cmath>
#include "Enemy.h"
#include "Animation.h"
#include "Projectile.h"
#include "Player.h"
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
	float beeBaseY;

	Projectile* projectiles;
	int projectileCount;


	Clock lockTimer;
	Clock cooldownClock;
	bool isLockedOn;
	bool canLock; 




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
		beeBaseY = 0;
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


		projectiles = nullptr;
		projectileCount = 0;


		isLockedOn = false;
		canLock = true;
		lockTimer.restart();
		cooldownClock.restart();


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

	int getProjectileCount() {
		return projectileCount;
	}

	Projectile* getProjectiles() {
		return projectiles;
	}

	int getProjectileCount() const {
		return projectileCount;
	}


	void movement(char** lvl, float player_x, float player_y, const int cell_size, int player_width, int player_height);
	void getBeebotCoordinates(char** lvl, int height, int width);
	void move_beebots(Beebot** beebots, int& beeIndex, int& beeCount, const int cell_size);
	void handleProjectilesCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY);
	void drawProjectiles(RenderWindow& window, float offset_x);


};


void Beebot::movement(char** lvl, float player_x, float player_y, const int cell_size, int player_width, int player_height) {

	if (player_x >= Start && player_x <= End && (player_y - beeBaseY) <= 256.0f && (player_y - beeBaseY) >= -100.0f) {

		if (!attackingPlayer) {
			attackingPlayer = true;
		}
	}

	else {

		if (attackingPlayer) {
			attackingPlayer = false;
		}
	}

	if (attackingPlayer) {

		float beeCenterX = x + getbeeWidth() / 2.0f;
		float playerCenterX = player_x + player_width / 2.0f /*- 10.0f*/;
		float distanceX = abs(beeCenterX - playerCenterX);

		if (player_x >= Start && player_x <= End && distanceX <= 60.0f && (player_y - beeBaseY) <= 256.0f && (player_y - beeBaseY) >= -100.0f) {

			if (!isLockedOn && canLock && cooldownClock.getElapsedTime().asSeconds() >= 5.0f) {
				isLockedOn = true;
				lockTimer.restart();
				canLock = false;
				cooldownClock.restart();
				targetX = playerCenterX;
				targetY = player_y + player_height / 2.0f;
				//cout << "Bee Locking on to player"<<endl;
			}

			if (isLockedOn) {

				y = beeBaseY;

				if (lockTimer.getElapsedTime().asSeconds() >= 1.0f && !shotProjectile) {

					shotProjectile = true;

					float projectileX = targetX - beeCenterX;
					float projectileY = (targetY)-(y + getbeeHeight() / 2.0f);

					float magnitude = sqrt(projectileX * projectileX + projectileY * projectileY);

					if (magnitude != 0) {
						projectileX /= magnitude;
						projectileY /= magnitude;
					}

					if (!projectiles) {
						projectiles = new Projectile();
					}

					projectiles->setPosition(beeCenterX, y + getbeeHeight() / 2.0f, projectileX, projectileY, 4.0f);

					//cout << "Bee Fired projectile at player"<<endl;

				}

				if (shotProjectile) {
					isLockedOn = false;
					shotProjectile = false;
					attackingPlayer = false;
					canLock = true;
					//cout << "Bee Resuming patrol" << endl;
				}

			}

		}

		else {

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

			y += (ZigZag ? speed : -speed);
		}

	}

	else {

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

		y += (ZigZag ? speed : -speed);

	}

	states[indexAnimation]->RunAnimation();
	sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];
	sprite.setPosition(x, y);

	if (projectiles && projectiles->Active()) {
		projectiles->move();
	}


}


void Beebot::move_beebots(Beebot** beebots, int& beeIndex, int& beeCount, const int cell_size)
{
	for (int i = 0; i < beeCount; i++) {

		float patrolStart = BeebotStart[i] * cell_size;
		float beebot_End = BeebotEnd[i] * cell_size;
		float beebot_maxEnd = patrolStart + 10 * cell_size;
		float patrolEnd = (beebot_End > beebot_maxEnd) ? beebot_maxEnd : beebot_End;

		float bee_X = (patrolStart + patrolEnd) / 2.0f;
		float bee_Y = BeebotHeights[i] * cell_size + 10;

		beebots[beeIndex]->setPosition(bee_X, bee_Y, patrolStart, patrolEnd);
		beebots[beeIndex]->beeBaseY = bee_Y;


		cout << "placed bee " << beeIndex << ": " << bee_X << ", " << bee_Y << endl;
		beeIndex++;
	}

	beeCount = beeIndex;
}

void Beebot::getBeebotCoordinates(char** lvl, int height, int width)
{
	for (int i = 5; i < height / 2 + 1; i++) { //////////// add variables for start and end range in loop conditions

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


void Beebot::drawProjectiles(RenderWindow& window, float offset_x) {

	if (projectiles && projectiles->Active()) {
		projectiles->draw(window, offset_x);
	}

}


void Beebot::handleProjectilesCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY)
{
	if (projectiles && projectiles->Active()) {

		projectiles->handleCollision(lvl, cell_size, player_x, player_y, player_width, player_height, hasKnockedBack, tempVelocityY);

		if (!projectiles->Active()) {
			delete projectiles;
			projectiles = nullptr;
			cout << "Bee Projectile deleted" << endl;
		}
	}
}


