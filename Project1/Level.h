#pragma once
#include<iostream>
#include"Enemy.h"
#include"Collectibles.h"
#include"Obstacle.h"
using namespace std;
#include"Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Level
{
	Collectible*** collectibles;
	Obstacle** obstacles;
	const int endMark;
protected:
	Texture backgorund;
	Sprite bgSprite;
	char** lvl;
	const int height;
	const int width;
	Enemy*** enemies;
public:
	Level(char** level = nullptr,Enemy*** e = nullptr,int h,int w):endMark(0),height(h),width(w)
	{
		
	}
	//Level2(Texture T,Sprite S,)
	//{
	//	enemies = new * Enemy[3];
	//	enemies[0][0] = new 
	//}

};