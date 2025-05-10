#pragma once
#include <iostream>
#include "Enemy.h"
#include "Player.h"
#include "HUD.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Motobug : public Enemy
{

private:

	bool attack;
	Clock clock;

	int MotoBugStart;
	int MotoBugEnd;
	int MotoBugWalls;

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
		totalAnimations = 3;
		indexAnimation = 0;

		MotoBugStart = 0;
		MotoBugEnd = 0;
		MotoBugWalls = 0;

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

		loadDeathAnimation("Sprites/death0.png", 41, 42, 1.65f, 1.65f); 

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


	void update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver) override;
	void movement(float player_x, float player_y);
	void move_motobugs(const int cell_size);
	bool getMotobugCoordinates(char** lvl, int height, int width, int& start_x, int end_x, int& j_start);
	bool PlayerBugCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight);
	void drawExtra(RenderWindow& window, float offset_x);

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

		if (Moving) 
		{

			if (x + speed >= End/* - MotobugWidth*/) 
			{
				x = End/* - MotobugWidth*/;
				Moving = false;
			}

			else 
			{
				x += speed;
			}

			facingRight = true;
		}

		else 
			{

			if (x - speed <= Start + MotobugWidth) 
			{
				x = Start + MotobugWidth;
				Moving = true;
			}

			else 
			{
				x -= speed;
			}
			facingRight = false;
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

	if (facingRight) 
	{
		if (indexAnimation == 0) 
		{
			sprite.setPosition(x + 167.f * 0.452f, y);
		}
		else
		{
			sprite.setPosition(x + 169.6f * 0.451f, y);
		}
	}

	else {
		sprite.setPosition(x, y);
	}
}



void Motobug::update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver)
{

	if (handleDeathAnimation())
		return;


	movement(player.getx(), player.gety());

	if (!hasKnockedBack)
	{
		if (PlayerBugCollision(player.getx(), player.gety(), player.getPwidth(), player.getPheight(), x, y, getMotobugWidth(), getMotobugHeight()))
		{
			if (indexAnimation == UPR || indexAnimation == UPL)
			{
				setHp(0);

				if (hp <= 0 && Alive) {
					setAlive(false);
					isDying = true;
					deathClock.restart();
					deathFrameClock.restart();
					hud.getScore() += 100;
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
}


void Motobug::move_motobugs(const int cell_size)
{
	float Start = MotoBugStart * cell_size;
	float motobug_End = MotoBugEnd * cell_size;
	float motobug_maxEnd = Start + 10 * cell_size;
	float End = (motobug_End > motobug_maxEnd) ? motobug_maxEnd : motobug_End;

	float bug_X = (Start + End) / 2.0f;
	float bug_Y = (MotoBugWalls + 1) * cell_size - MotobugHeight;

	setPosition(bug_X, bug_Y, Start, End);
	cout << "Placed bug at X: " << bug_X << ", Y: " << bug_Y << endl;
}

bool Motobug::getMotobugCoordinates(char** lvl, int height, int width, int& start_x, int end_x, int& j_start)
{

	for (int i = start_x; i < end_x; i++) {

		int j = (i == start_x) ? j_start : 0;

		for (; j < width - 1; j++) {

			if (lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q')) {

				int start = j;

				while (j < width && lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q')) {
					j++;
				}

				int end = j - 1;

				if (end - start + 1 >= 4) {

					MotoBugStart = start;
					MotoBugEnd = end;
					MotoBugWalls = i;

					std::cout << "Found bug zone from tile " << start << " to " << end << " at row " << i << std::endl;

					start_x = i;    
					j_start = j;     

					return true;
				}
			}
		}
	}
	return false;
}


void Motobug::drawExtra(RenderWindow& window, float offset_x) {

}

bool Motobug::PlayerBugCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
{
	return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
}

