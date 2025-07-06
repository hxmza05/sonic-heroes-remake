#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"
#include "Sonic.h"
#include "TailedFox.h"
#include "Knuckles.h"
#include"SpecialCharacter.h"
#include "time.h"
#include "Audio.h"

class Team
{
    Player** team;
    bool merged;
	int mergedCount;
    int playerIndex;
    // stores x and y coordinates of the leader
    int** leadersPath;
    float* leadersVelocityY;
    int pathIndex;
    bool spacePressed;
    bool spacePressedTwice;
    int spaceCount;
    bool isFlying;
    int isNotFlyingCount;


    
    Audio* audio;

public:
    Team()
    {
		audio = nullptr;
		mergedCount = 0;
        merged = false;
        isNotFlyingCount = 0;
        // haveBeenPutDown.restart();
        isFlying = false;
        team = new Player * [4];
        team[0] = new Sonic();
        team[1] = new TailedFox();
        team[2] = new Knuckles();
        team[3] = new SpecialCharacter();
        playerIndex = 0;
        leadersPath = new int* [100];
        leadersVelocityY = new float[100];
        for (int i = 0; i < 100; i++)
        {
            leadersPath[i] = new int[2];
        }
        pathIndex = 1;
        spacePressed = false;
        spacePressedTwice = false;
        spaceCount = 0;
        // reset = false;
    }
    int getPlayerIndex()
    {
        return playerIndex;
    }
    void setplayerIndex(int a)
    {
        playerIndex = a;
    }
    void switchLeader()
    {
        pathIndex = 0;
        for (int i = 0; i < 3; i++)
        {
            if (i == playerIndex)
                continue;
            switch (i)
            {
            case 0:
                team[0]->getDelayinFollow() = 25;
                break;
            case 1:
                team[1]->getDelayinFollow() = 28;
                break;
            case 2:
                team[2]->getDelayinFollow() = 30;
            }
            team[i]->setHasStartedFollowing(false);
            team[i]->getVelocityX() = 0;
            team[i]->getVelocityY() = 0;
            team[i]->getOnGround() = true;
        }
        if (playerIndex == 2)
        {
            playerIndex = 0;
            return;
        }
        playerIndex++;
    }
    Player** getPlayer()
    {
        return team;
    }
    int getmergedCount()
    {
		return mergedCount;
    }
    void setmergedCount(int m)
    {
        mergedCount = m;
	}

