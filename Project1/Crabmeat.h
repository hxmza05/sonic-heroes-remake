#pragma once
#include<iostream>
#include<cmath>
#include "Projectile.h"
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

	int* CrabStart;
	int* CrabEnd;
	int* CrabWalls;
	int crabCoordinates;
	int indexCrab;

	const float crabHeight;
	const float crabWidth;

	Projectile* projectile;
	Clock lockTimer, cooldownClock, afterShot;
	bool isLockedOn, canLock, shotProjectile;
	float targetX, targetY;
	bool isStoppingToShoot;



public:

	Crabmeat() : crabHeight(44.0), crabWidth(60.0) {

		this->hp = 4;
		this->speed = 1.0;
		Alive = true;
		Moving = true;
		attack = false;
		this->x = 0;
		this->y = 0;
		Start = 0;
		End = 0;

		totalAnimations = 4;
		indexAnimation = 0;

		crabCoordinates = 10;
		indexCrab = 0;

		projectile = nullptr;
		isLockedOn = false;
		canLock = true;
		shotProjectile = false;
		isStoppingToShoot = false;
		lockTimer.restart();
		cooldownClock.restart();
		afterShot.restart();


		CrabStart = new int[crabCoordinates];
		CrabEnd = new int[crabCoordinates];	
		CrabWalls = new int[crabCoordinates];


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

	float getcrabHeight() const {
		return crabHeight;
	}

	float getcrabWidth() const {
		return crabWidth;
	}

	bool handleProjectilesCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY);
	void drawProjectile(RenderWindow& window, float offset_x);
	void movement(char** lvl, Player& player, int cell_size);
	void getCrabCoordinates(char** lvl, int height, int width);
	void move_crabs(Crabmeat** crabs, int& crabIndex, int& crabCount, const int cell_size);

	bool getProjectileActive();

	bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight);

	bool CollisionCheckWithCrabs(Crabmeat** crabs, int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight);

};

void Crabmeat::movement(char** lvl, Player& player, int cell_size)
{

	float crabCenterX = x + crabWidth / 2.0f;
	float crabCenterY = y + crabHeight / 2.0f;

	float playerCenterX = player.getx() + player.getPwidth() / 2.0f;
	float playerCenterY = player.gety() + player.getPheight() / 2.0f;

	float ProjectileX = playerCenterX - crabCenterX;
	float ProjectileY = playerCenterY - crabCenterY;
	float distance = sqrt(ProjectileX * ProjectileX + ProjectileY * ProjectileY);
	float projectileRange = 4.0f * cell_size; 

	if (distance <= projectileRange && player.getOnGround()) {

		if (!isLockedOn && canLock && cooldownClock.getElapsedTime().asSeconds() >= 4.0f) {

			isLockedOn = true;
			canLock = false;

			lockTimer.restart();
			cooldownClock.restart();

			targetX = playerCenterX;
			targetY = playerCenterY;

			isStoppingToShoot = true;
			Moving = false; 

		}

		if (isLockedOn && lockTimer.getElapsedTime().asSeconds() >= 1.0f && !shotProjectile) {

			shotProjectile = true;
			afterShot.restart();

			// horizontl and vertical distance 
			float dx = targetX - crabCenterX;
			float dy = targetY - crabCenterY;

			// speed horiztonal - in pixels
			float desiredVx = 0.25f;

			// t = distance / speed
			float t = abs(dx) / desiredVx;  // gives numb of frames

			// setting range for t
			if (t < 3.0f)  // minimum hang time
				t = 3.0f; 
			
			if (t > 25.0f)  // max hang time
				t = 25.0f;     

			// gravity accel
			float g = 0.6f;  

			// initial horizontal speed
			float vx = dx / t;

			// initial vertical speed
			// s = vy*t + 1/2*(-g)*(t^2)
			float vy = (dy - 0.5f * g * t * t) / t;

			if (!projectile || !projectile->Active()) {
				if (projectile) delete projectile; // prevent leak
				projectile = new Projectile();
			}


			projectile->setCrabProjectileVelocity(crabCenterX, crabCenterY, vx, vy);

			cout << "Projectile Fired" << endl;
			cout << "dx: " << dx << " dy: " << dy << " distance: " << distance << endl;
			cout << "vx: " << vx << " vy: " << vy << endl;

		}

		if (shotProjectile && afterShot.getElapsedTime().asSeconds() >= 1.0f) {

			isLockedOn = false;
			shotProjectile = false;
			canLock = true;
			isStoppingToShoot = false;
			Moving = true; 

			cout << "Resume ---- Crab done firing --- resumes movement " << endl;

		}

	}

	if (isStoppingToShoot && shotProjectile && afterShot.getElapsedTime().asSeconds() >= 1.0f && (!projectile || !projectile->Active())) {

		isLockedOn = false;
		shotProjectile = false;
		canLock = true;
		isStoppingToShoot = false;
		Moving = true;

		cout << "Recovery --- Crab resumed --- due to timeout " << endl;
	}

	if (!isStoppingToShoot) {

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

	}

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

	if (projectile && projectile->Active()) {
		projectile->moveCrabProjectile();
	}


}

