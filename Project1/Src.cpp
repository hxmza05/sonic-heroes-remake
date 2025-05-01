#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//////////////////////////////


#include"Player.h"
#include"Sonic.h"
//#include"Animation.h"
#include"Motobug.h"
#include"Enemy.h"
#include"Crabmeat.h"
#include"Beebot.h"
#include"Batbrain.h"
#include"Eggstinger.h"
#include"Menu.h"
#include"Knuckles.h"
#include"TailedFox.h"
#include"Team.h"

//////////////////////////////


using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;

// prototypes
//void player_sonic.getGravity()(char** lvl, float& offset_y,float&, float& team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), bool& team.getPlayer()[team.getPlayerIndex()][0].getOnGround(), float& team.getPlayer()[team.getPlayerIndex()][0].getGravity(), float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& team.getPlayer()[team.getPlayerIndex()][0].getx(), float& team.getPlayer()[team.getPlayerIndex()][0].gety(), const int cell_size, int& Sonic.getPheight(), int& team.getPlayer()[team.getPlayerIndex()][0].getPwidth(),bool &spacePressed);

//void draw_player(RenderWindow& window, Sprite& LstillSprite, float x, float y);

void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite walls[], const int cell_size,int off_x);
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//////////////This is from where our own defined fucntions start from//////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord);
void draw_bg(RenderWindow& window, Sprite&, int);
void designlvl1(char** lvl, const char* filename, const int height, const int width);
bool checkCollision(char** lvl,int x,int y);
bool collisionCheckWithSpikes(char** lvl, int offset_y, int hit_box_factor_y, int hit_box_factor_x, int Pheight, int Pwidth, int x, int y, int cell_size, int velocityY);
//void playerVirtualsonic.getGravity()(char** lvl, float& offset_y, float&, float& sonic.getVelocityY(), bool& OnGround(), float& sonic.getGravity(), float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& sonic.getx(), float& sonic.gety(), const int cell_size, int& Sonic.getPheight(), int& sonic.getPwidth(), bool& spacePressed);


//void playerVirtualsonic.getGravity()(char** lvl, float& offset_y, float&, float& team[playerIndex][0].getVelocityY(), bool& OnGround(), float& team[playerIndex][0].getGravity(), float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& team[playerIndex][0].getx(), float& team[playerIndex][0].gety(), const int cell_size, int& Sonic.getPheight(), int& team[playerIndex][0].getPwidth(), bool& spacePressed);

//void draw_crabs(RenderWindow& window, Crabmeat crabs[], int& crabCount, int offset_x);
//void playerVirtualsonic.getGravity()(char** lvl, float& offset_y, float&, float& team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), bool& OnGround(), float& team.getPlayer()[team.getPlayerIndex()][0].getGravity(), float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& team.getPlayer()[team.getPlayerIndex()][0].getx(), float& team.getPlayer()[team.getPlayerIndex()][0].gety(), const int cell_size, int& Sonic.getPheight(), int& team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), bool& spacePressed);

//void draw_crabs(RenderWindow& window, Crabmeat crabs[], int& crabCount, int offset_x);
//void playerVirtualsonic.getGravity()(char** lvl, float& offset_y, float&, float& team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), bool& OnGround(), float& team.getPlayer()[team.getPlayerIndex()][0].getGravity(), float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& team.getPlayer()[team.getPlayerIndex()][0].getx(), float& team.getPlayer()[team.getPlayerIndex()][0].gety(), const int cell_size, int& Sonic.getPheight(), int& team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), bool& spacePressed);


//void playerVirtualsonic.getGravity()(char** lvl, float& offset_y, float&, float& team[playerIndex][0].getVelocityY(), bool& OnGround(), float& team[playerIndex][0].getGravity(), float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& team[playerIndex][0].getx(), float& team[playerIndex][0].gety(), const int cell_size, int& Sonic.getPheight(), int& team[playerIndex][0].getPwidth(), bool& spacePressed);


bool CollisionCheckWithCrabs(Crabmeat crabs[], int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight);

bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float crab_x, float crab_y, const float crabWidth, const float crabHeight);

bool CollisionCheckWithBeebots(Beebot**beebots, int& beeCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float beeWidth, const float beeHeight, bool onGround, bool spacePressed);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


