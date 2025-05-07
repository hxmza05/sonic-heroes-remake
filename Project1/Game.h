#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Team.h"
#include "Level.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "BossLevel.h"
#include "Rings.h"
#include "GlobalFunctions.h"
#include"HUD.h"
// #include"FallingPlatform.h"
class Game
{
    //some score and other stuff
    HUD hud;
    bool gameOver;



    int spaceCount;
    int buffer_start;
    int buffer_end;
    Texture buffer;
    Sprite bufferSpriteStart;
    Sprite bufferSpriteEnd;
    float offset_x;
    float offset_y;
    bool leftRight;
    int hit_box_factor_x;
    int hit_box_factor_y;

    //   int crabCount;
    //   int crabIndex;
    //   int crab_start;
    //   int crab_end;
    //   Crabmeat** crabs;

    //   int beeCount;
    //   int beeIndex;
    //   int bee_start;
    //   int bee_end;
    //   Beebot** beebots;

    //   int motobugCount;
    //   int motobugIndex;
    //   int motobug_start;
    //   int motobug_end;
    //   Motobug** motobugs;

    //   int batCount;
    // int batIndex;

    // Batbrain** batbrains;

    int stingerCount;
    bool eggStingerSpawn;
    Eggstinger* stinger;

    Texture backGround;
    Sprite backGroundSprite;

    Texture wallTex1;
    Sprite wallSprite1;

    Texture wall2;
    Sprite wall2Sprite;

    Texture wall3;
    Sprite wall3Sprite;

    Texture spikesTexture;
    Sprite spikes;

    Sprite* walls;

    Collectibles*** collectibles;

    Texture rings;

    Texture ring_effect;

    int ringsCollected;

    Team team;
    Level** level;
    int levelIndex;
    int cell_size;
    Clock Akey;

public:
    Game()
    {
        gameOver = false;
        cell_size = 64;
        // team = Team();
        // level = new * Level();
        level = new Level * [3];
        level[0] = new Level1();
        level[1] = new Level2();
        level[2] = new Level3();
        level[3] = new BossLevel();
        levelIndex = 0;
        buffer.loadFromFile("Data/bufferSprite.jpg");
        bufferSpriteStart.setTexture(buffer);
        bufferSpriteEnd.setTexture(buffer);
        buffer_start = 4 * 64;
        buffer_end = 13 * 64;
        offset_x = 0;
        offset_y = 0;
        leftRight = false;
        hit_box_factor_x = 8 * 2.5;
        hit_box_factor_y = 5 * 2.5;

        // crabCount = 5;
        ////////////////////////////////////
        /////////////////Bosss//////////////
        ////////////////////////////////////

        stingerCount = 1;
        eggStingerSpawn = false;
        stinger = new Eggstinger();

    


           ///////////////////////////////////
           //////////////batbrain
           ////////////////////////////////////

          /*

           batCount = 4;
           batIndex = 0;
           batbrains = new Batbrain * [batCount];

           for (int i = 0; i < batCount; ++i) {
               batbrains[i] = new Batbrain();
           }

           batbrains[0]->getBatbrainCoordinates(batbrains,level[levelIndex]->getLvl(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), batIndex, batCount, cell_size);

          */

        backGround.loadFromFile("Data/bg1.png");
        backGroundSprite.setTexture(backGround);

        wallTex1.loadFromFile("Data/brick1.png");
        wallSprite1.setTexture(wallTex1);

        wall2.loadFromFile("Data/brick2.png");
        wall2Sprite.setTexture(wall2);

        wall3.loadFromFile("Data/brick3.png");
        wall3Sprite.setTexture(wall3);

        spikesTexture.loadFromFile("Data/spike.png");
        spikes.setTexture(spikesTexture);

        walls = new Sprite[4];
        walls[0] = wallSprite1;
        walls[1] = wall2Sprite;
        walls[2] = wall3Sprite;
        walls[3] = spikes;

        spaceCount = 0;
        // levelIndex = 0;
        int height = level[levelIndex]->getHeight();
        int width = level[levelIndex]->getWidth();
        collectibles = new Collectibles * *[level[levelIndex]->getHeight()];

        for (int i = 0; i < height; i++)
        {

            collectibles[i] = new Collectibles * [width];

            for (int j = 0; j < width; j++)
            {

                collectibles[i][j] = nullptr;
            }
        }
        rings.loadFromFile("Sprites/rings.png");
        ring_effect.loadFromFile("Sprites/after_ring.png");
        placeRingsFromMap(level[levelIndex]->getLvl(), collectibles, level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), &rings, &ring_effect);
        if (!collectibles)
        {
            // cout << "collecitbles didnt work null h constructor m";
        }
        // else cout << "collecitbles  worked null nai h constructor m";

