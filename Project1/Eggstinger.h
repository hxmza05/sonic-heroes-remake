﻿#pragma once
#include <iostream>
#include "Player.h"
#include "HUD.h"
#include "Audio.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Eggstinger : public Enemy {

private:
    sf::RectangleShape hpBack;  
    sf::RectangleShape hpFill;   
    int maxHP;
    
	float hoverHeight;
	float targetY;
    float targetX;
	float targetSpeed;
	float raiseSpeed;
	float rangeStartX;
	float rangeEndX;

	bool isDiving;
	bool isRising;
    bool right;
	bool hasLiftedBlock;
    bool isTrackingBeforeDive;
	int targetTileJ;
	Clock diveClock;

    const float stingerHeight;
    const float stingerWidth;

    Texture stingerspikeTexture;
    Sprite stingerspikeSprite;
    Texture stingerTexture;

    float spikeHeightShown;    
    float maxSpikeHeight;      
    float spikeGrowSpeed; 
    float spikeOffsetY;

    Clock spikeHoldClock;
    float spikeHoldDuration; 
    bool spikeHold;
    bool speedIncreased;

    Clock animationClock;

    Text finalFormText;
    Font font;
public:

	Eggstinger() : stingerHeight(98), stingerWidth(120) {
        speedIncreased = 0;
		isDying = false;
		this->hp = 10;
        this->speed = 4.0;
		Alive = true;
        right = false;
		this->x = 0;
		this->y = 0;
        totalAnimations = 2; 
        indexAnimation = 0;
        animationClock.restart();

		hoverHeight = 2 * 64;
		targetY = 8 * 64/* - 97.6f + 5.f*/;
        targetX = 0;
		targetSpeed = 6.0f;
		raiseSpeed = 4;
		rangeStartX = 3 * 64;
		rangeEndX = 12 * 64;

		isDiving = false;
		isRising = false;
		hasLiftedBlock = false;
        isTrackingBeforeDive = false;
		targetTileJ = -1;
		diveClock.restart();

        spikeHeightShown = 0;     
        maxSpikeHeight = 64.f;      

        spikeGrowSpeed = 2.f;     
        spikeOffsetY = 0;
        spikeHoldClock.restart();
        spikeHoldDuration = 0.2f;
        spikeHold = false;

        enemyHeight = stingerHeight;
        enemyWidth = stingerWidth;
        hit_box_factor_x = 8.0;
        hit_box_factor_y = 8.0;
        hitBox_x = x + hit_box_factor_x;
        hitBox_y = y + hit_box_factor_y;

        stingerspikeTexture.loadFromFile("Data/spike.png");
        stingerspikeSprite.setTexture(stingerspikeTexture);
        sprite.setTextureRect(IntRect(0, 0, 12.f, 64.f));
        stingerspikeSprite.setScale(1.5f, -0.5f);


        states = new Animation * [totalAnimations];
        states[0] = new Animation(6); 
        stingerTexture.loadFromFile("Sprites/stinger.png");
        isDying = false;

        for (int i = 0, width = 0; i < 6; i++, width += 426 / 6) 
        {
            states[0]->getSprites()[i].setTexture(stingerTexture);
            states[0]->getSprites()[i].setTextureRect(IntRect(width, 0, 71, 58));
            states[0]->getSprites()[i].setScale(120.0f / 71.0f, 97.6f / 58.0f);
        }



        loadDeathAnimation("Sprites/stingerdeath.png", 41, 42, 3.f, 3.f);
        deathFinished = false;
        maxHP = hp;                                // store initial (max) health
        float barW = 140.f;                        // width of outer bar (pixels)
        float barH = 8.f;                          // height of bar
        hpBack.setSize({ barW, barH });
        hpBack.setFillColor(sf::Color::Black);
        hpBack.setOrigin(barW / 2.f, barH / 2.f);  // centre‑origin

        hpFill.setSize({ barW, barH });
        hpFill.setFillColor(sf::Color::Red);
        hpFill.setOrigin(barW / 2.f, barH / 2.f);
        finalFormText.setString("EggStinger Has Unleashed His Final Fury !!!");
        finalFormText.setScale(2, 2);
        font.loadFromFile("Fonts/scoreFont.ttf");
        finalFormText.setFont(font);
        finalFormText.setOutlineColor(sf::Color::Black);
        finalFormText.setOutlineThickness(3);
        finalFormText.setFillColor(sf::Color::Yellow);
        finalFormText.setPosition(400, 10);
        finalFormText.setCharacterSize(18);
	}


    float getSpikeX() const {
        return x + stingerWidth / 2.f - (18.f * 1.5f) / 2.f - 5.f;
    }

    float getSpikeY() const {
        return y + stingerHeight + spikeOffsetY - 5.f;
    }

    float getSpikeHeightShown() const {
        return spikeHeightShown;
    }

    float getStingerWidth() const {
        return stingerWidth;
    }

    float getStingerHeight() const {
        return stingerHeight;
    }

    void movement(float player_x, float player_y, float player_width, char** lvl, int cell_size);
    void drawSpike(RenderWindow& window, float offset_x);
    bool playerSpikeCollision(float playerX, float playerY, float playerW, float playerH);
    bool PlayerStingerCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight);
    void update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver) override;
    void drawExtra(RenderWindow& window, float offset_x) override;


};



