#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<iostream>
using namespace std;
using namespace sf;
class HUD
{
	Texture sonicHud;
	Texture tailedHud;
	Texture knucklesHud;
	int playIdx;
	Sprite* hudSprites;
	int selectedPlayerScale;
	int unselectedPlayerScale;

	int score;
	int ringsCollected;
	int lives;
	Clock timer;
	float levelTime;

	Texture hudTexture;
	Font scoreFont;
	Text label;
	Sprite hudSprite;
	float pos1;
	float pos2;
	float pos3;


	Text livesText;
	string livesString;


	Clock makeInvincible;
	bool invincibleRestarted;
	int prevScore;
	Clock scoreScaleClock;
	float scoreTextScale;
public:
	HUD()
	{
		playIdx = 0;
		invincibleRestarted = false;;

		score = 0;
		ringsCollected = 0;

		//lives = /*100*/;
		lives = 50;
		timer.restart();
		levelTime = 0.f;

		hudTexture.loadFromFile("Data/hud.png");
		scoreFont.loadFromFile("Fonts/scoreFont.ttf");
		livesText.setFont(scoreFont);
		livesText.setFillColor(Color::Red);
		livesText.setCharacterSize(42);


		label.setFont(scoreFont);
		label.setCharacterSize(42);
		label.setFillColor(Color::Red);

		hudSprite.setTexture(hudTexture);
		hudSprite.setColor(Color::Red);
		hudSprite.setScale(2.5f, 2.5f);

		prevScore = 0;
		scoreScaleClock.restart();
		scoreTextScale = 1.f;

		selectedPlayerScale = 4.35;
		unselectedPlayerScale = 3.5;
		sonicHud.loadFromFile("Data/sonicHud.png");
		tailedHud.loadFromFile("Data/tailedHud.png");
		knucklesHud.loadFromFile("Data/knucklesHud.png");
		hudSprites = new Sprite[3];
		hudSprites[0].setTexture(sonicHud);
		hudSprites[1].setTexture(tailedHud);
		hudSprites[2].setTexture(knucklesHud);
		//hudSprites[2].seto;


		 pos1 = 45;
		 pos2 = 140;
		 pos3 = 220;
		 playIdx = 0;


		 livesString = ' X ';
	}
	Clock& getInvincibleClk()
	{
		return makeInvincible;
	}
	void resetInvincibleClock()
	{
		makeInvincible.restart();
	}
	int&getScore()
	{
		return score;
	}
	int& getRings()
	{
		return ringsCollected;
	}
	int& getLives()
	{
		return lives;
	}
	void setLives(int n)
	{
		lives = n;
	}
	void updateTime() {
		levelTime = timer.getElapsedTime().asSeconds();
	}
	void resetTimer() {
		timer.restart();
		levelTime = 0.f;
	}
	void draw(RenderWindow& window,int playerIndex);
};
void HUD::draw(RenderWindow& window,int playerIndex)
{
	updateTime();

	float iconScale = 2.5f;
	hudSprite.setScale(iconScale, iconScale);

	float baseX = 25.f;
	float baseY = 84.f;
	float lineSpacing = 45.f;

	float colonOffsetX = 100.f;
	float colonOffsetY = 16.f;

	float valueOffsetX = 125.f;
	float valueOffsetY = 16.f;

	for (int i = 0; i < 3; i++) 
	{
		int iconY = (i == 0) ? 0 : (i == 1) ? 11 : 21;
		int iconH = (i == 0) ? 10 : 11;

		hudSprite.setTextureRect(sf::IntRect(0, iconY, 38, iconH));
		hudSprite.setPosition(baseX, baseY + i * lineSpacing);
		window.draw(hudSprite);

		label.setString(":");
		label.setScale(1.f, 1.f);
		label.setPosition(baseX + colonOffsetX, baseY + i * lineSpacing - colonOffsetY);
		window.draw(label);

		std::string valueText = (i == 0) ? std::to_string(score) :(i == 1) ? std::to_string((int)levelTime) : std::to_string(ringsCollected);

		label.setString(valueText);
		label.setPosition(baseX + valueOffsetX, baseY + i * lineSpacing - valueOffsetY);
		window.draw(label);

		
	}
	if (playerIndex != 3)
	{

		Sprite temp = hudSprites[playerIndex];
		temp.setPosition(baseX, baseY + 130);
		temp.setScale(2.5, 2.5);
		livesString = " X " + to_string(lives);
		livesText.setString(livesString);
		livesText.setPosition(baseX + 50, baseY + 120);

		//livesText.setScale(2, 2);
		window.draw(temp);
		window.draw(livesText);
	}
	if (playerIndex == 0)
	{
		hudSprites[0].setPosition(pos1, 800);
		hudSprites[1].setPosition(pos2, 800);
		hudSprites[2].setPosition(pos3, 800);
	}
	else if (playerIndex == 1)
	{
		hudSprites[0].setPosition(pos3, 800);
		hudSprites[1].setPosition(pos1, 800);
		hudSprites[2].setPosition(pos2, 800);
	}
	else if (playerIndex == 2)
	{
		hudSprites[0].setPosition(pos2, 800);
		hudSprites[1].setPosition(pos3, 800);
		hudSprites[2].setPosition(pos1, 800);
	}
	for (int i = 0;i < 3;i++)
	{
		hudSprites[i].setScale(unselectedPlayerScale, unselectedPlayerScale);
		if (playerIndex != 3)
			hudSprites[playerIndex].setScale(selectedPlayerScale, selectedPlayerScale);
		window.draw(hudSprites[i]);
	}
	
}