void Crabmeat::drawProjectile(RenderWindow& window, float offset_x) {

	if (projectile && projectile->Active()) {
		cout << "Drawing for crab at X: " << getX() << " Y: " << getY() << " Active: 1\n";
		projectile->draw(window, offset_x);
	}
}

bool Crabmeat::getProjectileActive() {
	return projectile && projectile->Active();
}


void Crabmeat::getCrabCoordinates(char** lvl, int height, int width) {

	for (int i = 5; i < height/2 + 2; i++) { //////////// add variables for start and end range in loop conditions

		int j = 0;

		while (j < width - 1) {

			if (lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q')) {

				int start = j;

				while (j < width && lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q'))
					j++;

				int end = j - 1;

				if (end - start + 1 >= 4 && indexCrab < crabCoordinates) {
					CrabStart[indexCrab] = start;
					CrabEnd[indexCrab] = end;
					CrabWalls[indexCrab] = i;
					indexCrab++;
				}
				//cout << "Found platform from tile " << start << " to " << end << " at row " << i << endl;
			}

			else { 
				j++;
			}
		}
	}
}

void Crabmeat::move_crabs(Crabmeat** crabs, int& crabIndex, int& crabCount, const int cell_size){

	int maxCrabs = min(indexCrab, crabCount);

	for (int i = 0; i < maxCrabs; i++) {

		if (crabIndex < 10) {

			float Start = CrabStart[i] * cell_size;
			float crabmeatEnd = CrabEnd[i] * cell_size;
			float crabmeatmaxEnd = Start + 12 * cell_size;
			float End = (crabmeatEnd > crabmeatmaxEnd) ? crabmeatmaxEnd : crabmeatEnd;

			float crabX = (Start + End) / 2.0f;
			float crabY = (CrabWalls[i] + 1) * cell_size - crabHeight;

			crabs[i]->setPosition(crabX, crabY, Start, End);

			crabIndex++;
		}
	}

	crabCount = crabIndex;
}



bool Crabmeat::handleProjectilesCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY) {
	
	if (projectile && projectile->Active()) {

		if (projectile->handleCollision(lvl, cell_size, player_x, player_y, player_width, player_height, hasKnockedBack, tempVelocityY)) {
			
			if (!projectile->Active()) {

				delete projectile;
				projectile = nullptr;
			}
			return true;
		}
	}
	return false;
}


bool Crabmeat::PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
{
	return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
}

bool Crabmeat::CollisionCheckWithCrabs(Crabmeat** crabs, int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight)
{

	for (int i = 0; i < crabCount; i++) {

		if (!crabs[i]->alive()) {
			continue;
		}

		if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, crabs[i]->getX(), crabs[i]->getY(), crabWidth, crabHeight)) {

			float bottom_of_Player = player_y + Pheight;
			float top_of_Crab = crabs[i]->getY();

			if (bottom_of_Player - 10 < top_of_Crab) {

				// crab ko marna hai ab becoz top collision, also add smoke effect and invincibilty 
				cout << " Top-hit:  " << i << endl;

				cout << "PlyrX: " << player_x << "crab X: " << crabs[i]->getX() << endl;

				velocityY = -10.0f;
			}

			else {

				hasKnockedBack = true;
				tempVelocityY = -7;

				crabs[i]->setAnimation(3);
				crabs[i]->RunNewAnimation();
				crabs[i]->setAttack();

				//cout << "PlyrX " << centre_of_Player << " Crab CenterX " << centre_of_CRab << endl;

				//cout << " Sidehit " << i << endl;

				//cout << "PlyrX " << player_x << " Crab X " << crabs[i].getX() << endl;
			}
			return true;
		}
	}

	return false;
}