void Eggstinger::update(char** lvl, Player& player, int cell_size, bool& hasKnockedBack, float& tempVelocityY, bool& onGround, int indexAnimation, HUD& hud, bool& gameOver)
{

    if (handleBossDeathAnimation())
        return;

    //cout << "Eggstinger update running!" << endl;
    if (hp == 3 && !speedIncreased)
    {
        speed *= 2.5;
        raiseSpeed *= 2.5;
        spikeGrowSpeed *= 2.5;
        targetSpeed *= 2.5;
        hpFill.setFillColor(sf::Color::Yellow);
        speedIncreased = true;
    }
    movement(player.getx(), player.gety(), player.getPwidth(), lvl, cell_size);

    if (!hasKnockedBack && playerSpikeCollision(player.getx(), player.gety(), player.getPwidth(), player.getPheight()))
    {
        hud.getLives()--;

        if (audio) {
            audio->playSound(audio->getHurt());
        }

        hasKnockedBack = true;
        tempVelocityY = -4;

        // Player damage animation 
        if (hud.getLives() <= 0)
            gameOver = true;

        return; 
    }

    if (!hasKnockedBack && PlayerEnemyCollision(player, getStingerWidth(), getStingerHeight()))
    {
        if (indexAnimation == UPR || indexAnimation == UPL)
        {
            hp--;

            if (hp == 0) {
                setAlive(false);
                if (audio) {
                    audio->playSound(audio->getBossDestroy());
                }
                isDying = true;
                deathClock.restart();
                deathFrameClock.restart();
            }
            else {
                if (hp > 0 && audio) {
                    audio->playSound(audio->getBossHit());
                }
            }

            hasKnockedBack = true;
            tempVelocityY = -2;

            //cout << "Stinger hp: " << hp <<endl;
        }

        else
        {
            hud.getLives()--;

            if (audio) {
                audio->playSound(audio->getHurt());
            }

            hasKnockedBack = true;
            tempVelocityY = -7;

            // Player damage animation 

            if (hud.getLives() <= 0)
                gameOver = true;
        }
    }
}


void Eggstinger::drawExtra(sf::RenderWindow& window, float offset_x)
{
    drawSpike(window, offset_x);

    float barX = x - offset_x + 50;                 // left edge aligns with sprite’s x
    float barY = y - 18.f;                     // 18 px above boss

    hpBack.setPosition(barX, barY);
    hpFill.setPosition(barX, barY);

    float ratio = static_cast<float>(hp) / static_cast<float>(maxHP);
    hpFill.setSize({ 140.f * ratio, hpFill.getSize().y });  // shrink only width
    if(alive())
    {
        window.draw(hpBack);
        window.draw(hpFill);
        if (hp <= 3)
        {
            window.draw(finalFormText);
        }
    }
}


bool Eggstinger::PlayerStingerCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
{
    return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
}

bool Eggstinger::playerSpikeCollision(float playerX, float playerY, float playerW, float playerH)
{
    if (getSpikeHeightShown() < 8.f)
    {
        return false;
    }

    return (playerX + playerW > getSpikeX() && (playerX < getSpikeX() + 18.0f)) && ((playerY + playerH > getSpikeY() - getSpikeHeightShown()) && (playerY < getSpikeY()));
}


