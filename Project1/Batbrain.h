#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Batbrain {

private:

	float x, y, speed;
	int hp;
	Texture texture;
	Sprite sprite;
	bool BatisAlive;

public:

	Batbrain() {

		this->hp = 3;
		this->speed = 1.5;
		BatisAlive = true;
		this->x = 800;
		this->y = 200;
		texture.loadFromFile("Sprites/batbrain.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 97, 95));
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

		return BatisAlive;
	}

	void movement(float player_x, float player_y) {

		player_x > x ? x += speed : x -= speed;

		player_y > y ? y += speed : y -= speed;

		sprite.setPosition(x, y);

	}

	void draw(RenderWindow& window) {

		if (BatisAlive) {

			window.draw(sprite);
		}

		else {

			sprite.setPosition(999, 999);
		}

	}
};
