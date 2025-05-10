#pragma once
#include <fstream>
#include "Level.h"
#include "Crabmeat.h"
#include "Beebot.h"
#include "MoveablePlatform.h"
#include "FallingPlatform.h"
#include "HUD.h"

class Level1 : public Level
{
    FallingPlatform** falling;
    MoveablePlatform* moveable;











    int crabCount;
    int crab_start;
    int crab_end;
    Crabmeat* crab;

    int beeCount;
    int bee_start;
    int bee_end;
    bool* occupiedColumns;
    Beebot* beebot;

    int motobugCount;
    int motobug_start;
    int motobug_end;
    Motobug* motobugs;


    int batbrainCount;
    int batStart;
    int batEnd;
    Batbrain* bats;


    Enemy** enemies;
    int enemyCount;
    int TotalEnemyCount;
    int j_start;
    int cell_size;


public:
    Level1()
    {
        friction = 0.3;
        cell_size = 64;
        height = 14;
        width = 200;
        lvl = new char* [height];
        for (int i = 0; i < height; i++)
        {
            lvl[i] = new char[width];
        }
        designlvl("lvl1.txt");
/*<<< HEAD
        crabCount = 5;
        crabIndex = 0;
        crabs = new Crabmeat * [crabCount];
        for (int i = 0; i < crabCount; i++)
        {
            crabs[i] = new Crabmeat();
        }
        crab_start = 5;
        crab_end = 9;
        for (int i = 0; i < crabCount; ++i)
        {
            crabs[i]->getCrabCoordinates(lvl, height, width, crab_start, crab_end);
        }
        crabs[0]->move_crabs(crabs, crabIndex, crabCount, cell_size);
        beeCount = 5;
        beeIndex = 0;
        beebots = new Beebot * [beeCount];
        for (int i = 0; i < beeCount; i++)
        {
            beebots[i] = new Beebot();
        }
        bee_start = 5;
        bee_end = 8;
        beebots[0]->getBeebotCoordinates(lvl, height, width, bee_start, bee_end);
        beebots[0]->move_beebots(beebots, beeIndex, beeCount, cell_size);
=======*/

        enemyCount = 0;
        TotalEnemyCount = 17;
        enemies = new Enemy * [TotalEnemyCount];

        j_start = 5;
        crab_start = 5;
        crab_end = 9;
        crabCount = 5;

        for (int i = 0; i < crabCount; i++) {

            crab = new Crabmeat();

            if (crab->getCrabCoordinates(lvl, height, width, crab_start, crab_end, j_start))
            {
                crab->move_crabs(cell_size);
                enemies[enemyCount++] = crab;
            }
        }


        j_start = 7;
        bee_start = 5;
        bee_end = 8;
        beeCount = 5;
        occupiedColumns = new bool[width]();

        for (int i = 0; i < beeCount; i++) {

            beebot = new Beebot();

            if (beebot->getBeebotCoordinates(lvl, height, width, bee_start, bee_end, j_start, occupiedColumns))
            {
                beebot->move_beebots(cell_size);
                enemies[enemyCount++] = beebot;
            }
        }


        j_start = 0;
        motobug_start = 8;
        motobug_end = 12;
        motobugCount = 5;


        for (int i = 0; i < motobugCount; i++) {

            motobugs = new Motobug();

            if (motobugs->getMotobugCoordinates(lvl, height, width, motobug_start, motobug_end, j_start))
            {
                motobugs->move_motobugs(cell_size);
                enemies[enemyCount++] = motobugs;
            }

        }
        
        batbrainCount = 2;
        batStart = 0;
        batEnd = 0;

        for (int i = 0; i < batbrainCount; ++i) {

            bats = new Batbrain();

            if (bats->getBatbrainCoordinates(lvl, height, width, batStart, batEnd, cell_size)) {
                enemies[enemyCount++] = bats;
            }

        }



        /*

>>>>>>> 6da9bdbf96a072d5143329fde596d3864afcf47d
        motobugCount = 5;
        motobugIndex = 0;
        motobugs = new Motobug * [motobugCount];
        for (int i = 0; i < motobugCount; i++)
        {
            motobugs[i] = new Motobug();
        }
        motobug_start = 10;
        motobug_end = 12;
        motobugs[0]->getMotobugCoordinates(lvl, height, width, motobug_start, motobug_end);
        motobugs[0]->move_motobugs(motobugs, motobugIndex, motobugCount, cell_size);
<<<<<<< HEAD
=======
        */


//>>>>>>> 6da9bdbf96a072d5143329fde596d3864afcf47d
        falling = new FallingPlatform * [8];
        for (int i = 0, f = 32; i < 8; i++, f++)
            falling[i] = new FallingPlatform(64 * f, 500);
        moveable = new MoveablePlatform(1000, 450, 850, 1500);
        levelEnd = 195 * 64;
    }
    MoveablePlatform* getMoveable() override
    {
        return moveable;
    }
    virtual FallingPlatform** getFalling()
    {
        return falling;
    }
    float getLevelEnd()
    {
        return levelEnd;
    }
    char getMapValues(int val)
    {
        switch (val)
        {
        case 0:
            return 's';
        case 1:
            return 'q';
        case 2:
            return 'w';
        case 3:
            return 'e';
        case 4:
            return 'p';
        case 5:
            return 'r';
        case 6:
            return 'i';
        case 9:
            return 'b';

        default:
            return 's';
        }
    }
    void designlvl(const char* filename)
    {
        //cout << "\n\n\nIn desgin function\n\n\n";

        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int wall;
                file >> wall;
                lvl[i][j] = getMapValues(wall);
                //cout << "lvl[" << i << "][" << j << "] = " << lvl[i][j] << endl;
            }
            //cout << endl;
        }
        file.close();
    }


    void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player, HUD& hud, bool& gameOver) override
    {
        for (int i = 0; i < enemyCount; ++i)
        {
            if (!enemies[i]->alive())
                continue;

            enemies[i]->update(lvl, player, cell_size, hasKnockedBack, tempVelocity, onGround, indexAnimation, hud, gameOver);

            enemies[i]->drawExtra(window, offset_x);
        }
    }

    void drawEnemies(RenderWindow& window, float offset_x) override
    {
        for (int i = 0; i < enemyCount; ++i)
        {
            if (enemies[i]->alive())
                enemies[i]->draw(window, offset_x);
        }
    }

 
};