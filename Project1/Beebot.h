#pragma once
#include <iostream>
#include<cmath>
#include "Projectile.h"
#include "Player.h"
#include "HUD.h"
#include "Audio.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Beebot : public Enemy {

private:

	int BeebotStart;
	int BeebotEnd;
	int BeebotHeights;

	const float bee_height;
	const float bee_width;

	Texture move_bee;

	Clock moveClock;
	Clock attackClock;
	Clock animClock;

	bool ZigZag;
	bool shotProjectile;
	bool attackingPlayer;
	float targetX, targetY;
	float beeBaseY;

	Projectile* projectiles;
	int projectileCount;


	Clock cooldownClock;
	bool isLockedOn;
	bool canLock; 

	float prevX;



public:

	Beebot() : bee_height(37.5), bee_width(88.5) {

		hp = 5;
		speed = 2.2;
		Alive = true;
		Moving = true;
		x = 0;
		y = 0;
		prevX = 0;
		Start = 0;
		End = 0;
		beeBaseY = 0;
		ZigZag = true;
		shotProjectile = false;
		attackingPlayer = false;
		targetX = 0, targetY = 0;
		moveClock.restart();
		attackClock.restart();


		enemyHeight = bee_height;
		enemyWidth = bee_width;
		hit_box_factor_x = 7.5;
		hit_box_factor_y = 7.5;
		hitBox_x = x + hit_box_factor_x;
		hitBox_y = y + hit_box_factor_y;

		BeebotStart = 0;
		BeebotEnd = 0;
		BeebotHeights = 0;


		projectiles = nullptr;
		projectileCount = 0;


		isLockedOn = false;
		canLock = true;
		cooldownClock.restart();
		animClock.restart();



		move_bee.loadFromFile("Sprites/bees.png");

		totalAnimations = 3;
		indexAnimation = 0;

		states = new Animation * [totalAnimations];

		states[0] = new Animation(2);

		// Move 1: y = 4, h = 30
		states[0]->getSprites()[0].setTexture(move_bee);
		states[0]->getSprites()[0].setTextureRect(IntRect(0, 4, 47, 30));
		states[0]->getSprites()[0].setScale(1.88f, 1.25f); 

		// Move 2: y = 34, h = 26
		states[0]->getSprites()[1].setTexture(move_bee);
		states[0]->getSprites()[1].setTextureRect(IntRect(0, 34, 47, 26));
		states[0]->getSprites()[1].setScale(1.88f, 1.4423077f);


		states[1] = new Animation(4);

		// Stop: y = 60, h = 30
		states[1]->getSprites()[0].setTexture(move_bee);
		states[1]->getSprites()[0].setTextureRect(IntRect(0, 60, 47, 30));
		states[1]->getSprites()[0].setScale(1.88f, 1.25f);

		// Lock: y = 90, h = 26
		states[1]->getSprites()[1].setTexture(move_bee);
		states[1]->getSprites()[1].setTextureRect(IntRect(0, 90, 47, 26));
		states[1]->getSprites()[1].setScale(1.88f, 1.4423077f);

		// Charge: y = 116, h = 40
		states[1]->getSprites()[2].setTexture(move_bee);
		states[1]->getSprites()[2].setTextureRect(IntRect(0, 116, 47, 40));
		states[1]->getSprites()[2].setScale(1.88f, 0.9375f);

		// Fire: y = 156, h = 32
		states[1]->getSprites()[3].setTexture(move_bee);
		states[1]->getSprites()[3].setTextureRect(IntRect(0, 152, 47, 32));
		states[1]->getSprites()[3].setScale(1.88f, 1.171875f);


		loadDeathAnimation("Sprites/death0.png", 41, 42, 1.5f, 1.5f);  



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
	bool getBeebotCoordinates(char** lvl, int height, int width, int y_start, int y_end, int& j_start, bool* occupiedColumns);
	void move_beebots(const int cell_size);
	bool handleProjectilesCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY,int h,int w);
	bool PlayerBeeCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight);
	void update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver) override;
	void drawExtra(RenderWindow& window, float offset_x) override;

};





