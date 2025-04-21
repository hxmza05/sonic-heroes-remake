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

public:

	Crabmeat() {

		this->hp = 4;
		this->speed = 2.0;
		CrabisAlive = true;
		moving = true;
		this->x = 250;
		this->y = 650;
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

		if(x>1200)
			moving = false;

		if (x < 0)
			moving = true;

		sprite.setPosition(x, y);

	}

	void draw(RenderWindow& window) {

		if (CrabisAlive) {

			window.draw(sprite);
		}

		else {

			sprite.setPosition(999, 999);
		}

	}
};
