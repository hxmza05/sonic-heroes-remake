#pragma once
#include "Player.h"
// #include"Game.h"
#include "GlobalFunctions.h"

// #include"Src.cpp"
void Player::draw_player(RenderWindow& window, Sprite& LstillSprite, float offset_x)
{
    LstillSprite.setPosition(x - offset_x, y);
    window.draw(LstillSprite);
}
void Player::player_gravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed, int height, int width,bool&gameOver)
{
    //cout << "\nIn player Gravity\n";
    offset_y = y;
    offset_y += velocityY;
    if ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size >= height)
    {
        gameOver = true;
        return;
    }
    int headY = (int)(y + hit_box_factor_y) / cell_size;
    int tileLeftX = (int)(x + hit_box_factor_x) / cell_size;
    int tileRightX = (int)(x + hit_box_factor_x + Pwidth - 1) / cell_size;

    // Clamp indices
    if (headY < 0)
        headY = 0;
    else if (headY >= height)
        headY = height - 1;

    if (tileLeftX < 0)
        tileLeftX = 0;
    else if (tileLeftX >= width)
        tileLeftX = width - 1;

    if (tileRightX < 0)
        tileRightX = 0;
    else if (tileRightX >= width)
        tileRightX = width - 1;

    bool hitsTopRow = (headY == 0 || headY == 1);
    bool leftHit = (lvl[headY][tileLeftX] == 'w' || lvl[headY][tileLeftX] == 'q' || lvl[headY][tileLeftX] == 'e');
    bool rightHit = (lvl[headY][tileRightX] == 'w' || lvl[headY][tileRightX] == 'q' || lvl[headY][tileRightX] == 'e');

    if (velocityY < 0 && hitsTopRow && (leftHit || rightHit))
    {
        velocityY = 0;
    }

    // Bottom collision check
    int row_bottom = (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
    int col_left = (int)(x + hit_box_factor_x) / cell_size;
    int col_right = (int)(x + hit_box_factor_x + Pwidth) / cell_size;
    int col_mid = (int)(x + hit_box_factor_x + Pwidth / 2) / cell_size;

    if (row_bottom < 0)
        row_bottom = 0;
    else if (row_bottom >= height)
        row_bottom = height - 1;
    if (col_left < 0)
        col_left = 0;
    else if (col_left >= width)
        col_left = width - 1;
    if (col_right < 0)
        col_right = 0;
    else if (col_right >= width)
        col_right = width - 1;
    if (col_mid < 0)
        col_mid = 0;
    else if (col_mid >= width)
        col_mid = width - 1;

    char bottom_left_down = lvl[row_bottom][col_left];
    char bottom_right_down = lvl[row_bottom][col_right];
    char bottom_mid_down = lvl[row_bottom][col_mid];

    int row_top = (int)(offset_y + hit_box_factor_y + 39) / cell_size;

    if (row_top < 0)
        row_top = 0;
    else if (row_top >= height)
        row_top = height - 1;

    char topLeft = lvl[row_top][col_left];
    char topMiddle = lvl[row_top][col_right];
    char topRight = lvl[row_top][col_mid];

    bool forLeft = topLeft == 's';
    bool forMiddle = topMiddle == 's';
    bool forRight = topRight == 's';

    if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' ||
        bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' ||
        bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') &&
        velocityY > 0 && (forLeft || forMiddle || forRight))
    {
        onGround = true;
        velocityY = 0;
        spacePressed = false;
    }
    else
    {
        y = offset_y;
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

void Player::player_dummy_gravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed, int height, int width)
{
    //cout << "\nIn player dummy Gravity\n";

    offset_y = y;
    offset_y += velocityY;

   /* if ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size >= height)
    {
        gameOver = true;
        return;
    }*/

    int headY = (int)(y + hit_box_factor_y) / cell_size;
    int tileLeftX = (int)(x + hit_box_factor_x) / cell_size;
    int tileRightX = (int)(x + hit_box_factor_x + Pwidth - 1) / cell_size;

    // Clamp top head indices
    if (headY < 0)
        headY = 0;
    else if (headY >= height)
        headY = height - 1;

    if (tileLeftX < 0)
        tileLeftX = 0;
    else if (tileLeftX >= width)
        tileLeftX = width - 1;

    if (tileRightX < 0)
        tileRightX = 0;
    else if (tileRightX >= width)
        tileRightX = width - 1;

    bool hitsTopRow = (headY == 0 || headY == 1);
    bool leftHit = (lvl[headY][tileLeftX] == 'w' || lvl[headY][tileLeftX] == 'q' || lvl[headY][tileLeftX] == 'e');
    bool rightHit = (lvl[headY][tileRightX] == 'w' || lvl[headY][tileRightX] == 'q' || lvl[headY][tileRightX] == 'e');

    if (velocityY < 0 && hitsTopRow && (leftHit || rightHit))
    {
        velocityY = 0;
    }

    int row_bottom = (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
    int col_left = (int)(x + hit_box_factor_x) / cell_size;
    int col_right = (int)(x + hit_box_factor_x + Pwidth) / cell_size;
    int col_mid = (int)(x + hit_box_factor_x + Pwidth / 2) / cell_size;

    // Clamp bottom collision check indices
    if (row_bottom < 0)
        row_bottom = 0;
    else if (row_bottom >= height)
        row_bottom = height - 1;

    if (col_left < 0)
        col_left = 0;
    else if (col_left >= width)
        col_left = width - 1;

    if (col_right < 0)
        col_right = 0;
    else if (col_right >= width)
        col_right = width - 1;

    if (col_mid < 0)
        col_mid = 0;
    else if (col_mid >= width)
        col_mid = width - 1;

    char bottom_left_down = lvl[row_bottom][col_left];
    char bottom_right_down = lvl[row_bottom][col_right];
    char bottom_mid_down = lvl[row_bottom][col_mid];

    int row_top = (int)(offset_y + hit_box_factor_y + 39) / cell_size;

    // Clamp top row index
    if (row_top < 0)
        row_top = 0;
    else if (row_top >= height)
        row_top = height - 1;

    char topLeft = lvl[row_top][col_left];
    char topMiddle = lvl[row_top][col_right];
    char topRight = lvl[row_top][col_mid];

    bool forLeft = topLeft == 's';
    bool forMiddle = topMiddle == 's';
    bool forRight = topRight == 's';

    if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' ||
        bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' ||
        bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') &&
        velocityY > 0 && (forLeft || forMiddle || forRight))
    {
        onGround = true;
        velocityY = 0;
        spacePressed = false;
    }
    else
    {
        y = offset_y;
        onGround = false;
    }

    if (!onGround)
    {
        velocityY += dummyGravity;
        if (velocityY >= terminal_Velocity)
            velocityY = terminal_Velocity;
    }
    else
    {
        velocityY = 0;
        spacePressed = false;
    }
}
void Player::playerVirtualGravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed, int height, int width, bool& gameOver)
{
    offset_y = y;
    offset_y += tempVelocityY;

    if ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size >= height) 
    {
        gameOver = true;
        return;
    }

    int row_bottom = (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
    int row_top = (int)(offset_y + hit_box_factor_y + 39) / cell_size;
    int col_left = (int)(x + hit_box_factor_x) / cell_size;
    int col_right = (int)(x + hit_box_factor_x + Pwidth) / cell_size;
    int col_mid = (int)(x + hit_box_factor_x + Pwidth / 2) / cell_size;

    if (row_bottom >= height || row_top >= height) {
        gameOver = true;
        return;
    }

    char bottom_left_down = lvl[row_bottom][col_left];
    char bottom_right_down = lvl[row_bottom][col_right];
    char bottom_mid_down = lvl[row_bottom][col_mid];

    char topLeft = lvl[row_top][col_left];
    char topMiddle = lvl[row_top][col_right];
    char topRight = lvl[row_top][col_mid];

    bool forLeft = topLeft == 's';
    bool forMiddle = topMiddle == 's';
    bool forRight = topRight == 's';

    if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' ||
        bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' ||
        bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') &&
        tempVelocityY > 0 && (forLeft || forMiddle || forRight))
    {
        onGround = true;
        tempVelocityY = 0;
        spacePressed = false;
    }
    else 
    {
        y = offset_y;
        tempVelocityY += tempGravity;
        onGround = false;
    }
}
void Player::decelerate(char** lvl, int width,float friction)
{

    int tempAnimationIndex = STILL;
    if (velocityX > 0)
    {
        velocityX -= friction;
        tempAnimationIndex = EDGER;

        if (velocityX < 0)
        {
            tempAnimationIndex = STILL;
            velocityX = 0;
        }
    }
    else if (velocityX < 0)
    {
        velocityX += friction;
        tempAnimationIndex = EDGEL;

        if (velocityX > 0)
        {
            velocityX = 0;
            tempAnimationIndex = STILL;
        }

    }
    int calculated_x = x + velocityX;
    if (checkCollision(lvl, calculated_x + hit_box_factor_x, y + hit_box_factor_y, 14, width) && (checkCollision(lvl, calculated_x + hit_box_factor_x + Pwidth - 1, y + hit_box_factor_y + Pheight - 10, 14, width) /*|| checkCollision(lvl, calculated_x + hit_box_factor_x + Pwidth - 1, y + hit_box_factor_y, 14, width)*/))
    {
        x += velocityX;
        indexAnimation = tempAnimationIndex;
    }
    else
    {
        //cout << "Collisoin Detected ";
        velocityX = 0;
    }
    //cout << "VeloctiyX  after frictio = " << velocityX << endl << endl;
}
void Player::decelerateRight(char** lvl, int width, float friction)
{
    //cout << "\n\nIn decelration : \n friction : " << friction << endl;
    //cout << "Vecloity before frition : " << velocityX;
    int tempAnimationIndex = STILL;
    if (velocityX > 0)
    {
        velocityX -= friction;
        tempAnimationIndex = EDGER;

        if (velocityX < 0)
        {
            tempAnimationIndex = STILL;
            velocityX = 0;
        }
    }
    else if (velocityX < 0)
    {
        velocityX += friction;
        tempAnimationIndex = EDGEL;

        if (velocityX > 0)
        {
            velocityX = 0;
            tempAnimationIndex = STILL;
        }

    }
    int calculated_x = x + velocityX;
    if (checkCollision(lvl, calculated_x + hit_box_factor_x, y + hit_box_factor_y, 14, width) && (checkCollision(lvl, calculated_x + hit_box_factor_x, y + hit_box_factor_y + Pheight - 10, 14, width) /*|| checkCollision(lvl, calculated_x + hit_box_factor_x + Pwidth - 1, y + hit_box_factor_y, 14, width)*/))
    {
        x += velocityX;
        indexAnimation = tempAnimationIndex;
    }
    else
    {
        //cout << "Collisoin Detected ";
        velocityX = 0;
    }
    //cout << "VeloctiyX  after frictio = " << velocityX << endl << endl;
}

