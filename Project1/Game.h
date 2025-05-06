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
#include"GlobalFunctions.h"
class Game
{
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

    int crabCount = 5;
    int crabIndex = 0;
    Crabmeat** crabs;

    int beeCount = 5;
    int beeIndex = 0;
    Beebot** beebots;

    int motobugCount;
    int motobugIndex;
    Motobug** motobugs;

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

public:
    Game()
    {
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

        ////////////////////////////Crabs
        int crabCount = 5;
        int crabIndex = 0;
        Crabmeat** crabs = new Crabmeat * [crabCount];
        for (int i = 0; i < crabCount; i++)
        {
            crabs[i] = new Crabmeat();
        }

        crabs[0]->getCrabCoordinates(level[levelIndex]->getLvl(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth());
        crabs[0]->move_crabs(crabs, crabIndex, crabCount, 64);
        ///////////////////////////////////
        //////////////bees
        ////////////////////////////////////
        beeCount = 5;
        beeIndex = 0;
        Beebot** beebots = new Beebot * [beeCount];

        for (int i = 0; i < beeCount; i++)
        {
            beebots[i] = new Beebot();
        }

        beebots[0]->getBeebotCoordinates(level[levelIndex]->getLvl(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth());
        beebots[0]->move_beebots(beebots, beeIndex, beeCount, 64);

        ///////////////////////////////////
        //////////////motobugs
        ////////////////////////////////////
        motobugCount = 5;
        motobugIndex = 0;
        Motobug** motobugs = new Motobug * [motobugCount];

        for (int i = 0; i < motobugCount; i++)
        {
            motobugs[i] = new Motobug();
        }

        motobugs[0]->getMotobugCoordinates(level[levelIndex]->getLvl(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth());
        motobugs[0]->move_motobugs(motobugs, motobugIndex, motobugCount, 64);

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
        levelIndex = 0;
        int height = level[levelIndex]->getHeight();
        int width = level[levelIndex]->getWidth();
         collectibles = new Collectibles **[level[levelIndex]->getHeight()];

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
        placeRingsFromMap(level[levelIndex]->getLvl(), collectibles, 14, 110, &rings, &ring_effect);
        if (!collectibles)
        {
            //cout << "collecitbles didnt work null h constructor m";
        }
        //else cout << "collecitbles  worked null nai h constructor m";
        

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
    void updateAndDrawCollectibles( int height, int width, RenderWindow& window)
    {/*
        if (!collectibles)
        {
            cout << "null h bhaiiyya\n\n";
        }*/
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                //cout << "i = " << i << "---- j = " << j << endl;
                if (collectibles[i][j])
                {
                    collectibles[i][j]->update();
                    collectibles[i][j]->draw(window);
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

    bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
    {
        return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
    }

    bool CollisionCheckWithCrabs(Crabmeat** crabs, int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight)
    {

        for (int i = 0; i < crabCount; i++)
        {

            if (!crabs[i]->alive())
            {
                continue;
            }

            if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, crabs[i]->getX(), crabs[i]->getY(), crabWidth, crabHeight))
            {

                float bottom_of_Player = player_y + Pheight;
                float top_of_Crab = crabs[i]->getY();

                if (bottom_of_Player - 10 < top_of_Crab)
                {

                    // crab ko marna hai ab becoz top collision, also add smoke effect and invincibilty
                    //cout << " Top-hit:  " << i << endl;

                    //cout << "PlyrX: " << player_x << "crab X: " << crabs[i]->getX() << endl;

                    velocityY = -10.0f;
                }

                else
                {

                    hasKnockedBack = true;
                    tempVelocityY = -7;

                    crabs[i]->setAnimation(3);
                    crabs[i]->RunNewAnimation();
                    crabs[i]->setAttack();

                    // cout << "PlyrX " << centre_of_Player << " Crab CenterX " << centre_of_CRab << endl;
                    // cout << " Sidehit " << i << endl;
                    // cout << "PlyrX " << player_x << " Crab X " << crabs[i].getX() << endl;
                }
                return true;
            }
        }

        return false;
    }

  

    bool CollisionCheckWithBeebots(Beebot** beebots, int& beeCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float beeWidth, const float beeHeight, bool onGround, bool spacePressed)
    {

        for (int i = 0; i < beeCount; i++)
        {

            if (!beebots[i]->alive())
            {
                continue;
            }

            if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, beebots[i]->getX(), beebots[i]->getY(), beeWidth, beeHeight))
            {

                if (!(onGround == false && spacePressed == true))
                {
                    hasKnockedBack = true;
                    tempVelocityY = -7; // knockback upwards initially
                    cout << "Player hit by Beebot --- thrown back" << endl;
                }

                return true;
            }
        }

        return false;
    }

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
        //cout << "in the start of play function \n\n";
        if (team.getPlayer()[team.getPlayerIndex()][0].getOnGround())
        {
            // collisionDetectedOffGround = false;//resetting the bool if player hits the platform
            team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = false;
            team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() = -7;
            team.getSpaceCount() = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        {
            // cout << "LEFT KEY PRESSED" << endl;
            if (checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() - 15, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2) && team.getPlayer()[team.getPlayerIndex()][0].getx() > 0)
            {
                team.getPlayer()[team.getPlayerIndex()][0].moveLeft();
                if (buffer_start > 4 * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() <= buffer_start)
                {
                    buffer_start = team.getPlayer()[team.getPlayerIndex()][0].getx();
                    buffer_end = buffer_start + 576;
                    offset_x -= team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
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
                if (team.getPlayer()[team.getPlayerIndex()][0].getx() <= 0 && !team.getPlayer()[team.getPlayerIndex()][0].getOnGround())
                {
                    // collisionDetectedOffGround = true;
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        {
            if (checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2))
            {
                team.getPlayer()[team.getPlayerIndex()][0].moveRight();
                if (buffer_end < 106 * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() >= buffer_end)
                {
                    buffer_end = team.getPlayer()[team.getPlayerIndex()][0].getx();
                    buffer_start = buffer_end - 576;
                    offset_x += team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
                    // offset_x += 15;
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
        /*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
           {
               team.switchPlayer();
           }*/
        else
            leftRight = false;
        if (!leftRight)
        {
            team.getPlayer()[team.getPlayerIndex()][0].getVelocityX() = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        {
            /* spaceCount++;
             cout << "\n\n\nSPaceCount = " << spaceCount<<"\n\n";*/
            team.jump();
        }
        //cout << "in the middle of play function \n\n";

        if (team.getSpacePressed())
        {
            if (team.getPlayerIndex() != 1)
            {
                team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = UPR;
                team.getPlayer()[team.getPlayerIndex()][0].getStates()[UPR][0].RunAnimation();
            }
            else if (team.getSpaceCount() < 10)
            {
                team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = UPR;
                team.getPlayer()[team.getPlayerIndex()][0].getStates()[UPR][0].RunAnimation();
            }
            leftRight = false;
        }
        if (!team.getSpacePressed() && !leftRight)
        {
            team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = STILL;
            team.getPlayer()[team.getPlayerIndex()][0].getStates()[STILL][0].RunAnimation();
        }
        if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = collisionCheckWithSpikes(level[levelIndex][0].getLvl(), offset_y, hit_box_factor_y, hit_box_factor_x, team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), 64, team.getPlayer()[team.getPlayerIndex()][0].getVelocityY());
        //cout << "before crab of play function \n\n";

        //cout << "team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = " << team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() << endl;
        // if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        //{
        //     CollisionCheckWithCrabs(crabs, crabCount, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack(), team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), 60, 44);
        // }/*
        /*  if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
          {
              CollisionCheckWithBeebots(beebots, beeCount, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack(), team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY(), beebots[0]->getbeeWidth(), beebots[0]->getbeeHeight(), team.getPlayer()[team.getPlayerIndex()][0].getOnGround(), team.getSpacePressed());
          }*/
        //cout << "after crab of play function \n\n";

        if (team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack()) /*|| team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedByProjectile()*/
        {
            //cout << "\n\nVirtual gravity function running\n\n";
            team.getPlayer()[team.getPlayerIndex()][0].getx() -= 6;
            team.getPlayer()[team.getPlayerIndex()][0].gety() += team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY();
            team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() += team.getPlayer()[team.getPlayerIndex()][0].getTempGravity();
            if (team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() >= 0)
            {
                team.getPlayer()[team.getPlayerIndex()][0].playerVirtualGravity(level[levelIndex][0].getLvl(), offset_y, offset_x, 64, team.getSpacePressed());
            }
        }
        /* if (team.getPlayer()[team.getPlayerIndex()][0].getOnGround())
         {
             team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = false;
             team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() = -7;
         }*/
        if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            team.getPlayer()[team.getPlayerIndex()][0].player_gravity(level[levelIndex][0].getLvl(), offset_y, offset_x, 64, team.getSpacePressed());

        team.storePath();
        team.autoMoveFollowers(level[levelIndex]->getLvl());
        if (level[levelIndex]->getMoveable()->move(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()]->getOnGround()))
        {
            if(team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() != STILL)
            {
                team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = STILL;
                team.getPlayer()[team.getPlayerIndex()][0].getStates()[STILL]->RunAnimation();
            }
            //team.
        }
        draw_bg(window, backGroundSprite, offset_x);
        level[levelIndex]->getMoveable()->draw(window, offset_x);

        display_level(window, level[levelIndex][0].getHeight(), level[levelIndex][0].getWidth(), level[levelIndex][0].getLvl(), walls, 64, offset_x);

        updateAndDrawCollectibles( level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), window);
        handleRingCollection(collectibles, level[levelIndex][0].getLvl(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), team.getPlayer()[team.getPlayerIndex()][0], ringsCollected, cell_size);

        // team.getPlayer()[team.getPlayerIndex()][0].draw_player(window, team.getPlayer()[team.getPlayerIndex()][0].getStates()[team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex()][0].getSprites()[team.getPlayer()[team.getPlayerIndex()][0].getStates()[team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex()]->getIndex()],offset_x);

        // for (int i = 0; i < beeCount; i++)
        //{
        //     beebots[i]->movement(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), cell_size, team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight());
        //     beebots[i]->draw(window, offset_x);
        //     beebots[i]->drawProjectiles(window, offset_x);
        //     //if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
        //     //{
        //     if (beebots[i]->handleProjectilesCollision(level[levelIndex][0].getLvl(), cell_size, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack(), team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY()))
        //     {
        //         team.getPlayer()[team.getPlayerIndex()][0].getOnGround() = false;

        //    }//}
        //}
        //cout << "Ongground = " << team.getPlayer()[team.getPlayerIndex()][0].getOnGround();
        //cout << "\n";
        team.draw(window, offset_x);
        // change these according to the movement logic of motobug, for now it moves with player

        /* for (int i = 0; i < crabCount; i++) {
             crabs[i]->movement();
             crabs[i]->draw(window, offset_x);
         }

         for (int i = 0; i < motobugCount; i++) {
             motobugs[i]->movement(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety());
             motobugs[i]->draw(window, offset_x);
         }*/

         /*
         for (int i = 0; i < batCount; i++) {
             batbrains[i].movement(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), cell_size);
             batbrains[i].draw(window, offset_x);
         }

         beebot.movement();
         beebot.draw(window);*/

         /*bat.movement(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety());
         bat.draw(window);*/

         /*stinger.movement(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety());
         stinger.draw(window);
         */

         // draw_buffer(window, bufferSpriteStart, buffer_start - offset_x);
         // draw_buffer(window, bufferSpriteEnd, buffer_end - offset_x);
    }
};
