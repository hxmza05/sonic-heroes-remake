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


//////////////////////////////


using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;

// prototypes
void player_gravity(char** lvl, float& offset_y,float&, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth,bool &spacePressed);

void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y);

void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite walls[], const int cell_size,int off_x);
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//////////////This is from where our own defined fucntions start from//////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord);
void draw_bg(RenderWindow& window, Sprite&, int);
void designlvl1(char** lvl, const char* filename, const int height, const int width);
bool checkCollision(char** lvl,int player_x,int player_y);
bool collisionCheckWithSpikes(char** lvl, int offset_y, int hit_box_factor_y, int hit_box_factor_x, int Pheight, int Pwidth, int player_x, int player_y, int cell_size, int velocityY);
void playerVirtualGravity(char** lvl, float& offset_y, float&, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth, bool& spacePressed);
void getCrabCoordinates(int CrabStart[], int CrabEnd[], int CrabWalls[], const int heigth, const int width, const int crabCoordinates, int& indexCrab, char** lvl);
void draw_crabs(RenderWindow& window, Crabmeat crabs[], int& crabCount, int offset_x);
void move_crabs(Crabmeat crabs[], int CrabStart[], int CrabEnd[], int CrabWalls[], int& indexCrab, int& crabIndex, int& crabCount, const int cell_size, const float crabHeight);
bool CollisionCheckWithCrabs(Crabmeat crabs[], int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight);
bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float crab_x, float crab_y, const float crabWidth, const float crabHeight);
void getBeebotCoordinates(int BeebotStart[], int BeebotEnd[], int BeebotHeights[], const int height, const int width, const int maxBeeBots, int& indexBee, char** lvl);
void move_beebots(Beebot beebots[], int BeebotStart[], int BeebotEnd[], int BeebotHeights[], int& indexBee, int& beeIndex, int& beeCount, const int cell_size, const float bee_height);
void draw_beebots(RenderWindow& window, Beebot beebots[], int& beeCount, int offset_x);

