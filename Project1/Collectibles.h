#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include"Animation.h"

class Collectibles 
{


protected:

	int x, y;
	bool collected;

	Animation** states;
	int indexAnimation;
	int totalAnimations;


	Texture* texture;
	Texture* afterEffect;
	Sprite sprite;

	bool showEffect;
	Clock effectClock;

public:

	Collectibles()
	{
		x = 0, y = 0;
		collected = false;
		indexAnimation = 0;
		totalAnimations = 0;
		states = nullptr;
		texture = nullptr;
		afterEffect = nullptr;
		showEffect = false;
		effectClock.restart();
	}


	Collectibles(int x, int y, bool collected)
	{
		this->x = x;
		this->y = y;
		this->collected = collected;
		indexAnimation = 0;
		totalAnimations = 0;
		states = nullptr;
		texture = nullptr;
		afterEffect = nullptr;
		showEffect = false;
		effectClock.restart();
	}

	virtual void draw(RenderWindow& window, float offset_x)
	{

		if (!collected || showEffect) {
			sprite.setPosition(x * 64 - offset_x, y * 64 + 12);
			window.draw(sprite);
		}

	}

	virtual void collect() = 0;
	virtual void update() 
	{
		
		if (collected) {
			return;
		}

		states[indexAnimation]->RunAnimation();
		sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];
		sprite.setPosition(x * 64, y * 64); 
	
	} 

	bool isActive() const { 
		return !collected; 
	}

	int getX() const { 
		return x; 
	}

	int getY() const { 
		return y; 
	}


	int getIndex() const {
		return states[indexAnimation]->getIndex();
	}


};


