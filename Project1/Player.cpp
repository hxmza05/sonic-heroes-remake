#pragma once
#include"Player.h"
//#include"Game.h"
#include"GlobalFunctions.h"

//#include"Src.cpp"
void Player::draw_player(RenderWindow& window, Sprite& LstillSprite, float offset_x)
{
	LstillSprite.setPosition(x - offset_x, y);
	window.draw(LstillSprite);
}
void Player::player_gravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed)
{
	offset_y = y;
	offset_y += velocityY;

	int headY = (int)(y + hit_box_factor_y) / cell_size;
	int tileLeftX = (int)(x + hit_box_factor_x) / cell_size;
	int tileRightX = (int)(x + hit_box_factor_x + Pwidth - 1) / cell_size;

	bool hitsTopRow = (headY == 0 || headY == 1);
	bool leftHit = (lvl[headY][tileLeftX] == 'w' || lvl[headY][tileLeftX] == 'q' || lvl[headY][tileLeftX] == 'e');
	bool rightHit = (lvl[headY][tileRightX] == 'w' || lvl[headY][tileRightX] == 'q' || lvl[headY][tileRightX] == 'e');

	if (velocityY < 0 && hitsTopRow && (leftHit || rightHit))
	{
		velocityY = 0;
	}
	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];

	char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];
	bool forLeft = topLeft == 's';
	bool forMiddle = topMiddle == 's';
	bool forRight = topRight == 's';


	if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' || bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' || bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') && velocityY > 0 && (forLeft || forMiddle || forRight))
	{
		onGround = true;
		/*y = ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size) * cell_size - hit_box_factor_y - Pheight;*/
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
		//cout << "Gravity being added correctly \n";
		if (velocityY >= terminal_Velocity)
			velocityY = terminal_Velocity;
	}
	else
	{
		velocityY = 0;
		spacePressed = false;
	}
}
void Player::player_dummy_gravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed)
{
	cout << "\n\nY beofer Func : " << y << endl;
	cout << "VelocityY beofer Func : " << velocityY << endl;

	offset_y = y;
	offset_y += velocityY;

	int headY = (int)(y + hit_box_factor_y) / cell_size;
	int tileLeftX = (int)(x + hit_box_factor_x) / cell_size;
	int tileRightX = (int)(x + hit_box_factor_x + Pwidth - 1) / cell_size;

	bool hitsTopRow = (headY == 0 || headY == 1);
	bool leftHit = (lvl[headY][tileLeftX] == 'w' || lvl[headY][tileLeftX] == 'q' || lvl[headY][tileLeftX] == 'e');
	bool rightHit = (lvl[headY][tileRightX] == 'w' || lvl[headY][tileRightX] == 'q' || lvl[headY][tileRightX] == 'e');

	if (velocityY < 0 && hitsTopRow && (leftHit || rightHit))
	{
		velocityY = 0;
	}

	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];

	char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];
	bool forLeft = topLeft == 's';
	bool forMiddle = topMiddle == 's';
	bool forRight = topRight == 's';


	if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' || bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' || bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') && velocityY > 0 && (forLeft || forMiddle || forRight))
	{
		onGround = true;
		/*y = ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size) * cell_size - hit_box_factor_y - Pheight;*/
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
		//cout << "Gravity being added correctly \n";
		if (velocityY >= terminal_Velocity)
			velocityY = terminal_Velocity;
	}
	else
	{
		velocityY = 0;
		spacePressed = false;
	}
	cout << "VelocityY after Func : " << velocityY << endl;
	cout << "Y after the func : " << y << "\n";
}
void Player::playerVirtualGravity(char** lvl, float& offset_y, float& offset_x, const int cell_size, bool& spacePressed)
{
	offset_y = y;
	offset_y += tempVelocityY;
	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];

	char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];
	bool forLeft = topLeft == 's';
	bool forMiddle = topMiddle == 's';
	bool forRight = topRight == 's';


	if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' || bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' || bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') && tempVelocityY > 0 && (forLeft || forMiddle || forRight))
	{
		onGround = true;
		/*y = ((int)(offset_y + hit_box_factor_y + Pheight) / cell_size) * cell_size - hit_box_factor_y - Pheight;*/
		tempVelocityY = 0;
		spacePressed = false;
	}
	else
	{
		y = offset_y;
		tempVelocityY += tempGravity;
		onGround = false;
	}
	cout << "tempVelocityY ------ (" << tempVelocityY << endl;
}
void Player::moveLeft()
{
	if (velocityX > 0)
	{
		//velocityX-=

	}
	{
		x += velocityX;
		if (velocityX - acceleration > -max_speed)
		{
			velocityX -= acceleration;
		}
		if (velocityX > -10)
		{
			indexAnimation = LEFT;
			states[LEFT][0].RunAnimation();/*&& topLeft != 'q' && topLeft != 'e';*/
		}
		else
		{
			indexAnimation = LEFTRUN;
			states[LEFTRUN][0].RunAnimation();
		}
	}
	direction = 0;
}
void Player::moveRight()
{
	x += velocityX;
	if (velocityX + acceleration < max_speed)
	{
		velocityX += acceleration;
	}
	if (velocityX < 10)
	{
		indexAnimation = RIGHT;
		states[RIGHT][0].RunAnimation();/*&& topLeft != 'q' && topLeft != 'e';*/
		//cout<<"right  animation running";
	}
	else
	{
		indexAnimation = RIGHTRUN;
		states[RIGHTRUN][0].RunAnimation();
	}
	direction = 1;
}
void Player::autoMove(int x_coord, int y_coord,char**lvl)
{
	if (!checkCollision(lvl, x_coord, y_coord))
	{
		return;
	}
	if (y_coord == y && x_coord == x)
	{
		if(indexAnimation != STILL)
		{
			indexAnimation = STILL;
			states[STILL][0].RunAnimation();
		}
		else
		{
			//moveRandomely();
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
		else if(x > x_coord)
		{
			indexAnimation = LEFTRUN;
			states[LEFTRUN][0].RunAnimation();
		}
	}
	//cout << "\n\nthe differnece  is : " << x_coord - x << endl<<endl<<endl;
	 x = x_coord;
	 y = y_coord;
	 //updateDelay();
}

void Player::checkDelayNow(int idx)
{
	if (idx > delayInFollow)
	{
		delayInFollow = 0;
		hasStartedFollowing = true;
	}
}
bool Player::checkFeet(char** lvl)
{
	int cell_size = 64;
	float offset_y = y;
	//offset_y += velocityY;

	char bottom_left_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char bottom_right_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char bottom_mid_down = lvl[(int)(offset_y + hit_box_factor_y + Pheight) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];

	char topLeft = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x) / cell_size)];
	char topMiddle = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth) / cell_size)];
	char topRight = lvl[((int)(offset_y + hit_box_factor_y + 39)) / cell_size][((int)(x + hit_box_factor_x + Pwidth / 2) / cell_size)];
	bool forLeft = topLeft == 's';
	bool forMiddle = topMiddle == 's';
	bool forRight = topRight == 's';
	if ((bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w' || bottom_left_down == 'e' || bottom_mid_down == 'e' || bottom_right_down == 'e' || bottom_left_down == 'q' || bottom_mid_down == 'q' || bottom_right_down == 'q') /*&& tempVelocityY > 0*/ && (forLeft || forMiddle || forRight))
	{
		//cout << "\n\n\nFeet on the Ground\n\n\n";
		onGround = true;
		return true;
	}
	//cout << "\n\n\nFeet not on the Ground\n\n\n";
	return false;
}
//void Player::detectYourself()
//{
//	if ((indexAnimation == JUMPL || indexAnimation == JUMPR) && !hasDetectedItself)
//	{
//		hasDetectedItself = true;
//		velocityY = 0;
//
//
//	}
//}
void Player::figureItOutYourself(float leader_x,char**lvl,float offset_x)
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
	if (!spacePressed)
	{
		spacePressed = true;
		onGround = false;
		velocityY = -18;
	}
	indexAnimation = JUMPR;
	states[JUMPR][0].RunAnimation();
	float o_y = 0;
	player_dummy_gravity(lvl,o_y,offset_x,64,spacePressed);
}
bool Player::teleportToTailed()
{
	/*if (tailed_x == -999 && tailed_y == -999)
	{
		tailed_x = target_x;
		target_y = target_y;
	}*/
	cout << "Tailed_x = " << tailed_x;
	cout << " ---- Tailed_y = " << tailed_y << endl;
	if (x < tailed_x)
	{
		if (x + 5 <= tailed_x)
			x += 5;
		else x = tailed_x;
	}
	else if (x > tailed_x)
	{
		if (x - 5 >= tailed_x)
			x -= 5;
		else x = tailed_x;
	}
	if (y < tailed_y)
	{
		if (y + 5 <= tailed_y)
			y += 5;
		else y = tailed_y;
	}
	else if (y > tailed_y)
	{
		if (y - 5 >= tailed_y)
			y -= 5;
		else y = tailed_y;
	}
	if (x == tailed_x && y == tailed_y)
	{
		/*tailed_x = -999;
		tailed_y = -999;*/
		return true;
	}
	return false;
}
