#include"Player.h"
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
}
void Player::moveLeft()
{
	x -= velocityX;
	if (velocityX + acceleration < max_speed)
	{
		velocityX += acceleration;
	}
	if (velocityX < 10)
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
		cout<<"right  animation running";
	}
	else
	{
		indexAnimation = RIGHTRUN;
		states[RIGHTRUN][0].RunAnimation();
	}
}
void Player::autoMove(int x_coord, int y_coord)
{
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
	 x = x_coord;
	 y = y_coord;
	 //updateDelay();
}

void Player:: checkDelayNow(int idx)
{
	if (idx > delayInFollow)
	{
		delayInFollow = 0;
		hasStartedFollowing = true;
	}
}
