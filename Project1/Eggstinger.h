#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Eggstinger {

private:

	float x, y, speed;
	int hp;
	bool right;
	//bool left;
	//bool up;
	//bool down;
	bool StingerIsAlive;
	Texture texture;
	Sprite sprite;
	Clock clock;

public:

	Eggstinger() {

		this->hp = 15;
		this->speed = 2.0;
		StingerIsAlive = true;
		this->right = true;
		this->x = 400;
		this->y = 100;
		texture.loadFromFile("Sprites/eggstinger.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 150, 122));
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

		return StingerIsAlive;
	}

	void movement(float player_x, float player_y) {

		right ? x += speed : x -= speed;

		if (x >= player_x+100)
			right = false;

		if (x <= player_x-100)
			right = true;

		//if (clock.getElapsedTime().asSeconds() >= 10)

		sprite.setPosition(x, y);

	}

	void draw(RenderWindow& window) {

		if (StingerIsAlive) {

			window.draw(sprite);
		}

		else {

			sprite.setPosition(999, 999);
		}

	}
};
