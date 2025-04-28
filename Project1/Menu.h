#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;


class Menu 
{

private:

    static const int totalMenuOptions = 6;
    const char* menuOptions[totalMenuOptions] = { "New Game", "Options", "Continue", "Leader Board", "Credits", "Exit" };
    int alignmentofTEXT[totalMenuOptions] = { 169, 117, 137, 205, 107, 54 }; // these are the pixels of text written in the above array
    int horizontal_x;
    int vertical_y;
    int selectedOption;

    Text text[totalMenuOptions];
    Text title;
    Font font;

    bool arrowUp;
    bool arrowDown;
    bool enter;
    bool menuState;
    bool gameState;

public:

    Menu(int screenWidth, int screenHeigth) : title("Sonic Classic Heroes", font, 64) {

        selectedOption = 0;
        horizontal_x = screenWidth;
        vertical_y = screenHeigth;
        menuState = true;
        gameState = false;
        arrowUp = false;
        arrowDown = false;
        enter = false;

        font.loadFromFile("Fonts/arial.ttf");
        title.setFillColor(Color::Yellow);
        title.setPosition(352.5f, 80);

        for (int i = 0; i < totalMenuOptions; i++)
        {
            Text temp(menuOptions[i], font, 42);
            temp.setPosition(float(screenWidth / 2) - float(alignmentofTEXT[i] / 2), float(screenHeigth / 3.6) + float(i * screenHeigth / 12));
            text[i] = temp;
            text[i].setFillColor(i == selectedOption ? sf::Color::Blue : sf::Color::White);

        }

    }

    bool isGameStateActive() { 

        return gameState; 
    }

    void update(sf::RenderWindow& window)
    {

        if (menuState)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (arrowUp == false)
                {
                    selectedOption--;
                    if (selectedOption < 0)
                    {

                        selectedOption = totalMenuOptions - 1;
                    }
                    arrowUp = true;
                }
            }
            else
            {
                arrowUp = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (arrowDown == false)
                {
                    selectedOption++;
                    if (selectedOption >= totalMenuOptions)
                    {

                        selectedOption = 0;
                    }
                    arrowDown = true;
                }
            }
            else
            {
                arrowDown = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if (enter == false)
                {
                    if (selectedOption == 0)
                    {
                        menuState = false;
                        gameState = true;
                    }
                    else if (selectedOption == totalMenuOptions - 1)
                    {
                        window.close();
                    }
                    enter = true;
                }
            }
            else
            {
                enter = false;
            }

            for (int i = 0; i < totalMenuOptions; i++)
            {

                text[i].setFillColor(i == selectedOption ? Color::Blue : Color::White);
            }
        }
    }

    void draw(RenderWindow& window)
    {
        if (menuState)
        {
            window.draw(title);

            for (int i = 0; i < totalMenuOptions; i++) {
                window.draw(text[i]);
            }
        }
    }

};