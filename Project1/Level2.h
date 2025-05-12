#pragma once
#include<fstream>
#include"Level.h"
#include"Crabmeat.h"
#include"Beebot.h"
#include"Motobug.h"
#include"MoveablePlatform.h"
#include"HUD.h"

class Level2 : public Level
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


    int batbrainCount;
    int batStart;
    int batEnd;
    Batbrain* bats;


    Enemy** enemies;
    int enemyCount;
    int j_start;
    int cell_size;

public:
	Level2(Audio* ad) 
	{
        this->audio = ad;
        levelTimer = 120;
        backGround.loadFromFile("Data/bgLvl2O.jpg");
        backGroundSprite.setTexture(backGround);
        unsigned int bgWidth = backGround.getSize().x;
        unsigned int bgHeight = backGround.getSize().y;
        scX = (float)1200 / bgWidth;
        scY = (float)900 / bgHeight;
        backGroundSprite.setScale(scX, scY);

        backGroundSprite.setScale(scX, scY);
        walls = new Sprite[4];
        if (!wallText1.loadFromFile("Data/wall31.jpg"))
        {
            cerr << "\n\n\nFailed to load\n\n\n";
        }
        else cout << "\n\nsuccess in 1\n\n";
        wallText1.loadFromFile("Data/wall31.png");
        wallText2.loadFromFile("Data/wall31.png");
        wallText3.loadFromFile("Data/wall31.png");
        walls[0].setTexture(wallText1);
        walls[1].setTexture(wallText2);
        walls[2].setTexture(wallText3);
        walls[3].setTexture(wallText4);
        for (int i = 0;i < 3;i++)
        {
            walls[i].setScale(1.03, 1.03);
        }
        friction = 0.2;
        cell_size = 64;
        cout << "LEVEL 2 COnstructor being loaded : " << endl;
		height = 14;
		width = 250;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}
        designlvl("lvl2.txt");
        enemyCount = 0;
        TotalEnemyCount = 17;
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

        batbrainCount = 2;
        batStart = 0;
        batEnd = 0;

        for (int i = 0; i < batbrainCount; ++i) {

            bats = new Batbrain();
            bats->setAudio(audio);

            if (bats->getBatbrainCoordinates(lvl, height, width, batStart, batEnd, cell_size)) {
                enemies[enemyCount++] = bats;
            }

        }

        falling = new FallingPlatform * [fallingCount = 15];
        for (int i = 0, f = 64; i < fallingCount; i++, f++)
            falling[i] = new FallingPlatform(64 * f, 350);
		moveable = new MoveablePlatform(35*64,7*64,35*64,44*64);
        levelEnd = 245 * 64;
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
	MoveablePlatform* getMoveable() override
	{
		return moveable;
	}
	virtual FallingPlatform**getFalling()
	{
		return falling;
	}
    void setAudio(Audio* a) override {
        audio = a;
        audio->playLevelMusicByIndex(audio->getLevel2Music());
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
            }
    }



    /*
    * 
    void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player, HUD& hud, bool& gameOver)
    {
        for (int i = 0; i < beeCount; i++)
        {
            if (!beebots[i]->alive())
            {
                continue;
            }
            if (!gameOver)
                beebots[i]->movement(lvl, x, y, cell_size, Pwidth, Pheight);
            if (beebots[i]->handleProjectilesCollision(lvl, cell_size, x, y, Pwidth, Pheight, hasKnockedBack, tempVelocity, height, width))
            {
                hud.getLives()--;
                if (hud.getLives() == 0)
                {
                    return;
                }
                onGround = false;
            }
            if (hasKnockedBack)
            {
                if (beebots[i]->PlayerBeeCollision(x, y, Pwidth, Pheight, beebots[i]->getX(), beebots[i]->getY(), beebots[i]->getbeeWidth(), beebots[i]->getbeeHeight()))
                {
                    if (indexAnimation == UPR || indexAnimation == UPL)
                    {
                        beebots[i]->setHp(0);
                        beebots[i]->setAlive(false);
                        hud.getScore() += 200;
                        continue;
                    }
                    else
                    {
                        hud.getLives()--;
                        if (hud.getLives() == 0)
                        {
                            return;
                        }
                        hasKnockedBack = true;
                        tempVelocity = -7;
                    }
                }
            }
            beebots[i]->drawProjectiles(window, offset_x);
            beebots[i]->draw(window, offset_x);
        }

        for (int i = 0; i < crabCount; i++)
        {

            if (!crabs[i]->alive())
            {
                continue;
            }
            if (!gameOver)
                crabs[i]->movement(lvl, player, cell_size);
            if (crabs[i]->handleProjectilesCollision(lvl, cell_size, x, y, Pwidth, Pheight, hasKnockedBack, tempVelocity, height, width))
            {
                onGround = false;
                hud.getLives()--;
                if (hud.getLives() == 0)
                {
                    return;
                }
            }
            if (!hasKnockedBack)
            {
                if (crabs[i]->checkCollisionWithPlayer(player))
                {

                    if (indexAnimation == UPR || indexAnimation == UPL)
                    {

                        crabs[i]->setHp(0);
                        crabs[i]->setAlive(false);
                        hud.getScore() += 150;
                        continue;
                    }
                    else
                    {
                        hud.getLives()--;
                        if (hud.getLives() == 0)
                        {
                            return;
                        }
                    }
                }
            }
            crabs[i]->drawProjectile(window, offset_x);
            crabs[i]->draw(window, offset_x);
        }

        for (int i = 0; i < motobugCount; i++)
        {

            if (!motobugs[i]->alive())
            {
                continue;
            }
            if (!gameOver)
                motobugs[i]->movement(x, y);
            motobugs[i]->movement(x, y);

            if (!hasKnockedBack)
            {
                if (motobugs[i]->PlayerBugCollision(x, y, Pwidth, Pheight, motobugs[i]->getX(), motobugs[i]->getY(), motobugs[i]->getMotobugWidth(), motobugs[i]->getMotobugHeight()))
                {
                    if (indexAnimation == UPR || indexAnimation == UPL)
                    {
                        motobugs[i]->setHp(0);
                        motobugs[i]->setAlive(false);
                        hud.getScore() += 100;
                        continue;
                    }
                    else
                    {
                        hud.getLives()--;
                        if (hud.getLives() == 0)
                        {
                            return;
                        }
                        hasKnockedBack = true;
                        tempVelocity = -7;
                    }
                }
            }
            motobugs[i]->draw(window, offset_x);
        }
    }

    
    void drawEnemies(RenderWindow& window, float offset_x)
    {
        for (int i = 0;i < motobugCount;i++)
        {
            if (motobugs[i]->alive())
            {
                cout << "Drawig for LEVEL 2 motobugs";
                cout << "\noffset_x" << offset_x << endl;

                motobugs[i]->draw(window, offset_x);
            }
        }
        for (int i = 0;i < crabCount;i++)
        {
            if (crabs[i]->alive())
                crabs[i]->draw(window, offset_x);
        }
        for (int i = 0;i < beeCount;i++)
        {
            if (beebots[i]->alive())
                beebots[i]->draw(window, offset_x);
        }
    }

    */
};