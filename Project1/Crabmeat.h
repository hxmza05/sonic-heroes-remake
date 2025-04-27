#pragma once
#include<iostream>
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

	const float crabHeight = 44.0;
	const float crabWidth = 60.0;


public:

	Crabmeat() {

		this->hp = 4;
		this->speed = 2.0;
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

	void movement()
	{

		Moving ? x += speed : x -= speed;

		if(x>= End)
			Moving = false;

		if (x <= Start)
			Moving = true;


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

	}

	void getCrabCoordinates(char** lvl, int height, int width);
	void draw_crabs(RenderWindow& window, Crabmeat crabs[], int& crabCount, int offset_x);
	void move_crabs(Crabmeat crabs[], int& crabIndex, int& crabCount, const int cell_size);



};

void Crabmeat::draw_crabs(RenderWindow& window, Crabmeat crabs[], int& crabCount, int offset_x)
{
	for (int i = 0; i < crabCount; i++) {

		crabs[i].movement();
		crabs[i].draw(window, offset_x);

	}
}


void Crabmeat::getCrabCoordinates(char** lvl, int height, int width) {

	for (int i = 5; i < height - 1; i++) {

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



void Crabmeat::move_crabs(Crabmeat crabs[], int& crabIndex, int& crabCount, const int cell_size){

	int maxCrabs = min(indexCrab, crabCount);

	for (int i = 0; i < maxCrabs; i++) {

		if (crabIndex < 10) {

			float patrolStart = CrabStart[i] * cell_size;
			float crabmeatEnd = CrabEnd[i] * cell_size;
			float crabmeatmaxEnd = patrolStart + 12 * cell_size;
			float patrolEnd = (crabmeatEnd > crabmeatmaxEnd) ? crabmeatmaxEnd : crabmeatEnd;

			float crabX = (patrolStart + patrolEnd) / 2.0f;
			float crabY = (CrabWalls[i] + 1) * cell_size - crabHeight;

			crabs[i].setPosition(crabX, crabY, patrolStart, patrolEnd);

			crabIndex++;
		}
	}

	crabCount = crabIndex;
}