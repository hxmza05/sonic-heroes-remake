#pragma once
#include <iostream>
#include <cmath>
#include "Player.h"
#include "HUD.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Batbrain : public Enemy {

private:

	bool chasingPlayer;   
	bool facingRight; 

	float StartX, StartY; 

	const float Batheight;
	const float BatWidth;

	Clock chaseCooldownClock;
	bool isCooldown;


	Texture spawn;
	Texture initial_move;
	Texture move;
	Texture accel;


	Clock animationClock;
	Clock animationPhaseClock;  
	Clock frameClock;

	int animationFrame;




public:

	Batbrain() : Batheight(71.25), BatWidth(72.75f) {

		this->hp = 3;
		this->speed = 2.0f;
		Alive = true;
		Moving = true;
		chasingPlayer = false;
		facingRight = false;  
		StartX = x;
		StartY = y;
		indexAnimation = 0;
		totalAnimations = 4;
		animationClock.restart();
		animationPhaseClock.restart();
		frameClock.restart();
		animationFrame = 0;


		chaseCooldownClock.restart();
		isCooldown = false;


		states = new Animation * [totalAnimations];

		//  spawn

		states[0] = new Animation(1);
		spawn.loadFromFile("Sprites/bat_sleep.png");
		states[0]->getSprites()[0].setTexture(spawn);
		states[0]->getSprites()[0].setTextureRect(IntRect(0, 0, 36, 60));
		//states[0]->getSprites()[0].setScale(BatWidth / 36, Batheight / 60);


		// move 0 

		const int frameWidths[4] = { 77, 66, 80, 86 };
		initial_move.loadFromFile("Sprites/bat_move.png");
		states[1] = new Animation(4);
		int offsetX = 0;

		for (int i = 0; i < 4; i++)
		{
			states[1]->getSprites()[i].setTexture(initial_move);
			states[1]->getSprites()[i].setTextureRect(IntRect(offsetX, 0, frameWidths[i], 79));
			states[1]->getSprites()[i].setScale(BatWidth / frameWidths[i], Batheight / 79.0f);
			states[1]->getSprites()[i].setOrigin(frameWidths[i] / 2.0f, 0);
			offsetX += frameWidths[i];
		}



		// move 1
		const int move1Widths[4] = { 77, 76, 82, 91 };
		const int move1Offsets[4] = { 0, 82, 158, 240 };

		move.loadFromFile("Sprites/bat_move1.png");
		states[2] = new Animation(4);
		offsetX = 0;

		for (int i = 0; i < 4; ++i) 
		{
			states[2]->getSprites()[i].setTexture(move);
			states[2]->getSprites()[i].setTextureRect(IntRect(move1Offsets[i], 0, move1Widths[i], 69));
			states[2]->getSprites()[i].setScale(BatWidth / float(move1Widths[i]), Batheight / 69.0f);
			states[2]->getSprites()[i].setOrigin(move1Widths[i] / 2.0f, 0);
		}


		accel.loadFromFile("Sprites/bat_accel.png");
		states[3] = new Animation(1);
		states[3]->getSprites()[0].setTexture(accel);
		states[3]->getSprites()[0].setTextureRect(IntRect(0, 0, 95, 53));
		//states[3]->getSprites()[0].setScale(BatWidth / 95, Batheight / 53);
		states[3]->getSprites()[0].setOrigin(95.0f / 2.0f, 0);



	}


	float getBatBrainHeight() const {
		return Batheight;
	}

	float getBatBrainWidth() const {
		return BatWidth;
	}


	void movement(char** lvl, float player_x, float player_y, const int cell_size);
	bool getBatbrainCoordinates(char** lvl, int height, int width, int& i_start, int& j_start, const int cell_size);
	void setPosition(float startX, float startY, float patrolStart, float patrolEnd);
	bool PlayerBatCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight);
	void update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver) override;
	void drawExtra(RenderWindow& window, float offset_x) override {}  // Nothing for now


};


