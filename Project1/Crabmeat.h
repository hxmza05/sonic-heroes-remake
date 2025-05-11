#pragma once
#include<iostream>
#include<cmath>
#include "Projectile.h"
#include "Player.h"
#include "HUD.h"
#include "Audio.h"
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

	int crabStart;
	int crabEnd;
	int crabWall;

	const float crabHeight;
	const float crabWidth;

	Projectile* projectile;
	Clock lockTimer, cooldownClock, afterShot;
	bool isLockedOn, canLock, shotProjectile;
	float targetX, targetY;
	bool isStoppingToShoot;



public:

	Crabmeat() : crabHeight(44.0), crabWidth(60.0) 
	{

		this->hp = 4;
		this->speed = 1.0;
		Alive = true;
		Moving = true;
		attack = false;
		this->x = 0;
		this->y = 0;
		Start = 0;
		End = 0;

		totalAnimations = 5;
		indexAnimation = 0;

		enemyHeight = crabHeight;
		enemyWidth = crabWidth;
		hit_box_factor_x = 2;  
		hit_box_factor_y = 2;
		hitBox_x = x + hit_box_factor_x;
		hitBox_y = y + hit_box_factor_y;

		projectile = nullptr;
		isLockedOn = false;
		canLock = true;
		shotProjectile = false;
		isStoppingToShoot = false;
		lockTimer.restart();
		cooldownClock.restart();
		afterShot.restart();


		crabStart = 0;
		crabEnd = 0;
		crabWall = 0;



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

		// deatg


		loadDeathAnimation("Sprites/death0.png", 41, 42, 1.5f, 1.5f);



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

	float getStart() const {
		return Start;
	}

	float getEnd() const {
		return End;
	}


	bool handleProjectilesCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY,int height,int width);
	void movement(char** lvl, Player& player, int cell_size);
	void move_crabs(const int cell_size);
	bool getProjectileActive();
	bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight);
	bool checkCollisionWithPlayer(Player& player);
	void update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver) override;
	void drawExtra(RenderWindow& window, float offset_x) override;
	bool getCrabCoordinates(char** lvl, int height, int width, int y_start, int y_end, int& j_start);


};


bool Crabmeat::getCrabCoordinates(char** lvl, int height, int width, int y_start, int y_end, int& j_start) {

	for (int i = y_start; i < y_end; i++) {

		for (int j = j_start; j < width - 1; j++) {

			if (lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q')) {

				int start = j;

				while (j < width && lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q')){
					j++;
				}

				int end = j - 1;

				if (end - start + 1 >= 4) 
				{
					crabStart = start;
					crabEnd = end;
					crabWall = i;
					j_start = j; 
					return true;
				}
			}
		}

		j_start = 0;  
	}

	return false;
}


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

		if (isLockedOn && lockTimer.getElapsedTime().asSeconds() >= 0.7f && !shotProjectile) {

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
				if (projectile) delete projectile; 
				projectile = new Projectile();
			}

			projectile->setCrabProjectileVelocity(crabCenterX, crabCenterY, vx, vy);

			if (audio) {
				audio->playSound(audio->getShot());
			}

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

	if (isStoppingToShoot && shotProjectile && afterShot.getElapsedTime().asSeconds() >= 1.0f) {

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

	if (isStoppingToShoot) {

		indexAnimation = 3; 
	}

	else if (attack) {

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

	updateHitbox();

	if (projectile && projectile->Active()) {
		projectile->moveCrabProjectile();
	}


}


bool Crabmeat::getProjectileActive() {
	return projectile && projectile->Active();
}


void Crabmeat::update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver)
{

	if (handleDeathAnimation()) 
		return;

	movement(lvl, player, cell_size);

	if (handleProjectilesCollision(lvl, cell_size, player.getx(), player.gety(), player.getPwidth(), player.getPheight(), hasKnockedBack, tempVelocityY, 14, 200)) 
	{

		if (audio) {
			audio->playSound(audio->getExplosion());
		}

		hud.getLives()--;
		onGround = false;

		if (hud.getLives() <= 0)
			gameOver = true;
	}

	if (!hasKnockedBack && PlayerEnemyCollision(player, crabWidth, crabHeight)) {

		if (indexAnimation == UPR || indexAnimation == UPL) {

			setHp(0);

			if (hp <= 0 && Alive)
			{
				setAlive(false);
				if (audio) {
					audio->playSound(audio->getDestroy());
				}
				isDying = true;
				deathClock.restart();
				deathFrameClock.restart();
				hud.getScore() += 150;
			}

		}

		else 
		{

			hud.getLives()--;

			if (hud.getLives() <= 0) 
				gameOver = true;

			hasKnockedBack = true;
			tempVelocityY = -7;
		}
	}
}


void Crabmeat::drawExtra(RenderWindow& window, float offset_x)  {

	if (projectile && projectile->Active()) {
		projectile->draw(window, offset_x);
	}
}


void Crabmeat::move_crabs(const int cell_size)
{

	float Start = crabStart * cell_size;
	float crabmeatEnd = crabEnd * cell_size;
	float crabmeatmaxEnd = Start + 12 * cell_size;
	float End = (crabmeatEnd > crabmeatmaxEnd) ? crabmeatmaxEnd : crabmeatEnd;

	float crabX = (Start + End) / 2.0f;
	float crabY = (crabWall + 1) * cell_size - crabHeight;

	setPosition(crabX, crabY, Start, End);


	cout << "Placed crab at X: " << crabX << ", Y: " << crabY << endl;

}


bool Crabmeat::handleProjectilesCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY,int height,int width) 
{
	
	if (projectile && projectile->Active()) {

		if (projectile->handleCollision(lvl, cell_size, player_x, player_y, player_width, player_height, hasKnockedBack, tempVelocityY,height,width)) 
		{
			
			if (!projectile->Active()) {

				delete projectile;
				projectile = nullptr;
			}
			return true;
		}
	}
	return false;
}


bool Crabmeat::PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight)
{
	return (player_x + Pwidth > x + hit_box_factor_x && player_x < x + hit_box_factor_x + (enemyWidth - 2 * hit_box_factor_x) && player_y + Pheight > y + hit_box_factor_y && player_y < y + hit_box_factor_y + (enemyHeight - 2 * hit_box_factor_y));
}

bool Crabmeat::checkCollisionWithPlayer(Player& player)
{

	if (!Alive) {
		return false;
	}

	if (PlayerEnemyCollision(player, crabWidth, crabHeight)) {

		float bottom_of_Player = player.gety() + player.getPheight();
		float top_of_Crab = y;

		if (bottom_of_Player - 10 < top_of_Crab) 
		{
			//Alive = false;
			//hp = 0;
		}

		else {

			player.getHasKnockedBack() = true;
			player.getTempVelocityY() = -7;
			setAnimation(3);
			RunNewAnimation();
			setAttack();
		}

		return true;
	}

	return false;
}

