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
#include "HUD.h"

#include"Audio.h"

#include "FallingPlatform.h"

class Game
{
    // some score and other stuff
    Text gameover;
    Font font;
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
    Clock makeInvincible;

    Audio* audio;




    Clock specialBoostClock;
    bool specialBoostUsed;

    Team team;
    Level** level;
    int levelIndex;
    int cell_size;
    Clock Akey;

    ////////////////////////////
    Clock levelTimer;
    int ringsCollected;
    bool BoostStatus;
    int randomLives;
    Clock gameOverClock;
    bool gameOverRestarted;
    ////////////////////////////

public:
    Game(Audio* ad) : audio(ad)
    {
        specialBoostUsed = false;
        font.loadFromFile("Fonts/scoreFont.ttf");
        gameover.setFont(font);
        gameover.setString("GAME OVER");
        gameover.setScale(4.3, 4.3);
        gameover.setPosition(320, 350);
        gameover.setFillColor(Color::Red);

        team.setAudio(audio);

        gameOver = false;
        cell_size = 64;
        // team = Team();
        // level = new * Level();
        level = new Level * [3];
        level[0] = new Level1(audio);
        level[0]->setAudio(audio);

        level[1] = new Level2(audio);
        level[1]->setAudio(audio);

        level[2] = new Level3(audio);
        level[2]->setAudio(audio);

       /* level[3] = new BossLevel(audio);
        level[3]->setAudio(audio);*/


        levelIndex = 1;
        buffer.loadFromFile("Data/bufferSprite.jpg");
        bufferSpriteStart.setTexture(buffer);
        bufferSpriteEnd.setTexture(buffer);
        buffer_start = 4 * 64;
        buffer_end = 9 * 64;
        offset_x = 0;
        offset_y = 0;
        leftRight = false;
        hit_box_factor_x = 8 * 2.5;
        hit_box_factor_y = 5 * 2.5;

        spaceCount = 0;
        int height = level[levelIndex]->getHeight();
        int width = level[levelIndex]->getWidth();

        level[levelIndex]->loadAndPlaceCollectibles();


        ringsCollected = 0;
        BoostStatus = false;
        randomLives = 0;
    }
    void setLevelIndex(int index)
    {
        levelIndex = index;
    }
    int getLevelIndex()
    {
        return levelIndex;
    }

    bool collisionCheckWithSpikes(char** lvl, int offset_y, int hit_box_factor_y, int hit_box_factor_x, int Pheight, int Pwidth, int player_x, int player_y, int cell_size, int velocityY, int height, int width)
    {
        offset_y = player_y;
        offset_y += velocityY;

        if ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size >= height)
        {
            gameOver = true;
            if (!gameOverRestarted)
            {
                gameOverClock.restart();
                gameOverRestarted = true;
            }
            return false;
        }

