#pragma once
#include<iostream>
#include"Enemy.h"
#include"Collectibles.h"
#include"MoveablePlatform.h"
#include"FallingPlatform.h"
#include"HUD.h"
#include"Extralives.h"
#include"SpecialBoost.h"
#include"FallingPlatform.h"
#include"Audio.h"
using namespace std;
#include"Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Level
{
protected:
	
	double levelTimer;
	int fallingCount;
	FallingPlatform** falling;
	float levelEnd;
	float levelEndY;
	//Collectible*** collectibles;
	//Obstacle** obstacles;

	const int endMark;
	Texture backgorund;
	Sprite bgSprite;
	char** lvl;

	Ring** rings;
	Texture* ringTex;
	Texture* ringEffect;
	int ringCount;

	ExtraLife** lives;
	Texture* lifeTex;
	int livesCount;
	
	SpecialBoost** boosts;
	Texture* boostTex;
	int boostCount;


	 int height;
	 int width;
	 float friction;
	//Enemy*** enemies;

	 int TotalEnemyCount;


	 Enemy** enemies;
	 int enemyCount;

	 Sprite* walls;
	 Texture wallText1;
	 Texture wallText2;
	 Texture wallText3;
	 Texture wallText4;

	 Texture backGround;
	 Sprite backGroundSprite;
	 float scX;
	 float scY;

	 Audio* audio;


public:
	Level(char** level = nullptr) :endMark(0)
	{
		wallText4.loadFromFile("Data/Spike.png");

	}
	virtual void designlvl(const char* filename) = 0;
	
	void drawLevel(RenderWindow& window, const int height, const int width, char** lvl, Sprite walls[], const int cell_size, int offset_x)
	{
		for (int i = 0; i < height; i += 1)
		{
			for (int j = 0; j < width; j += 1)
			{
				if (lvl[i][j] == 's')
					continue;
				else if (lvl[i][j] == 'w')
				{
					walls[0].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[0]);
				}
				else if (lvl[i][j] == 'q')
				{
					walls[1].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[1]);
				}
				else if (lvl[i][j] == 'e')
				{
					walls[2].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[2]);
				}
				else if (lvl[i][j] == 'p')
				{
					walls[3].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[3]);
				}
				else if (lvl[i][j] == 'i') 
				{
					walls[3].setScale(1.f, -1.f); 
					walls[3].setPosition(j * cell_size - offset_x, (i + 1) * cell_size);
					window.draw(walls[3]);
					walls[3].setScale(1.f, 1.f); 
				}
			}
		}
	}
	char** getLvl()
	{
		return lvl;
	}
	float getLevelEndY()
	{
		return levelEndY;

		
	}
	int getHeight()
	{
		return height;
	}
	int getWidth()
	{
		return width;
	}
	virtual MoveablePlatform* getMoveable()
	{
		return nullptr;
	}
	virtual Eggstinger* getStinger() = 0;
	float& getFriction()
	{
		return friction;
	}
	double getTimer()
	{
		return levelTimer;
	}
	virtual void setAudio(Audio* a) {
		audio = a;

		for (int i = 0; i < enemyCount; i++) {
			if (enemies[i]) {
				enemies[i]->setAudio(audio);
			}
		}
	}
	
	 FallingPlatform** getFalling()
	{
		return falling;
	}
	virtual void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player, HUD& hud, bool&) = 0;
	virtual void drawEnemies(RenderWindow& window, float offset_x) = 0;

	bool hasLevelEnded(float x)
	{
		if (x >= levelEnd)
			return true;
		return false;
	}


	void setRingTextures(Texture* r, Texture* re) {
		ringTex = r;
		ringEffect = re;
	}
	int getTotalEnemyCount()
	{
		return TotalEnemyCount;
	}
	Enemy** getEnemies()
	{
		return enemies;
	}

	void setLifeTexture(Texture* tex) { 
		lifeTex = tex; 
	}

	void setBoostTexture(Texture* tex) { 
		boostTex = tex; 
	}

	int getRingCount() const {
		return ringCount;
	}

	int getLivesCount() const {
		return livesCount;
	}

	int getBoostCount() const {
		return boostCount;
	}

	Ring** getRings() {
		return rings; 
	}

	ExtraLife** getLives() {
		return lives;
	}

	SpecialBoost** getBoosts() { 
		return boosts; 
	}

	void placeRingsFromMap(Texture* ringTex, Texture* ringEffect);
	void placeExtraLivesFromMap();
	void placeBoostsFromMap();
	void loadAndPlaceCollectibles();
	void display_level(RenderWindow& window, const int cell_size, int offset_x)
	{
		/*cout << "\n\nHeight = " << height;
		cout << "\nWidth = " << width << endl;*/
		for (int i = 0; i < height; i += 1)
		{
			for (int j = 0; j < width; j += 1)
			{
				if (lvl[i][j] == 's')
					continue;
				else if (lvl[i][j] == 'w')
				{
					walls[0].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[0]);
				}
				else if (lvl[i][j] == 'q')
				{
					//cout << "i*c"
					walls[1].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[1]);
				}
				else if (lvl[i][j] == 'e')
				{
					walls[2].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[2]);
				}
				else if (lvl[i][j] == 'p')
				{
					walls[3].setPosition(j * cell_size - offset_x, i * cell_size);
					window.draw(walls[3]);
				}
				else if (lvl[i][j] == 'i')
				{
					walls[3].setScale(1.f, -1.f);
					walls[3].setPosition(j * cell_size - offset_x, (i + 1) * cell_size);
					window.draw(walls[3]);
					walls[3].setScale(1.f, 1.f);
				}
			}
		}
	}
	void draw_bg(RenderWindow& window)
	{
		backGroundSprite.setPosition(0, 0);
		window.draw(backGroundSprite);
	}
	int getFallingCount()
	{
		return fallingCount;
	}

	/*
	
	~Level() {

		if (falling) {
			for (int i = 0; i < fallingCount; ++i) {
				delete falling[i];
			}
			delete[] falling;
		}

		if (rings) {
			for (int i = 0; i < ringCount; ++i) {
				delete rings[i];
			}
			delete[] rings;
		}

		if (lives) {
			for (int i = 0; i < livesCount; ++i) {
				delete lives[i];
			}
			delete[] lives;
		}

		if (boosts) {
			for (int i = 0; i < boostCount; ++i) {
				delete boosts[i];
			}
			delete[] boosts;
		}

		if (enemies) {
			for (int i = 0; i < enemyCount; ++i) {
				delete enemies[i];
			}
			delete[] enemies;
		}

		if (lvl) {
			for (int i = 0; i < height; ++i) {
				delete[] lvl[i];
			}
			delete[] lvl;
		}

		delete ringTex;
		delete ringEffect;
		delete lifeTex;
		delete boostTex;
		delete audio;
	}

	*/
	int getLevelEnd()

	{
		return levelEnd;
	}
};


