#pragma once
#include "Src.cpp"
#include <SFML/Graphics.hpp>

class Motobug {

private:

	float x, y;
	int hp;
	Texture texture;
	Sprite sprite;
	bool isAlive;


public:

	Motobug() {

		this->hp = 2;
		isAlive = true;
		this->x = 250;
		this->y = 150;
		texture.loadFromFile("Sprites/PC Computer - Sonic Mania - Badniks Plus.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 32, 32));
		sprite.setPosition(x, y);
		sprite.setScale(2.0f, 2.0f);

	}

	int getX() {

		return x;
	}

	int getY() {

		return y;
	}

	int getHp() {

		return hp;
	}


	void movement(float player_x, float player_y) {

		if (player_x > x) {

			x += 2.0f;
		}

		else if (player_x < x) {

			x -= 2.0f;
		}

		sprite.setPosition(x, y);

	}

	void draw(RenderWindow& window) {

		if (isAlive) {

			window.draw(sprite);
		}

		else {

			sprite.setPosition(999, 999);
		}
		
	}
};
