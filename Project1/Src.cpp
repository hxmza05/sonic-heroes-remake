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
//void player_sonic.getGravity()(char** lvl, float& offset_y,float&, float& sonic.getVelocityY(), bool& sonic.getOnGround(), float& sonic.getGravity(), float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& sonic.getx(), float& sonic.gety(), const int cell_size, int& Sonic.getPheight(), int& sonic.getPwidth(),bool &spacePressed);

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
void getCrabCoordinates(int CrabStart[], int CrabEnd[], int CrabWalls[], const int heigth, const int width, const int crabCoordinates, int& indexCrab, char** lvl);
void placeSpikesUnderPlatforms(char** lvl, int height, int width);
void draw_crabs(RenderWindow& window, Sprite& crab, Crabmeat crabs[], int& crabCount, int offset_x);
void move_crabs(Crabmeat crabs[], int CrabStart[], int CrabEnd[], int CrabWalls[], int& indexCrab, int& crabIndex, int& crabCount, Sprite& sprite);

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

    //backGroundSprite.setColor(sf::Color(255, 255, 255, 180));  
    //backGroundSprite.setScale((float)screen_x / bgTextureWidth, (float)screen_y / bgTextureHeight);

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
  /*  float sonic.getx() = 150;
    float sonic.gety() = 150;*/
    //bool sonic.getHasCollided() = false;
    //bool sonic.getHasKnockedBack() = false;

    float max_speed = 15;

    //float sonic.getVelocityX() = 0;
    //float sonic.getVelocityY() = 0;
    bool spacePressed = false;// our own defined
    bool collisionDetectedOffGround = false;

    //float sonic.getJumpStrength() = -20; // Initial jump velocity
    //float sonic.getGravity() = 1;        // sonic.getGravity() sonic.getacceleration()


    ///////////////////////////////////////////
    /// for knockBack parabolic Trajecotry///
    //////////////////////////////////////
    float tempTerminalVelocityY= 15;
    /*float sonic.getTempVelocityY()() = -7;*/
    //float sonic.() = 0.6;
    Texture LstillTex;
    LstillTex.loadFromFile("Data/0left_still.png");
    Sprite LstillSprite(LstillTex);

    //bool sonic.getOnGround() = false;

    float offset_x = 0;
    float offset_y = 0;

    //float terminal_Velocity = 20;

    //float sonic.getacceleration() = 0.2;

    float scale_x = 2.5;
    float scale_y = 2.5;

    ////////////////////////////
    int raw_img_x = 24;
    int raw_img_y = 35;

    /*int Sonic.getPheight( = raw_img_y * scale_y;
    int sonic.getPwidth() = raw_img_x * scale_x;*/

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
    Beebot beebot;
    Batbrain bat;
    Eggstinger stinger;


    /////////////////////////////////
    ////////////Crab Meat////////////
    /////////////////////////////////

    const int crabCoordinates = 100;
    int CrabStart[crabCoordinates];
    int CrabEnd[crabCoordinates];
    int CrabWalls[crabCoordinates];
	int indexCrab = 0;

    Crabmeat crabs[4];
    int crabIndex = 0;
    int crabCount = 4;

    getCrabCoordinates(CrabStart, CrabEnd, CrabWalls, height, width, crabCoordinates, indexCrab, lvl);
    move_crabs(crabs, CrabStart, CrabEnd, CrabWalls, indexCrab, crabIndex, crabCount, crabs->getSprite());



    /////////////////////////////////
    ///////////////////////////////////
    /////////////time stuff//////////////
    ///////////////////////////////////
    float timeChange = 1 ;
    float knockedBacktime = 0;





    /////////////////////////////////
    ////////////Spikes///////////////
    /////////////////////////////////
    bool leftRight = false;

    placeSpikesUnderPlatforms(lvl, height, width);

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
            if (sonic.getOnGround())
            {
                collisionDetectedOffGround = false;//resetting the bool if player hits the platform
                sonic.getHasKnockedBack() = false;
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sonic.getHasKnockedBack())
             {
                ///////////////////////////////////////
                // i have to change this afterwards////
                ///////////////////////////////////////
             
                /////dont check when collision is detetced off the ground till the player is off the ground/////
                 if (checkCollision(lvl, sonic.getx() , sonic.gety()) && checkCollision(lvl, sonic.getx() , sonic.gety() + sonic.getPheight() - 1) && checkCollision(lvl, sonic.getx() - 15, sonic.gety() + sonic.getPheight() / 2) && sonic.getx() > 0)
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
                     if(sonic.getVelocityY() <= 0 )
                        sonic.getVelocityY() = 15;
                     if (sonic.getx() <= 0 && !sonic.getOnGround())
                     {
                         collisionDetectedOffGround = true;
                     }
                 }
             }
             else  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&!sonic.getHasKnockedBack())
             {
                 if (checkCollision(lvl, sonic.getx() + sonic.getPwidth() + 15 - 1, sonic.gety()) && checkCollision(lvl, sonic.getx() + sonic.getPwidth() + 15 - 1, sonic.gety() + sonic.getPheight() - 1) && checkCollision(lvl, sonic.getx() + sonic.getPwidth() + 15 - 1, sonic.gety() + sonic.getPheight() / 2))
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
                     if(sonic.getVelocityY() >= 0)
                     sonic.getVelocityY() = 15;
                 }
             }
			 else leftRight = false;
              if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed && !sonic.getHasKnockedBack())
                {
                       
                sonic.getVelocityY() = -19.6;
                sonic.getOnGround() = false;
                spacePressed = true;
                
                }
             if (spacePressed)
             {
                 sonic.getAnimationIndex() = UPR;
                 sonic.getStates()[UPR][0].RunAnimation();
                 leftRight = false;
             }
			 if (!spacePressed && !leftRight)
             {
                 sonic.getAnimationIndex() = EDGER;
                 sonic.getStates()[EDGER][0].RunAnimation();
             }
            if(!sonic.getHasKnockedBack())
                sonic.getHasKnockedBack() = collisionCheckWithSpikes(lvl,offset_y,hit_box_factor_y,hit_box_factor_x,sonic.getPheight(), sonic.getPwidth(), sonic.getx(), sonic.gety(), cell_size, sonic.getVelocityY());
             //cout << "sonic.getHasKnockedBack() = " << sonic.getHasKnockedBack() << endl;
             if (sonic.getHasKnockedBack())
                {
                    sonic.getx() -= 6;
                    sonic.gety() += sonic.getTempVelocityY();
                    sonic.getTempVelocityY() += sonic.getTempGravity();
                    if (sonic.getTempVelocityY() >= 0)
                    {
                        sonic.playerVirtualGravity(lvl, offset_y, offset_x, cell_size,spacePressed);
                    }
                }
             if (sonic.getOnGround())
             {
                 sonic.getHasKnockedBack() = false;
                 sonic.getTempVelocityY() = -7;
             }
            if(!sonic.getHasKnockedBack())
                sonic.player_gravity(lvl, offset_y,offset_x, cell_size, spacePressed);

            draw_bg(window, backGroundSprite, offset_x);

            display_level(window, height, width, lvl, walls, cell_size, offset_x);

            sonic.draw_player(window, sonic.getStates()[sonic.getAnimationIndex()][0].getSprites()[sonic.getStates()[sonic.getAnimationIndex()]->getIndex()],offset_x);

            // change these according to the movement logic of motobug, for now it moves with player
            
            draw_crabs( window, crabs->getSprite(), crabs, crabCount, offset_x);


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


