#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//////////////////////////////


//#include"Player.h"
//#include"Sonic.h"
//#include"Collectibles.h"
//#include"Rings.h"
//#include"Motobug.h"
//#include"Enemy.h"
//#include"Crabmeat.h"
//#include"Beebot.h"
//#include"Batbrain.h"
//#include"Eggstinger.h"
//#include"Menu.h"
//#include"Knuckles.h"
//#include"TailedFox.h"
//#include"Team.h"
#include"StateManager.h"

//////////////////////////////


using namespace sf;
using namespace std;

int screen_x = 1200;
int screen_y = 900;


void draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord);
bool checkCollision(char** lvl,int x,int y);
bool collisionCheckWithSpikes(char** lvl, int offset_y, int hit_box_factor_y, int hit_box_factor_x, int Pheight, int Pwidth, int x, int y, int cell_size, int velocityY);

int main()
{
    //trying new main
    RenderWindow window;
    window.create(VideoMode(screen_x, screen_y), "Sonic the Hedgehog", Style::Close | Style::Resize | Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    Leaderboard* leaderboard = new Leaderboard();
    StateManager game(leaderboard,window);
    game.run();
}


