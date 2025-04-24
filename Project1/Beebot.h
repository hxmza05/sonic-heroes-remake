#pragma once
#include <iostream>
#include<cmath>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Beebot : public Enemy {

private:

	float increase;
	float amplitude;
	float baseY;

public:

	Beebot() {

		hp = 5;
		increase = 0;
		speed = 0.8;
		amplitude = 20;
		baseY = 0;
		Alive = true;
		Moving = true;
		x = 0;
		y = 0;
		Start = 0;
		End = 0;

		texture.loadFromFile("Sprites/beebot.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 118, 50));
		sprite.setPosition(x, y);
		sprite.setScale(0.75f, 0.75f);

	}

	void setBaseY(int baseY) {
		this->baseY = baseY;
	}

	void movement() {

		increase += 0.1;

		x += speed;

		if (x >= End) {
			speed = -abs(speed);
		}
		if (x <= Start) {
			speed = abs(speed);
		}

		y = baseY + amplitude * sin(increase);

		sprite.setPosition(x, y);

	}

};
