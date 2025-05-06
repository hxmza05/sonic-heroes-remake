#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"
#include "Sonic.h"
#include "TailedFox.h"
#include "Knuckles.h"
#include "time.h"
class Team
{
    Player** team;
    int playerIndex;
    // stores x and y coordinates of the leader
    int** leadersPath;
    float *leadersVelocityY;
    int pathIndex;
    bool spacePressed;
    bool spacePressedTwice;
    int spaceCount;

public:
    Team()
    {
        team = new Player * [3];
        team[0] = new Sonic();
        team[1] = new TailedFox();
        team[2] = new Knuckles();
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
    }
    int getPlayerIndex()
    {
        return playerIndex;
    }
    /*void switchPlayer()
    {
        if (playerIndex == 2)
        {
            playerIndex = 0;
            return;
        }
        playerIndex++;

    }*/
    Player** getPlayer()
    {
        return team;
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
    void switchLeader()
    {
    }
    void autoMoveFollowers(char** lvl)
    {
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
                if (playerIndex == 1 && team[1]->getAnimationIndex() == JUMPR)
                {
                    float dummy = 0;
                    float dummy2 = 0;
                    bool dummybool = true;
                    for (int j = 0, h = team[1]->getPheight(); j < 3; j += 2, h += 40)
                    {
                        if (team[j]->getAnimationIndex() == JUMPL || team[j]->getAnimationIndex() == JUMPR || team[j]->getAnimationIndex() == GLIDEL || team[j]->getAnimationIndex() == GLIDER)
                        {
                            if(team[j]->getAnimationIndex() == JUMPL || team[j]->getAnimationIndex() == JUMPR )
                            {
                                if(canFollowerGlide(team[j]->getx(), team[j]->gety(), team[j]->getPwidth(), team[1]->getx(), team[1]->gety(), team[1]->getPheight(), team[1]->getPwidth()))
                                {
                                    makeThemGlide(j, h);
                                }
                                else
                                {
									
                                }
                            }
                            else 
                            {
                                makeThemGlide(j, h);
                            }
                            if (team[j]->checkFeet(lvl)  && team[j]->getAnimationIndex() != STILL)
                            {
                                team[j]->getAnimationIndex() = STILL;
                                team[j]->getStates()[STILL][0].RunAnimation();
                            }
                            // team[i]->glideAndFollowTails();
                        }
                        else
                        {
                            //team[j]->player_gravity(lvl, dummy, dummy2, 64, dummybool);
                     /*       cout << "Velcoty for ";
                            if(j == 0)
								cout << "Sonic";
							else cout << "Knuckles";
                            cout << " is = " << team[j]->getVelocityY()<<"\n\n\n";*/
                        }
                    }
                }
                else
                {
                    // team[i]->updateDelay();
                    team[i][0].autoMove(leadersPath[team[i][0].getDelayinFollow()][0] - 16, leadersPath[team[i][0].getDelayinFollow()][1], lvl);
					team[i][0].getVelocityY() = -19;
                   /* if (team[playerIndex]->getAnimationIndex() == STILL)
                    {
                        team[i]->getAnimationIndex() = STILL;
                    }*/
                    //if()
					//cout << "\n\n\nVelcotuy when automvoing  = " << team[i][0].getVelocityY() << "\n\n\n";

                }
                // cout << "Path index LEader's = " << pathIndex << "----- tailed fox's = " << team[1][0].getDelayinFollow() << "----- knuckel's = " << team[2][0].getDelayinFollow() << "\n";
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
            team[j]->getStates()[GLIDER][0].RunAnimation();
        }
        team[j]->getx() = team[1]->getx();
        team[j]->gety() = team[1]->gety() + h;
    }
    bool canFollowerGlide( int playerLeft, int playerTop, int playerWidth, int tailed_x, int tailed_y, int tailedHeight, int tailedWidth)
    {
        int playerRight = playerLeft + playerWidth;
        int tailedBottom = tailed_y + tailedHeight;
        int tailedRight = tailed_x + tailedWidth;

        const int verticalMargin = 10;

        bool verticalAligned = playerTop <= tailedBottom + verticalMargin;
        bool horizontalOverlap = playerRight > tailed_x && playerLeft < tailedRight;

        bool cond = verticalAligned && horizontalOverlap;

        //cout << "\n\nCan Glide  = " << cond;
        return cond;
    }
    /*void runAnimation()
    {
        for (int i = 0;i < 3;i++)
        {
            team[i].
        }
    }*/
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
        /*if (spacePressed && !spacePressedTwice)
        {
            spacePressedTwice = true;
        }*/
        spaceCount++;
        team[playerIndex]->moveUp(spacePressed, spaceCount);
        spacePressed = true;
    }
    ~Team()
    {
        for (int i = 0; i < 3; i++)
        {
            delete team[i];
        }
        delete[] team;
    }
};