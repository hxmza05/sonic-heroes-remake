#pragma once
class Obstacle
{
	int x, y;
	bool exists;
public :
	Obstacle(int _x = -200,int  _y = -200)
	{
		x = _x;
		y = _y;
	}
};