void Eggstinger::drawSpike(RenderWindow& window, float offset_x)
{
    if (spikeHeightShown > 0)
    {
        float spikeWidth = 12.f;
        float spikeX = x + stingerWidth / 2.f - spikeWidth / 2.f;
        float spikeY = y + stingerHeight + spikeHeightShown * 0.5f;

        stingerspikeSprite.setTextureRect(IntRect(0, 64 - (int)spikeHeightShown, (int)spikeWidth, (int)spikeHeightShown));
        stingerspikeSprite.setPosition(spikeX - offset_x - 7.f, spikeY - 5.f);

        window.draw(stingerspikeSprite);

    }
}

void Eggstinger::movement(float player_x, float player_y, float player_width, char** lvl, int cell_size)
{
    const float platformY = 8 * cell_size;
    const int platformRow = 8;

    if (!isDiving && !isRising && !isTrackingBeforeDive && diveClock.getElapsedTime().asSeconds() >= 5.0f)
    {
        diveClock.restart();
        isTrackingBeforeDive = true;

        targetTileJ = (int)((player_x + player_width / 2) / cell_size);
        targetX = targetTileJ * cell_size + cell_size / 2 - stingerWidth / 2;

        //cout << "stinger dive tracking initiated. Target column: " << targetTileJ << ", x = " << targetX << endl;
    }

    if (isTrackingBeforeDive)
    {
        if (abs(x - targetX) <= speed)
        {
            x = targetX;
            isTrackingBeforeDive = false;
            isDiving = true;
            //cout << "stnger Aligned. dive at x = " << x << endl;
        }
        else if (x < targetX)
        {
            x += speed;
        }
        else
        {
            x -= speed;
        }

        sprite.setPosition(x, y);
        spikeHeightShown = 0;

        return;
    }

    if (isDiving)
    {
        y += targetSpeed;

        //cout << "stinger Diving at y = " << y << endl;

        if (spikeHeightShown < maxSpikeHeight) {
            spikeHeightShown += spikeGrowSpeed;
        }

        if (y + stingerHeight >= platformY)
        {
            y = platformY - stingerHeight;
            isDiving = false;
            isRising = true;
            hasLiftedBlock = false;
            spikeHold = false;             
            spikeHoldClock.restart();
            //cout << "00 Reached platform ----- Begin rising" << endl;
        }
    }

    else if (isRising)
    {
        y -= raiseSpeed;
        //cout << "stinger rising at y = " << y << endl;

        if (!spikeHold) 
        {
            spikeHold = true;
            spikeHoldClock.restart();
        }

        else if (spikeHoldClock.getElapsedTime().asSeconds() >= spikeHoldDuration) 
        {
            if (spikeHeightShown > 0) 
            {
                spikeHeightShown -= spikeGrowSpeed;
            }
        }

        if (!hasLiftedBlock && y + stingerHeight >= platformY - cell_size)
        {
            if (lvl[platformRow][targetTileJ] != 's')
            {
                lvl[platformRow][targetTileJ] = 's';
                hasLiftedBlock = true;
                //cout << "stinger removed wall at " << platformRow << ", " << targetTileJ << endl;
            }
        }

        if (y <= hoverHeight)
        {
            y = hoverHeight;
            isRising = false;
            //cout << "stinger back to hovering" << endl;
        }
    }

    else
    {

        spikeHeightShown = 0;

        if (right)
        {
            x += speed;

            if (x >= rangeEndX)
            {
                x = rangeEndX;
                right = false;
                //cout << "stinger right bound" << endl;
            }
        }

        else
        {
            x -= speed;

            if (x <= rangeStartX)
            {
                x = rangeStartX;
                right = true;
                //cout << "stinger left bound" << endl;
            }
        }
    }

    if (isDiving || isRising || hp <=3 )
    {
        sprite = states[indexAnimation]->getSprites()[5];
    }

    else {

        if (animationClock.getElapsedTime().asSeconds() >= 0.2f) {
            states[indexAnimation]->RunAnimation();
            animationClock.restart();
        }

        sprite = states[indexAnimation]->getSprites()[states[indexAnimation]->getIndex()];
    }


    if (right) 
    {
        sprite.setScale(-(120.0f / 71.0f), 97.6f / 58.0f);
        sprite.setOrigin(71.f, 0);
    }
    else 
    {
        sprite.setScale(120.0f / 71.0f, 97.6f / 58.0f);
        sprite.setOrigin(0, 0);
    }

    sprite.setPosition(x, y);

    updateHitbox();

}