void Player::moveLeft(char** lvl, int width ,float friction)
{
    //checking for current position espcially wfor when we switch the keys insatbtly over th edge
    if (velocityX > 0)
    {
		decelerate(lvl, width, friction);
        return;
    }
    int  proposed_x = x + velocityX;
    if (!checkCollision(lvl, proposed_x + hit_box_factor_x, y + hit_box_factor_y, 14, width) && !checkCollision(lvl, proposed_x + hit_box_factor_x, y + hit_box_factor_y + Pheight - 1, 14, width))
    {
        //cout << "Collsion Detecetd (LEFT) : \n";
        velocityX = 0;  
        return;
    }
    //cout << "\n\nIn Left its working \n\n\n";
    x = proposed_x;
    if (velocityX - acceleration > -max_speed)
    {
        velocityX -= acceleration;
    }
    if (velocityX > -10)
    {
        indexAnimation = LEFT;
        states[LEFT][0].RunAnimation();
    }
    else
    {
        indexAnimation = LEFTRUN;
        states[LEFTRUN][0].RunAnimation();
    }
    if (velocityX > 0)
    {
        indexAnimation = EDGER;
    }
    direction = 0;
}

void Player::moveRight(char** lvl, int width,float friction)
{
    int proposed_x = x + velocityX;
    if (velocityX < 0)
    {
		decelerateRight(lvl, width, friction);
		return;
    }
    if (!checkCollision(lvl, proposed_x + hit_box_factor_x, y + hit_box_factor_y, 14, width) && !checkCollision(lvl, proposed_x + hit_box_factor_x, y + hit_box_factor_y + Pheight - 1, 14, width) )
    {
        //cout << "Collsion Detecetd (RIGHT) : \n";

        velocityX = 0;  
        return;
    }
    x = proposed_x;
    if (velocityX + acceleration < max_speed)
    {
        velocityX += acceleration;
    }
    if (velocityX < 10)
    {
        indexAnimation = RIGHT;
        states[RIGHT][0].RunAnimation();
    }
    else
    {
        indexAnimation = RIGHTRUN;
        states[RIGHTRUN][0].RunAnimation();
    }
    if (velocityX < 0)
    {
        indexAnimation = EDGEL;
    }
    direction = 1;
}
void Player::autoMove(int x_coord, int y_coord, char** lvl,int height,int width)
{
    if (!checkCollision(lvl, x_coord, y_coord,height,width))
    {
        return;
    }
    if (y_coord == y && x_coord == x)
    {
        if (indexAnimation != STILL)
        {
            indexAnimation = STILL;
            states[STILL][0].RunAnimation();
        }
        else
        {
            // moveRandomely();
        }
        return;
    }
    if (y > y_coord)
    {
        indexAnimation = JUMPR;
        states[JUMPR][0].RunAnimation();
        onGround = false;
    }
    else if (y <= y_coord && x != x_coord)
    {
        if (x < x_coord)
        {
            indexAnimation = RIGHTRUN;
            states[RIGHTRUN][0].RunAnimation();
        }
        else if (x > x_coord)
        {
            indexAnimation = LEFTRUN;
            states[LEFTRUN][0].RunAnimation();
        }
    }
    // cout << "\n\nthe differnece  is : " << x_coord - x << endl<<endl<<endl;
    x = x_coord;
    y = y_coord;
    // updateDelay();
}

