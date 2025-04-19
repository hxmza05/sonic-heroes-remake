#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;

// prototypes
void player_gravity(char** lvl, float& offset_y,float&, float& velocityY, bool& onGround, float& gravity, float& terminal_Velocity, int& hit_box_factor_x, int& hit_box_factor_y, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth,bool &spacePressed);

void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y);

void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, Sprite& wallSprite2, Sprite& wallSprite3, const int cell_size,int off_x);
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//////////////This is from where our own defined fucntions start from//////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord);
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
    Texture wallTex1;
    wallTex1.loadFromFile("Data/brick1.png");
    Sprite wallSprite1(wallTex1);


    Texture wall2;
    wall2.loadFromFile("Data/brick2.png");
    Sprite wall2Sprite(wall2);

    Texture wall3;
    wall3.loadFromFile("Data/brick3.png");
    Sprite wall3Sprite(wall3);

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
    buffer.loadFromFile("C:/Users/PMLS/Desktop/oop project/Skeleton-final/Data/bufferSprite.png");
    Sprite bufferSpriteStart(buffer);
    Sprite bufferSpriteEnd(buffer);










    ////////////////////////////////////////////////////////
    float player_x = 150;
    float player_y = 150;

    float max_speed = 15;

    float velocityX = 0;
    float velocityY = 0;
    bool spacePressed = false;

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

    ////////////////////////////////////////////////////////

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
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && checkCollision(lvl, player_x - 64 , player_y) && player_x > 0)
             {
                 ////////////////////////////////////
                 // i have to change this afterwards
                 ///////////////////////////////////
                 player_x -= 15;
                 if (buffer_start > 4 * 64  && player_x <= buffer_start)
                 {
                     buffer_start = player_x;
                     buffer_end = buffer_start + 576;
                     offset_x -= 15;
                 }

             }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && checkCollision(lvl,player_x + 64 ,player_y))
             {

                 player_x += 15;
                 if (buffer_end < 106 * 64 && player_x >= buffer_end)
                 {
                     buffer_end = player_x;
                     buffer_start = buffer_end - 576;
                     offset_x += 15;
                 }
             }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !spacePressed )
             {
                 
                 velocityY = -19.6;
                 onGround = false;
                 spacePressed = true;
                
             }
            player_gravity(lvl, offset_y,offset_x, velocityY, onGround, gravity, terminal_Velocity, hit_box_factor_x, hit_box_factor_y, player_x, player_y, cell_size, Pheight, Pwidth,spacePressed);
            display_level(window, height, width, lvl, wallSprite1, wall2Sprite,wall3Sprite, cell_size, offset_x);
            draw_player(window, LstillSprite, player_x - offset_x, player_y);
         /*   draw_buffer(window, bufferSpriteStart, buffer_start - offset_x);
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


    char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size) + ((int)((offset_x + offset_x)/2)/cell_size)];
    char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size) + ((int)((offset_x + offset_x) / 2) / cell_size)];
    char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size) + ((int)((offset_x + offset_x) / 2) / cell_size)];

    if (bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w'|| bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e'|| bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q')
    {
        onGround = true;
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

void draw_player(RenderWindow& window, Sprite& LstillSprite, float player_x, float player_y)
{

    LstillSprite.setPosition(player_x, player_y);
    window.draw(LstillSprite);
}
void display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite& wallSprite1, Sprite& wallSprite2, Sprite& wallSprite3, const int cell_size,int offset_x)
{
    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < width; j += 1)
        {
            if (lvl[i][j] == 's')
                continue;
            else if (lvl[i][j] == 'w')
            {
                wallSprite1.setPosition(j * cell_size - offset_x, i * cell_size);
                window.draw(wallSprite1);
            }
            else if (lvl[i][j] == 'q')
            {
                wallSprite2.setPosition(j * cell_size - offset_x, i * cell_size);
                window.draw(wallSprite2);
            }
            else if (lvl[i][j] == 'e')
            {
                wallSprite3.setPosition(j * cell_size - offset_x, i * cell_size);
                window.draw(wallSprite3);
            }
        }
    }
}
void designlvl1(char** lvl)
{
  
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 110; j++)
        {
            lvl[i][j] = 's';
        }
    }
    for (int i = 0; i < 110; i++)
    {
        if (rand() % 12 != 0) 
        {
            if(rand() & 1)
                lvl[12][i] = 'w';
            else 
            lvl[12][i] = 'e';
            if (rand() & 1)
                lvl[11][i] = 'q';
            else lvl[11][i] = 'e';
        }
    }
    for (int i = 0; i < 110; i += 20)
    {
        lvl[2][i] = 'q';
        lvl[3][i] = 'q';
    }
    for (int i = 5; i < 105; i += 10)
    {
        int height = 7 + rand() % 3; 
        for (int j = 0; j < 5; j++)
        {
            lvl[height][i + j] = (j % 2 == 0) ? 'e' : 'q'; 
        }
    }
    for (int i = 20; i < 110; i += 25)
    {
        for (int j = 10; j < 12; j++)
        {
            lvl[j][i] = 'e';
        }
        for (int j = 8; j < 10; j++)
        {
            lvl[j][i] = 'w';
        }
    }
    for (int i = 0; i < 110; i += 13)
    {
        if (rand() % 2 == 0)
            lvl[5][i] = 'b';
    }
    for (int i = 0;i < 110;i++)
    {
        lvl[1][i] = 'q';
        lvl[0][i] = 'q';
    }
}
bool checkCollision(char** lvl, int player_x, int player_y)
{
    /*if (player_x % 64 == 0)
        player_x -= 32;*/
    return !(lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q');
}




