#pragma once

class Enemy 
{

protected:

	float x, y, speed;
	float hp;
	bool Alive, Moving;
	float Start, End;

	Texture texture;
	Sprite sprite;

public:

	Enemy() {

		x = 0, y = 0, speed = 0;
		hp = 0;
		Alive = false, Moving = false;
		Start = 0, End = 0;
	}

	
	float& getX() {

		return x;
	}

	float& getY() {

		return y;
	}

	float& getHp() {

		return hp;
	}

	bool& alive() {

		return Alive;
	}

	void setPosition(float startX, float startY, float Start, float End) {

		x = startX;
		y = startY;
		this->Start = Start;
		this->End = End;
		sprite.setPosition(x, y);

	}

	virtual void draw(RenderWindow& window, float offset_x) {

		if (Alive) {

			sprite.setPosition(x - offset_x, y);
			window.draw(sprite);
		}

		else {

			sprite.setPosition(999, 999);
		}

	}

	////////////////////////// remove this later /////////////////////////////

	float getSpriteHeight() 
	{
		return sprite.getGlobalBounds().height;
	}

	sf::FloatRect getBounds() const {
		sf::FloatRect bounds = sprite.getGlobalBounds();
		bounds.left = x;
		return bounds;
	}

	////////////////////////// remove this later /////////////////////////////

	Sprite& getSprite() {
		return sprite;
	}


};
