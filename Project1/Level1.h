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


    /*
    
    void handleEnemies(RenderWindow& window, float& x, float& y, int& Pwidth, int& Pheight, bool& hasKnockedBack, float& tempVelocity, bool& onGround, int& indexAnimation, float& offset_x, Player& player, HUD& hud,bool& gameOver)
    {
        for (int i = 0; i < beeCount; i++)
        {
            if (!beebots[i]->alive())
            {
                continue;
            }
            if(!gameOver)
                beebots[i]->movement(lvl, x, y, cell_size, Pwidth, Pheight);
            if (beebots[i]->handleProjectilesCollision(lvl, cell_size, x, y, Pwidth, Pheight, hasKnockedBack, tempVelocity,height,width))
            {
                hud.getLives()--;
                if (hud.getLives() == 0)
                {
                    return;
                }
                onGround = false;
            }
            if (!hasKnockedBack)
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
            //beebots[i]->draw(window, offset_x);
        }

        for (int i = 0; i < crabCount; i++)
        {

            if (!crabs[i]->alive())
            {
                continue;
            }
			if (!gameOver)
             crabs[i]->movement(lvl, player, cell_size);
            if (crabs[i]->handleProjectilesCollision(lvl, cell_size, x, y, Pwidth, Pheight, hasKnockedBack, tempVelocity,height,width))
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
            //crabs[i]->draw(window, offset_x);
        }

        for (int i = 0; i < motobugCount; i++)
        {

            if (!motobugs[i]->alive())
            {
                continue;
            }
			if (!gameOver)
				motobugs[i]->movement(x, y);
            //motobugs[i]->movement(x, y);

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
            //motobugs[i]->draw(window, offset_x);
        }
    }


    */



    /* void handleBees()
     {

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD




		falling = new FallingPlatform * [8];
		for(int i = 0,f = 32;i < 8;i++,f++)
		falling[i] = new FallingPlatform(64 * f, 500);
		moveable = new MoveablePlatform(1000,450,850,1500);

	}
	MoveablePlatform* getMoveable() override
	{
		return moveable;
	}
	virtual FallingPlatform** getFalling()
	{
		return falling;
	}

	char  getMapValues(int val)
	{
		switch (val)
		{
		case 0: return 's';
		case 1: return 'q';
		case 2: return 'w';
		case 3: return 'e';
		case 4: return 'p';
		case 5: return 'r';
		case 6: return 'p';
		case 9: return 'b';

		default: return 's';
		}
	}
	void designlvl(const char* filename)
	{
		cout << "\n\n\nIn desgin function\n\n\n";
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
				cout << "lvl[" << i << "][" << j << "] = " << lvl[i][j] << endl;
			}
			cout << endl;
		}
		file.close();
	}
	 void handleEnemies(RenderWindow&window,float& x,float& y,int&Pwidth,int&Pheight,bool&hasKnockedBack,float&tempVelocity,bool&onGround,int&indexAnimation,float&offset_x,Player& player)
	 {

		 cout << "hello" << endl;

		 for (int i = 0; i < beeCount; i++)
		 {
			 if (!beebots[i]->alive()) {
				 continue;
			 }
			 beebots[i]->movement(lvl,x, y, cell_size, Pwidth,Pheight);
			 if (beebots[i]->handleProjectilesCollision(lvl, cell_size, x, y, Pwidth, Pheight, hasKnockedBack, tempVelocity))
			 {
				 onGround = false;
			 }
			 if (hasKnockedBack)  // change this to ! but after adding the condition that the player isnt flying
			 {
				 if (beebots[i]->PlayerBeeCollision(x, y, Pwidth, Pheight, beebots[i]->getX(), beebots[i]->getY(), beebots[i]->getbeeWidth(), beebots[i]->getbeeHeight()))
				 {
					 if (indexAnimation == UPR || indexAnimation == UPL)
					 {
						 beebots[i]->setHp(0);
						 beebots[i]->setAlive(false);
						 continue;
					 }
					 else
					 {
						hasKnockedBack = true;
						 tempVelocity = -7;
					 }
				 }
			 }
			 beebots[i]->drawProjectiles(window, offset_x);
			 beebots[i]->draw(window, offset_x);
		 }




		 for (int i = 0; i < crabCount; i++) {

			 if (!crabs[i]->alive()) {
				 continue;
			 }
			 crabs[i]->movement(lvl, player, cell_size);
			 if (crabs[i]->handleProjectilesCollision(lvl, cell_size, x, y, Pwidth, Pheight, hasKnockedBack, tempVelocity))
			 {
				 onGround = false;

			 }
			 if (!hasKnockedBack)
			 {
				 if (crabs[i]->checkCollisionWithPlayer(player)) 
				 {

					 if (indexAnimation == UPR || indexAnimation == UPL) {

						 crabs[i]->setHp(0);
						 crabs[i]->setAlive(false);
						 continue;

					 }
				 }
			 }
			 crabs[i]->drawProjectile(window, offset_x);
			 crabs[i]->draw(window, offset_x);
		 }



		 for (int i = 0; i < motobugCount; i++)
		 {

			 if (!motobugs[i]->alive()) {
				 continue;
			 }

			 motobugs[i]->movement(x, y);

			 if (!hasKnockedBack)
			 {
				 if (motobugs[i]->PlayerBugCollision(x, y, Pwidth, Pheight, motobugs[i]->getX(), motobugs[i]->getY(), motobugs[i]->getMotobugWidth(), motobugs[i]->getMotobugHeight()))
				 {
					 if (indexAnimation == UPR || indexAnimation == UPL)
					 {
						 motobugs[i]->setHp(0);
						 motobugs[i]->setAlive(false);
						 continue;
					 }
					 else
					 {
						 hasKnockedBack = true;
						 tempVelocity = -7;
					 }
				 }
			 }
			 motobugs[i]->draw(window, offset_x);
		 }

	 }
	/* void handleBees()
	 {

	 }*/


     


    /*
    void drawEnemies(RenderWindow&window,float offset_x)
    {
        for (int i = 0;i < motobugCount;i++)
        {
            if(motobugs[i]->alive())
                motobugs[i]->draw(window, offset_x);
        }
        for (int i = 0;i < crabCount;i++)
        {
            if(crabs[i]->alive())
                crabs[i]->draw(window, offset_x);
        }
        for (int i = 0;i < beeCount;i++)
        {
            if(beebots[i]->alive())
                beebots[i]->draw(window, offset_x);
        }
    }
    */

	/*oveablePlatform* getMoveable() override
	{
		return moveable;
	}
	virtual FallingPlatform** getFalling()
	{
		return falling;
	}*/
	 
};