void draw_crabs(RenderWindow& window, Sprite& crab, Crabmeat crabs[], int& crabCount, int offset_x) 
{
    for (int i = 0; i < crabCount; i++) {

        crabs[i].movement();
        crabs[i].draw(window, offset_x);

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

                //cout << "Found platform from tile " << start << " to " << end << " at row " << i << endl;

            }

            else {

                j++;
            }


        }

    }


}

void move_crabs(Crabmeat crabs[], int CrabStart[], int CrabEnd[], int CrabWalls[], int& indexCrab, int& crabIndex, int& crabCount , Sprite& sprite) {

    for (int i = 0; i < crabCount; i++) {

        if (crabIndex < 10) {

            float patrolStart = CrabStart[i] * 64;
            float crabmeatEnd = CrabEnd[i] * 64;
            float crabmeatmaxEnd = patrolStart + 12 * 64;
            float patrolEnd = (crabmeatEnd > crabmeatmaxEnd) ? crabmeatmaxEnd : crabmeatEnd;

            float crabX = (patrolStart + patrolEnd) / 2.0f;
            float crabY = (CrabWalls[i] + 1) * 64 - 44.0f;

            crabs[crabIndex].setPositionAndPatrol(crabX, crabY, patrolStart, patrolEnd);

            //cout << "plcd crabb " << crabIndex << ": " << crabX << ", " << crabY << endl;

            crabIndex++;

        }
    }

    //cout << "detec " << indexCrab << " crab platform rangrs" << endl


    crabCount = crabIndex;

}
void placeSpikesUnderPlatforms(char** lvl, int height, int width) {

    for (int i = 1; i < height ; i++) {

        for (int j = 0; j < width; j++) {

            if ((lvl[i][j] == 'w' || lvl[i][j] == 'q' || lvl[i][j] == 'e') && lvl[i - 1][j] == 's' && lvl[i + 1][j] == 's') {

                if (rand() % 100 < 10) {

                    lvl[i + 1][j] = 'p';
                }
            }
        }
    }
}
bool checkCollision(char** lvl, int player_x, int player_y)
{
    return !(lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q' || lvl[player_y / 64][player_x / 64] == 'p');
}