void Batbrain::movement(char** lvl, float player_x, float player_y, const int cell_size)
{
	float distanceX = player_x - x;
	float distanceY = player_y - y;
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	float batCenter = x + BatWidth / 2.0f;
	float playerCenter = player_x + 10.0f;

	if (playerCenter < batCenter - 10.0f) {
		facingRight = false;
	}
	else if (playerCenter > batCenter + 10.0f) {
		facingRight = true;
	}


	if (isCooldown && chaseCooldownClock.getElapsedTime().asSeconds() < 1.0f) 
	{
		sprite.setPosition(x, y);
		return;
	}

	else if (isCooldown && chaseCooldownClock.getElapsedTime().asSeconds() >= 1.0f) 
	{
		isCooldown = false;
	}

	bool withinVerticalRange = player_y >= StartY - 128;
	bool withinHorizontalRange = (distanceX < cell_size*6 && distanceX > cell_size * -6);

	if (!chasingPlayer && !isCooldown && withinHorizontalRange && withinVerticalRange) 
	{
		chasingPlayer = true;
		animationFrame = 0;
		frameClock.restart();
		animationPhaseClock.restart(); 

	}

	else if (chasingPlayer && (!withinVerticalRange || (distanceX > cell_size * 6 || distanceX < cell_size * -6)))
	{
		chasingPlayer = false;
		isCooldown = true;
		chaseCooldownClock.restart();
	}

	if (chasingPlayer)
	{
		if (distance != 0)
		{
			distanceX /= distance;
			distanceY /= distance;

			float move_x = x + distanceX * speed;
			float move_y = y + distanceY * speed;

			if (move_x < Start) {
				move_x = Start;
			}

			if (move_x > End) {
				move_x = End;
			}

			if (!checkWallCollisionWithEnemy(lvl, move_x + (facingRight ? -6.0f : 6.0f), move_y + 6.0f, cell_size))
			{
				x = move_x;
				y = move_y;
			}
		}

		float elapsed = animationPhaseClock.getElapsedTime().asSeconds();
		float cycleDuration = 4.5f; 

		if (elapsed >= cycleDuration) {
			animationPhaseClock.restart();
			elapsed = 0;
		}

		if (elapsed < 3.0f) {

			indexAnimation = 2;  // move1

			if (frameClock.getElapsedTime().asSeconds() >= 0.15f) 
			{
				frameClock.restart();
				animationFrame++;

				if (animationFrame >= 4) {
					animationFrame = 0;
				}
			}
		}
		else {
			indexAnimation = 3;  // accel
			animationFrame = 0;
		}

	}

	else {

		animationFrame = 0;

		if (y == StartY) {
			indexAnimation = 0; 
		}

		else {
			indexAnimation = 3;  
		}
	}

	if (indexAnimation == 2) {
		sprite = states[2]->getSprites()[animationFrame];
	}

	else {
		sprite = states[indexAnimation]->getSprites()[0]; 
	}


	sprite.setScale((facingRight ? -1.0f : 1.0f), Batheight / 69.0f);


}


void Batbrain::update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver)
{

	movement(lvl, player.getx(), player.gety(), cell_size);

	if (!hasKnockedBack)
	{
		if (PlayerBatCollision(player.getx(), player.gety(), player.getPwidth(), player.getPheight(), x, y, getBatBrainWidth(), getBatBrainHeight()))
		{
			if (indexAnimation == UPR || indexAnimation == UPL)
			{
				setHp(0);
				setAlive(false);
				hud.getScore() += 120;
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
}



//void Batbrain::getBatbrainCoordinates(Batbrain** batbrains, char** lvl, int height, int width, int& batIndex, int batCount, int cell_size)
//{
//	for (int i = 0; i < height && batIndex < batCount; i++)
//	{
//		for (int j = 0; j < width && batIndex < batCount; j++)
//		{
//			if (lvl[i][j] == 'b')
//			{
//				float bat_x = j * cell_size;
//				float bat_y = i * cell_size;
//
//				int patrolStartTile = (j - 7 < 0) ? 0 : j - 7;
//				int patrolEndTile = (j + 7 >= width) ? (width - 1) : (j + 7);
//
//				float patrolStart = patrolStartTile * cell_size;
//				float patrolEnd = patrolEndTile * cell_size;
//
//				batbrains[batIndex]->setPosition(bat_x, bat_y, patrolStart, patrolEnd);
//				lvl[i][j] = 's';
//				batIndex++;
//			}
//		}
//	}
//}

bool Batbrain::getBatbrainCoordinates(char** lvl, int height, int width, int& i_start, int& j_start, const int cell_size)
{
	for (int i = i_start; i < height; i++) {

		int j = (i == i_start) ? j_start : 0;

		for (; j < width; j++) {

			if (lvl[i][j] == 'b') {

				float bat_x = j * cell_size;
				float bat_y = i * cell_size;

				int patrolStartTile = (j - 7 < 0) ? 0 : j - 7;
				int patrolEndTile = (j + 7 >= width) ? (width - 1) : (j + 7);

				float patrolStart = patrolStartTile * cell_size;
				float patrolEnd = patrolEndTile * cell_size;

				setPosition(bat_x, bat_y, patrolStart, patrolEnd);

				std::cout << "Placed Batbrain at (" << bat_x << ", " << bat_y << ")\n";

				lvl[i][j] = 's';  
				i_start = i;      
				j_start = j + 1;  

				return true;
			}
		}
		j_start = 0;  
	}
	return false;
}




void Batbrain::setPosition(float startX, float startY, float patrolStart, float patrolEnd) 
{
	x = startX;
	y = startY;
	StartX = startX;
	StartY = startY;
	Start = patrolStart;
	End = patrolEnd;
	sprite.setPosition(x, y);
}



bool Batbrain::PlayerBatCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
{
	return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
}
