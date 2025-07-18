#pragma once
#include<iostream>
#include <cmath> 
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Projectile {


private:

	float x, y;
	float speed_x, speed_y;
	float gravity;
	float terminalVelocityY;
	bool active;
	bool wallCollision;
	bool playerCollision;

	Texture texture;
	Sprite sprite;

	CircleShape circle;

	const float x_width;
	const float x_heigth;


public:

	Projectile() : x_width(17.9f), x_heigth(18.0f) {

		x = 0,y = 0;
		speed_x = 0, speed_y = 0;
		active = false, wallCollision = false;
		playerCollision = false;
		gravity = 0.6f;
		terminalVelocityY = 15.0f;

		//texture.loadFromFile("Sprites/projectile.png");
		//sprite.setTexture(texture);
		//sprite.setTextureRect(IntRect(0, 0, 187, 185));
		//sprite.setOrigin(78.5f, 78.5f);
		//sprite.setColor(Color::Yellow);
		//sprite.setScale(0.1f, 0.1f);

		circle.setRadius(9.0f);
		circle.setFillColor(Color::White);
		//circle.setOrigin(9.0f, 9.0f);

		//circle.setOutlineColor(Color::Yellow);
		//circle.setOutlineThickness(2.0f);
		//circle.setFillColor(Color::Cyan);

	}

	bool& getActive() {
		return active;
	}

	void setActive(bool active) {
		this->active = active;
	}

	bool getWallCollision() {
		return wallCollision;
	}

	bool getPlayerCollision() {
		return playerCollision;
	}

	void setPosition(float startX, float startY, float directionX, float directionY, float speed);
	void move();
	void draw(RenderWindow& window, float offset_x);
	bool Active() const;
	bool checkCollisionWithPlayer(float player_x, float player_y, int Pwidth, int Pheight, float x, float y, const float x_width, const float x_heigth);
	bool checkCollisionWithWall(char** lvl, int cell_size,int height,int width);
	bool handleCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY,int h,int w);
	void moveCrabProjectile();
	void setCrabProjectileVelocity(float startX, float startY, float vx, float vy);


};


void Projectile::setPosition(float startX, float startY, float directionX, float directionY, float speed) {

	x = startX;
	y = startY;

	float magnitude = sqrt(directionX * directionX + directionY * directionY);

	if (magnitude != 0) {

		speed_x = (directionX / magnitude) * speed;
		speed_y = (directionY / magnitude) * speed;
	}

	else {

		speed_x = 0;
		speed_y = 0;
	}

	active = true;
	circle.setPosition(x, y);

}

void Projectile::move() {

	if (active == false) {
		return;
	}

	if (active) {

		x += speed_x;
		y += speed_y;

		circle.setPosition(x, y);

	}
}


void Projectile::draw(RenderWindow& window, float offset_x) {

	if (active) {
		circle.setPosition(x - offset_x, y);
		//cout << "Projectile draw: (" << x << " - " << offset_x << ", " << y << ") = (" << x - offset_x << ", " << y << ")\n";
		window.draw(circle);
	}
}

bool Projectile::checkCollisionWithPlayer(float player_x, float player_y, int Pwidth, int Pheight, float x, float y, const float x_width, const float x_heigth) {

	return (x + x_width > player_x && x < player_x + Pwidth && y + x_heigth > player_y && y < player_y + Pheight);

}

bool Projectile::checkCollisionWithWall(char** lvl, int cell_size, int height, int width) 
{
	int tile_x = (int)(x + x_width / 2) / cell_size;
	int tile_y = (int)(y + x_heigth / 2) / cell_size;

	if (tile_x < 0) tile_x = 0;
	else if (tile_x >= width) tile_x = width - 1;

	if (tile_y < 0) tile_y = 0;
	else if (tile_y >= height) tile_y = height - 1;

	char tile = lvl[tile_y][tile_x];

	if (tile == 'w' || tile == 'q' || tile == 'e' || tile == 'p') {
		active = false;
		//cout << "Projectile Hit wall � deactivated" << endl;
		return true;
	}

	return false;
}


bool Projectile::handleCollision(char** lvl, int cell_size, float player_x, float player_y, int player_width, int player_height, bool& hasKnockedBack, float& tempVelocityY,int height,int width)
{	
	if (checkCollisionWithPlayer(player_x, player_y, player_width, player_height, x, y, x_width, x_heigth))
	{
		active = false;	
		//cout << "Projectile Hit player  deactivated" << endl;
		hasKnockedBack = true;
		tempVelocityY = -10;
		//cout << "Knockback active ? " << hasKnockedBack << endl;
		return true;
	}
	else if (checkCollisionWithWall(lvl, cell_size,14,width)) 
	{
		active = false;
		//cout << "Projectile Hit wall  deactivated" << endl;
		return true;
	}

	return false;
}


bool Projectile::Active() const {
	return active;
}


void Projectile::moveCrabProjectile() {

	//cout << "Projectile moved to x: " << x << ", y: " << y << endl;

	if (active == false) {
		//cout << "Projectile deactivated immediately for crab at X: " << x << ", Y: " << y << endl;
		return;
	}

	if (active) {

		x += speed_x;

		speed_y += gravity;

		if (speed_y > terminalVelocityY) {
			speed_y = terminalVelocityY;
		}

		y += speed_y;

		circle.setPosition(x, y);
	}
}

void Projectile::setCrabProjectileVelocity(float startX, float startY, float vx, float vy) {

	x = startX;
	y = startY;

	speed_x = vx;
	speed_y = vy;

	active = true;

	circle.setPosition(x, y);

}