int main()
{

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

    const int cell_size = 64;
    const int height = 14;
    const int width = 110;

    char** lvl = NULL;

    //////////////////////////////////
    //////wall realted variables//////
    //////////////////////////////////

    ///////////////////////////
    //bacgrnd/////////////////
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

    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 110; ++j) {
            cout << lvl[i][j];
        }
        cout << "\n";
    }

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
	Sonic sonic;
    float player_x = 150;
    float player_y = 150;
    bool hasCollided = false;
    bool hasKnockedBack = false;

    float max_speed = 15;

    float velocityX = 0;
    float velocityY = 0;
    bool spacePressed = false;// our own defined
    bool collisionDetectedOffGround = false;

    float jumpStrength = -20; // Initial jump velocity
    float gravity = 1;        // Gravity acceleration


    ///////////////////////////////////////////
    /// for knockBack parabolic Trajecotry///
    //////////////////////////////////////
    float tempTerminalVelocityY = 15;
    float tempVelocityY = -7;
    float tempGravity = 0.6;
    Texture LstillTex;
    LstillTex.loadFromFile("Data/0left_still.png");
    Sprite LstillSprite(LstillTex);

    bool onGround = false;

    float offset_x = 0;
    float offset_y = 0;

    float terminal_Velocity = 20;

    float acceleration = 0.2;

    float scale_x = 2.5;
    float scale_y = 2.5;

    ////////////////////////////
    int raw_img_x = 24;
    int raw_img_y = 35;

    int Pheight = raw_img_y * scale_y;
    int Pwidth = raw_img_x * scale_x;

    // only to adjust the player's hitbox

    int hit_box_factor_x = 8 * scale_x;
    int hit_box_factor_y = 5 * scale_y;

    LstillSprite.setTexture(LstillTex);
    LstillSprite.setScale(scale_x, scale_y);

    ////////////////////////////////////////////////////////

    Menu menu(screen_x, screen_y);


    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////DECLARING ENEMIES///////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////


    Motobug bug;
    Batbrain bat;
    Eggstinger stinger;


    /////////////////////////////////
    ////////////Crab Meat////////////
    /////////////////////////////////

    const int crabCoordinates = 10;
    int CrabStart[crabCoordinates];
    int CrabEnd[crabCoordinates];
    int CrabWalls[crabCoordinates];
	int indexCrab = 0;
    const float crabHeight = 44.0;
    const float crabWidth = 60.0;

    Crabmeat crabs[4];
    int crabIndex = 0;
    int crabCount = 4;

    getCrabCoordinates(CrabStart, CrabEnd, CrabWalls, height, width, crabCoordinates, indexCrab, lvl);
    move_crabs(crabs, CrabStart, CrabEnd, CrabWalls, indexCrab, crabIndex, crabCount, cell_size, crabHeight);

    /////////////////////////////////
    ////////////Bee Botss////////////
    /////////////////////////////////

    const int beeCoordintes = 10;
    int air_Row = 5;
    int BeebotStart[beeCoordintes];
    int BeebotEnd[beeCoordintes];
    int BeebotHeights[beeCoordintes];
    const float bee_height = 37.5;
    const float bee_width = 88.5;
    int indexBee = 0;
    int beeIndex = 0;
    int beeCount = 5;

    Beebot beebots[5];
    

    getBeebotCoordinates(BeebotStart, BeebotEnd, BeebotHeights, height, width, beeCoordintes, indexBee, lvl);
    move_beebots(beebots, BeebotStart, BeebotEnd, BeebotHeights, indexBee, beeIndex, beeCount, cell_size, bee_height);



    /////////////////////////////////
    ///////////////////////////////////
    /////////////time stuff//////////////
    ///////////////////////////////////
    float timeChange = 1 ;
    float knockedBacktime = 0;


    //sf::FloatRect playerBounds(sonic.getx(), sonic.gety(), Pwidth, Pheight);



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

        if (!menu.isGameStateActive())
        {
            menu.update(window);
            menu.draw(window);
        }

        else if (menu.isGameStateActive())
        {
			
            for (int i = 0; i < repeatCount; i++) {

                backGroundSprite.setPosition(i * bgWidth - float(offset_x*0.5f), 0);  
                window.draw(backGroundSprite);

            }




            if (onGround)
            {
                collisionDetectedOffGround = false;//resetting the bool if player hits the platform
                hasKnockedBack = false;
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !hasKnockedBack)
             {
                ///////////////////////////////////////
                // i have to change this afterwards////
                ///////////////////////////////////////
             
                /////dont check when collision is detetced off the ground till the player is off the ground/////
                 if (checkCollision(lvl, sonic.getx(), sonic.gety()) && checkCollision(lvl, sonic.getx(), sonic.gety() + Pheight - 1) && checkCollision(lvl, sonic.getx() - 15, sonic.gety() + Pheight / 2) && player_x > 0)
                 {
					 cout << "LEFT KEY PRESSED" << endl;
                     sonic.getAnimationIndex()  = LEFT;
					 sonic.getStates()[LEFT][0].RunAnimation();
                     sonic.getx() -= 15;
                     if (buffer_start > 4 * 64 && sonic.getx() <= buffer_start)
                     {
                         buffer_start = sonic.getx();
                         buffer_end = buffer_start + 576;
                         offset_x -= 15;
                     }
					 leftRight = true;
                 }
                 else
                 {
                     if(velocityY <= 0 )
                        velocityY = 15;
                     if (sonic.getx() <= 0 && !onGround)
                     {
                         collisionDetectedOffGround = true;
                     }
                 }
             }
             else  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&!hasKnockedBack)
             {
                 if (checkCollision(lvl, sonic.getx() + Pwidth + 15 - 1, sonic.gety()) && checkCollision(lvl, sonic.getx() + Pwidth + 15 - 1, sonic.gety() + Pheight - 1) && checkCollision(lvl, sonic.getx() + Pwidth + 15 - 1, sonic.gety() + Pheight / 2))
                 {
					 cout << "RIGHT KEY PRESSED" << endl;
                     sonic.getAnimationIndex() = RIGHT;
                      sonic.getStates()[RIGHT][0].RunAnimation();
                     sonic.getx() += 15;
                     if (buffer_end < 106 * 64 && sonic.getx() >= buffer_end)
                     {
                         buffer_end = sonic.getx();
                         buffer_start = buffer_end - 576;
                         offset_x += 15;
                     }
					 leftRight = true;
                 }
                 else
                 {
                     if(velocityY >= 0)
                     velocityY = 15;
                 }
             }
			 else leftRight = false;
              if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed && !hasKnockedBack)
                {
                       
                velocityY = -19.6;
                onGround = false;
                spacePressed = true;
                sonic.getAnimationIndex() = UPR;
                sonic.getStates()[UPR][0].RunAnimation();
                }
             if (spacePressed && leftRight)
             {
                 sonic.getAnimationIndex() = UPR;
                 sonic.getStates()[UPR][0].RunAnimation();
                 leftRight = false;
             }
			 if (!spacePressed && !leftRight)
             {
                 sonic.getAnimationIndex() = EDGEL;
                 sonic.getStates()[EDGEL][0].RunAnimation();
             }
            if(!hasKnockedBack)
                hasKnockedBack = collisionCheckWithSpikes(lvl,offset_y,hit_box_factor_y,hit_box_factor_x,Pheight,Pwidth,sonic.getx(), sonic.gety(), cell_size, velocityY);
             cout << "HASKNOCKEDBACK = " << hasKnockedBack << endl;


            if (!hasKnockedBack) {

                CollisionCheckWithCrabs(crabs, crabCount, sonic.getx(), sonic.gety(), Pwidth, Pheight, velocityY, hasKnockedBack, tempVelocityY, crabWidth, crabHeight);
            }

             if (hasKnockedBack)
                {
                    sonic.getx() -= 6;
                    sonic.gety() += tempVelocityY;
                    tempVelocityY += tempGravity;
                    if (tempVelocityY >= 0)
                    {
                        playerVirtualGravity(lvl, offset_y, offset_x, tempVelocityY, onGround, tempGravity, tempTerminalVelocityY, hit_box_factor_x, hit_box_factor_y, sonic.getx(), sonic.gety(), cell_size, Pheight, Pwidth, spacePressed);
                    }
                }
             if (onGround)
             {
                 hasKnockedBack = false;
                 tempVelocityY = -7;
             }
            if(!hasKnockedBack)
                player_gravity(lvl, offset_y,offset_x, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, sonic.getx(), sonic.gety(), cell_size, Pheight, Pwidth, spacePressed);

           // draw_bg(window, backGroundSprite, offset_x);

            display_level(window, height, width, lvl, walls, cell_size, offset_x);

            draw_player(window, sonic.getStates()[sonic.getAnimationIndex()][0].getSprites()[sonic.getStates()[sonic.getAnimationIndex()]->getIndex()], sonic.getx() - offset_x, sonic.gety());

            // change these according to the movement logic of motobug, for now it moves with player
            
            draw_crabs( window, crabs, crabCount, offset_x);
            draw_beebots(window, beebots, beeCount, offset_x);


            /*
            bug.movement(sonic.getx(), sonic.gety());
            bug.draw(window);

            beebot.movement();
            beebot.draw(window);

			bat.movement(sonic.getx(), sonic.gety());
            bat.draw(window);

            stinger.movement(sonic.getx(), sonic.gety());
            stinger.draw(window);
            */

           /*draw_buffer(window, bufferSpriteStart, buffer_start - offset_x);
           draw_buffer(window, bufferSpriteEnd, buffer_end - offset_x);*/

        }
        window.display();
    }
    return 0;
}

