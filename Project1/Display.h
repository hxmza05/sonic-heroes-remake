#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace sf;
class Layout
{
    const int cell_size ;
    const int height ;
    const int width;
    char** lvl;
    Texture background;
	Sprite backgroundSprite;

};