int main()
{

    Team team;


    RenderWindow window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog", Style::Close | Style::Resize | Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);


    /////////////////////////////////////////////////////////////////
    // a cell is 64 by 64 pixels

    // 's' is regular space
    // 'q' is wall1 or floor1
    // 'w' is wall2 or floor2
    // 'e' is wall3 or floor3
    // 'b' is breakable wall
    // 'z' is spring

    // Uppercase for not interactable background accessories

    // C is for crystals
    srand(time(0));
    const int cell_size = 64;
    const int height = 14;
    const int width = 110;

    char** lvl = NULL;

    //////////////////////////////////
    //////wall realted variables//////
    //////////////////////////////////

    ///////////////////////////
    //bacground////////////////
    //////////////////////////
    Texture backGround;
    backGround.loadFromFile("Data/bg1.png");
    Sprite backGroundSprite(backGround);

    const int bgTextureWidth = 1600;
    const int bgTextureHeight = 900;
    const int bgWidth = 1200;  
    int levelWidthPixels = 110 * 64;  // if 110 tiles wide, each 64px

    sf::Vector2u textureSize = backGround.getSize();
    sf::Vector2u windowSize = window.getSize();

    backGroundSprite.setColor(sf::Color(255, 255, 255, 180));  
    backGroundSprite.setScale((float)screen_x / bgTextureWidth, (float)screen_y / bgTextureHeight);

    int repeatCount = levelWidthPixels / bgWidth + 1;


    backGroundSprite.setScale(1,(float)windowSize.y / textureSize.y);

    
    Texture wallTex1;
    wallTex1.loadFromFile("Data/brick1.png");
    Sprite wallSprite1(wallTex1);


    Texture wall2;
    wall2.loadFromFile("Data/brick2.png");
    Sprite wall2Sprite(wall2);

    Texture wall3;
    wall3.loadFromFile("Data/brick3.png");
    Sprite wall3Sprite(wall3);


    Texture spikesTexture;
    spikesTexture.loadFromFile("Data/spike.png");
    Sprite spikes(spikesTexture);

    Sprite walls[4] = {wallSprite1,wall2Sprite,wall3Sprite,spikes};

    /////////////////////////////////////////////////////////////
    //sf::FloatRect wall1bounds = wall2Sprite.getGlobalBounds();
    //cout << "Width pf the 1st wall : " << wall1bounds.width << "----" << " Heifht = " << wall1bounds.height << "\n";
    ///////////////////////////////////////////

    Music lvlMus;

    lvlMus.openFromFile("Data/labrynth.ogg");
    lvlMus.setVolume(30);
    lvlMus.play();
    lvlMus.setLoop(true);

    lvl = new char* [height];
    for (int i = 0; i < height; i += 1)
    {
        lvl[i] = new char[width] {'\0'};
    }

    designlvl1(lvl, "lvl1.txt", height, width);

   /* for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 110; ++j) {
            cout << lvl[i][j];
        }
        cout << "\n";
    }*/

    ///////////////////////////////////////
    //////  using virtual bufferZone///////
    ///////////////////////////////////////
    int buffer_start = 4 * 64;
    int buffer_end = 13 * 64;
    Texture buffer;
    buffer.loadFromFile("Data/bufferSprite.jpg");
    Sprite bufferSpriteStart(buffer);
    Sprite bufferSpriteEnd(buffer);




    ////////////////////////////////////////////////////////
	//Sonic team.getPlayer()[team.getPlayerIndex()][0].
    float max_speed = 15;
    bool spacePressed = false;// our own defined
    bool collisionDetectedOffGround = false;
    ///////////////////////////////////////////
    /// for knockBack parabolic Trajecotry///
    //////////////////////////////////////
    //bool team.getPlayer()[team.getPlayerIndex()][0].getOnGround() = false;

    float offset_x = 0;
    float offset_y = 0;

    float scale_x = 2.5;
    float scale_y = 2.5;

    ////////////////////////////
    int raw_img_x = 24;
    int raw_img_y = 35;

    int hit_box_factor_x = 8 * scale_x;
    int hit_box_factor_y = 5 * scale_y;

	//team.getPlayer()[team.getPlayerIndex()][0].setHitBoxFactorX(hit_box_factor_x);

    ////////////////////////////////////////////////////////

    Leaderboard leaderboard;

    Menu menu(screen_x, screen_y, &leaderboard);



    ////////////////////////////////////////////////////////
    ////////////////DECLARING ENEMIES///////////////////////
    ////////////////////////////////////////////////////////

    Motobug bug;
    Eggstinger stinger;


    /////////////////////////////////
    ////////////Crab Meat////////////
    /////////////////////////////////



    Crabmeat crabs[5];
    int crabCount = 5;

    crabs[0].getCrabCoordinates(lvl, height, width);


    int crabIndex = 0; 

    crabs[0].move_crabs(crabs, crabIndex, crabCount, cell_size);



    /////////////////////////////////
    ////////////Bee Botss////////////
    /////////////////////////////////


    int beeCount = 5;
    int beeIndex = 0;
    Beebot** beebots = new Beebot * [beeCount];

    for (int i = 0; i < beeCount; i++) {
        beebots[i] = new Beebot();
    }

    beebots[0]->getBeebotCoordinates(lvl, height, width);
    beebots[0]->move_beebots(beebots, beeIndex, beeCount, cell_size);



    /////////////////////////////////
    ////////////Bat Brain////////////
    /////////////////////////////////

    //Batbrain batbrains[2];
    //int batCount = 2;

    //batbrains[0].getBatbrainCoordinates(lvl, height, width);

    //int batIndex = 0;

    //batbrains[0].move_Batbrain(batbrains, batIndex, batCount, cell_size);


    /////////////////////////////////
    ///////////////////////////////////
    /////////////time stuff//////////////
    ///////////////////////////////////
    float timeChange = 1 ;
    float knockedBacktime = 0;


    //sf::FloatRect playerBounds(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), Pwidth, Pheight);



    /////////////////////////////////
    ////////////Spikes///////////////
    /////////////////////////////////
    bool leftRight = false;


    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        window.clear();

        if (menu.isEnteringName())
        {
            while (window.pollEvent(event)) {

                if (event.type == Event::Closed) {
                    window.close(); 
                }

                menu.update(window, event); 
            }
            menu.update(window);
            menu.draw(window);
        }
        else if (!menu.isGameStateActive())
        {
            menu.update(window);
            menu.draw(window);
        }
        else if (menu.isGameStateActive())            /// leaderboard.addNewScore(menu.getPlayerName(), playerScore); ye add krna hai when player dies and score > highscores[] ho
        {
            if (team.getPlayer()[team.getPlayerIndex()][0].getOnGround())
            {
                collisionDetectedOffGround = false;//resetting the bool if player hits the platform
                team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = false;
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
             {
                 //cout << "LEFT KEY PRESSED" << endl;
                 if (checkCollision(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx() , team.getPlayer()[team.getPlayerIndex()][0].gety()) && checkCollision(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx() , team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1) && checkCollision(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx() - 15, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2) && team.getPlayer()[team.getPlayerIndex()][0].getx() > 0)
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
                     if (!checkCollision(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety()))
                     {
                         team.getPlayer()[team.getPlayerIndex()][0].executePushingLeft();
                     }
                     if(team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() <= 0 )
                        team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() = 15;
                     if (team.getPlayer()[team.getPlayerIndex()][0].getx() <= 0 && !team.getPlayer()[team.getPlayerIndex()][0].getOnGround())
                     {
                         collisionDetectedOffGround = true;
                     }
                 }
             }
             else  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
             {
                 if (checkCollision(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety()) && checkCollision(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() - 1) && checkCollision(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety() + team.getPlayer()[team.getPlayerIndex()][0].getPheight() / 2))
                 {
                     team.getPlayer()[team.getPlayerIndex()][0].moveRight();
                     if (buffer_end < 106 * 64 && team.getPlayer()[team.getPlayerIndex()][0].getx() >= buffer_end)
                     {
                         buffer_end = team.getPlayer()[team.getPlayerIndex()][0].getx();
                         buffer_start = buffer_end - 576;
                         offset_x += team.getPlayer()[team.getPlayerIndex()][0].getVelocityX();
                         //offset_x += 15;
                     }
					 leftRight = true;
                 }
                 else
                 {
                     if (!checkCollision(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx() + team.getPlayer()[team.getPlayerIndex()][0].getPwidth() + 15 - 1, team.getPlayer()[team.getPlayerIndex()][0].gety()))
                     {
                         team.getPlayer()[team.getPlayerIndex()][0].executePushingRight();

                     }
                     if(team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() >= 0)
                     team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() = 15;
                 }
             }
          /*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
             {
                 team.switchPlayer();
             }*/

			 else leftRight = false;
             if (!leftRight)
             {
				 team.getPlayer()[team.getPlayerIndex()][0].getVelocityX() = 0;
             }
              if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed && !team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
                {
                       
                team.getPlayer()[team.getPlayerIndex()][0].getVelocityY() = -19.6;
                team.getPlayer()[team.getPlayerIndex()][0].getOnGround() = false;
                spacePressed = true;
                
                }
             if (spacePressed)
             {
                 team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = UPR;
                 team.getPlayer()[team.getPlayerIndex()][0].getStates()[UPR][0].RunAnimation();
                 leftRight = false;
             }
			 if (!spacePressed && !leftRight)
             {
                 team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex() = STILL;
                 team.getPlayer()[team.getPlayerIndex()][0].getStates()[STILL][0].RunAnimation();
             }
            if(!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
                team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = collisionCheckWithSpikes(lvl,offset_y,hit_box_factor_y,hit_box_factor_x,team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), cell_size, team.getPlayer()[team.getPlayerIndex()][0].getVelocityY());
             //cout << "team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = " << team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() << endl;
            if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack()) {
                CollisionCheckWithCrabs(crabs, crabCount, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack(), team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY(), 60, 44);
            }
            if (!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack()) {
                CollisionCheckWithBeebots(beebots, beeCount, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getVelocityY(), team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack(), team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY(), beebots[0]->getbeeWidth(), beebots[0]->getbeeHeight(), team.getPlayer()[team.getPlayerIndex()][0].getOnGround(), spacePressed);
            }
            if (team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() )/*|| team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedByProjectile()*/
                {
                    team.getPlayer()[team.getPlayerIndex()][0].getx() -= 6;
                    team.getPlayer()[team.getPlayerIndex()][0].gety() += team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY();
                    team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() += team.getPlayer()[team.getPlayerIndex()][0].getTempGravity();
                    if (team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() >= 0)
                    {
                        team.getPlayer()[team.getPlayerIndex()][0].playerVirtualGravity(lvl, offset_y, offset_x, cell_size,spacePressed);
                    }
                }
             if (team.getPlayer()[team.getPlayerIndex()][0].getOnGround())
             {
                 team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack() = false;
                 team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY() = -7;
             }
            if(!team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack())
                team.getPlayer()[team.getPlayerIndex()][0].player_gravity(lvl, offset_y,offset_x, cell_size, spacePressed);

           // draw_bg(window, backGroundSprite, offset_x);
            team.storePath();
            team.autoMoveFollowers();
            draw_bg(window, backGroundSprite, offset_x);

            display_level(window, height, width, lvl, walls, cell_size, offset_x);

            //team.getPlayer()[team.getPlayerIndex()][0].draw_player(window, team.getPlayer()[team.getPlayerIndex()][0].getStates()[team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex()][0].getSprites()[team.getPlayer()[team.getPlayerIndex()][0].getStates()[team.getPlayer()[team.getPlayerIndex()][0].getAnimationIndex()]->getIndex()],offset_x);
            team.draw(window, offset_x);
            // change these according to the movement logic of motobug, for now it moves with player
            

            for (int i = 0; i < crabCount; i++) {
                crabs[i].movement();
                crabs[i].draw(window, offset_x);
            }


            
            for (int i = 0; i < beeCount; i++) {
                beebots[i]->movement(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), cell_size, team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight());
                beebots[i]->draw(window, offset_x);
                beebots[i]->drawProjectiles(window, offset_x);
                beebots[i]->handleProjectilesCollision(lvl, cell_size, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), team.getPlayer()[team.getPlayerIndex()][0].getPwidth(), team.getPlayer()[team.getPlayerIndex()][0].getPheight(), team.getPlayer()[team.getPlayerIndex()][0].getHasKnockedBack(), team.getPlayer()[team.getPlayerIndex()][0].getTempVelocityY());

            }



            /*
            for (int i = 0; i < batCount; i++) {
                batbrains[i].movement(lvl, team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety(), cell_size);
                batbrains[i].draw(window, offset_x);
            }
            
            bug.movement(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety());
            bug.draw(window);

            beebot.movement();
            beebot.draw(window);*/

			/*bat.movement(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety());
            bat.draw(window);*/

            /*stinger.movement(team.getPlayer()[team.getPlayerIndex()][0].getx(), team.getPlayer()[team.getPlayerIndex()][0].gety());
            stinger.draw(window);
            */

           //draw_buffer(window, bufferSpriteStart, buffer_start - offset_x);
           //draw_buffer(window, bufferSpriteEnd, buffer_end - offset_x);

        }
        window.display();
    }
    return 0;
}