void Player::checkDelayNow(int idx)
{
    if (idx > delayInFollow)
    {
        delayInFollow = 0;
        hasStartedFollowing = true;
    }
}
bool Player::checkFeet(char** lvl, int height, int width)
{
    const int cell_size = 64;
    float offset_y = y;

    int row_bottom = (int)(offset_y + hit_box_factor_y + Pheight) / cell_size;
    int col_left = (int)(x + hit_box_factor_x) / cell_size;
    int col_right = (int)(x + hit_box_factor_x + Pwidth) / cell_size;
    int col_mid = (int)(x + hit_box_factor_x + Pwidth / 2) / cell_size;

    int row_top = (int)(offset_y + hit_box_factor_y + 39) / cell_size;

    if (row_bottom < 0) row_bottom = 0;
    else if (row_bottom >= height) row_bottom = height - 1;

    if (row_top < 0) row_top = 0;
    else if (row_top >= height) row_top = height - 1;

    if (col_left < 0) col_left = 0;
    else if (col_left >= width) col_left = width - 1;

    if (col_right < 0) col_right = 0;
    else if (col_right >= width) col_right = width - 1;

    if (col_mid < 0) col_mid = 0;
    else if (col_mid >= width) col_mid = width - 1;

    char bottom_left_down = lvl[row_bottom][col_left];
    char bottom_right_down = lvl[row_bottom][col_right];
    char bottom_mid_down = lvl[row_bottom][col_mid];

    char topLeft = lvl[row_top][col_left];
    char topMiddle = lvl[row_top][col_right];
    char topRight = lvl[row_top][col_mid];

    bool forLeft = topLeft == 's';
    bool forMiddle = topMiddle == 's';
    bool forRight = topRight == 's';

    if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' ||
        bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' ||
        bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') &&
        (forLeft || forMiddle || forRight))
    {
        onGround = true;
        return true;
    }

    return false;
}

