//#pragma once
//#include"Game.h"
////#include<iostream>
////using namespace std;
////using namespace sf;
//bool Game:: collisionCheckWithSpikes(char** lvl, int offset_y, int hit_box_factor_y, int hit_box_factor_x, int Pheight, int Pwidth, int player_x, int player_y, int cell_size, int velocityY)
//{
//    offset_y = player_y;
//    offset_y += velocityY;
//    char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
//    char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
//    char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];
//
//    char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x) / cell_size)];
//    char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth) / cell_size)];
//    char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(player_x + hit_box_factor_x + Pwidth / 2) / cell_size)];
//    bool forLeft = topLeft != 'w' && topLeft != 'q' && topLeft != 'e';
//    bool forMiddle = topMiddle != 'w' && topMiddle != 'q' && topMiddle != 'e';
//    bool forRight = topRight != 'w' && topRight != 'q' && topRight != 'e';
//
//    //cout << "Left : " << bottom_left_down << " ---- Mid : " << bottom_mid_down << " -------" << "Right : " << bottom_right_down << "----";
//
//    return ((bottom_left_down == 'p' || bottom_mid_down == 'p' || bottom_right_down == 'p') && velocityY > 0 && (forLeft || forMiddle || forRight));
//}
//void Game::draw_buffer(RenderWindow& window, Sprite& bufferSprite, int buffer_coord)
//{
//    bufferSprite.setPosition(buffer_coord, 500);
//    window.draw(bufferSprite);
//}
//void draw_bg(RenderWindow& window, Sprite& bgSprite, int offset_x)
//{
//    bgSprite.setPosition(0, 0);
//    window.draw(bgSprite);
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////Rings////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//void Game:: placeRingsFromMap(char** lvl, Collectibles*** collectibles, int height, int width, Texture* rings, Texture* afterEffect)
//{
//
//    for (int i = 0; i < height; ++i) {
//
//        for (int j = 0; j < width; ++j) {
//
//            if (lvl[i][j] == 'r') {
//
//                collectibles[i][j] = new Ring(j, i, rings, afterEffect);
//            }
//        }
//    }
//}
//void Game::updateAndDrawCollectibles(Collectibles*** collectibles, int height, int width, RenderWindow& window) {
//    for (int i = 0; i < height; ++i)
//    {
//        for (int j = 0; j < width; ++j)
//        {
//            if (collectibles[i][j])
//            {
//                collectibles[i][j]->update();
//                collectibles[i][j]->draw(window);
//            }
//        }
//    }
//}
//
//void Game:: handleRingCollection(Collectibles*** collectibles, char** lvl, int height, int width, Player& player, int& ringsCollected, int cell_size) {
//
//
//    for (int i = 0; i < height; ++i) {
//
//        for (int j = 0; j < width; ++j) {
//
//            if (collectibles[i][j] && collectibles[i][j]->isActive()) {
//
//                float ring_x = j * cell_size;
//                float ring_y = i * cell_size + 12;
//
//                int frameIndex = collectibles[i][j]->getIndex();
//                float rawWidths[4] = { 66, 56, 32, 53 };
//                float ringWidth = rawWidths[frameIndex] * 0.75f;
//                float ringHeight = 66 * 0.75f;
//
//                if (player.getx() + player.getPwidth() > ring_x && player.getx() < ring_x + ringWidth
//                    && player.gety() + player.getPheight() > ring_y && player.gety() < ring_y + ringHeight) {
//
//                    collectibles[i][j]->collect();
//                    ringsCollected++;
//                    lvl[i][j] = 's';
//
//                }
//            }
//        }
//    }
//}
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////Rings////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//char Game::getMapValues(int val)
//{
//    switch (val)
//    {
//    case 0: return 's';
//    case 1: return 'q';
//    case 2: return 'w';
//    case 3: return 'e';
//    case 4: return 'p';
//    case 5: return 'r';
//    default: return 's';
//    }
//}
//void Game:: display_level(RenderWindow& window, const int height, const int width, char** lvl, Sprite walls[], const int cell_size, int offset_x)
//{
//    for (int i = 0; i < height; i += 1)
//    {
//        for (int j = 0; j < width; j += 1)
//        {
//            if (lvl[i][j] == 's')
//                continue;
//            else if (lvl[i][j] == 'w')
//            {
//                walls[0].setPosition(j * cell_size - offset_x, i * cell_size);
//                window.draw(walls[0]);
//            }
//            else if (lvl[i][j] == 'q')
//            {
//                walls[1].setPosition(j * cell_size - offset_x, i * cell_size);
//                window.draw(walls[1]);
//            }
//            else if (lvl[i][j] == 'e')
//            {
//                walls[2].setPosition(j * cell_size - offset_x, i * cell_size);
//                window.draw(walls[2]);
//            }
//            else if (lvl[i][j] == 'p')
//            {
//                walls[3].setPosition(j * cell_size - offset_x, i * cell_size);
//                window.draw(walls[3]);
//            }
//        }
//    }
//}
//void Game:: designlvl1(char** lvl, const char* filename, const int height, const int width)
//{
//    ifstream in("lvl1.txt");
//
//    for (int i = 0; i < height; i++) {
//
//        for (int j = 0; j < width; j++) {
//
//            int wall;
//            in >> wall;
//            lvl[i][j] = getMapValues(wall);
//        }
//    }
//    in.close();
//}
//
//
//bool Game:: PlayerCrabCollision(float player_x, float player_y, int Pwidth, int Pheight, float enemy_x, float enemy_y, const float enemyWidth, const float enemyHeight)
//{
//    return (player_x + Pwidth > enemy_x && player_x < enemy_x + enemyWidth && player_y + Pheight > enemy_y && player_y < enemy_y + enemyHeight);
//}
//
//bool Game:: CollisionCheckWithCrabs(Crabmeat** crabs, int& crabCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float crabWidth, const float crabHeight)
//{
//
//    for (int i = 0; i < crabCount; i++) {
//
//        if (!crabs[i]->alive()) {
//            continue;
//        }
//
//        if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, crabs[i]->getX(), crabs[i]->getY(), crabWidth, crabHeight)) {
//
//            float bottom_of_Player = player_y + Pheight;
//            float top_of_Crab = crabs[i]->getY();
//
//            if (bottom_of_Player - 10 < top_of_Crab) {
//
//                // crab ko marna hai ab becoz top collision, also add smoke effect and invincibilty 
//                cout << " Top-hit:  " << i << endl;
//
//                cout << "PlyrX: " << player_x << "crab X: " << crabs[i]->getX() << endl;
//
//                velocityY = -10.0f;
//            }
//
//            else {
//
//                hasKnockedBack = true;
//                tempVelocityY = -7;
//
//                crabs[i]->setAnimation(3);
//                crabs[i]->RunNewAnimation();
//                crabs[i]->setAttack();
//
//                //cout << "PlyrX " << centre_of_Player << " Crab CenterX " << centre_of_CRab << endl;
//
//                //cout << " Sidehit " << i << endl;
//
//                //cout << "PlyrX " << player_x << " Crab X " << crabs[i].getX() << endl;
//            }
//            return true;
//        }
//    }
//
//    return false;
//}
//
//
//
//bool Game::checkCollision(char** lvl, int player_x, int player_y)
//{
//    return !(lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q' || lvl[player_y / 64][player_x / 64] == 'p');
//}
//
//bool Game::CollisionCheckWithBeebots(Beebot** beebots, int& beeCount, float& player_x, float& player_y, int Pwidth, int Pheight, float& velocityY, bool& hasKnockedBack, float& tempVelocityY, const float beeWidth, const float beeHeight, bool onGround, bool spacePressed)
//{
//
//    for (int i = 0; i < beeCount; i++) {
//
//        if (!beebots[i]->alive()) {
//            continue;
//        }
//
//        if (PlayerCrabCollision(player_x, player_y, Pwidth, Pheight, beebots[i]->getX(), beebots[i]->getY(), beeWidth, beeHeight)) {
//
//            if (!(onGround == false && spacePressed == true)) {
//                hasKnockedBack = true;
//                tempVelocityY = -7; // knockback upwards initially
//                cout << "Player hit by Beebot --- thrown back" << endl;
//            }
//
//            return true;
//        }
//    }
//
//    return false;
//}
