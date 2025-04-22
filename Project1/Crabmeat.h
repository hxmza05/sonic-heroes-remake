#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Crabmeat {

private:

	float x, y, speed;
	int hp;
	Texture texture;
	Sprite sprite;
	bool CrabisAlive;
	bool moving;
	float crabStart, crabEnd;

public:

	Crabmeat() {

		this->hp = 4;
		this->speed = 2.0;
		CrabisAlive = true;
		moving = true;
		this->x = 0;
		this->y = 0;
		crabStart = 0;
		crabEnd = 0;
		texture.loadFromFile("Sprites/crabmeat.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 120, 88));
		sprite.setPosition(x, y);
		sprite.setScale(0.5f, 0.5f);

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

		return CrabisAlive;
	}

	void movement() {

		moving ? x += speed : x -= speed;

		if(x>= crabEnd)
			moving = false;

		if (x <= crabStart)
			moving = true;

		sprite.setPosition(x, y);

	}

	void setPositionAndPatrol(float startX, float startY, float crabStart, float crabEnd) {

		x = startX;
		y = startY;

		this->crabStart = crabStart;
		this->crabEnd = crabEnd;
		sprite.setPosition(x, y);

	}

	void draw(RenderWindow& window, float offset_x) {

		if (CrabisAlive) {

			sprite.setPosition(x - offset_x, y);
			window.draw(sprite);
		}

		else {

			sprite.setPosition(999, 999);
		}

	}

	float getSpriteHeight() {
		return sprite.getGlobalBounds().height;
	}

	Sprite& getSprite() {
		return sprite;
	}
};
