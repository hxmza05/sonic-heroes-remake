#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "Input.h"

class Leaderboard {

private:

    static const int maxScores = 10;
    int scoresList[maxScores + 1]; 
    string namesList[maxScores + 1];


    Font font;
    Text title;
    Text names[maxScores];
    Text scores[maxScores];

    Input* inputHandler; 


public:

    Leaderboard(Input* input = nullptr) : inputHandler(input) {

        font.loadFromFile("Fonts/scoreFont.ttf");
        title.setFont(font);
        title.setString("High Scores");
        title.setCharacterSize(64);
        title.setFillColor(Color::Yellow);
        title.setPosition(300, 50);

        readScores();
        prepareEntries();

    }

    void readScores() {

        ifstream file("HighScore.txt");
        for (int i = 0; i < maxScores; i++)
            scoresList[i] = 0;
        if (file.is_open())
        {
            for (int i = 0; i < maxScores && !file.eof(); i++)
            {
                getline(file, namesList[i]);
                string sc;
                getline(file, sc);
                scoresList[i] = stoi(sc);
            }
            file.close();
        }
    }

    void writeScores() {

        ofstream file("HighScore.txt");
        if (file.is_open())
        {
            for (int i = 0; i < maxScores; i++)
            {
                file << (namesList[i].empty() ? "------" : namesList[i]) << "\n" << scoresList[i] << "\n";
            }
            file.close();
        }
    }

    void sortScores() {

        int n = maxScores + 1;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (scoresList[j] < scoresList[j + 1])
                {
                    swap(scoresList[j], scoresList[j + 1]);
                    swap(namesList[j], namesList[j + 1]);
                }
            }
        }
    }

    void addNewScore(std::string name, int score) {

        namesList[maxScores] = name;
        scoresList[maxScores] = score;
        sortScores();
        writeScores();
        prepareEntries();

    }

    void prepareEntries() {
        
        for (int i = 0; i < maxScores; i++)
        {
            names[i].setFont(font);
            scores[i].setFont(font);

            names[i].setString(namesList[i]);
            scores[i].setString(to_string(scoresList[i]));

            names[i].setCharacterSize(32);
            scores[i].setCharacterSize(32);

            names[i].setFillColor(Color::White);
            scores[i].setFillColor(Color::White);

            names[i].setPosition(300, 150 + i * 50);
            scores[i].setPosition(700, 150 + i * 50);
        }
    }

    void draw(RenderWindow& window) {

        window.draw(title);
        for (int i = 0; i < maxScores; i++)
        {
            window.draw(names[i]);
            window.draw(scores[i]);
        }
    }
};
