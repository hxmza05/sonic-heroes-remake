#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class Eggstinger : public Enemy {

private:

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

    float spikeHeightShown;    
    float maxSpikeHeight;      
    float spikeGrowSpeed; 
    float spikeOffsetY;



    Clock spikeHoldClock;
    float spikeHoldDuration; 
    bool spikeHold;




public:

	Eggstinger() : stingerHeight(98), stingerWidth(120){

		this->hp = 15;
		this->speed = 3.0;
		Alive = true;
        right = false;
		this->x = 0;
		this->y = 0;


		hoverHeight = 2 * 64;
		targetY = 8 * 64/* - 97.6f + 5.f*/;
        targetX = 0;
		targetSpeed = 4.0f;
		raiseSpeed = 2.5f;
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



        stingerspikeTexture.loadFromFile("Data/spike.png");
        stingerspikeSprite.setTexture(stingerspikeTexture);
        sprite.setTextureRect(IntRect(0, 0, 12.f, 64.f));
        stingerspikeSprite.setScale(1.5f, -0.5f);



		texture.loadFromFile("Sprites/eggstinger.png");
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, 150, 122));
		sprite.setScale(0.8f, 0.8f);

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



};


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

    if (!Alive) {
        return;
    }

    if (!isDiving && !isRising && !isTrackingBeforeDive && diveClock.getElapsedTime().asSeconds() >= 10.0f)
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

    sprite.setPosition(x, y);
}