void Level::loadAndPlaceCollectibles() {

	ringTex = new Texture();
	ringEffect = new Texture();
	lifeTex = new Texture();
	boostTex = new Texture();

	ringTex->loadFromFile("Sprites/rings.png");
	ringEffect->loadFromFile("Sprites/after_ring.png");
	lifeTex->loadFromFile("Data/life.png");
	boostTex->loadFromFile("Sprites/boost.png");

	placeRingsFromMap(ringTex, ringEffect);
	placeExtraLivesFromMap();
	placeBoostsFromMap();

}


void Level::placeRingsFromMap(Texture* ringTex, Texture* ringEffect) {

	ringCount = 0;

	for (int i = 0; i < height; ++i) {

		for (int j = 0; j < width; ++j) {

			if (lvl[i][j] == 'r') {
				ringCount++;
			}
		}
	}

	rings = new Ring * [ringCount];

	int index = 0;

	for (int i = 0; i < height; ++i) {

		for (int j = 0; j < width; ++j) {

			if (lvl[i][j] == 'r') {
				rings[index] = new Ring(j, i, ringTex, ringEffect);
				rings[index]->setAudio(audio);
				index++;
			}
		}
	}
}


void Level::placeExtraLivesFromMap() {

	livesCount = 0;

	for (int i = 0; i < height; ++i) {

		for (int j = 0; j < width; ++j) {

			if (lvl[i][j] == 'l') {
				livesCount++;
			}
		}
	}

	lives = new ExtraLife * [livesCount];

	int index = 0;

	for (int i = 0; i < height; ++i) {

		for (int j = 0; j < width; ++j) {

			if (lvl[i][j] == 'l') {
				lives[index] = new ExtraLife(j, i, lifeTex);
				lives[index]->setAudio(audio);
				index++;
			}
		}
	}
}

void Level::placeBoostsFromMap() {

	boostCount = 0;

	for (int i = 0; i < height; ++i) {

		for (int j = 0; j < width; ++j) {

			if (lvl[i][j] == 'j') {
				boostCount++;
			}
		}
	}

	boosts = new SpecialBoost * [boostCount];

	int index = 0;

	for (int i = 0; i < height; ++i) {

		for (int j = 0; j < width; ++j) {

			if (lvl[i][j] == 'j') {
				boosts[index] = new SpecialBoost(j, i, boostTex);
				boosts[index]->setAudio(audio);
				index++;
			}
		}
	}
}