// functions
void player_gravity(char** lvl, float& offset_y, float& offset_x,float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth,bool& spacePressed)
{
    offset_y = player_y;
    offset_y += velocityY;

    int headY = (int)(player_y + hit_box_factor_y) / cell_size;
    int tileLeftX  = (int)(player_x + hit_box_factor_x) / cell_size;
    int tileRightX = (int)(player_x + hit_box_factor_x + Pwidth - 1) / cell_size;

    bool hitsTopRow = (headY == 0 || headY == 1);
    bool leftHit = (lvl[headY][tileLeftX] == 'w' || lvl[headY][tileLeftX] == 'q' || lvl[headY][tileLeftX] == 'e');
    bool rightHit = (lvl[headY][tileRightX] == 'w' || lvl[headY][tileRightX] == 'q' || lvl[headY][tileRightX] == 'e');

    if (velocityY < 0 && hitsTopRow && (leftHit || rightHit)) 
    {
        velocityY = 0;
    }


    char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
    char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size) ];
    char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];

    char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
    char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
    char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];
    bool forLeft = topLeft == 's';
    bool forMiddle = topMiddle == 's';
    bool forRight = topRight == 's';


    if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w'|| bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e'|| bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') && velocityY > 0 &&(forLeft || forMiddle || forRight))
    {
        onGround = true;
        /*player_y = ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size) * cell_size - hit_box_factor_y - Pheight;*/
        velocityY = 0;
        spacePressed = false;
    }
    else
    {
        player_y = offset_y;
        onGround = false;
    }
    if (!onGround)
    {
        velocityY += gravity;
        if (velocityY >= terminal_Velocity)
            velocityY = terminal_Velocity;
    }
    else
    {
        velocityY = 0;
        spacePressed = false;
    }
}
void playerVirtualGravity(char** lvl, float& offset_y, float& offset_x, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth, bool& spacePressed)
{
    offset_y = player_y;
    offset_y += velocityY;
    char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
    char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
    char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];

    char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
    char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
    char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];
    bool forLeft = topLeft == 's';
    bool forMiddle = topMiddle == 's';
    bool forRight = topRight == 's';


    if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' || bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' || bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') && velocityY > 0 && (forLeft || forMiddle || forRight))
    {
        onGround = true;
        /*player_y = ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size) * cell_size - hit_box_factor_y - Pheight;*/
        velocityY = 0;
        spacePressed = false;
    }
    else
    {
        player_y = offset_y;
        velocityY += gravity;
        onGround = false;
    }
}
bool collisionCheckWithSpikes(char ** lvl,int offset_y,int hit_box_factor_y,int hit_box_factor_x,int Pheight,int Pwidth,int player_x,int player_y, int cell_size,int velocityY)
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

    cout << "Left : " << bottom_left_down << " ---- Mid : " << bottom_mid_down << " -------" << "Right : " << bottom_right_down << "----";

    return ((bottom_left_down == 'p' || bottom_mid_down == 'p' || bottom_right_down == 'p') && velocityY > 0 && (forLeft || forMiddle || forRight));
}
void knockBack(int& velocityY, int& player_x, int& player_y, bool& hasknockedBack)
{
    //hasknockedBack = collisionCheckWithSpikes()
}
void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord)
{
    bufferSprite.setPosition(buffer_coord,500);
    window.draw(bufferSprite);
}
void draw_bg(RenderWindow& window, Sprite& bgSprite, int offset_x)
{
    bgSprite.setPosition(-offset_x, 0);
    window.draw(bgSprite);
}

