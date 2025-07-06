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
    bool playMusic;
    bool levelEnded;
    bool left;
    bool right;
    int tempPlayerIndex;
    Event e;
    bool clkRestarted;
    bool beingMerged;
    string cheatBuffer;
    bool cheatActivated;
    int cheatState;
    Clock cheatClk;
    Text cheatCodeText;
    // some score and other stuff
    Text youWin;
    Clock youWinClk;
    bool youwinrestarted;
    Text gameover;
    Font font;
    HUD hud;
    bool gameOver;
    int spaceCount;
    float buffer_start;
    float buffer_end;
    //Texture buffer;
    RectangleShape bufferSpriteStart;
    RectangleShape bufferSpriteEnd;
    float offset_x;
    float offset_y;
    bool leftRight;
    int hit_box_factor_x;
    int hit_box_factor_y;
    Clock makeInvincible;
    Clock jumpSFXClock;


    Audio* audio;




    Clock specialBoostClock;
    bool specialBoostUsed;
    Text specialBoost;
    Team team;
    Level** level;
    int levelIndex;
    int cell_size;
    Clock Akey;
    bool wantToReturnToMenu;

    ////////////////////////////
    Clock levelTimer;
    int ringsCollected;
    bool BoostStatus;
    int randomLives;
    Clock gameOverClock;
    bool gameOverRestarted;
    
    Texture levelTransitionTexture;
    Sprite levelTransitionSprite;
	Clock levelTransitionClock;
    bool transitionRestarted;
    ////////////////////////////
    const char* levelQuotes[4] = 
    {
        "Level 1: Every great journey begins with a single step.",
        "Level 2: Stay sharp—the real challenge is just beginning.",
        "Level 3: You’ve made it this far. Don’t slow down now.",
        "Boss Level: All or nothing. Show them what you’re made of."
    };
    Text transitionText;
    bool transitionStarted;




    sf::Texture goalPostTexture;
    sf::Sprite goalPostSprite;
    sf::Clock goalPostClock;
    //sf::Clock levelTransitionClock;

    int goalPostFrameIndex = 0;
    int goalPostLoopCount = 0;
    sf::Clock goalPostHoldClock;
    bool goalPostHoldStarted = false;

    bool goalPostSpinning = false;
    bool goalPostAnimationDone = false;

    // Optional sound
    sf::SoundBuffer goalPostSoundBuffer;
    sf::Sound goalPostSound;

    std::vector<sf::IntRect>goalPostFrames = {
    {0, 0, 32, 63},
    {32, 0, 24, 63},
    {40, 0, 14, 63},
    {54, 0, 11, 63},
    {65, 0, 34, 63},
    {99, 0, 11, 63},
    {121, 0, 19, 63},
    {140, 0, 11, 63},
    {162, 0, 43, 63},
    {205, 0, 11, 63},
    {227, 0, 25, 63},
    {252, 0, 14, 63},
    {277, 0, 34, 63},
    {311, 0, 11, 63},
    {333, 0, 19, 63},
    {352, 0, 11, 63},
    {374, 0, 51, 63},
    {436, 0, 34, 63},
    {492, 0, 19, 63},
    {533, 0, 43, 63},
    {587, 0, 50, 63},
    {648, 0, 34, 63},
    {704, 0, 19, 63},
    {745, 0, 49, 63}
    };
    Font boostFont;
    Text SpecialBoostText;
    Text CheatTime;
    Text ExtraLife;
    Clock extraClk;
    bool extraLifeGained;
