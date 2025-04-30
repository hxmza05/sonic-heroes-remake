#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include"Leaderboard.h"
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
    bool leaderboardState;
    bool enteringName;

    Leaderboard* leaderboard;
    string playerName;
    Text promptText;
    Text nameInputText;


public:

    Menu(int screenWidth, int screenHeigth, Leaderboard* lb) : title("Sonic Classic Heroes", font, 64), leaderboard(lb) {


        selectedOption = 0;
        horizontal_x = screenWidth;
        vertical_y = screenHeigth;
        menuState = true;
        gameState = false;
        arrowUp = false;
        arrowDown = false;
        leaderboardState = false;
        enteringName = false;
        enter = false;


        font.loadFromFile("Fonts/scoreFont.ttf");
        title.setFillColor(Color::Yellow);
        title.setPosition(352.5f, 80);

        promptText.setFont(font);
        promptText.setString("Enter your Name:");
        promptText.setCharacterSize(48);
        promptText.setFillColor(Color::Yellow);
        promptText.setPosition(300, 300);

        nameInputText.setFont(font);
        nameInputText.setCharacterSize(42);
        nameInputText.setFillColor(Color::White);
        nameInputText.setPosition(300, 400);


        for (int i = 0; i < totalMenuOptions; i++)
        {
            Text temp(menuOptions[i], font, 42);
            temp.setPosition(float(screenWidth / 2) - float(alignmentofTEXT[i] / 2), float(screenHeigth / 3.6) + float(i * screenHeigth / 12));
            text[i] = temp;
            text[i].setFillColor(i == selectedOption ? Color::Blue : Color::White);

        }
    }

    bool isGameStateActive() { 
        return gameState; 
    }

    bool isEnteringName() { 
        return enteringName; 
    }

    void setLeaderboard(Leaderboard* lb) {
        leaderboard = lb;
    }

    string getPlayerName() { 
        return playerName; 
    }

    string& getRefToPlayerName() {
        return playerName;
    }
    
    Font& getFont() {
        return font;
    }

    void startGame() {
        enteringName = false;
        gameState = true;
    }

    void update(RenderWindow& window)
    {
        if (menuState)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (!arrowUp)
                {
                    selectedOption--;
                    if (selectedOption < 0) selectedOption = totalMenuOptions - 1;
                    arrowUp = true;
                }
            }

            else {
                arrowUp = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (!arrowDown)
                {
                    selectedOption++;
                    if (selectedOption >= totalMenuOptions) selectedOption = 0;
                    arrowDown = true;
                }
            }

            else {
                arrowDown = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if (!enter)
                {
                    if (selectedOption == 0) {
                        gameState = true;
                        menuState = false;
                    }
                    else if (selectedOption == 3) {
                        leaderboardState = true;
                        menuState = false;
                    }
                    else if (selectedOption == totalMenuOptions - 1) {
                        window.close();
                    }
                    enter = true;
                }
            }

            else {
                enter = false;
            }

            for (int i = 0; i < totalMenuOptions; i++) {
                text[i].setFillColor(i == selectedOption ? Color::Blue : Color::White);
            }
        }

        else if (leaderboardState)
        {
            if (Keyboard::isKeyPressed(Keyboard::M))
            {
                leaderboardState = false;
                menuState = true;
            }
        }
    }

    void update(RenderWindow& window, Event& event)
    {
        if (enteringName)
        {
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode == '\b' && !playerName.empty())
                {
                    playerName.pop_back();
                }
                else if (event.text.unicode < 128 && playerName.length() < 15 &&
                    event.text.unicode != '\r' && event.text.unicode != '\n')
                {
                    playerName += static_cast<char>(event.text.unicode);
                }

                nameInputText.setString(playerName);
            }

            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                if (!playerName.empty())
                {
                    enteringName = false;
                    gameState = true;
                }
            }
        }
    }


    void draw(RenderWindow& window)
    {
        if (enteringName)
        {
            window.draw(promptText);
            window.draw(nameInputText);
        }
        else if (menuState)
        {
            window.draw(title);
            for (int i = 0; i < totalMenuOptions; i++)
            {
                window.draw(text[i]);
            }
        }
        else if (leaderboardState)
        {
            leaderboard->draw(window);
        }
    }

};