void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y)
{
    LstillSprite.setPosition(player_x, player_y);
    window.draw(LstillSprite);
}
void draw_crabs(RenderWindow& window, Crabmeat crabs[], int& crabCount, int offset_x) 
{
    for (int i = 0; i < crabCount; i++) {

        crabs[i].movement();
        crabs[i].draw(window, offset_x);

    }
}
void draw_beebots(RenderWindow& window, Beebot beebots[], int& beeCount, int offset_x)
{
    for (int i = 0; i < beeCount; i++) {

        beebots[i].movement();
        beebots[i].draw(window, offset_x);

    }
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
bool checkCollision(char** lvl, int player_x, int player_y)
{
    return !(lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q' || lvl[player_y / 64][player_x / 64] == 'p');
}

void getCrabCoordinates(int CrabStart[], int CrabEnd[], int CrabWalls[], const int heigth, const int width, const int crabCoordinates, int& indexCrab, char**lvl) {

    for (int i = 5; i < heigth - 1; i++) {

        int j = 0;

        while (j < width - 1) {

            if (lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q')) {

                int start = j;

                while (j < width && lvl[i][j] == 's' && (lvl[i + 1][j] == 'w' || lvl[i + 1][j] == 'e' || lvl[i + 1][j] == 'q'))
                    j++;

                int end = j - 1;

                if (end - start + 1 >= 4 && indexCrab < crabCoordinates) {

                    CrabStart[indexCrab] = start;
                    CrabEnd[indexCrab] = end;
                    CrabWalls[indexCrab] = i;
                    indexCrab++;
                }

                cout << "Found platform from tile " << start << " to " << end << " at row " << i << endl;

            }

            else {

                j++;
            }


        }

    }


}

void move_crabs(Crabmeat crabs[], int CrabStart[], int CrabEnd[], int CrabWalls[], int& indexCrab, int& crabIndex, int& crabCount, const int cell_size, const float crabHeight) {

    int maxCrabs = min(indexCrab, crabCount);

    for (int i = 0; i < maxCrabs; i++) {

        if (crabIndex < 10) {

            float patrolStart = CrabStart[i] * cell_size;
            float crabmeatEnd = CrabEnd[i] * cell_size;
            float crabmeatmaxEnd = patrolStart + 12 * cell_size;
            float patrolEnd = (crabmeatEnd > crabmeatmaxEnd) ? crabmeatmaxEnd : crabmeatEnd;

            float crabX = (patrolStart + patrolEnd) / 2.0f;
            float crabY = (CrabWalls[i] + 1) * cell_size - crabHeight;

            crabs[crabIndex].setPosition(crabX, crabY, patrolStart, patrolEnd);

            cout << "plcd crabb " << crabIndex << ": " << crabX << ", " << crabY << endl;

            crabIndex++;

        }
    }

    cout << "detec " << indexCrab << " crab platform rangrs" << endl;


    crabCount = crabIndex;

}

bool PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float crab_x, float crab_y, const float crabWidth, const float crabHeight)
{
    return (player_x + Pwidth > crab_x && player_x < crab_x + crabWidth && player_y + Pheight > crab_y && player_y < crab_y + crabHeight);
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

                float centre_of_Player = player_x + Pwidth / 2.0f;
                float centre_of_CRab = crabs[i].getX() + crabWidth / 2.0f;

                cout << "PlyrX " << centre_of_Player << " Crab CenterX " << centre_of_CRab << endl;

                if (centre_of_Player < centre_of_CRab) {
                    player_x -= 10;
                }

                else {
                    player_x += 10;
                }

                cout << "PlyrX " << centre_of_Player << " Crab CenterX " << centre_of_CRab << endl;

                cout << " Sidehit " << i << endl;

                cout << "PlyrX " << player_x << " Crab X " << crabs[i].getX() << endl;
            }
            return true;
        }
    }

    return false;
}