public:
    Game(Audio* ad,int l = 0) : audio(ad)
    {
        playMusic = false;
        transitionRestarted = false;
        left = false;
        right = false;
        tempPlayerIndex = 0;
        beingMerged = false;
        cheatState = 0;
		cheatActivated = false;


        specialBoostUsed = false;


        font.loadFromFile("Fonts/NiseSegaSonic.ttf");
        boostFont.loadFromFile("Fonts/scoreFont.ttf");
        cheatCodeText.setString("Cheat Mode On !!!");
        cheatCodeText.setFont(boostFont);
        cheatCodeText.setFillColor(sf::Color::White);
        cheatCodeText.setOutlineColor(sf::Color::Black);
        cheatCodeText.setOutlineThickness(5);
        cheatCodeText.setCharacterSize(52);
        cheatCodeText.setPosition(450, 780);
        //cheat
        CheatTime.setFont(boostFont);
        CheatTime.setFillColor(sf::Color::White);
        CheatTime.setOutlineColor(sf::Color::Black);
        CheatTime.setOutlineThickness(5);
        CheatTime.setCharacterSize(32);
        CheatTime.setPosition(850, 780);

        gameover.setFont(boostFont);
        gameover.setString("GAME OVER !");
        gameover.setScale(4.3, 4.3);
        gameover.setPosition(320, 350);
        gameover.setFillColor(Color::Red);

        clkRestarted = false;
        transitionStarted = false;;

        SpecialBoostText.setString("Special Boost Activated!!!");
        SpecialBoostText.setCharacterSize(45);
        SpecialBoostText.setPosition(350, 90);

        specialBoost.setFont(boostFont);
        specialBoost.setFillColor(sf::Color::Blue);
        specialBoost.setOutlineColor(sf::Color::Black);
        specialBoost.setOutlineThickness(4);

        SpecialBoostText.setFont(boostFont);
        SpecialBoostText.setFillColor(sf::Color::Blue);
        SpecialBoostText.setOutlineColor(sf::Color::Black);
        SpecialBoostText.setOutlineThickness(4);

        specialBoost.setPosition(800, 20);
        specialBoost.setCharacterSize(45);

        ExtraLife.setFont(boostFont);
        ExtraLife.setFillColor(sf::Color::Red);
        ExtraLife.setOutlineColor(sf::Color::Black);
        ExtraLife.setOutlineThickness(4);
        ExtraLife.setString("Extra Life Gained!!!");
        ExtraLife.setCharacterSize(45);
        ExtraLife.setPosition(350, 150);



        youwinrestarted = false;
		youWin.setFont(boostFont);
		youWin.setString("YOU WIN");
		youWin.setScale(4.3, 4.3);
		youWin.setPosition(320, 350);
		youWin.setFillColor(Color::Yellow);
        team.setAudio(audio);

        //specialBoost.setFont(font);

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
        level[3] = new BossLevel(audio);
        level[3]->setAudio(audio);
        levelIndex = 0;
        if (levelIndex == 2)
        {
            for (int i = 0;i < 3;i++)
            {
                team.getPlayer()[i]->setGravity(0.6);
            }
        }

        //buffer.loadFromFile("Data/bufferSprite.jpg");
        bufferSpriteStart.setSize(Vector2f(2,300));
        bufferSpriteEnd.setSize(Vector2f(2, 300));
		bufferSpriteStart.setFillColor(Color::Red);
		bufferSpriteEnd.setFillColor(Color::Red);
        buffer_start = 6 * 64;
        buffer_end = 11 * 64;
        bufferSpriteStart.setPosition(buffer_start,400);
        bufferSpriteEnd.setPosition(buffer_end, 400);
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
        jumpSFXClock.restart();
        wantToReturnToMenu = false;
        //cout << "buffer start = " << buffer_start << " | buffer end = " << buffer_end << "| offsetx = " << offset_x;
		levelTransitionTexture.loadFromFile("Data/levelTransition.png");
		levelTransitionSprite.setTexture(levelTransitionTexture);
		levelTransitionSprite.setPosition(0, 0);
		int scX = (float)1200 / levelTransitionTexture.getSize().x;
		int scY = (float)900 / levelTransitionTexture.getSize().y;
		levelTransitionSprite.setScale(scX, 3.75);
        levelEnded = false;

        transitionText.setFont(font);
        transitionText.setCharacterSize(24);
        transitionText.setFillColor(sf::Color::Black);
        transitionText.setPosition(90, 380);


        goalPostTexture.loadFromFile("Data/goalPostSpin.png");
        goalPostSprite.setTexture(goalPostTexture);
        goalPostSprite.setTextureRect(sf::IntRect(0, 0, 61, 53));
        goalPostSprite.setPosition(level[levelIndex]->getLevelEnd(), level[levelIndex]->getLevelEndY());
        goalPostSprite.setScale(1.5, 1.5);
      

       /* if (!goalPostSoundBuffer.loadFromFile("Audio/goalPostSpin.ogg"))
            std::cout << "Failed to load goalpost sound\n";
        goalPostSound.setBuffer(goalPostSoundBuffer);*/
       

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
			 cout << "Game Over in spikes check\n";
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
        audio->playLevelMusicByIndex(levelIndex);
        level[levelIndex]->setAudio(audio);
        if (levelIndex != 3)
            level[levelIndex]->loadAndPlaceCollectibles();
            for (int i = 0;i < 4;i++)
            {
                team.getPlayer()[i]->getx() = 150;
                team.getPlayer()[i]->gety() = 150;
                team.getPlayer()[i]->getVelocityY() = 15;
                team.getPlayer()[i]->setGravity(1);
            }
        team.getPlayer()[team.getPlayerIndex()]->getOnGround() = true;
        if (levelIndex == 2)
        {
            for (int i = 0;i < 4;i++)
            {
                team.getPlayer()[i]->setGravity(0.6);

            }
        }
        buffer_start = 8 * 64;
        buffer_end = 13 * 64;
        offset_x = 0;
        hud.resetTimer();
        levelTimer.restart();
        if (levelIndex == 3)
        {
            //cout << "LEVEL $ it is  \n ";
        }
        transitionRestarted = false;
        goalPostSprite.setPosition(level[levelIndex]->getLevelEnd(), level[levelIndex]->getLevelEndY());
        goalPostSpinning = false;
        goalPostAnimationDone = false;
        goalPostLoopCount = 0;
        goalPostFrameIndex = 0;
       
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
        out << team.getPlayer()[team.getPlayerIndex()]->getx() << "\n";
        out << team.getPlayer()[team.getPlayerIndex()]->gety() << "\n";
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

        in >> levelIndex >> hp >> playerIdx >> x >> y >> hud.getRings() >> sc;

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
    bool WantToReturnToMenu() {
        return wantToReturnToMenu;
    }

    void resetReturnToMenuFlag() {
        wantToReturnToMenu = false;
    }

    bool play(RenderWindow& window)
    {
        if (!playMusic)
        {
            cout << "PLAYMUSIC CALLED";
            audio->setCurrentlyPlayingMusic(levelIndex);
            audio->playMusic();
            //audio->setMusicVolume(0);
            playMusic = true;
        }
        
       /* if (playMusic)
        {
            audio
        }*/
        //cout << "In play start veloctyx = " << team.getPlayer()[team.getPlayerIndex()]->getVelocityX();
        //cout << "cheat activated = " << cheatActivated;
        //cout << "---------- beingmerged  = " << beingMerged<< "---------merged = " << team.getMerged()<<endl;
        //cout << cheatState<<endl;
        
        if (cheatActivated && team.getMerged() && !clkRestarted)
        {
			clkRestarted = true;
            //cout << "clk retsarted ";
            cheatClk.restart();
        }
        if (cheatActivated && !team.getMerged())
        {
            //cout << "(Merging right now)\n";
            beingMerged = true;
            team.merge(level[levelIndex]->getLvl());
        }
        else if(!cheatActivated)
            beingMerged = false;
        if(cheatActivated && team.getMerged() && clkRestarted && cheatClk.getElapsedTime().asSeconds() > 10)
        {
            beingMerged = false;
			clkRestarted = false;
            cheatActivated = false;
			team.setMerged(false);
            cheatState = 0;
            team.setmergedCount(0);
            team.setPlayerIndex(tempPlayerIndex);
		}
        if (cheatActivated && team.getMerged())
        {
            beingMerged = false;
        }

        // cout << "level = " << levelIndex<<endl;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            wantToReturnToMenu = true;
            audio->stopMusic();
            playMusic = false;
            return true;
        }

        if (levelIndex == 3)
        {
            team.setplayerIndex(0);
        }
        if (!gameOver && !beingMerged)
        {
            if (team.getPlayer()[team.getPlayerIndex()]->getOnGround())
            {
                team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack() = false;
                team.getPlayer()[team.getPlayerIndex()]->getTempVelocityY() = -7;
                team.getSpaceCount() = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack())
            {
                if (checkCollision(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()]->getx(), team.getPlayer()[team.getPlayerIndex()]->gety(), 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()]->getx(), team.getPlayer()[team.getPlayerIndex()]->gety() + team.getPlayer()[team.getPlayerIndex()]->getPheight() - 1, 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()]->getx() - 15, team.getPlayer()[team.getPlayerIndex()]->gety() + team.getPlayer()[team.getPlayerIndex()]->getPheight() / 2, 14, level[levelIndex]->getWidth()) && team.getPlayer()[team.getPlayerIndex()]->getx() > 0)
                {
                        team.getPlayer()[team.getPlayerIndex()]->moveLeft(level[levelIndex]->getLvl(), level[levelIndex]->getWidth(), level[levelIndex]->getFriction());
                 /*   if (buffer_start > 4 * 64 && team.getPlayer()[team.getPlayerIndex()]->getx() <= buffer_start)
                    {
                        buffer_start = team.getPlayer()[team.getPlayerIndex()]->getx();
                        buffer_end = buffer_start + 320;
                        offset_x += team.getPlayer()[team.getPlayerIndex()]->getVelocityX();
                    }*/
                    leftRight = true;
                    left = true;
                    right = false;
                }
                else
                {
                    if (!checkCollision(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()]->getx(), team.getPlayer()[team.getPlayerIndex()]->gety(), 14, level[levelIndex]->getWidth()))
                    {
                        team.getPlayer()[team.getPlayerIndex()]->executePushingLeft();
                        team.getPlayer()[team.getPlayerIndex()]->getVelocityX() = 0;
                    }
                    if (team.getPlayer()[team.getPlayerIndex()]->getVelocityY() <= 0)
                        team.getPlayer()[team.getPlayerIndex()]->getVelocityY() = 15;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack())
            {
                if (checkCollision(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()]->getx() + team.getPlayer()[team.getPlayerIndex()]->getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()]->gety(), 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()]->getx() + team.getPlayer()[team.getPlayerIndex()]->getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()]->gety() + team.getPlayer()[team.getPlayerIndex()]->getPheight() - 1, 14, level[levelIndex]->getWidth()) && checkCollision(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()]->getx() + team.getPlayer()[team.getPlayerIndex()]->getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()]->gety() + team.getPlayer()[team.getPlayerIndex()]->getPheight() / 2, 14, level[levelIndex]->getWidth()))
                {

                    team.getPlayer()[team.getPlayerIndex()]->moveRight(level[levelIndex]->getLvl(), level[levelIndex]->getWidth(), level[levelIndex]->getFriction());
                    leftRight = true;
                    right = true;
                    left = false;
                }
                else
                {
                    if (!checkCollision(level[levelIndex]->getLvl(), team.getPlayer()[team.getPlayerIndex()]->getx() + team.getPlayer()[team.getPlayerIndex()]->getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()]->gety(), 14, level[levelIndex]->getWidth()))
                    {
                        team.getPlayer()[team.getPlayerIndex()]->executePushingRight();

                        team.getPlayer()[team.getPlayerIndex()]->getVelocityX() = 0;
                    }
                    if (team.getPlayer()[team.getPlayerIndex()]->getVelocityY() >= 0)
                        team.getPlayer()[team.getPlayerIndex()]->getVelocityY() = 15;
                }
            }
            else
            {

                left = false;;
                right = false;
                leftRight = false;
                if (!team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack())
                {
                    team.getPlayer()[team.getPlayerIndex()]->decelerate(level[levelIndex]->getLvl(), level[levelIndex]->getWidth(), level[levelIndex]->getFriction());
                }
                else
                {
                    team.getPlayer()[team.getPlayerIndex()]->getVelocityX() = 0;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack())
            {
                team.jump();

                if (audio && jumpSFXClock.getElapsedTime().asSeconds() >= 3.f) {
                    audio->playSound(audio->getJump());
                    jumpSFXClock.restart();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack() && Akey.getElapsedTime().asMilliseconds() > 500)
            {
                team.switchLeader();
                tempPlayerIndex = team.getPlayerIndex();
                Akey.restart();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack())
            {
                team.useSpecial(level[levelIndex]->getLvl(), 14, level[levelIndex]->getWidth());
                team.getPlayer()[team.getPlayerIndex()]->getSpecialAbiltyUsed() = true;
            }
            if (team.getPlayer()[team.getPlayerIndex()]->getSpecialAbiltyUsed() == true && (team.getPlayerIndex() == 0 || team.getPlayerIndex() == 3))
            {
                team.getPlayer()[team.getPlayerIndex()]->spinDash(level[levelIndex]->getLvl(), level[levelIndex]->getWidth(), level[levelIndex]->getFriction());
               
            }
            if (team.getSpacePressed())
            {
                if(team.getPlayerIndex() != 3)
                {
                    if (team.getPlayerIndex() != 1)
                    {
                        team.getPlayer()[team.getPlayerIndex()]->getAnimationIndex() = UPR;
                    }
                    else if (team.getSpaceCount() < 10)
                    {
                        team.getPlayer()[team.getPlayerIndex()]->getAnimationIndex() = UPR;
                    }
                    leftRight = false;
                }
                else if(team.getPlayer()[team.getPlayerIndex()]->getAnimationIndex() != JUMPR && team.getPlayer()[team.getPlayerIndex()]->getAnimationIndex() != JUMPL)
                {
                    if (left)
                        team.getPlayer()[team.getPlayerIndex()]->setAnimationIndex(UPL);
                    else if (right)
                        team.getPlayer()[team.getPlayerIndex()]->setAnimationIndex(UPR);
                }
            }
            if (!team.getPlayer()[team.getPlayerIndex()]->getVelocityX() && !team.getPlayer()[team.getPlayerIndex()]->getVelocityY())
            {
                //cout << "Player is Still!!!!!\n";;
                team.getPlayer()[team.getPlayerIndex()]->getAnimationIndex() = STILL;
            }
            if (!team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack())
                team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack() = collisionCheckWithSpikes(level[levelIndex]->getLvl(), offset_y, hit_box_factor_y, hit_box_factor_x, team.getPlayer()[team.getPlayerIndex()]->getPheight(), team.getPlayer()[team.getPlayerIndex()]->getPwidth(), team.getPlayer()[team.getPlayerIndex()]->getx(), team.getPlayer()[team.getPlayerIndex()]->gety(), 64, team.getPlayer()[team.getPlayerIndex()]->getVelocityY(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth());
            if (team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack())
            {
                team.getPlayer()[team.getPlayerIndex()]->getx() -= 6;
                team.getPlayer()[team.getPlayerIndex()]->gety() += team.getPlayer()[team.getPlayerIndex()]->getTempVelocityY();
                team.getPlayer()[team.getPlayerIndex()]->getTempVelocityY() += team.getPlayer()[team.getPlayerIndex()]->getTempGravity();
                if (team.getPlayer()[team.getPlayerIndex()]->getTempVelocityY() >= 0)
                {
                    team.getPlayer()[team.getPlayerIndex()]->playerVirtualGravity(level[levelIndex]->getLvl(), offset_y, offset_x, 64, team.getSpacePressed(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), gameOver);
                }
                if (!gameOverRestarted && gameOver)
                {
                    gameOverClock.restart();
                    gameOverRestarted = true;
                }
                makeInvincible.restart();
            }
            if (!team.getPlayer()[team.getPlayerIndex()]->getHasKnockedBack())
                team.getPlayer()[team.getPlayerIndex()]->player_gravity(level[levelIndex]->getLvl(), offset_y, offset_x, 64, team.getSpacePressed(), level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), gameOver);
            if (!gameOverRestarted && gameOver)
            {
                gameOverClock.restart();
                gameOverRestarted = true;
            }
            team.storePath();
            team.autoMoveFollowers(level[levelIndex]->getLvl(), offset_x, level[levelIndex]->getWidth());
            if (levelIndex != 0 && levelIndex != 3 && level[levelIndex]->getMoveable()->move(team.getPlayer()[team.getPlayerIndex()]->getx(), team.getPlayer()[team.getPlayerIndex()]->gety(), team.getPlayer()[team.getPlayerIndex()]->getPwidth(), team.getPlayer()[team.getPlayerIndex()]->getPheight(), team.getPlayer()[team.getPlayerIndex()]->getOnGround()))
            {
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
        //cout << " \n\nbuffer start = " << buffer_start << " | buffer end = " << buffer_end << "| offsetx = " << offset_x<<"\n\n";

        updateBufferZone();

        // draw_bg(window, backGroundSprite, offset_x);
        level[levelIndex]->draw_bg(window);
        if (levelIndex != 3 && !gameOver)
            level[levelIndex]->getMoveable()->draw(window, offset_x);

        // display_level(window, level[levelIndex]->getHeight(), level[levelIndex]->getWidth(), level[levelIndex]->getLvl(), walls, 64, offset_x);
        level[levelIndex]->display_level(window, 64, offset_x);
        if (levelIndex != 3 && !gameOver)
            for (int i = 0; i < level[levelIndex]->getFallingCount(); i++)
                level[levelIndex]->getFalling()[i]->draw(window, offset_x,levelIndex);

   
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
                    extraLifeGained = true;
                    extraClk.restart();
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
        if (extraLifeGained && extraClk.getElapsedTime().asMilliseconds() < 4000)
        {
            //cout << "Extra Life";
            window.draw(ExtraLife);
        }
        else extraLifeGained = false;
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
			//cout << "IN check timer\n";
            gameOver = true;
            if (!gameOverRestarted)
            {
                gameOverClock.restart();
                gameOverRestarted = true;
            }
        }
        //cout << "LIVE ARE " << hud.getLives() << endl;
        if (!gameOver)
            team.animate();
        if(!cheatActivated || (cheatActivated && !team.getMerged()))
        {
            if (levelIndex != 3)
                team.draw(window, offset_x);
            else
                team.drawSonic(window, offset_x);
        }
        if (cheatActivated && team.getMerged())
        {
            team.drawSpecial(window,offset_x);
        }
        hud.draw(window,team.getPlayerIndex());
        if (levelIndex != 3)
            for (int i = 0; i < 8; i++)
            {
                level[levelIndex]->getFalling()[i]->shouldItActivate(team.getPlayer()[team.getPlayerIndex()]->getx());
                if (level[levelIndex]->getFalling()[i]->getActivated())
                {
                    level[levelIndex]->getFalling()[i]->fall();
                }
            }
        if (levelIndex == 3)
        {
			//cout << "egg stinger in game = " << level[levelIndex]->getStinger()->alive() << "\n";
        }
        level[levelIndex]->drawEnemies(window, offset_x);
      
        if (hud.getLives() <= 0 || gameOver)
        {
            if (levelIndex == 3)
            {
               /* cout << "game over hugai h level 3 k bad ";
                cout << "GameOver " << gameOver;
				cout << hud.getLives() << endl;*/
            }
            gameOver = true;
            if (!gameOverRestarted)
            {
                gameOverClock.restart();
                gameOverRestarted = true;
            }
            window.draw(gameover);
        }
        if (cheatActivated)
        {
            //cout << "drawing";
            int rem = 10 - (int)cheatClk.getElapsedTime().asSeconds();
            CheatTime.setString("Time Remaining : " + to_string(rem));
            window.draw(CheatTime);
            window.draw(cheatCodeText);
        }
        if (specialBoostUsed)
        {
           
            int rem = 6 - (int)specialBoostClock.getElapsedTime().asSeconds();
            specialBoost.setString("Time Remaining : " + to_string(rem));
           
            window.draw(specialBoost);
            window.draw(SpecialBoostText);

        }
        /*draw_buffer(window, bufferSpriteStart, buffer_start - offset_x);
        draw_buffer(window, bufferSpriteEnd, buffer_end - offset_x);*/
       /* cout << "\n\nin play \n";
        cout << "buffer start = " << buffer_start << " | buffer end = " << buffer_end << "| offsetx = " << offset_x;
        bufferSpriteEnd.setPosition(buffer_end - offset_x, 500);
        bufferSpriteStart.setPosition(buffer_start - offset_x, 500);
        bufferSpriteEnd.setPosition(buffer_end-offset_x, 500);
		window.draw(bufferSpriteStart);
		window.draw(bufferSpriteEnd);*/
        if (gameOver && gameOverClock.getElapsedTime().asMilliseconds() > 3000)
            return true;
        if (levelIndex == 3)
        {
            //cout<<"death of egg stinger done ? "<<level[3]->getStinger()->deathDone();
            cout << endl;
        }
        if (levelIndex == 3 && level[3]->getStinger()->deathDone())
        {
            if (!youwinrestarted)
            {
				youWinClk.restart();
				youwinrestarted = true;
            }
        }
        
		//cout << "youwinrestarted = " << youwinrestarted << endl;
        if (youwinrestarted && youWinClk.getElapsedTime().asMilliseconds() > 5000)
        {
            return true;
        }
		if (youwinrestarted && youWinClk.getElapsedTime().asMilliseconds() < 5000)
		{
			window.draw(youWin);
		}
        drawGoalPost(window, offset_x);
            //cout << "\n\nIn play end veloctyx = " << team.getPlayer()[team.getPlayerIndex()]->getVelocityX()<<"\n\n";
      // Handle goalpost animation and then level transition
        int goalX = level[levelIndex]->getLevelEnd();
        int playerX = team.getPlayer()[team.getPlayerIndex()]->getx();

        if (abs(playerX - goalX) < 10 || goalPostSpinning || goalPostAnimationDone)
        {
            if (!goalPostSpinning && !goalPostAnimationDone)
            {
                goalPostSpinning = true;
                goalPostFrameIndex = 0;
                goalPostHoldStarted = false;
                goalPostClock.restart();
                audio->playSound(audio->getGoalPostSpin());
            }

            handleGoalPostAnimation(window, offset_x);

            if (goalPostAnimationDone && !transitionRestarted)
            {
                levelTransitionClock.restart();
                transitionRestarted = true;
            }

            if (transitionRestarted)
            {
                if (levelTransitionClock.getElapsedTime().asSeconds() < 2.f)
                {
                    window.draw(levelTransitionSprite);
                    transitionText.setString(levelQuotes[levelIndex + 1]);
                    window.draw(transitionText);
                }
                else
                {
                    updateLevel();
                    transitionRestarted = false;
                    goalPostFrameIndex = 0;
                    goalPostAnimationDone = false;
                }
            }
        }



        return false;
    }
    void drawGoalPost(sf::RenderWindow& window, int offset_x)
    {
        int goalPostX = level[levelIndex]->getLevelEnd();
        int goalPostY = level[levelIndex]->getLevelEndY();

        // Show idle frame if not spinning yet
        if (!goalPostSpinning)
        {
            goalPostSprite.setTextureRect(sf::IntRect(0, 0, 64, 53)); // first frame
        }

        goalPostSprite.setPosition(goalPostX - offset_x, goalPostY);
        window.draw(goalPostSprite);
    }

    void handleGoalPostAnimation(sf::RenderWindow& window, int offset_x)
{
    int goalPostX = level[levelIndex]->getLevelEnd();
    int goalPostY = level[levelIndex]->getLevelEndY();

    if (!goalPostSpinning)
    {
        goalPostSprite.setTextureRect(goalPostFrames[0]);
        goalPostSprite.setScale(1.5, 1.5);
    }
    else
    {
        // If all frames shown
        if (goalPostFrameIndex >= goalPostFrames.size() - 1)
        {
            if (!goalPostHoldStarted)
            {
                goalPostHoldClock.restart();
                goalPostHoldStarted = true;
            }

            if (goalPostHoldClock.getElapsedTime().asSeconds() > 2.0f)
            {
                goalPostSpinning = false;
                goalPostAnimationDone = true;
            }
        }
        else if (goalPostClock.getElapsedTime().asMilliseconds() > 40)
        {
            goalPostFrameIndex++;
            goalPostSprite.setTextureRect(goalPostFrames[goalPostFrameIndex]);
            goalPostSprite.setScale(1.5, 1.5);
            goalPostClock.restart();
        }
    }

    goalPostSprite.setPosition(goalPostX - offset_x, goalPostY);
    window.draw(goalPostSprite);
}



    void setLevel(int l)
    {
        //audio->playLevelMusicByIndex(l);
		levelIndex = l;
        level[levelIndex]->setAudio(audio);
        if (levelIndex != 3)
            level[levelIndex]->loadAndPlaceCollectibles();
        if(levelIndex == 3)
        {
            for (int i = 0;i < 3;i++)
            {
                team.getPlayer()[i]->getx() = 450;
                team.getPlayer()[i]->gety() = 400;
                team.getPlayer()[i]->getVelocityY() = 15;
                team.getPlayer()[i]->setGravity(1);
            }
        }
        team.getPlayer()[team.getPlayerIndex()]->getOnGround() = true;
        if (levelIndex == 2)
        {
            for (int i = 0;i < 3;i++)
            {
                team.getPlayer()[i]->setGravity(0.6);
            }
        }
        buffer_start = 8 * 64;
        buffer_end = 13 * 64;
        offset_x = 0;
        hud.resetTimer();
        levelTimer.restart();
        if (levelIndex == 3)
        {
            cout << "LEVEL $ it is  \n ";
        }
    }
    
    /*
    ~Game()
    {
        for (int i = 0; i < 4; ++i)
        {
            delete level[i];
        }
        delete[] level;
    }
    */
    //std::string cheatBuffer;  // Declare somewhere accessible (maybe in Game or StateManager)
    //bool cheatActivated = false;

    //int cheatState = 0;  // Initial state
    //const std::string cheatCode = "OOP";
    void updateBufferZone()
    {
        float tempX = team.getPlayer()[team.getPlayerIndex()]->getx();
        float tempV = team.getPlayer()[team.getPlayerIndex()]->getVelocityX();
        float tempBufferStart = buffer_start - offset_x;
        float tempBufferEnd = buffer_end - offset_x;
        float Pwidth = 24 * 2.5;
        // Move buffer when player crosses right boundary
        if (tempX +  Pwidth > buffer_end && buffer_end < (level[levelIndex]->getWidth() - 5) * 64)
        {
            float overshoot = (tempX + Pwidth) - buffer_end;

            buffer_end += overshoot;
            buffer_start += overshoot;

            offset_x += overshoot;
        }
        // Move buffer when player crosses left boundary
        else if (tempX < buffer_start && buffer_start > 6 * 64)
        {
            float overshoot = buffer_start - tempX;

            buffer_start -= overshoot;
            buffer_end -= overshoot;

            offset_x -= overshoot;

            if (offset_x < 0)
                offset_x = 0;
        }

        // Clamp offset to stay within level bounds
        float maxOffset = (level[levelIndex]->getWidth() * 64) - 900;
        if (offset_x < 0)
            offset_x = 0;
        if (offset_x > maxOffset)
            offset_x = maxOffset;

        //cout << "x = " << tempX << " | Buffer Start = " << buffer_start << " | Buffer End = " << buffer_end << " | Offset_x = " << offset_x << endl;
    }

    void handleInput(Event& event)
    {
        if (event.type == Event::TextEntered)
        {
            char entered = static_cast<char>(event.text.unicode);
            if (isalpha(entered))
            {
                entered = toupper(entered); // Case insensitive

                switch (cheatState)
                {
                case 0:
                    //cout << "case 0";
                    if (entered == 'O')
                        cheatState = 1;
                    else
                        cheatState = 0; // stay/reset
                    break;

                case 1:
                    //cout << "case 1";

                    if (entered == 'O')
                        cheatState = 2;
                    else
                        cheatState = 0;
                    break;

                case 2:
                    //cout << "case 2";

                    if (entered == 'P')
                    {

                        cheatState = 3;
						cheatActivated = true; // Activate the cheat
                        tempPlayerIndex = team.getPlayerIndex();
                        team.setPlayerIndex(3);
                        //cout << "CHeat code has been actiaved \n";
                        // activateCheatPlayer();
                        cheatState = 0; // Reset for next detection
                    }
                    else if (entered == 'O')
                    {
                        cheatState = 2; // Could stay in state 2 if O repeats, depends on desired behavior
                    }
                    else
                    {
                        cheatState = 0;
                    }
                    break;
                }
            }
        }
    }
};

