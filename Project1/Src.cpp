#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//////////////////////////////

#include"player.h"
#include"Motobug.h"
#include"Enemy.h"
#include"Crabmeat.h"
#include"Beebot.h"
#include"Batbrain.h"
#include"Eggstinger.h"

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
void designlvl1(char**);
bool checkCollision(char** lvl,int player_x,int player_y);
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

    sf::Vector2u textureSize = backGround.getSize(); // original size of the image
    sf::Vector2u windowSize = window.getSize(); // size of your SFML window

    // Scale the sprite
    backGroundSprite.setScale((float)windowSize.x / textureSize.x,(float)windowSize.y / textureSize.y
  );


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

    Sprite walls[4] = { wallSprite1,wall2Sprite,wall3Sprite,spikes };


    //sf::FloatRect wall1bounds = wall2Sprite.getGlobalBounds();
    //cout << "Width pf the 1st wall : " << wall1bounds.width << "----" << " Heifht = " << wall1bounds.height << "\n";
    //////////////////////////////////////////

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
    designlvl1(lvl);
    ///////////////////////////////////////
    //////  using virtual bufferZone///////
    ///////////////////////////////////////
    int buffer_start = 4 * 64;
    int buffer_end = 13 * 64;
    Texture buffer;
    buffer.loadFromFile("Data/bufferSprite.png");
    Sprite bufferSpriteStart(buffer);
    Sprite bufferSpriteEnd(buffer);










    ////////////////////////////////////////////////////////
    Player sonic;
    float player_x = 150;
    float player_y = 150;
    bool hasCollided = false;

    float max_speed = 15;

    float velocityX = 0;
    float velocityY = 0;
    bool spacePressed = false;// our own defined
    bool collisionDetectedOffGround = false;

    float jumpStrength = -20; // Initial jump velocity
    float gravity = 1;        // Gravity acceleration

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

    const int totalMenuOptions = 6;
    const char* menuOptions[totalMenuOptions] = { "New Game", "Options", "Continue", "Leader Board", "Credits", "Exit" };
    int alignmentofTEXT[totalMenuOptions] = { 169, 117, 137, 205, 107, 54 }; // these are the pixels of text written in the above array
    int selectedOption = 0;

    Font font;
    font.loadFromFile("Fonts/arial.ttf");
    Text text[totalMenuOptions];

    Text title("Sonic Classic Heroes", font, 64);
    title.setFillColor(Color::Yellow);
    title.setPosition(352.5f, 80);

    for (int i = 0; i < totalMenuOptions; i++)
    {

        Text temp(menuOptions[i], font, 42);
        temp.setPosition(float(screen_x / 2) - float(alignmentofTEXT[i] / 2), float(screen_y / 3.6) + float(i * screen_y / 12));
        text[i] = temp;
    }

    bool gameState = false;
    bool menuState = true;
    bool arrowUp = false;
    bool arrowDown = false;
    bool enter = false;

    Motobug enemy;


    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////DECLARING ENEMIES///////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////


    Motobug bug;
    Crabmeat crab;
    Beebot beebot;
    Batbrain bat;
    Eggstinger stinger;

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
        if (menuState)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (arrowUp == false)
                {
                    selectedOption--;
                    if (selectedOption < 0)
                    {

                        selectedOption = totalMenuOptions - 1;
                    }
                    arrowUp = true;
                }
            }
            else
            {
                arrowUp = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (arrowDown == false)
                {
                    selectedOption++;
                    if (selectedOption >= totalMenuOptions)
                    {

                        selectedOption = 0;
                    }
                    arrowDown = true;
                }
            }
            else
            {
                arrowDown = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if (enter == false)
                {
                    if (selectedOption == 0)
                    {
                        menuState = false;
                        gameState = true;
                    }
                    else if (selectedOption == totalMenuOptions - 1)
                    {
                        window.close();
                    }
                    enter = true;
                }
            }
            else
            {
                enter = false;
            }

            for (int i = 0; i < totalMenuOptions; i++)
            {

                text[i].setFillColor(i == selectedOption ? Color::Blue : Color::White);
            }

            window.draw(title);

            for (int i = 0; i < totalMenuOptions; i++)
            {

                window.draw(text[i]);
            }
        }

        else if (gameState)
        {
            if (onGround)
                collisionDetectedOffGround = false;//resetting the bool if player hits the platform
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
             {
                ///////////////////////////////////////
                // i have to change this afterwards////
                ///////////////////////////////////////
             
                /////dont check when collision is detetced off the ground till the player is off the ground/////
                 if (checkCollision(lvl, sonic.getx() - 15, sonic.gety()) && checkCollision(lvl, sonic.getx() - 15, sonic.gety() + Pheight - 1) && checkCollision(lvl, sonic.getx() - 15, sonic.gety() + Pheight / 2) && player_x > 0)
                 {
                     sonic.getx() -= 15;
                     if (buffer_start > 4 * 64 && sonic.getx() <= buffer_start)
                     {
                         buffer_start = sonic.getx();
                         buffer_end = buffer_start + 576;
                         offset_x -= 15;
                     }
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
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
             {
                 if (checkCollision(lvl, sonic.getx() + Pwidth + 15 - 1, sonic.gety()) && checkCollision(lvl, sonic.getx() + Pwidth + 15 - 1, sonic.gety() + Pheight - 1) && checkCollision(lvl, sonic.getx() + Pwidth + 15 - 1, sonic.gety() + Pheight / 2))
                 {
                     sonic.getx() += 15;
                     if (buffer_end < 106 * 64 && sonic.getx() >= buffer_end)
                     {
                         buffer_end = sonic.getx();
                         buffer_start = buffer_end - 576;
                         offset_x += 15;
                     }
                 }
                 else
                 {
                     if(velocityY >= 0)
                     velocityY = 15;
                 }
             }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed )
             {
                 
                 velocityY = -19.6;
                 onGround = false;
                 spacePressed = true;
                
             }
            player_gravity(lvl, offset_y,offset_x, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, sonic.getx(), sonic.gety(), cell_size, Pheight, Pwidth, spacePressed);
            display_level(window, height, width, lvl, walls, cell_size, offset_x);
            draw_player(window, LstillSprite, sonic.getx() - offset_x, sonic.gety());
            //draw_bg(window, backGroundSprite, offset_x);

			enemy.movement(sonic.getx(), sonic.gety());
			enemy.draw(window);
            // change these according to the movement logic of motobug, for now it moves with player
            bug.movement(sonic.getx(), sonic.gety());
            bug.draw(window);

            crab.movement();
            crab.draw(window);

            beebot.movement();
            beebot.draw(window);

			bat.movement(sonic.getx(), sonic.gety());
            bat.draw(window);

            stinger.movement(sonic.getx(), sonic.gety());
            stinger.draw(window);

          /*  draw_buffer(window, bufferSpriteStart, buffer_start - offset_x);
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
    char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
    char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size) ];
    char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];

    char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
    char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
    char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];
    bool forLeft = topLeft != 'w' && topLeft != 'q' && topLeft != 'e';
    bool forMiddle = topMiddle != 'w' && topMiddle != 'q' && topMiddle != 'e';
    bool forRight = topRight != 'w' && topRight != 'q' && topRight != 'e';
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
void designlvl1(char** lvl)
{
    // Fill entire level with sky
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 110; j++)
            lvl[i][j] = 's';

    // Top ceiling rows
    for (int j = 0; j < 110; j++) {
        lvl[0][j] = 'q';
        lvl[1][j] = 'q';
    }

    // Bottom ground rows with pits
    for (int j = 0; j < 110; j++) {
        // Leave some pits
        if ((j >= 15 && j < 18) || (j >= 40 && j < 43) || (j >= 80 && j < 84))
            continue;
        lvl[12][j] = 'w';
        lvl[13][j] = 'w';
    }

    // Add vertical ceiling drops every 20 tiles
    for (int j = 10; j < 110; j += 20) {
        lvl[2][j] = 'q';
        lvl[3][j] = 'q';
    }

    // Add structured platforms with increasing/decreasing height
    for (int j = 5; j < 15; j++)
        lvl[8][j] = (j % 2 == 0) ? 'e' : 'q';  // Low platform

    for (int j = 25; j < 30; j++)
        lvl[6][j] = (j % 2 == 0) ? 'q' : 'e';  // Medium

    for (int j = 45; j < 50; j++)
        lvl[5][j] = (j % 2 == 0) ? 'e' : 'q';  // Higher

    for (int j = 66; j < 72; j++)
        lvl[6][j] = (j % 2 == 0) ? 'q' : 'e';  // Medium again

    for (int j = 90; j < 96; j++)
        lvl[8][j] = (j % 2 == 0) ? 'e' : 'q';  // Low again

    // Spikes on ground
    lvl[11][14] = 'p';
    lvl[11][19] = 'p';
    lvl[11][42] = 'p';
    lvl[11][86] = 'p';

    // Spikes on platforms
    lvl[7][6] = 'p';
    lvl[5][27] = 'p';
    lvl[4][47] = 'p';
    lvl[7][92] = 'p';
}



bool checkCollision(char** lvl, int player_x, int player_y)
{
    return !(lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q');
}




