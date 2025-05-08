#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
using namespace sf;
class HUD
{
	int score;
	int ringsCollected;
	int lives;
	Clock timer;
	float levelTime;

	Texture hudTexture;
	Font scoreFont;
	Text label;
	Sprite hudSprite;


	int prevScore;
	Clock scoreScaleClock;
	float scoreTextScale;




public:
	HUD()
	{
		score = 0;
		ringsCollected = 0;
		lives = 100;
		lives = 5;
		timer.restart();
		levelTime = 0.f;

		hudTexture.loadFromFile("Data/hud.png");
		scoreFont.loadFromFile("Fonts/scoreFont.ttf");

		label.setFont(scoreFont);
		label.setCharacterSize(42);
		label.setFillColor(Color::Red);

		hudSprite.setTexture(hudTexture);
		hudSprite.setColor(Color::Red);
		hudSprite.setScale(2.5f, 2.5f);

		prevScore = 0;
		scoreScaleClock.restart();
		scoreTextScale = 1.f;

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

	void updateTime() {
		levelTime = timer.getElapsedTime().asSeconds();
	}

	void resetTimer() {
		timer.restart();
		levelTime = 0.f;
	}

	void draw(RenderWindow& window);

};



void HUD::draw(RenderWindow& window)
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
}