void getBeebotCoordinates(int BeebotStart[], int BeebotEnd[], int BeebotHeights[], const int height, const int width, const int maxBeeBots, int& indexBee, char** lvl)
{
    for (int i = 2; i < height / 2 + 1; i++) {  

        int j = 0;

        while (j < width - 1) {

            if (lvl[i][j] == 's' && lvl[i + 1][j] == 's' && lvl[i - 1][j] == 's') {\

                int start = j;

                while (j < width && lvl[i][j] == 's' && lvl[i + 1][j] == 's' && lvl[i - 1][j] == 's') {
                    j++;
                }

                int end = j - 1;

                if (end - start + 1 >= 4 && indexBee < maxBeeBots) {
                    BeebotStart[indexBee] = start;
                    BeebotEnd[indexBee] = end;
                    BeebotHeights[indexBee] = i;
                    indexBee++;

                    cout << "Found air zone from tile " << start << " to " << end << " at row " << i << endl;
                }
            }
            else {
                j++;
            }
        }
    }
}


void move_beebots(Beebot beebots[], int BeebotStart[], int BeebotEnd[], int BeebotHeights[], int& indexBee, int& beeIndex, int& beeCount, const int cell_size, const float bee_height)
{
    for (int i = 0; i < beeCount; i++) {

        float patrolStart = BeebotStart[i] * cell_size;
        float beebot_End = BeebotEnd[i] * cell_size;
        float beebot_maxEnd = patrolStart + 10 * cell_size;
        float patrolEnd = (beebot_End > beebot_maxEnd) ? beebot_maxEnd : beebot_End;

        float bee_X = (patrolStart + patrolEnd) / 2.0f;
        float bee_Y = BeebotHeights[i] * cell_size + 10;  

        beebots[beeIndex].setPosition(bee_X, bee_Y, patrolStart, patrolEnd);
        beebots[i].setBaseY(270);

        cout << "placed bee " << beeIndex << ": " << bee_X << ", " << bee_Y << endl;
        beeIndex++;
    }
    beeCount = beeIndex;
}