void Beebot::update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver)
{

	if (handleDeathAnimation())
		return;

	movement(lvl, player.getx(), player.gety(), cell_size, player.getPwidth(), player.getPheight());

	if (handleProjectilesCollision(lvl, cell_size, player.getx(), player.gety(), player.getPwidth(), player.getPheight(), hasKnockedBack, tempVelocityY, 14, 200)) 
	{
		hud.getLives()--;
		onGround = false;

		if (hud.getLives() <= 0)
			gameOver = true;
	}

	if (!hasKnockedBack) {

		if (PlayerEnemyCollision(player, getbeeWidth(), getbeeHeight())) {

			if (indexAnimation == UPR || indexAnimation == UPL || indexAnimation == GLIDEL || indexAnimation == GLIDER) {

				setHp(0);

				if (Alive) 
				{
					setAlive(false);
					if (audio) {
						audio->playSound(audio->getDestroy());
					}
					isDying = true;
					deathClock.restart();
					deathFrameClock.restart();
					hud.getScore() += 200;
				}
			}

			else {

				hud.getLives()--;
				if (hud.getLives() <= 0) gameOver = true;
				hasKnockedBack = true;
				tempVelocityY = -7;
			}
		}
	}
}


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
				canLock = false;
				cooldownClock.restart();
				attackClock.restart();
				targetX = playerCenterX;
				targetY = player_y + player_height / 2.0f;
				//cout << "Bee Locking on to player"<<endl;
			}

			if (isLockedOn) {

				y = beeBaseY;

				float time = attackClock.getElapsedTime().asSeconds();

				indexAnimation = 1;

				if (time < 0.2f)
					sprite = states[1]->getSprites()[0]; // stop
				else if (time < 0.4f)
					sprite = states[1]->getSprites()[1]; // lock-on
				else if (time < 0.6f)
					sprite = states[1]->getSprites()[2]; // charge

				else {

					sprite = states[1]->getSprites()[3]; // fire

					if (!shotProjectile) {

						shotProjectile = true;

						float projectileX = targetX - beeCenterX;
						float projectileY = targetY - (y + getbeeHeight() / 2.0f);
						float magnitude = sqrt(projectileX * projectileX + projectileY * projectileY);

						if (magnitude != 0) {
							projectileX /= magnitude;
							projectileY /= magnitude;
						}

						if (!projectiles)
							projectiles = new Projectile();

						projectiles->setPosition(beeCenterX, y + getbeeHeight() / 2.0f, projectileX, projectileY, 4.0f);
						if (audio) {
							audio->playSound(audio->getShot());
						}
					}
				}

				if (time > 1.0f && shotProjectile) {
					isLockedOn = false;
					attackingPlayer = false;
					canLock = true;
					shotProjectile = false;
				}

			}

			if(isLockedOn && (player_x < Start || player_x > End || distanceX > 60.0f || (player_y - beeBaseY) > 256.0f || (player_y - beeBaseY) < -100.0f)) {
				isLockedOn = false;
				shotProjectile = false;
				attackClock.restart();
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

	if (!attackingPlayer || !isLockedOn) {

		indexAnimation = 0;

		if (animClock.getElapsedTime().asSeconds() >= 0.175f) {
			states[0]->RunAnimation();
			animClock.restart();
		}

		sprite = states[0]->getSprites()[states[0]->getIndex()];
	}

	if (x > prevX) {
		sprite.setScale(-1.88f, 1.346f);
		sprite.setOrigin(47.f, 0);
	}

	else if (x < prevX) {
		sprite.setScale(1.88f, 1.346f);
		sprite.setOrigin(0, 0);
	}

	prevX = x;

	sprite.setPosition(x, y);

	updateHitbox();

	if (projectiles && projectiles->Active()) {
		projectiles->move();
	}

}



void Beebot::move_beebots(const int cell_size)
{

	float patrolStart = BeebotStart * cell_size;
	float beebot_End = BeebotEnd * cell_size;
	float beebot_maxEnd = patrolStart + 10 * cell_size;
	float patrolEnd = (beebot_End > beebot_maxEnd) ? beebot_maxEnd : beebot_End;

	float bee_X = (patrolStart + patrolEnd) / 2.0f;
	float bee_Y = BeebotHeights * cell_size + 10;

	setPosition(bee_X, bee_Y, patrolStart, patrolEnd);
	beeBaseY = bee_Y;

	cout << "Placed Beebot at: " << bee_X << ", " << bee_Y << endl;

}

bool Beebot::getBeebotCoordinates(char** lvl, int height, int width, int y_start, int y_end, int& j_start, bool* occupiedColumns)

{

	for (int i = y_start; i < y_end; i++) {

		for (int j = j_start; j < width - 1; j++) {

			if (lvl[i][j] == 's' && lvl[i + 1][j] == 's' && lvl[i - 1][j] == 's') {

				int start = j;

				while (j < width && lvl[i][j] == 's' && lvl[i + 1][j] == 's' && lvl[i - 1][j] == 's') {
					j++;
				}

				int end = j - 1;

				if (end - start + 1 >= 7) {

					int midpoint = (start + end) / 2;
					int patrolStart = max(0, midpoint - 2);
					int patrolEnd = min(width - 1, midpoint + 2);

					bool conflict = false;

					for (int col = patrolStart; col <= patrolEnd; col++) {

						if (occupiedColumns[col]) {
							conflict = true;
							break;
						}
					}

					if (!conflict) {

						BeebotStart = patrolStart;
						BeebotEnd = patrolEnd;
						BeebotHeights = i;

						for (int col = patrolStart; col <= patrolEnd; col++) {
							occupiedColumns[col] = true;
						}

						cout << "Placed Beebot from column " << patrolStart << " to " << patrolEnd << " at row " << i << endl;

						j_start = j;

						return true;
					}
				}
			}
		}

		j_start = 0; 
	}

	return false;
}



void Beebot::drawExtra(RenderWindow& window, float offset_x)
{
	if (projectiles && projectiles->Active()) {
		projectiles->draw(window, offset_x);
	}
}



bool Beebot::handleProjectilesCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY,int height,int width)
{
	if (projectiles && projectiles->Active()) 
	{
		if (projectiles->handleCollision(lvl, cell_size, player_x, player_y, player_width, player_height, hasKnockedBack, tempVelocityY,height,width))
		{
			if (!projectiles->Active())
			{
				delete projectiles;
				projectiles = nullptr;
				cout << "Bee Projectile deleted" << endl;
			}
			return true;
		}
	}
	return false;
}

bool Beebot::PlayerBeeCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
{
	return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
}