// void Player::detectYourself()
//{
//	if ((indexAnimation == JUMPL || indexAnimation == JUMPR) && !hasDetectedItself)
//	{
//		hasDetectedItself = true;
//		velocityY = 0;
//
//
//	}
// }
void Player::figureItOutYourself(float leader_x, char** lvl, float offset_x,int width)
{
    if (x < leader_x)
    {
        if (x + 1 > leader_x)
        {
            x = leader_x;
        }
        else
        {
            x += 1;
        }
    }
    else if (x > leader_x)
    {
        if (x - 1 < leader_x)
        {
            x = leader_x;
        }
        {
            x -= 1;
        }
    }
    cout << "x in figutre it out x = " << x << endl;
    if (!spacePressed)
    {
        spacePressed = true;
        onGround = false;
        velocityY = -18;
    }
    indexAnimation = JUMPR;
    states[JUMPR][0].RunAnimation();
    float o_y = 0;
    player_dummy_gravity(lvl, o_y, offset_x, 64, spacePressed,14,width);
}
bool Player::teleportToTailed()
{
    /*if (tailed_x == -999 && tailed_y == -999)
    {
        tailed_x = target_x;
        target_y = target_y;
    }*/
    /*cout << "Tailed_x = " << tailed_x;
    cout << " ---- Tailed_y = " << tailed_y << endl;*/
    if (x < tailed_x)
    {
        if (x + 5 <= tailed_x)
            x += 5;
        else
            x = tailed_x;
    }
    else if (x > tailed_x)
    {
        if (x - 5 >= tailed_x)
            x -= 5;
        else
            x = tailed_x;
    }
    if (y < tailed_y)
    {
        if (y + 5 <= tailed_y)
            y += 5;
        else
            y = tailed_y;
    }
    else if (y > tailed_y)
    {
        if (y - 5 >= tailed_y)
            y -= 5;
        else
            y = tailed_y;
    }
    if (x == tailed_x && y == tailed_y)
    {
        /*tailed_x = -999;
        tailed_y = -999;*/
        indexAnimation = STILL;
        return true;
    }
    return false;
}
