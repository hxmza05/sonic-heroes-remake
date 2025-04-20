#pragma once
class Player
{
	float x;
	float y;
public:
	Player(float _x = 150, float _y = 150)
	{
		x = _x;
		y = _y;
	}
	float& getx()
	{
		return x;
	}
	float& gety()
	{
		return y;
	}
};
