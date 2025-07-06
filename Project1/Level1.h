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

    int j_start;
    int cell_size;


public:
    Level1(Audio* ad) 
    {
        this->audio = ad;
        backGround.loadFromFile("Data/sonicbg6.png");
        backGroundSprite.setTexture(backGround);
        //hardcoded
        unsigned int bgWidth = 1280;
        unsigned int bgHeight = 720;
        scX = (float)1200 / bgWidth;
        scY = (float)900 / bgHeight;
        backGroundSprite.setScale(scX, scY);
      
         backGroundSprite.setScale(scX, scY);
        walls = new Sprite [4];
        wallText1.loadFromFile("Data/brick1.png");
        wallText2.loadFromFile("Data/brick1.png");
        wallText3.loadFromFile("Data/brick1.png");
        float scx = (float)64 / wallText1.getSize().x;
        float scy = (float)64 / wallText1.getSize().y;

        walls[0].setTexture(wallText1);
        walls[1].setTexture(wallText2);
        walls[2].setTexture(wallText3);
        walls[3].setTexture(wallText4);
        for (int i = 0;i < 3;i++)
        {
            walls[i].setScale(scx, scy);
        }
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


        enemyCount = 0;
        TotalEnemyCount = 15;
        enemies = new Enemy * [TotalEnemyCount];

        j_start = 5;
        crab_start = 5;
        crab_end = 9;
        crabCount = 5;

        for (int i = 0; i < crabCount; i++) {

            crab = new Crabmeat();
            crab->setAudio(audio);

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
            beebot->setAudio(audio);

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
            motobugs->setAudio(audio);

            if (motobugs->getMotobugCoordinates(lvl, height, width, motobug_start, motobug_end, j_start))
            {
                motobugs->move_motobugs(cell_size);
                enemies[enemyCount++] = motobugs;
            }

        }
        

        levelTimer = 900;
        falling = new FallingPlatform * [8];
        for (int i = 0, f = 32; i < 8; i++, f++)
            falling[i] = new FallingPlatform(64 * f, 500);
        moveable = new MoveablePlatform(1000, 450, 850, 1500);
        levelEnd = 195 * 64;
        levelEndY = 433;


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
        case 7:
            return 'j';
        case 8:
            return 'l';
        case 9:
            return 'b';

        default:
            return 's';
        }
    }
    void designlvl(const char* filename)
    {

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

    void setAudio(Audio* a) override {
        audio = a;
        //audio->playLevelMusicByIndex(audio->getLevel1Music());
    }

    void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player, HUD& hud, bool& gameOver) override
    {
        for (int i = 0; i < enemyCount; i++)
        {
            if (!enemies[i]->alive() && enemies[i]->deathDone())
                continue;

            enemies[i]->update(lvl, player, cell_size, hasKnockedBack, tempVelocity, onGround, indexAnimation, hud, gameOver);

            enemies[i]->drawExtra(window, offset_x);
        }
    }

    void drawEnemies(RenderWindow& window, float offset_x) override
    {
        for (int i = 0; i < enemyCount; i++)
        {
            if (!enemies[i]->deathDone())
                enemies[i]->draw(window, offset_x);

            //enemies[i]->drawHitBox(window, offset_x);
        }
    }
    int getCrabCount() const { return crabCount; }
    int getBeeCount() const { return beeCount; }
    int getMotobugCount() const { return motobugCount; }
    int getEnemyCount() const { return enemyCount; }
    int getTotalEnemyCount() const { return TotalEnemyCount; }
    Eggstinger* getStinger() { return nullptr; }

    /*
    ~Level1()
    {
        for (int i = 0; i < height; i++)
        {
            delete[] lvl[i];
        }
        delete[] lvl;

        for (int i = 0; i < enemyCount; i++)
        {
            delete enemies[i];
        }
        delete[] enemies;

        for (int i = 0; i < 8; i++)
        {
            delete falling[i];
        }
        delete[] falling;

        delete[] occupiedColumns;

        delete moveable;
    }
    */
 
};