        char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
        char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
        char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];

        char top_left_up = lvl[(offset_y + hit_box_factor_y) / cell_size][(player_x + hit_box_factor_x) / cell_size];
        char top_right_up = lvl[(offset_y + hit_box_factor_y) / cell_size][(player_x + hit_box_factor_x + Pwidth) / cell_size];
        char top_mid_up = lvl[(offset_y + hit_box_factor_y) / cell_size][(player_x + hit_box_factor_x + Pwidth / 2) / cell_size];

        char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
        char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
        char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];

        bool forLeft = topLeft != 'w' && topLeft != 'q' && topLeft != 'e';
        bool forMiddle = topMiddle != 'w' && topMiddle != 'q' && topMiddle != 'e';
        bool forRight = topRight != 'w' && topRight != 'q' && topRight != 'e';

        // cout << "Left : " << bottom_left_down << " ---- Mid : " << bottom_mid_down << " -------" << "Right : " << bottom_right_down << "----";

        bool b = ((bottom_left_down == 'p' || bottom_mid_down == 'p' || bottom_right_down == 'p') && velocityY > 0 && (forLeft || forMiddle || forRight)) || ((top_left_up == 'i' || top_mid_up == 'i' || top_right_up == 'i') && velocityY < 0);
        if (b)
        {
           hud.getLives()--;
        }
    }
    void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord)
    {
        bufferSprite.setPosition(buffer_coord, 500);
        window.draw(bufferSprite);
    }
    void updateLevel()
    {
        if (levelIndex == 3)
        {
            return;
        }
        levelIndex++;
        level[levelIndex]->setAudio(audio);
        if (levelIndex != 3)
            level[levelIndex]->loadAndPlaceCollectibles();
        team.getPlayer()[team.getPlayerIndex()]->getx() = 150;
        team.getPlayer()[team.getPlayerIndex()]->gety() = 150;
        team.getPlayer()[team.getPlayerIndex()]->getVelocityY() = 15;
        team.getPlayer()[team.getPlayerIndex()]->getOnGround() = true;
        if (levelIndex == 2)
        {
            for (int i = 0;i < 3;i++)
            {
                team.getPlayer()[i]->setGravity(0.4);
            }
        }
        buffer_start = 4 * 64;
        buffer_end = 9 * 64;
        offset_x = 0;
        hud.resetTimer();
        levelTimer.restart();
        if (levelIndex == 3)
        {
            cout << "LEVEL $ it is  \n ";
        }
    }
    HUD& getHUD()
    {
        return hud;
    }
    void setTeamAudio(Audio* a) { 
        team.setAudio(a);
    }
    void saveGame(string& playerName)
    {
        ofstream out("savefile.txt");
        if (!out)
            return;

        out << playerName << "\n"; // assuming you have playerName stored somewhere
        out << levelIndex << "\n";
        out << hud.getLives() << "\n";
        out << team.getPlayerIndex() << "\n";
        out << team.getPlayer()[team.getPlayerIndex()][0].getx() << "\n";
        out << team.getPlayer()[team.getPlayerIndex()][0].gety() << "\n";
        out << hud.getRings() << "\n"; // if you store this somewhere
        out << hud.getScore() << "\n"; // assuming you track it
        /*cout << level[levelIndex]->getTotalEnemyCount();
        cout << level[levelIndex]->getEnemies();*/
        /*for (int i = 0;i < level[levelIndex]->getTotalEnemyCount();i++)
        {
            out << (int)level[levelIndex]->getEnemies()[i]->alive()<<"\n";
            cout << level[levelIndex]->getEnemies()[i]->alive() << "\n";
        }*/
        out.close();
    }
    bool loadGame(string& playerName)
    {
        ifstream in("savefile.txt");
        if (!in)
            return false;

        string name;
        float x, y;
        int hp, playerIdx;
        int sc;

        getline(in, name);
        playerName = name;

        in >> levelIndex >> hp >> playerIdx >> x >> y >> hud.getRings() /*>> enemiesDefeated*/ >> sc;
        /*   for (int i = 0;i < level[levelIndex]->getTotalEnemyCount();i++)
           {
               bool b;
               in >> b;
               level[levelIndex]->getEnemies()[i]->setAlive(b);
           }*/
        team.setPlayerIndex(playerIdx);
        hud.setLives(hp);

        team.getPlayer()[playerIdx]->setx(x);
        team.getPlayer()[playerIdx]->sety(y);

        in.close();
        return true;
    }
    bool checkTimer()
    {
        if (levelTimer.getElapsedTime().asSeconds() >= level[levelIndex]->getTimer())
            return true;
        return false;
    }
    bool play(RenderWindow& window)
    {
        // cout << "level = " << levelIndex<<endl;
        if (levelIndex == 3)
        {
            team.setplayerIndex(0);
        }
        if (!gameOver)
        {
            if (team.getPlayer()[team.getPlayerIndex()][0].getOnGround())
            {
                team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = false;
                team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() = -7;
                team.getSpaceCount() = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            {
                if (checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1, 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() - 15, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2, 14, level[levelIndex]->getWidth()) && team.getPlayer()[team.getPlayerIndex()][0].getx() > 0)
                {
                    team.getPlayer()[team.getPlayerIndex()][0].moveLeft(level[levelIndex]->getLvl(), level[levelIndex]->getWidth(), level[levelIndex]->getFriction());
                    if (buffer_start > 4 * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() <= buffer_start)
                    {
                        buffer_start = team.getPlayer()[team.getPlayerIndex()][0].getx();
                        buffer_end = buffer_start + 320;
                        offset_x += team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
                    }
                    leftRight = true;
                }
                else
                {
                    if (!checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), 14, level[levelIndex]->getWidth()))
                    {
                        team.getPlayer()[team.getPlayerIndex()][0].executePushingLeft();
                        team.getPlayer()[team.getPlayerIndex()][0].getVelocityX() = 0;
                    }
                    if (team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() <= 0)
                        team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() = 15;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            {
                if (checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety(), 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1, 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2, 14, level[levelIndex]->getWidth()))
                {
                    team.getPlayer()[team.getPlayerIndex()][0].moveRight(level[levelIndex]->getLvl(), level[levelIndex]->getWidth(), level[levelIndex]->getFriction());
                    if (buffer_end < (level[levelIndex]->getWidth() - 5) * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() >= buffer_end)
                    {
                        buffer_end = team.getPlayer()[team.getPlayerIndex()][0].getx();
                        buffer_start = buffer_end - 320;
                        offset_x += team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
                    }
                    leftRight = true;
                }
                else
                {
                    if (!checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety(), 14, level[levelIndex]->getWidth()))
                    {
                        team.getPlayer()[team.getPlayerIndex()][0].executePushingRight();
                        team.getPlayer()[team.getPlayerIndex()][0].getVelocityX() = 0;
                    }
                    if (team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() >= 0)
                        team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() = 15;
                }
            }
            else
            {
                leftRight = false;
                if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
                    team.getPlayer()[team.getPlayerIndex()]->decelerate(level[levelIndex]->getLvl(), level[levelIndex]->getWidth(), level[levelIndex]->getFriction());
                else
                    team.getPlayer()[team.getPlayerIndex()][0].getVelocityX() = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            {
                team.jump();
                //audio->playSound(audio->getJump());

                // cout << "Jumped\n\n";
                // cout << "onground  in (space ) = " << team.getPlayer()[team.getPlayerIndex()]->getOnGround()<<endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() && Akey.getElapsedTime().asMilliseconds() > 500)
            {
                team.switchLeader();
                Akey.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            {
                team.useSpecial(level[levelIndex]->getLvl(), 14, level[levelIndex]->getWidth());
                team.getPlayer()[team.getPlayerIndex()]->getSpecialAbiltyUsed() = true;
            }
            if (team.getPlayer()[team.getPlayerIndex()]->getSpecialAbiltyUsed() == true && team.getPlayerIndex() == 0)
            {
                // cout << "SpinDash being called";
                team.getPlayer()[0]->spinDash(level[levelIndex]->getLvl(), level[levelIndex]->getWidth(), level[levelIndex]->getFriction());
                if (checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety(), 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1, 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex][0].getLvl(), team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2, 14, level[levelIndex]->getWidth()))
                {
                    if (buffer_start > 4 * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() <= buffer_start)
                    {
                        buffer_start = team.getPlayer()[team.getPlayerIndex()][0].getx();
                        buffer_end = buffer_start + 320;
                        offset_x += team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
                    }
                    if (buffer_end < (level[levelIndex]->getWidth() - 5) * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() >= buffer_end)
                    {
                        buffer_end = team.getPlayer()[team.getPlayerIndex()][0].getx();
                        buffer_start = buffer_end - 320;
                        offset_x += team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
                    }
                }
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
            if (!team.getPlayer()[team.getPlayerIndex()]->getVelocityX() && !team.getPlayer()[team.getPlayerIndex()]->getVelocityY())
            {
                team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = STILL;
            }
            if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
                team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = collisionCheckWithSpikes(level[levelIndex][0].getLvl(), offset_y, hit_box_factor_y, hit_box_factor_x, team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), 64, team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth());
            if (team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
            {
                team.getPlayer()[team.getPlayerIndex()][0].getx() -= 6;
                team.getPlayer()[team.getPlayerIndex()][0].gety() += team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY();
                team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() += team.getPlayer()[team.getPlayerIndex()][0].getTempGravity();
                if (team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() >= 0)
                {
                    team.getPlayer()[team.getPlayerIndex()][0].playerVirtualGravity(level[levelIndex][0].getLvl(), offset_y, offset_x, 64, team.getSpacePressed(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), gameOver);
                }
                if (!gameOverRestarted && gameOver)
                {
                    gameOverClock.restart();
                    gameOverRestarted = true;
                }
                makeInvincible.restart();
            }
            if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
                team.getPlayer()[team.getPlayerIndex()][0].player_gravity(level[levelIndex][0].getLvl(), offset_y, offset_x, 64, team.getSpacePressed(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), gameOver);
            if (!gameOverRestarted && gameOver)
            {
                gameOverClock.restart();
                gameOverRestarted = true;
            }
            team.storePath();
            team.autoMoveFollowers(level[levelIndex]->getLvl(), offset_x, level[levelIndex]->getWidth());
            if (levelIndex != 0 && levelIndex != 3 && level[levelIndex]->getMoveable()->move(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()]->getOnGround()))
            {
                // cout << "Buffers working\n";
                if (buffer_end < (level[levelIndex]->getWidth() - 5) * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() >= buffer_end)
                {
                    // cout << "Buffers updaintg";
                    buffer_end = team.getPlayer()[team.getPlayerIndex()][0].getx();
                    buffer_start = buffer_end - 320;
                    offset_x += 3;
                }
                if (buffer_start > 4 * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() <= buffer_start)
                {
                    buffer_start = team.getPlayer()[team.getPlayerIndex()][0].getx();
                    buffer_end = buffer_start + 320;
                    offset_x -= 3;
                }
                team.getPlayer()[team.getPlayerIndex()]->getOnGround() = true;
                for (int i = 0; i < 3; i++)
                {
                    if (team.getPlayerIndex() == i)
                        continue;
                    team.getPlayer()[i]->gety() = team.getPlayer()[team.getPlayerIndex()]->gety();
                }
                team.getSpacePressed() = false;
            }
        }
        // draw_bg(window, backGroundSprite, offset_x);
        level[levelIndex]->draw_bg(window);
        if (levelIndex != 3 && !gameOver)
            level[levelIndex]->getMoveable()->draw(window, offset_x);

        // display_level(window, level[levelIndex][0].getHeight(), level[levelIndex][0].getWidth(), level[levelIndex][0].getLvl(), walls, 64, offset_x);
        level[levelIndex]->display_level(window, 64, offset_x);
        if (levelIndex != 3 && !gameOver)
            for (int i = 0; i < level[levelIndex]->getFallingCount(); i++)
                level[levelIndex]->getFalling()[i]->draw(window, offset_x);

        if (!gameOver)
        {

            for (int i = 0; i < level[levelIndex]->getRingCount(); i++)
            {
                level[levelIndex]->getRings()[i]->update();
                level[levelIndex]->getRings()[i]->draw(window, offset_x);
                level[levelIndex]->getRings()[i]->handleCollision(team.getPlayer()[team.getPlayerIndex()][0], level[levelIndex]->getLvl(), cell_size, ringsCollected);
            }

            for (int i = 0; i < level[levelIndex]->getLivesCount(); i++)
            {
                level[levelIndex]->getLives()[i]->update();
                level[levelIndex]->getLives()[i]->draw(window, offset_x);
                if (level[levelIndex]->getLives()[i]->handleCollision(team.getPlayer()[team.getPlayerIndex()][0], level[levelIndex]->getLvl(), cell_size, randomLives))
                {
                    hud.setLives(hud.getLives() + 1);
                }
            }

            for (int i = 0; i < level[levelIndex]->getBoostCount(); i++)
            {
                level[levelIndex]->getBoosts()[i]->update();
                level[levelIndex]->getBoosts()[i]->draw(window, offset_x);
                if (level[levelIndex]->getBoosts()[i]->handleCollision(team.getPlayer()[team.getPlayerIndex()][0], level[levelIndex]->getLvl(), cell_size, randomLives))
                {
                    team.useSpecialBoost();
                    specialBoostUsed = true;
                    // specialBoosClock
                    specialBoostClock.restart();
                }
            }
        }
        if (specialBoostUsed && specialBoostClock.getElapsedTime().asSeconds() > 6)
        {
            specialBoostUsed = false;
            team.undoBoost();
        }

        // team.draw(window, offset_x);

        if (levelIndex != 3 && !gameOver)
            for (int i = 0; i < level[levelIndex]->getFallingCount(); i++)
            {
                level[levelIndex]->getFalling()[i]->shouldItActivate(team.getPlayer()[team.getPlayerIndex()]->getx());
                if (level[levelIndex]->getFalling()[i]->getActivated())
                {
                    level[levelIndex]->getFalling()[i]->fall();
                }
            }
        int tempLives = hud.getLives();
            bool tempGameOver = gameOver;
