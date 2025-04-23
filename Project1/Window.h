#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
class Wind
{
	 int screen_x;
	 int screen_y;
	 RenderWindow window;
public:
	Wind()
	{
		screen_x = 0;
		screen_y = 0;
	}
	Wind(int sx, int sy)
	{
		screen_x = sx;
		screen_y = sy;
		RenderWindow window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog", Style::Close | Style::Resize | Style::Close);
		window.setVerticalSyncEnabled(true);
		window.setFramerateLimit(60);
	}
	RenderWindow& getWindow()
	{
		return window;
	}
};