        // placeRingsFromMap(lvl, collectibles, height, width, &rings, &ring_effect);

        ringsCollected = 0;
    }
    void setLevelIndex(int index)
    {
        levelIndex = index;
    }
    int getLevelIndex()
    {
        return levelIndex;
    }
    /*char getMapValues(int val);

    void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite* walls, const int cell_size, int off_x);
    void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord);
    void draw_bg(RenderWindow& window, Sprite&, int);
    void designlvl1(char** lvl, const char* filename, const int height, const int width);
    bool checkCollision(char**lvl, int x, int y);
    bool collisionCheckWithSpikes(char** lvl, int offset_y, int hit_box_factor_y, int hit_box_factor_x, int Pheight, int Pwidth, int x, int y, int cell_size, int velocityY);

    bool CollisionCheckWithCrabs(Crabmeat** crabs, int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight);

    bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float crab_x, float crab_y, const float crabWidth, const float crabHeight);

    bool CollisionCheckWithBeebots(Beebot** beebots, int& beeCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float beeWidth, const float beeHeight, bool onGround, bool);


    void placeRingsFromMap(char** lvl, Collectibles*** collectibles, int height, int width, Texture* rings, Texture* afterEffect);

    void updateAndDrawCollectibles(Collectibles*** collectibles, int height, int width, RenderWindow& window);


    */
    // void handleRingCollection(Collectibles*** collectibles, char** lvl, int height, int width, Player& player, int& ringsCollected, int cell_size);
    //
    //
    ///////
    ///////
    //////
    // #pragma once
    // #include"Game.h"
    // #include<iostream>
    // using namespace std;
    // using namespace sf;
    bool collisionCheckWithSpikes(char** lvl, int offset_y, int hit_box_factor_y, int hit_box_factor_x, int Pheight, int Pwidth, int player_x, int player_y, int cell_size, int velocityY)
    {
        offset_y = player_y;
        offset_y += velocityY;

        // cout<<"offsety = "<<offse
        /*std::cout << "player_x: " << player_x << ", player_y: " << player_y << ", offset_y: " << offset_y << ", velocityY: " << velocityY << std::endl;
        std::cout << "hit_box_factor_x: " << hit_box_factor_x << ", hit_box_factor_y: " << hit_box_factor_y << std::endl;
        std::cout << "Pwidth: " << Pwidth << ", Pheight: " << Pheight << ", cell_size: " << cell_size << std::endl;
        cout << "Row : " << (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
        cout << "--------Columnleftdown : " << ((int)(player_x + hit_box_factor_x) / cell_size);
        cout << "-----ColumnRightdown : " << (int)((player_x + hit_box_factor_x + Pwidth) / cell_size);
        cout << "-------ColumnMidDown : " << ((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size);
        cout << "\n\n\n";*/

        char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
        char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
        char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];

        char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
        char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
        char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];
        bool forLeft = topLeft != 'w' && topLeft != 'q' && topLeft != 'e';
        bool forMiddle = topMiddle != 'w' && topMiddle != 'q' && topMiddle != 'e';
        bool forRight = topRight != 'w' && topRight != 'q' && topRight != 'e';

        // cout << "Left : " << bottom_left_down << " ---- Mid : " << bottom_mid_down << " -------" << "Right : " << bottom_right_down << "----";

        return ((bottom_left_down == 'p' || bottom_mid_down == 'p' || bottom_right_down == 'p') && velocityY > 0 && (forLeft || forMiddle || forRight));
    }
    void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord)
    {
        bufferSprite.setPosition(buffer_coord, 500);
        window.draw(bufferSprite);
    }
    void draw_bg(RenderWindow& window, Sprite& bgSprite, int offset_x)
    {
        bgSprite.setPosition(0, 0);
        window.draw(bgSprite);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////Rings////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    void placeRingsFromMap(char** lvl, Collectibles*** collectibles, int height, int width, Texture* rings, Texture* afterEffect)
    {
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                if (lvl[i][j] == 'r')
                {
                    collectibles[i][j] = new Ring(j, i, rings, afterEffect);
                }
            }
        }
    }
    void updateAndDrawCollectibles(int height, int width, RenderWindow& window)
    { /*
         if (!collectibles)
         {
             cout << "null h bhaiiyya\n\n";
         }*/
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                // cout << "i = " << i << "---- j = " << j << endl;
                if (collectibles[i][j])
                {
                    collectibles[i][j]->update();
                    collectibles[i][j]->draw(window, offset_x);
                }
            }
        }
    }

    void handleRingCollection(Collectibles*** collectibles, char** lvl, int height, int width, Player& player, int& ringsCollected, int cell_size)
    {

        for (int i = 0; i < height; ++i)
        {

            for (int j = 0; j < width; ++j)
            {

                if (collectibles[i][j] && collectibles[i][j]->isActive())
                {

                    float ring_x = j * cell_size;
                    float ring_y = i * cell_size + 12;

                    int frameIndex = collectibles[i][j]->getIndex();
                    float rawWidths[4] = { 66, 56, 32, 53 };
                    float ringWidth = rawWidths[frameIndex] * 0.75f;
                    float ringHeight = 66 * 0.75f;

                    if (player.getx() + player.getPwidth() > ring_x && player.getx() < ring_x + ringWidth && player.gety() + player.getPheight() > ring_y && player.gety() < ring_y + ringHeight)
                    {

                        collectibles[i][j]->collect();
                        ringsCollected++;
                        lvl[i][j] = 's';
                    }
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////Rings////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite* walls, const int cell_size, int offset_x)
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
            }
        }
    }
    // void   designlvl1(char** lvl, const char* filename, const int height, const int width)
    //{
    //     ifstream in("lvl1.txt");
    //
    //     for (int i = 0; i < height; i++) {
    //
    //         for (int j = 0; j < width; j++) {
    //
    //             int wall;
    //             in >> wall;
    //             lvl[i][j] = getMapValues(wall);
    //         }
    //     }
    //     in.close();
    // }

    // bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
    //{
    //     return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
    // }

    // bool CollisionCheckWithCrabs(Crabmeat** crabs, int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight)
    //{

    //    for (int i = 0; i < crabCount; i++)
    //    {

    //        if (!crabs[i]->alive())
    //        {
    //            continue;
    //        }

    //        if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, crabs[i]->getX(), crabs[i]->getY(), crabWidth, crabHeight))
    //        {

    //            float bottom_of_Player = player_y + Pheight;
    //            float top_of_Crab = crabs[i]->getY();

    //            if (bottom_of_Player - 10 < top_of_Crab)
    //            {

    //                // crab ko marna hai ab becoz top collision, also add smoke effect and invincibilty
    //                //cout << " Top-hit:  " << i << endl;

    //                //cout << "PlyrX: " << player_x << "crab X: " << crabs[i]->getX() << endl;

    //                velocityY = -10.0f;
    //            }

    //            else
    //            {

    //                hasKnockedBack = true;
    //                tempVelocityY = -7;

    //                crabs[i]->setAnimation(3);
    //                crabs[i]->RunNewAnimation();
    //                crabs[i]->setAttack();
    //            }
    //            return true;
    //        }
    //    }

    //    return false;
    //}

    // bool CollisionCheckWithBeebots(Beebot** beebots, int& beeCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float beeWidth, const float beeHeight, bool onGround, bool spacePressed)
    //{

    //    for (int i = 0; i < beeCount; i++)
    //    {

    //        if (!beebots[i]->alive())
    //        {
    //            continue;
    //        }

    //        if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, beebots[i]->getX(), beebots[i]->getY(), beeWidth, beeHeight))
    //        {

    //            if (!(onGround == false && spacePressed == true))
    //            {
    //                hasKnockedBack = true;
    //                tempVelocityY = -7; // knockback upwards initially
    //                cout << "Player hit by Beebot --- thrown back" << endl;
    //            }

    //            return true;
    //        }
    //    }

    //    return false;
    //}

    ////
    //
    //
    //
    //
    //
    //
    //
    ///////////////////////////////
    //////////////////////////////
    /////////
    /////////////////////////////////
    /////////////////////////////////
    void play(RenderWindow& window)
    {
        if (team.getPlayer()[team.getPlayerIndex()][0].getOnGround())
        {
            team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = false;
            team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() = -7;
            team.getSpaceCount() = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        {
            if (checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() - 15, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2) && team.getPlayer()[team.getPlayerIndex()][0].getx() > 0)
            {
                team.getPlayer()[team.getPlayerIndex()][0].moveLeft();
                if (buffer_start > 4 * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() <= buffer_start)
                {
                    buffer_start = team.getPlayer()[team.getPlayerIndex()][0].getx();
                    buffer_end = buffer_start + 576;
                    offset_x += team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
                }
                leftRight = true;
            }
            else
            {
                if (!checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety()))
                {
                    team.getPlayer()[team.getPlayerIndex()][0].executePushingLeft();
                }
                if (team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() <= 0)
                    team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() = 15;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        {
            if (checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2))
            {
                team.getPlayer()[team.getPlayerIndex()][0].moveRight();
                if (buffer_end < 196 * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() >= buffer_end)
                {
                    buffer_end = team.getPlayer()[team.getPlayerIndex()][0].getx();
                    buffer_start = buffer_end - 576;
                    offset_x += team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
                }
                leftRight = true;
            }
            else
            {
                if (!checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety()))
                {
                    team.getPlayer()[team.getPlayerIndex()][0].executePushingRight();
                }
                if (team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() >= 0)
                    team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() = 15;
            }
        }
        else
            leftRight = false;
        if (!leftRight)
        {
            team.getPlayer()[team.getPlayerIndex()][0].getVelocityX() = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        {
            team.jump();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() && Akey.getElapsedTime().asMilliseconds() > 500)
        {
            team.switchLeader();
            Akey.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        {
            team.useSpecial(level[levelIndex]->getLvl());
        }
        if (team.getSpacePressed())
        {
            if (team.getPlayerIndex() != 1)
            {
                team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = UPR;
            }
            else if (team.getSpaceCount() < 10)
            {
                team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = UPR;
            }
            leftRight = false;
        }
        if (!team.getSpacePressed() && !leftRight)
        {
            team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = STILL;
        }
        if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = collisionCheckWithSpikes(level[levelIndex][0].getLvl(), offset_y, hit_box_factor_y, hit_box_factor_x, team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), 64, team.getPlayer()[team.getPlayerIndex()][0].getVelocityY());
        if (team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack()) /*|| team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedByProjectile()*/
        {
            team.getPlayer()[team.getPlayerIndex()][0].getx() -= 6;
            team.getPlayer()[team.getPlayerIndex()][0].gety() += team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY();
            team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() += team.getPlayer()[team.getPlayerIndex()][0].getTempGravity();
            if (team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() >= 0)
            {
                team.getPlayer()[team.getPlayerIndex()][0].playerVirtualGravity(level[levelIndex][0].getLvl(), offset_y, offset_x, 64, team.getSpacePressed());
            }
        }
        if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            team.getPlayer()[team.getPlayerIndex()][0].player_gravity(level[levelIndex][0].getLvl(), offset_y, offset_x, 64, team.getSpacePressed());
        team.storePath();
        team.autoMoveFollowers(level[levelIndex]->getLvl(), offset_x);
        if (level[levelIndex]->getMoveable()->move(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()]->getOnGround()))
        {
            if (team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() != STILL)
            {
                team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = STILL;
                // team.getPlayer()[team.getPlayerIndex()][0].getStates()[STILL]->RunAnimation();
            }
            // team.
        }
        draw_bg(window, backGroundSprite, offset_x);
        level[levelIndex]->getMoveable()->draw(window, offset_x);

        display_level(window, level[levelIndex][0].getHeight(), level[levelIndex][0].getWidth(), level[levelIndex][0].getLvl(), walls, 64, offset_x);
        for (int i = 0; i < 8; i++)
            level[levelIndex]->getFalling()[i]->draw(window, offset_x);

        updateAndDrawCollectibles(level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), window);
        handleRingCollection(collectibles, level[levelIndex][0].getLvl(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), team.getPlayer()[team.getPlayerIndex()][0], hud.getRings(), cell_size);
        team.draw(window, offset_x);
        /*

        if (!eggStingerSpawn)
        {
            stinger->setPosition(12 * cell_size, 2*cell_size, 0, 0);
            eggStingerSpawn = true;
        }


        if (stinger->alive())
        {

            stinger->movement(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), level[levelIndex]->getLvl(), cell_size);

            if (stinger->playerSpikeCollision(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight()))
            {
                team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = true;
                team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() = -7;
            }

            if (stinger->PlayerStingerCollision(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), stinger->getX(), stinger->getY(), stinger->getStingerWidth(), stinger->getStingerHeight()))
            {

                if (team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() == UPR || team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() == UPL)
                {

                    if (stinger->getHp() == 0)
                    {
                        stinger->setAlive(false);
                    }
                    stinger->setHp(--(stinger->getHp()));
                }

                else
                {
                    /// yahan par player loosess hp aye ga
                }

            }

            stinger->draw(window, offset_x);
            stinger->drawSpike(window, offset_x);

        }


        for (int i = 0; i < batCount; ++i) {

            if (!batbrains[i]->alive()) {
                continue;
            }


            batbrains[i]->movement(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), cell_size);


            if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack()) {

                if (batbrains[i]->PlayerBatCollision(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), batbrains[i]->getX(), batbrains[i]->getY(), batbrains[i]->getBatBrainWidth(), batbrains[i]->getBatBrainHeight())) {


                    if (team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() == UPR || team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() == UPL) {

                        team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() = -7.0f;
                        batbrains[i]->setHp(0);
                        batbrains[i]->setAlive(false);
                        continue;
                    }

                    else {
                        team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = true;
                        team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() = -7;
                    }
                }
            }


            batbrains[i]->draw(window, offset_x);

        }



       */
        for (int i = 0; i < 8; i++)
        {
            level[levelIndex]->getFalling()[i]->shouldItActivate(team.getPlayer()[team.getPlayerIndex()]->getx());
            if (level[levelIndex]->getFalling()[i]->getActivated())
            {
                level[levelIndex]->getFalling()[i]->fall();
            }
        }
        level[levelIndex]->handleEnemies(window, team.getPlayer()[team.getPlayerIndex()]->getx(), team.getPlayer()[team.getPlayerIndex()]->gety(), team.getPlayer()[team.getPlayerIndex()]->getPwidth(), team.getPlayer()[team.getPlayerIndex()]->getPheight(), team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack(), team.getPlayer()[team.getPlayerIndex()]->getTempVelocityY(), team.getPlayer()[team.getPlayerIndex()]->getOnGround(), team.getPlayer()[team.getPlayerIndex()]->getAnimationIndex(), offset_x, team.getPlayer()[team.getPlayerIndex()][0],hud);
        cout << "Score is : " << hud.getScore();
        cout << "\nLives are : " << hud.getLives() << "\n\n\n";
        team.animate();
        team.draw(window, offset_x);

        // draw_buffer(window, bufferSpriteStart, buffer_start - offset_x);
        // draw_buffer(window, bufferSpriteEnd, buffer_end - offset_x);
    }
};
