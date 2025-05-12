#pragma once
#include<iostream>
using namespace std;
using namespace sf;
#include"Animation.h"
#include "Player.h"
#include "HUD.h"
#include "Audio.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>



class Enemy 
{

protected:

	float x, y, speed;
	float hp;
	bool Alive, Moving, Attack;
	float Start, End;

	float hitBox_x, hitBox_y;
	float enemyHeight, enemyWidth;
	int hit_box_factor_x, hit_box_factor_y;

	Texture texture;
	Sprite sprite;
	Animation** states;
	int indexAnimation;
	int totalAnimations;

	bool isDying;          
	bool deathFinished;    

	Clock deathClock;             
	Clock deathFrameClock;      
	Texture* deathTexture;

	void loadDeathAnimation(const string& filepath, int frameWidth, int frameHeight, float scaleX, float scaleY);
	bool handleDeathAnimation();

	//RectangleShape hitBoxShape;  

	Audio* audio;


public:

	Enemy() {

		x = 0, y = 0, speed = 0;
		hp = 0;
		Alive = false, Moving = false;
		Start = 0, End = 0;
		enemyHeight = 0, enemyWidth = 0;
		hit_box_factor_x = 5*2.5f, hit_box_factor_y = 5*2.5f;
		hitBox_x = 0, hitBox_y = 0;
		indexAnimation = 0, totalAnimations = 0;	
		isDying = false, deathFinished = false;    
		deathClock.restart(), deathFrameClock.restart();        
		deathTexture = nullptr;

		//hitBoxShape.setFillColor(Color::Transparent);
		//hitBoxShape.setOutlineColor(Color::Red);
		//hitBoxShape.setOutlineThickness(1.f);
		//hitBoxShape.setSize(FloatRect(0, 0, 1, 1).getSize());

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

	void setHp(float x) {
		hp = x;
	}

	void setAlive(bool status) { 
		this->Alive = status; 
	}

	void setAudio(Audio* a) 
	{ 
		audio = a; 
	}

	void setAnimation(int animationIndex) {
		indexAnimation = animationIndex;
	}
	
	void RunNewAnimation() {
		states[indexAnimation]->RunAnimation();
		sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];
	}

	void setPosition(float startX, float startY, float Start, float End) {

		x = startX;
		y = startY;
		this->Start = Start;
		this->End = End;
		sprite.setPosition(x, y);

	}

	void draw(RenderWindow& window, float offset_x)
	{

		sprite.setPosition(x - offset_x, y);
		window.draw(sprite);

	}


	Sprite& getSprite() {
		return sprite;
	}

	bool deathDone() const {
		return deathFinished;
	}

	bool checkWallCollisionWithEnemy(char** lvl, float enemy_x, float enemy_y, const int cell_size = 64) {

		return !(lvl[(int)(enemy_y) / cell_size][(int)(enemy_x) / cell_size] == 's');
	}

	bool PlayerEnemyCollision(Player& player, float enemyWidth, float enemyHeight)
	{
		return (player.getx() + player.getPwidth() > hitBox_x && player.getx() < hitBox_x + (enemyWidth - 2 * hit_box_factor_x) && player.gety() + player.getPheight() > hitBox_y && player.gety() < hitBox_y + (enemyHeight - 2 * hit_box_factor_y));
	}

	virtual void update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver) = 0;
	virtual void drawExtra(RenderWindow& window, float offset_x) {}
	virtual ~Enemy() {}
	/*
	void drawHitBox(RenderWindow& window, float offset_x) 
	{
		hitBoxShape.setPosition(hitBox_x - offset_x, hitBox_y);
		window.draw(hitBoxShape);
	}
	*/
	void updateHitbox() 
	{
		hitBox_x = x + hit_box_factor_x;
		hitBox_y = y + hit_box_factor_y;

		//float w = enemyWidth - 2 * hit_box_factor_x;
		//float h = enemyHeight - 2 * hit_box_factor_y;
		//hitBoxShape.setSize(FloatRect(0, 0, w, h).getSize());  
		//hitBoxShape.setPosition(hitBox_x, hitBox_y);
	}

	/*
	~Enemy() {
		if (deathTexture) {
			delete deathTexture;
			deathTexture = nullptr;
		}
	}
	*/

};


void Enemy::loadDeathAnimation(const string& filepath, int frameWidth, int frameHeight, float scaleX, float scaleY)
{

	Texture* deathTex = new Texture();
	deathTex->loadFromFile(filepath);  
	states[totalAnimations - 1] = new Animation(40);  

	for (int i = 0; i < 40; ++i) {
		int count = i % 4;
		states[totalAnimations - 1]->getSprites()[i].setTexture(*deathTex);
		states[totalAnimations - 1]->getSprites()[i].setTextureRect(IntRect(count * frameWidth, 0, frameWidth, frameHeight));
		states[totalAnimations - 1]->getSprites()[i].setScale(scaleX, scaleY);
	}

}

bool Enemy::handleDeathAnimation() 
{

	if (!Alive && isDying)
	{
		cout << "in deathanimation : \n";
		indexAnimation = totalAnimations - 1;

		if (deathFrameClock.getElapsedTime().asMilliseconds() >= 50) 
		{
			states[indexAnimation]->RunAnimation();
			deathFrameClock.restart();
		}

		sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];

		if (deathClock.getElapsedTime().asMilliseconds() >= 200) 
		{
			deathFinished = true;
		}
		return true; 
	}
	return false;  
}
