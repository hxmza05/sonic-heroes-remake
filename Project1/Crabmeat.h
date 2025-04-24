#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Crabmeat : public Enemy {

private:
	

public:

	Crabmeat() {

		this->hp = 4;
		this->speed = 2.0;
		Alive = true;
		Moving = true;
		this->x = 0;
		this->y = 0;
		Start = 0;
		End = 0;
		texture.loadFromFile("Sprites/crabmeat.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 120, 88));
		sprite.setPosition(x, y);
		sprite.setScale(0.5f, 0.5f);

	}

	void movement() {

		Moving ? x += speed : x -= speed;

		if(x>= End)
			Moving = false;

		if (x <= Start)
			Moving = true;

		sprite.setPosition(x, y);

	}


};
