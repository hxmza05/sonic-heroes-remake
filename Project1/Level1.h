#pragma once
#include<fstream>
#include"Level.h"
#include"Crabmeat.h"
#include"Beebot.h"
#include"MoveablePlatform.h"
#include"FallingPlatform.h"

class Level1 : public Level
{
	FallingPlatform **falling;
	MoveablePlatform* moveable;


	int crabCount;
	int crabIndex;
	int crab_start;
	int crab_end;
	Crabmeat** crabs;


	int beeCount;
	int beeIndex;
	int bee_start;
	int bee_end;
	Beebot** beebots;


	int motobugCount;
	int motobugIndex;
	int motobug_start;
	int motobug_end;
	Motobug** motobugs;
	int cell_size;
public:
	Level1()
	{
		cell_size = 64;
		height = 14;
		width = 200;
		lvl = new char* [height];
		for (int i = 0; i < height; i++)
		{
			lvl[i] = new char[width];
		}

		designlvl("lvl1.txt");


		crabCount = 5;
		crabIndex = 0;
		crabs = new Crabmeat * [crabCount];

		for (int i = 0; i < crabCount; i++) {
			crabs[i] = new Crabmeat();
		}

		crab_start = 5;
		crab_end = 9;

		for (int i = 0; i < crabCount; ++i) {
			crabs[i]->getCrabCoordinates(lvl, height, width, crab_start, crab_end);
		}

		crabs[0]->move_crabs(crabs, crabIndex, crabCount, cell_size);



		beeCount = 5;
		beeIndex = 0;
		beebots = new Beebot * [beeCount];

		for (int i = 0; i < beeCount; i++) {
			beebots[i] = new Beebot();
		}

		bee_start = 5;
		bee_end = 8;
		beebots[0]->getBeebotCoordinates(lvl, height, width, bee_start, bee_end);
		beebots[0]->move_beebots(beebots, beeIndex, beeCount, cell_size);







		motobugCount = 5;
		motobugIndex = 0;
		motobugs = new Motobug * [motobugCount];

		for (int i = 0; i < motobugCount; i++) {
			motobugs[i] = new Motobug();
		}

		motobug_start = 10;
		motobug_end = 12;

		motobugs[0]->getMotobugCoordinates(lvl, height, width, motobug_start, motobug_end);
		motobugs[0]->move_motobugs(motobugs, motobugIndex, motobugCount, cell_size); 






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

};