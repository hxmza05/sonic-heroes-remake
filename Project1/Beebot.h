#pragma once
#include <iostream>
#include<cmath>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Beebot {

private:

	float x, y, speed;
	float increase;
	int hp;
	Texture texture;
	Sprite sprite;
	bool BeeisAlive;

public:

	Beebot() {

		this->hp = 5;
		this->increase = 0;
		this->speed = 4.0;
		BeeisAlive = true;
		this->x = 300;
		this->y = 300;
		texture.loadFromFile("Sprites/beebot.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 118, 50));
		sprite.setPosition(x, y);
		sprite.setScale(0.75f, 0.75f);

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

		return BeeisAlive;
	}

	void movement() {

		increase += 0.1;

		x += speed;
		y = 300 + 30 * sin(increase);

		sprite.setPosition(x, y);

	}

	void draw(RenderWindow& window) {

		if (BeeisAlive) {

			window.draw(sprite);
		}

		else {

			sprite.setPosition(999, 999);
		}

	}
};