;        if (!gameOver)
            level[levelIndex]->handleEnemies(window, team.getPlayer()[team.getPlayerIndex()]->getx(), team.getPlayer()[team.getPlayerIndex()]->gety(), team.getPlayer()[team.getPlayerIndex()]->getPwidth(), team.getPlayer()[team.getPlayerIndex()]->getPheight(), team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack(), team.getPlayer()[team.getPlayerIndex()]->getTempVelocityY(), team.getPlayer()[team.getPlayerIndex()]->getOnGround(), team.getPlayer()[team.getPlayerIndex()]->getAnimationIndex(), offset_x, team.getPlayer()[team.getPlayerIndex()][0], hud, gameOver);
        // team.getPlayer()[team.getPlayerIndex()]->drawHitBox(window);
         
        if (specialBoostUsed && team.getPlayerIndex() == 2)
        {
            hud.setLives(tempLives);
            gameOver = tempGameOver;
        }
        if (!gameOverRestarted && gameOver)
        {
            gameOverClock.restart();
            gameOverRestarted = true;
        }
        if (checkTimer())
        {
            gameOver = true;
            if (!gameOverRestarted)
            {
                gameOverClock.restart();
                gameOverRestarted = true;
            }
        }
        cout << "LIVE ARE " << hud.getLives() << endl;
        if (!gameOver)
            team.animate();
        if (levelIndex != 3)
            team.draw(window, offset_x);
        else
            team.drawSonic(window, offset_x);
        hud.draw(window);
        if (levelIndex != 3)
            for (int i = 0; i < 8; i++)
            {
                level[levelIndex]->getFalling()[i]->shouldItActivate(team.getPlayer()[team.getPlayerIndex()]->getx());
                if (level[levelIndex]->getFalling()[i]->getActivated())
                {
                    level[levelIndex]->getFalling()[i]->fall();
                }
            }

        level[levelIndex]->drawEnemies(window, offset_x);
        if (level[levelIndex]->hasLevelEnded(team.getPlayer()[team.getPlayerIndex()]->getx()) || hud.getRings() > 75)
        {
            updateLevel();
        }

        if (hud.getLives() <= 0 || gameOver)
        {
            if (levelIndex == 3)
            {
                cout << "game over hugai h level 3 k bad ";
            }
            gameOver = true;
            if (!gameOverRestarted)
            {
                gameOverClock.restart();
                gameOverRestarted = true;
            }
            window.draw(gameover);
        }
        if (gameOver && gameOverClock.getElapsedTime().asMilliseconds() > 3000)
            return true;
        return false;
        /*draw_buffer(window, bufferSpriteStart, buffer_start - offset_x);
        draw_buffer(window, bufferSpriteEnd, buffer_end - offset_x);*/
    }
};