// functions
bool collisionCheckWithSpikes(char** lvl, int offset_y, int hit_box_factor_y, int hit_box_factor_x, int Pheight, int Pwidth, int player_x, int player_y, int cell_size, int velocityY)
{
    offset_y = player_y;
    offset_y += velocityY;
    char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
    char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
    char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];

    char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
    char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
    char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];
    bool forLeft = topLeft != 'w' && topLeft != 'q' && topLeft != 'e';
    bool forMiddle = topMiddle != 'w' && topMiddle != 'q' && topMiddle != 'e';
    bool forRight = topRight != 'w' && topRight != 'q' && topRight != 'e';

    //cout << "Left : " << bottom_left_down << " ---- Mid : " << bottom_mid_down << " -------" << "Right : " << bottom_right_down << "----";

    return ((bottom_left_down == 'p' || bottom_mid_down == 'p' || bottom_right_down == 'p') && velocityY > 0 && (forLeft || forMiddle || forRight));
}
void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord)
{
    bufferSprite.setPosition(buffer_coord,500);
    window.draw(bufferSprite);
}
void draw_bg(RenderWindow& window, Sprite& bgSprite, int offset_x)
{
    bgSprite.setPosition(0, 0);
    window.draw(bgSprite);
}


char getMapValues(int val) 
{
    switch (val) 
    {
        case 0: return 's';
        case 1: return 'q'; 
        case 2: return 'w'; 
        case 3: return 'e';
        case 4: return 'p'; 
        default: return 's'; 
    }
}
void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite walls[], const int cell_size, int offset_x)
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
void designlvl1(char** lvl, const char* filename, const int height, const int width)
{
    ifstream in("lvl1.txt");

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            int wall;
            in >> wall;
            lvl[i][j] = getMapValues(wall);
        }
    }
    in.close();
}


bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
{
    return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
}

bool CollisionCheckWithCrabs(Crabmeat crabs[], int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight)
{
    
    if (hasKnockedBack) {

        return false;
    }

    for (int i = 0; i < crabCount; i++) {

        if (!crabs[i].alive()) {
            continue;
        }

        if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, crabs[i].getX(), crabs[i].getY(), crabWidth, crabHeight)) {

            float bottom_of_Player = player_y + Pheight;
            float top_of_Crab = crabs[i].getY();

            if (bottom_of_Player - 10 < top_of_Crab) {

                // crab ko marna hai ab becoz top collision, also add smoke effect and invincibilty 
                cout << " Top-hit:  " << i << endl;

                cout << "PlyrX: " << player_x << "crab X: " << crabs[i].getX() << endl;

                velocityY = -10.0f;
            }

            else {

                hasKnockedBack = true;
                tempVelocityY = -7;

                //float centre_of_Player = player_x + Pwidth / 2.0f;
                //float centre_of_CRab = crabs[i].getX() + crabWidth / 2.0f;

                //cout << "PlyrX " << centre_of_Player << " Crab CenterX " << centre_of_CRab << endl;

                //if (centre_of_Player < centre_of_CRab) {
                //    player_x -= 10;
                //}

                //else {
                //    player_x += 10;
                //}

                crabs[i].setAnimation(3);
                crabs[i].RunNewAnimation();
                crabs[i].setAttack();

                //cout << "PlyrX " << centre_of_Player << " Crab CenterX " << centre_of_CRab << endl;

                //cout << " Sidehit " << i << endl;

                //cout << "PlyrX " << player_x << " Crab X " << crabs[i].getX() << endl;
            }
            return true;
        }
    }

    return false;
}



bool checkCollision(char** lvl, int player_x, int player_y)
{
    return !(lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q' || lvl[player_y / 64][player_x / 64] == 'p');
}

bool CollisionCheckWithBeebots(Beebot** beebots, int& beeCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float beeWidth, const float beeHeight, bool onGround, bool spacePressed)
{
    if (hasKnockedBack) {

        return false;
    }

    for (int i = 0; i < beeCount; i++) {

        if (!beebots[i]->alive()) {
            continue;
        }

        if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, beebots[i]->getX(), beebots[i]->getY(), beeWidth, beeHeight)) {

            if (!(onGround == false && spacePressed == true)) {
                hasKnockedBack = true;
                tempVelocityY = -7; // knockback upwards initially

                float center_of_player = player_x + Pwidth / 2.0f;
                float center_of_bee = beebots[i]->getX() + beeWidth / 2.0f;

                if (center_of_player < center_of_bee) {
                    player_x -= 10; // knock player left
                }
                else {
                    player_x += 10; // knock player right
                }

                cout << "Player hit by Beebot --- thrown back" << endl;
            }

            return true;
        }
    }

    return false;
}