    int& getIsnotFlyingcount()
    {
        return isNotFlyingCount;
    }
    int** getLeadersPath()
    {
        return leadersPath;
    }
    int getPathIndex()
    {
        return pathIndex;
    }
    bool& getSpacePressed()
    {
        return spacePressed;
    }
    bool& getspaceTwice()
    {
        return spacePressedTwice;
    }
    int& getSpaceCount()
    {
        return spaceCount;
    }
    bool getMerged()
    {
        return merged;
	}
    void setMerged(bool m)
    {
        merged = m;
	}
    void setAudio(Audio* a) 
    { 
        audio = a; 
        for (int i = 0; i < 3; ++i) {
            team[i]->setAudio(a);
        }
    }
    void autoMoveFollowers(char** lvl, float offsetx, int width)
    {
        team[3]->setCoords(team[playerIndex]->getx(), team[playerIndex]->gety());
        for (int i = 0; i < 3; i++)
        {
            if (i == playerIndex)
                continue;
            if (team[i]->getHasStartedFollowing() == false)
            {
                team[i]->checkDelayNow(pathIndex);
            }
            else
            {
                team[i]->updateDelay();
                //    JUMPR is for flying here
                if (playerIndex == 1 && (team[1]->getAnimationIndex() == JUMPR || (team[1]->getAnimationIndex() == JUMPL)))
                {
                    isFlying = true;
                    pathIndex = 0;
                    float dummy = 0;
                    float dummy2 = 0;
                    bool dummybool = true;
                    for (int j = 0, h = team[1]->getPheight(); j < 3; j+=2, h += 64)
                    {
                        if (team[j]->getAnimationIndex() == JUMPL || team[j]->getAnimationIndex() == JUMPR || team[j]->getAnimationIndex() == GLIDEL || team[j]->getAnimationIndex() == GLIDER)
                        {
                            if (team[j]->getAnimationIndex() == JUMPL || team[j]->getAnimationIndex() == JUMPR)
                            {
                                if (canFollowerGlide(team[j]->getx(), team[j]->gety(), team[j]->getPwidth(), team[1]->getx(), team[1]->gety(), team[1]->getPheight(), team[1]->getPwidth()))
                                {
                                    makeThemGlide(j, h);
                                }
                                else
                                {
                                    team[j]->figureItOutYourself(team[playerIndex]->getx(), lvl, offsetx, width);
                                }
                            }
                            else
                            {
                                makeThemGlide(j, h);
                            }
                            if (team[j]->checkFeet(lvl, 14, width) && team[j]->getAnimationIndex() != STILL)
                            {
                                team[j]->getAnimationIndex() = STILL;
                                team[j]->getStates()[STILL][0].RunAnimation();
                                team[j]->getHaveBeenPutDown().restart();
                            }
                        }
                        else
                        {

                            
                            if (team[j]->getHaveBeenPutDown().getElapsedTime().asSeconds() > 1)
                            {
                                team[j]->figureItOutYourself(team[playerIndex]->getx(), lvl, offsetx, width);
                            }
                        }
                    }
               
                }
                else
                
                {
                    if (playerIndex == 1 && isNotFlyingCount == 0 && isFlying && /*team[1]->getAnimationIndex() != UPR && team[1]->getAnimationIndex() != JUMPR &&*/ team[1]->getOnGround()/*&& team[1]->getAnimationIndex() == STILL*/)
                    {
                        
                        team[0]->setTailedCoords(team[1]->getx() - 5, team[1]->gety() + 10);
                        team[2]->setTailedCoords(team[1]->getx() - 5, team[1]->gety() + 10);
                        team[2]->getAnimationIndex() = BREAKR;
                        pathIndex = 0;
                        isNotFlyingCount++;
                    }
                    if (playerIndex == 1 && isFlying && playerIndex == 1 && isNotFlyingCount == 1)
                    {
                        int tempCount = 0;
                        if (team[0]->teleportToTailed())
                        {
                            tempCount++;
                        }
                        if (team[2]->teleportToTailed())
                        {
                            tempCount++;
                        }
                        if (tempCount == 2)
                        {
                            isFlying = false;
                            isNotFlyingCount = 0;
                            team[0]->getDelayinFollow() = 15;
                            team[2]->getDelayinFollow() = 20;
                            team[0]->setHasStartedFollowing(false);
                            team[2]->setHasStartedFollowing(false);
                            break;
                        }
                        break;
                    }
                    if (!(playerIndex == 1 && isFlying))
                    {
                        team[i][0].autoMove(leadersPath[team[i][0].getDelayinFollow()][0] - 16, leadersPath[team[i][0].getDelayinFollow()][1], lvl, 14, width);
                        team[i][0].getVelocityY() = -19;
                    }
                    
                }
            }
        }
    }
    void makeThemGlide(int j, int h)
    {
        // cout << "\n\n\nGliding outside as well";
        if (team[j]->getAnimationIndex() != GLIDER)
        {
            // cout << "\nGliding\n\n\n";
            team[j]->getAnimationIndex() = GLIDER;
            //team[j]->getStates()[GLIDER][0].RunAnimation();
        }
        team[j]->getx() = team[1]->getx();
        team[j]->gety() = team[1]->gety() + h + 5;
    }
    /* bool getReset()
     {
         return reset;
     }*/
    bool canFollowerGlide(int playerLeft, int playerTop, int playerWidth, int tailed_x, int tailed_y, int tailedHeight, int tailedWidth)
    {
        int playerRight = playerLeft + playerWidth;
        int tailedBottom = tailed_y + tailedHeight;
        int tailedRight = tailed_x + tailedWidth;

        const int verticalMargin = 10;

        bool verticalAligned = playerTop <= tailedBottom + verticalMargin;
        bool horizontalOverlap = playerRight > tailed_x && playerLeft < tailedRight;

        bool cond = verticalAligned && horizontalOverlap;

        // cout << "\n\nCan Glide  = " << cond;
        return cond;
    }
    void draw(RenderWindow& window, int offsetx)
    {

        for (int i = 2; i >= 0; i--)
        {
            if (i == playerIndex)
                continue;
            team[i][0].draw_player(window, team[i][0].getStates()[team[i][0].getAnimationIndex()][0].getSprites()[team[i][0].getStates()[team[i][0].getAnimationIndex()][0].getIndex()], offsetx);
            // team.getPlayer()[team.getPlayerIndex()][0].draw_player(window, team.getPlayer()[team.getPlayerIndex()][0].getStates()[team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex()][0].getSprites()[team.getPlayer()[team.getPlayerIndex()][0].getStates()[team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex()]->getIndex()],offset_x);
        }
        team[playerIndex][0].draw_player(window, team[playerIndex][0].getStates()[team[playerIndex][0].getAnimationIndex()][0].getSprites()[team[playerIndex][0].getStates()[team[playerIndex][0].getAnimationIndex()][0].getIndex()], offsetx);
    }
    void drawSpecial(RenderWindow& window, int offsetx)
    {
        team[3]->draw_player(window, team[3]->getStates()[team[3]->getAnimationIndex()]->getSprites()[team[3]->getStates()[team[3]->getAnimationIndex()]->getIndex()], offsetx);
    }
    void storePath()
    {
        leadersPath[pathIndex][0] = team[playerIndex]->getx();
        leadersPath[pathIndex][1] = team[playerIndex]->gety();
        leadersVelocityY[pathIndex] = team[playerIndex]->getVelocityY();
        pathIndex++;
        if (pathIndex == 100)
        {
            pathIndex = 0;
        }
    }
    void jump()
    {
        spaceCount++;
        team[playerIndex]->moveUp(spacePressed, spaceCount);
        spacePressed = true;
    }
    void useSpecial(char** lvl, int height, int width)
    {
        if(playerIndex != 1)
        {
            team[playerIndex]->useSpecialAbilty(lvl, height, width);
        }
    }
    void animate()
    {
        for (int i = 0; i < 4; i++)
        {
            team[i]->getStates()[team[i]->getAnimationIndex()]->RunAnimation();
        }
    }
    void checkYCoords()
    {
        for (int i = 0; i < 3; i++)
        {
            if (team[i]->gety() / 64 > 12)
            {
            }
        }
    }
    void setPlayerIndex(int n)
    {
        playerIndex = n;
    }
    void drawSonic(RenderWindow& window, float offset_x)
    {
        team[0]->draw_player(window, team[0]->getStates()[team[0]->getAnimationIndex()][0].getSprites()[team[0]->getStates()[team[0]->getAnimationIndex()][0].getIndex()], offset_x);
    }
    void useSpecialBoost()
    {
        if (playerIndex == 0)
        {
            team[0]->setAccelration(team[0]->getAcceleration() + 1.5);
            team[0]->setVelcotiyX(team[0]->getVelocityX() + 4);
        }
        if (playerIndex == 1)
        {
            team[1]->setFlyingTime(11);
        }
        if (playerIndex == 2)
        {
            team[2]->setInvincible(true);
        }
    }
    void undoBoost()
    {
        if (playerIndex == 0)
        {
            team[0]->setAccelration(0.2);
            team[0]->setVelcotiyX(2);
        }
        else if (playerIndex == 1)
        {
            team[1]->setFlyingTime(7);
        }
        else if (playerIndex == 2)
        {
            team[2]->setInvincible(false);
        }
    }
    void merge(char**lvl)
    {
        for (int i = 0;i < 3;i++)
        {
            if(i == playerIndex)
				continue;
            if (!checkIfMergedAlready(team[i]->getx(), team[i]->gety(), team[playerIndex]->getx(), team[playerIndex]->gety()))
            {
                team[i]->getAnimationIndex() = STILL;
                team[i]->updateCoords(team[playerIndex]->getx(), team[playerIndex]->gety());
                if (checkIfMergedAlready(team[i]->getx(), team[i]->gety(), team[playerIndex]->getx(), team[playerIndex]->gety()))
                    mergedCount++;
            }
            if (mergedCount == 2)
                merged = true;

           /* if()
            {

            }*/
			//team[i]->getAnimationIndex() = GLIDEL; // Assuming GLIDEL is the animation for merging
        }
    }
    void teleportToleader()
    {
        for (int i = 0;i < 3;i++)
        {
            if (i == playerIndex)
                continue;
            team[i]->updateCoords(team[playerIndex]->getx(),team[playerIndex]->gety());
        }
    }
    bool checkIfMergedAlready(float x, float y, float lx, float ly)
    {
        if (x == lx && y == ly)
            return true;
        return false;
    }
    

    
  /*  ~Team()
    {
        for (int i = 0; i < 3; i++)
        {
            delete team[i];
        }
        delete[] team;
    }*/
};