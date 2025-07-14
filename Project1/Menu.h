#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Leaderboard.h"
#include "Animation.h"
#include"Game.h"
#include"Audio.h"
using namespace sf;
using namespace std;

class Menu
{

private:

    int level;
    bool nameHasAlreadyBeenEntered;

    static const int totalMenuOptions = 6;
    const char* menuOptions[totalMenuOptions] = { "New Game", "Load Game", "Continue", "Options", "LeaderBoard", "Exit" };
    Text text[totalMenuOptions];
    float mainLabelX[totalMenuOptions] = { 726, 722.5, 747, 764.5, 793, 708 };
    float mainLabelY[totalMenuOptions] = { 377, 452, 527, 602, 677, 752 };
    float mainLabelScaleX[totalMenuOptions] = { 1, 1, 1, 1, 1, 1 };
    float mainLabelScaleY[totalMenuOptions] = { 1, 1, 1, 1, 1, 1 };


    static const int totalMenuOptions2 = 6;
    const char* menuOptions2[totalMenuOptions2] = { "Choose Level", "Tutorial", "Controls", "", "", "Credits" };
    Text text2[totalMenuOptions2];
    float subLabelX[totalMenuOptions2] = { 420, 471, 470.5, 482, 472.5, 484 };
    float subLabelY[totalMenuOptions2] = { 374, 449, 524, 599, 674, 749 };
    float subLabelScaleX[totalMenuOptions2] = { 1.83f, 1.32f, 1.325f, 1.2f, 1.305f, 1.19f };
    float subLabelScaleY[totalMenuOptions2] = { 1.42f, 1.42f, 1.42f, 1.42f, 1.42f, 1.42f };

    static const int totalLevels = 4;
    string levelOptions[totalLevels] = { "Level 1", "Level 2", "Level 3", "Boss Level" };
    Text levelTexts[totalLevels];
    float levelLabelX[totalLevels] = { 735.5f, 733, 732, 705 };
    float levelLabelY[totalLevels] = { 208, 283, 358, 433 };
    float levelLabelScaleX[totalLevels] = { 1.045f, 1.07f, 1.08f, 1.35f };
    float levelLabelScaleY[totalLevels] = { 1.32727f, 1.32727f, 1.32727f, 1.32727f };



    int selectedLevelIndex;
    int horizontal_x;
    int vertical_y;
    int selectedOption;
    int currentMenuLevel;
    int currentMenuOption;
    int lastSelectedOption;
    int lastCurrentMenuOption;

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
    Text Sonic;

    Clock mouseCursor;
    bool showCursor;
    RectangleShape nameBox;

    //Animation** states;
    Sprite selector;
    Texture ringTexture;
    Clock selectorClock;
    int indexAnimation;
    int totalAnimations;

    Texture backgroundTexture;
    Sprite backgroundSprite;
    RectangleShape backgroundOverlay;

    int sfxVolume;
    int musicVolume;

    Texture segaTexture;
    Sprite segaSprite;
    SoundBuffer segaBuffer;
    Sound segaSound;

    const int segaStartFrame = 1;
    const int segaEndFrame = 50;
    const int segaFrameHeight = 76;
    const int segaFrameWidth = 320;
    const int segaFrameCount = segaEndFrame - segaStartFrame + 1;
    float segaFrameDuration;

    Clock segaClock;
    bool showSegaIntro;
    bool segaSoundPlayed;
    float segaSoundDelay; 
    bool segaStarted;

    Font subMenuFont;
    Texture* islandTextures;
    Sprite islandSprite;

    Clock islandClock;
    float islandFrameDuration;
    const int islandFrameCount = 284;
    int currentIslandFrame;

    bool showIslandIntro;
    bool islandInputReceived;
    bool islandStarted;
    float islandStartDelay;

    bool showBlackScreen;
    Clock transitionClock;
    float blackScreenDuration;

    bool gameLoaded;
    bool gameON;

    Texture labelBgTexture;
    Sprite labelBgSprite;
    int currentSubMenuPage; 


    Texture tutorialBg;
    Sprite tutorialSp;

    Texture controlsBg;
    Sprite controlsSp;

    Texture creditsBg;
    Sprite creditsSp;

    Texture levelSelectBg;
    Sprite levelSelectSp;  

    float selectorX_main[6] = { 392, 388.5, 414, 430.5, 359, 474 };   
    float selectorY_main[6] = { 399, 474, 549, 624, 699, 774 };

    float selectorX_sub[6] = { 387, 438, 437.5, 450, 439.5, 451 };   
    float selectorY_sub[6] = { 395, 470, 545, 620, 695, 770 };

    Audio* audio;
    bool segaSoundEnded;
	Texture* menuTextures;
    Sprite* menuSprites;

    Text loadGameText;
    Text continueText;
    Clock continueClk;
    Clock loadScreenClk;
    bool showLoadedScreen;
    bool showContinueScreen;
    string continueStrings[2] = { "You Have'nt Loaded The Game Yet !!!", "Continuing From The Saved State!!!"};
    Text backTomainMenu;
    string backtoMenuStr;
    bool mKeyHeld;
public:
    Menu(int screenWidth, int screenHeigth, Leaderboard* lb) : leaderboard(lb)
    {
        mKeyHeld = false;
        
        subMenuFont.loadFromFile("Fonts/scoreFont.ttf");
        segaSoundEnded = false;

		menuTextures = new Texture[totalMenuOptions];
		menuSprites = new Sprite[totalMenuOptions];
		menuTextures[0].loadFromFile("Menu/1.png");
		menuTextures[1].loadFromFile("Menu/2.png");
		menuTextures[2].loadFromFile("Menu/3.png");
		menuTextures[3].loadFromFile("Menu/4.png");
		menuTextures[4].loadFromFile("Menu/5.png");
		menuTextures[5].loadFromFile("Menu/6.png");
        for(int i = 0; i < totalMenuOptions; ++i)
        {
            menuSprites[i].setTexture(menuTextures[i]);
            menuSprites[i].setPosition(0, 0);
            float scX = float(screenWidth) / menuTextures[i].getSize().x;
            float scY = float(screenHeigth) / menuTextures[i].getSize().y;
            menuSprites[i].setScale(scX, scY);
		}
        nameHasAlreadyBeenEntered = false;
        level = 0;
        gameLoaded = false;
        selectedOption = 0;
        currentMenuLevel = 0;
        currentMenuOption = 0;
        selectedLevelIndex = 0;
        currentSubMenuPage = 0;
        sfxVolume = 100;
        musicVolume = 100;
        lastSelectedOption = selectedOption;
        lastCurrentMenuOption = currentMenuOption;
        horizontal_x = screenWidth;
        vertical_y = screenHeigth;
        menuState = true;
        gameState = false;
        arrowUp = false;
        arrowDown = false;
        leaderboardState = false;
        enteringName = false;
        enter = false;
        gameON = false;

        segaFrameDuration = 0.08;
        segaSoundDelay = 1.1f; 
        islandFrameDuration = 10.8f / 284.0f;
        currentIslandFrame = 0;
        islandStartDelay = 0.5f;
        blackScreenDuration = 0.5f;

        showIslandIntro = false;
        islandInputReceived = false;
        islandStarted = false;
        showSegaIntro = true;
        segaSoundPlayed = false;
        segaStarted = false;
        showBlackScreen = false;


        segaClock.restart();
        islandClock.restart();
        transitionClock.restart();


        backgroundTexture.loadFromFile("Data/levelTransition.png");

        backgroundSprite.setTexture(backgroundTexture);
		float scX = float(screenWidth) / backgroundTexture.getSize().x;
		float scY = float(screenHeigth) / backgroundTexture.getSize().y;
		backgroundSprite.setScale(scX, scY);


        segaTexture.loadFromFile("Menu/Sega/sega_intro.png");
        segaSprite.setTexture(segaTexture);
        segaSprite.setScale(3.0f, 3.0f);

        segaBuffer.loadFromFile("Audio/Sega.wav");
        segaSound.setBuffer(segaBuffer);
        segaSound.setVolume(100);
        segaClock.restart();

        islandTextures = new Texture[islandFrameCount];

        for (int i = 0; i < islandFrameCount; ++i)
        {
            string filename = "Menu/Animation/frame_" + std::to_string(i) + ".png";
            islandTextures[i].loadFromFile(filename);
        }

        font.loadFromFile("Fonts/NiseSegaSonic.ttf");
        Sonic.setString("SONIC \n HEROES");
        Sonic.setFont(font);
        Sonic.setPosition(350, 75);
        Sonic.setFillColor(sf::Color::Blue);
        Sonic.setOutlineColor(sf::Color::Black);
        Sonic.setOutlineThickness(4);
        Sonic.setCharacterSize(92);
        //Sonic.setScale(3.3, 3.3);

        promptText.setFont(font);
        promptText.setString("Enter your Name:");
        promptText.setCharacterSize(48);
        promptText.setFillColor(Color::Blue);
        promptText.setPosition(405, 330);

        nameInputText.setFont(font);
        nameInputText.setCharacterSize(42);
        nameInputText.setFillColor(Color::Blue);
        nameInputText.setPosition(440, 447);

        nameBox.setSize(Vector2f(420, 70));
        nameBox.setFillColor(Color::Black);
        nameBox.setOutlineColor(Color::Blue);
        nameBox.setOutlineThickness(5);
        nameBox.setPosition(430, 440);

        loadGameText.setString("Game Loaded Successfully!!!");
        //continueText.s
        continueText.setString(continueStrings[0]);
        loadGameText.setFont(subMenuFont);
        loadGameText.setCharacterSize(70);
        loadGameText.setFillColor(Color::Yellow);
        loadGameText.setPosition(265, 377);
        loadGameText.setOutlineColor(sf::Color::Black);
        loadGameText.setOutlineThickness(4);

        continueText.setFont(subMenuFont);
        continueText.setCharacterSize(60);
        continueText.setFillColor(Color::Yellow);
        continueText.setPosition(205, 377);
        continueText.setOutlineColor(sf::Color::Black);
        continueText.setOutlineThickness(6);
        
        backTomainMenu.setFont(font);
        backTomainMenu.setCharacterSize(36);
        backTomainMenu.setFillColor(Color::Blue);
        backTomainMenu.setPosition(275, 240);
        backTomainMenu.setOutlineColor(sf::Color::Black);
        backTomainMenu.setOutlineThickness(4);
        //backtoMenuStr.set

        ringTexture.loadFromFile("Sprites/rgs.png");
        selectorClock.restart();
        indexAnimation = 0;
        totalAnimations = 1;

       

        indexAnimation = 0;

        float xMainOptions[] = { 760, 790, 870, 905, 920, 1000 };

        for (int i = 0; i < totalMenuOptions; i++)
        {
            Text temp(menuOptions[i], font, 60);
            float startY = float(screenHeigth / 5.4f);
            float y = startY + float(i * screenHeigth / 7.7f);
            float x = xMainOptions[i];

            temp.setPosition(x, y);
            text[i] = temp;
            text[i].setFillColor(i == selectedOption ? Color::Blue : Color::Red);
            text[i].setOutlineColor(sf::Color::Black);
            text[i].setOutlineThickness(3.5);
            text[i].setCharacterSize(36);
            if (i == 4)
                text[i].setCharacterSize(24);
        }

        float xSubmenu[] = { 460, 460, 460, 460, 460, 460 };
        float ySubmenu[] = { 55, 130, 205, 280, 355, 430 };
        for (int i = 0; i < totalMenuOptions2; i++)
        {
            string label = menuOptions2[i];
            Text temp(label, font, 52);
            float x = xSubmenu[i];
            float y = ySubmenu[i];
            temp.setPosition(x, y);
            text2[i] = temp;
            text2[i].setFillColor(i == currentMenuOption ? Color::Blue : Color::Red);
            text2[i].setOutlineColor(sf::Color::Black);
            text2[i].setOutlineThickness(3.5);
            text2[i].setCharacterSize(34);

        }
     

        levelSelectBg.loadFromFile("Menu/chooselevel.jpg");
        levelSelectSp.setTexture(levelSelectBg);


        float xLevels[] = { 545.5, 543, 542, 515 };
        float yLevels[] = { 225, 295, 365, 435 };
        for (int i = 0; i < totalLevels; i++) 
        {
            levelTexts[i].setFont(subMenuFont);
            levelTexts[i].setString(levelOptions[i]);
            levelTexts[i].setCharacterSize(40);
            levelTexts[i].setFillColor(Color::Blue);
            levelTexts[i].setOutlineColor(Color::Black);
            levelTexts[i].setOutlineThickness(3.f);

            float x = xLevels[i];
            float y = yLevels[i];
            levelTexts[i].setPosition(x, y);
        }

        menuOptions2[3] = "SFX: ";
        menuOptions2[4] = "Music: ";

        labelBgTexture.loadFromFile("Menu/textbackground.png");
        labelBgSprite.setTexture(labelBgTexture);


        tutorialBg.loadFromFile("Menu/tutorialbg.jpg");  
        tutorialSp.setTexture(tutorialBg);

        controlsBg.loadFromFile("Menu/controlsbg.jpg");  
        controlsSp.setTexture(controlsBg);

        creditsBg.loadFromFile("Menu/credits.jpg");
        creditsSp.setTexture(creditsBg);


    }

    bool isGameStateActive()
    {
        return gameState;
    }
    bool isgameOn() {
        return gameON;
    }
    bool isEnteringName()
    {
        return enteringName;
    }

    void setLeaderboard(Leaderboard* lb)
    {
        leaderboard = lb;
    }

    string getPlayerName()
    {
        return playerName;
    }

    string& getRefToPlayerName()
    {
        return playerName;
    }

    Font& getFont()
    {
        return font;
    }
    bool getSegaMusicPlayed()
    {
		return segaSoundEnded;
    }
    bool getSegaIntroState()
    {
        return showSegaIntro;
	}
    bool getShowIslandIntro()
    {
        return showIslandIntro;
	}
    void startGame()
    {
        enteringName = false;
        gameState = true;
    }
    bool isMenuFullyReady()
    {
        bool a = (showIslandIntro || menuState)&& !showSegaIntro;
        //cout << a;
        return  a;
    }

    void setAudio(Audio* a)
    {
        audio = a;
        audio->setSFXVolume((float)sfxVolume);
        audio->setMusicVolume((float)musicVolume);
        //audio->playLevelMusicByIndex(audio->getLevel2Music());
    }
    void returnToMenuFromGame()
    {
        gameState = false;
        menuState = true;
        enteringName = false;
    }

    void update(RenderWindow& window,Game*game)
    {
        //window.draw(Sonic);

        if (showSegaIntro)
        {
            float elapsed = segaClock.getElapsedTime().asSeconds();

            if (!segaSoundPlayed && elapsed >= segaSoundDelay)
            {
                segaSound.play();
                segaSoundPlayed = true;

            }

            if (elapsed >= segaFrameCount * segaFrameDuration)
            {
                showSegaIntro = false;
                showBlackScreen = true;
                transitionClock.restart();
                return;
            }

            return;
        }

        if (showBlackScreen)
        {
            if (transitionClock.getElapsedTime().asSeconds() >= 0.125f)
            {
                showBlackScreen = false;
                showIslandIntro = true;
                transitionClock.restart();
            }
            return;
        }

        if (showIslandIntro && Keyboard::isKeyPressed(Keyboard::Enter))
        {
            segaSoundEnded = true;
            showIslandIntro = false;
            menuState = true;
            return;
        }

       /* if (selectorClock.getElapsedTime().asSeconds() > 0.125f)
        {
            states[0]->RunAnimation();
            selector = states[0]->getSprites()[states[0]->getIndex()];
            selectorClock.restart();
        }*/


        if (menuState && currentMenuLevel == 0)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (!arrowUp)
                {
                    selectedOption--;
                    if (selectedOption < 0)
                        selectedOption = totalMenuOptions - 1;
                    arrowUp = true;
                }
            }

            else
            {
                arrowUp = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (!arrowDown)
                {
                    selectedOption++;
                    if (selectedOption >= totalMenuOptions)
                        selectedOption = 0;
                    arrowDown = true;
                }
            }
            else
            {
                arrowDown = false;
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if (!enter)
                {
                    audio->playSound(audio->getSelect());

                    if (selectedOption == 0)
                    {
                        if(!nameHasAlreadyBeenEntered)
                        {
                            enteringName = true;
                            nameHasAlreadyBeenEntered = true;
                        }
                        else
                        {
                            menuState = 0;
                            gameState = 1;
                        }
                        gameON = true;
                    }
                    else if (selectedOption == 1)
                    {
                        gameLoaded = game->loadGame(playerName);
                        showLoadedScreen = true;
                        loadScreenClk.restart();
                    }
                    else if (selectedOption == 2)
                    {
                            continueClk.restart();
                            showContinueScreen = true;
                            continueClk.restart();
                            /*gameState = 1;
                            return;*/
                    }
                    else if (selectedOption == 3)
                    {
                        currentMenuLevel = 1;
                    }
                    else if (selectedOption == 4)
                    {
                        leaderboardState = true;
                        menuState = false;
                    }
                    else if (selectedOption == 5)
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

            if (selectedOption != lastSelectedOption)
            {
                audio->playSound(audio->getMenuButton());
                lastSelectedOption = selectedOption;
            }

            for (int i = 0; i < totalMenuOptions; i++)
            {
                text[i].setFillColor(i == selectedOption ? Color::Blue : Color::Yellow);
            }

            selector.setPosition(selectorX_main[selectedOption], selectorY_main[selectedOption]);          

        }

      else if (menuState && currentMenuLevel == 1)
      {
              bool mDown = Keyboard::isKeyPressed(Keyboard::Escape) ||
                  Keyboard::isKeyPressed(Keyboard::M);

              if (mDown && !mKeyHeld)        // key just went down
              {
                  mKeyHeld = true;           // latch
                  audio->playSound(audio->getBackButton());

                  if (currentSubMenuPage > 0)
                      currentSubMenuPage = 0;
                  else
                      currentMenuLevel = 0;
              }
              else if (!mDown)
              {
                  mKeyHeld = false;          // key released → ready for next press
              }

            if (currentSubMenuPage == 0)
            {
                if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    if (!arrowUp)
                    {
                        currentMenuOption--;
                        if (currentMenuOption < 0) {
                            currentMenuOption = totalMenuOptions2 - 1;
                        }

                        arrowUp = true;
                        audio->playSound(audio->getMenuButton());
                    }
                }

                else {
                    arrowUp = false;
                }

                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    if (!arrowDown)
                    {
                        currentMenuOption++;
                        if (currentMenuOption >= totalMenuOptions2)
                            currentMenuOption = 0;
                        arrowDown = true;
                        audio->playSound(audio->getMenuButton());
                    }
                }

                else {
                    arrowDown = false;
                }

                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    if (currentMenuOption == 3 && sfxVolume < 100)
                    {
                        sfxVolume++;
                        audio->setSFXVolume((float)sfxVolume);
                    }
                    else if (currentMenuOption == 4 && musicVolume < 100)
                    {
                        musicVolume++;
                        audio->setMusicVolume((float)musicVolume);
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    if (currentMenuOption == 3 && sfxVolume > 0)
                    {
                        sfxVolume--;
                        audio->setSFXVolume((float)sfxVolume);

                    }
                    else if (currentMenuOption == 4 && musicVolume > 0)
                    {
                        musicVolume--;
                        audio->setMusicVolume((float)musicVolume);
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if (!enter)
                    {
                        audio->playSound(audio->getSelect());

                        if (currentMenuOption == 0) 
                            currentSubMenuPage = 4; // ChoosLevel

                        else if (currentMenuOption == 1)
                            currentSubMenuPage = 1; // Tutoral

                        else if (currentMenuOption == 2) 
                            currentSubMenuPage = 2; // Controls

                        else if (currentMenuOption == 5)
                            currentSubMenuPage = 3; // Credts

                        enter = true;
                    }
                }

                else {
                    enter = false;
                }

       
                if (currentMenuOption != lastCurrentMenuOption)
                {
                    audio->playSound(audio->getMenuButton());
                    lastCurrentMenuOption = currentMenuOption;
                }
                text2[3].setString("SFX: " + std::to_string(sfxVolume));
                text2[4].setString("Music: " + std::to_string(musicVolume));

                text2[3].setPosition(460, 280);   
                text2[4].setPosition(460, 375);

                for (int i = 0; i < totalMenuOptions2; i++)
                {
                    text2[i].setFillColor(i == currentMenuOption ? Color::Blue : Color::Yellow);
                }

                selector.setPosition(selectorX_sub[currentMenuOption], selectorY_sub[currentMenuOption]);

            }

            else if (currentSubMenuPage == 4)
            {
                if (Keyboard::isKeyPressed(Keyboard::Up))
                {
                    if (!arrowUp)
                    {
                        selectedLevelIndex = (selectedLevelIndex - 1 + totalLevels) % totalLevels;
                        arrowUp = true;
                        audio->playSound(audio->getMenuButton());
                    }
                }

                else {
                    arrowUp = false;
                }

                if (Keyboard::isKeyPressed(Keyboard::Down))
                {
                    if (!arrowDown)
                    {
                        selectedLevelIndex = (selectedLevelIndex + 1) % totalLevels;
                        arrowDown = true;
                        audio->playSound(audio->getMenuButton());
                    }
                }

                else {
                    arrowDown = false;
                }

                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if (!enter)
                    {
                        audio->playSound(audio->getSelect());
                        // Use selectedLevelIndex for game->startLevel(selectedLevelIndex);
						game->setLevel(selectedLevelIndex);
                        currentSubMenuPage = 0;
                        currentMenuLevel = 0;
                        enter = true;
                    }
                }
                else enter = false;

                for (int i = 0; i < totalLevels; i++)
                {
                    levelTexts[i].setFillColor(i == selectedLevelIndex ? Color::Blue : Color::Blue);
                    levelTexts[i].setOutlineColor(i == selectedLevelIndex ? Color::Black : Color::Black);
                }
            }
        }


        else if (leaderboardState)
        {
            leaderboard->readScores();
            leaderboard->sortScores();
            if (Keyboard::isKeyPressed(Keyboard::M) || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                audio->playSound(audio->getBackButton());
                leaderboardState = false;
                menuState = true;
            }
        }

        if (enteringName)
        {
            if (mouseCursor.getElapsedTime().asSeconds() >= 0.5f)
            {
                showCursor = !showCursor;
                mouseCursor.restart();
            }

            string displayName = playerName;
            if (showCursor && playerName.length() < 15)
                displayName += "_";
            nameInputText.setString(displayName);
            if (Keyboard::isKeyPressed(Keyboard::M) || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                audio->playSound(audio->getBackButton());
                enteringName = false;
                menuState = true;
            }
        }
    }

    void update(RenderWindow& window, Event& event)
    {
        window.draw(Sonic);

        if (enteringName)
        {
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    char entered = static_cast<char>(event.text.unicode);
                    if (entered == '\b' && !playerName.empty())
                    {
                        playerName.pop_back();
                    }
                    else if ((isalnum(entered) || entered == ' ') && playerName.length() < 15)
                    {
                        playerName += entered;
                    }
                    // Don't set nameInputText here — done in display lsfxic
                }
            }

            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                playerName.erase(0, playerName.find_first_not_of(" \n\r\t"));
                size_t lastChar = playerName.find_last_not_of(" \n\r\t");
                if (lastChar != std::string::npos)
                    playerName.erase(lastChar + 1);

                if (!playerName.empty())
                {
                    nameHasAlreadyBeenEntered = true;
                    enteringName = false;
                    gameState = true;
                    menuState = false;
                }
            }
        }

        if (showIslandIntro && event.type == Event::KeyPressed && event.key.code == Keyboard::RShift)
        {
            showIslandIntro = false;
            menuState = true;
        }
    }

    void draw(RenderWindow& window)
    {

        if (showSegaIntro)
        {
            window.clear(Color::White);

            float elapsed = segaClock.getElapsedTime().asSeconds();

            int frame = static_cast<int>(elapsed / segaFrameDuration);

            if (frame >= segaFrameCount)
            {
                frame = segaFrameCount - 1;
            }

            segaSprite.setTextureRect(IntRect(0, frame * segaFrameHeight, segaFrameWidth, segaFrameHeight));
            segaSprite.setPosition(120.f, 336.f);
            window.draw(segaSprite);
            return;
        }

        if (showBlackScreen)
        {
            window.clear(Color::Black);
            return;
        }

        if (showIslandIntro)
        {
            window.clear(Color::Black);
            float elapsed = transitionClock.getElapsedTime().asSeconds();
            currentIslandFrame = int(elapsed / islandFrameDuration) % islandFrameCount;
            islandSprite.setTexture(islandTextures[currentIslandFrame]);
            islandSprite.setScale(1200.f / 424.f, 900.f / 240.f);
            islandSprite.setPosition(0, 0);
            window.draw(islandSprite);
            return;
        }

        if (enteringName)
        {
            window.draw(backgroundSprite);
            window.draw(promptText);
            window.draw(nameBox);
            window.draw(nameInputText);
        }
        else if (menuState && currentMenuLevel == 0)
        {
            window.draw(backgroundSprite);
            window.draw(selector);

            for (int i = 0; i < totalMenuOptions; i++) 
            {
                string label = menuOptions[i];
                if (i == selectedOption)
                {
                    label = "> "  + label  + " <";
                   
                }
                text[i].setString(label);
                //window.draw(text[i]);

            }

        }

        else if (menuState && currentMenuLevel == 1)
        {
            if (currentSubMenuPage == 0)
            {
                window.draw(backgroundSprite);

                for (int i = 0; i < totalMenuOptions2; i++)
                {
                    string label = menuOptions2[i];
                    if (i == 3)
                    {
                        text2[3].setPosition(460, 280);
                        label = label + to_string(sfxVolume);
                    }
                    if (i == 4)
                    {
                        text2[4].setPosition(460, 355);

                        label = label + to_string(musicVolume);
                    }
                    if (i == currentMenuOption)
                    {
                        label = "> " + label + " <";

                    }
                    text2[i].setString(label);
                    window.draw(text2[i]);
                }

                window.draw(selector);
            }

            else if (currentSubMenuPage == 1) 
            {
                window.draw(tutorialSp);  

                Text heading("Tutorial - HOW TO WIN THE GAME", subMenuFont, 52);
                heading.setFillColor(Color::Blue);
                heading.setStyle(Text::Bold | Text::Underlined);
                heading.setPosition(horizontal_x * 0.35f, vertical_y * 0.14f);
                window.draw(heading);

                string lines[] = {
                    "- Explore each level to uncover secrets",
                    "- Collect ALL rings to unlock the goal",
                    "- Dodge or defeat enemy robots",
                    "- Use Sonic's speed",
                    "- Use Tails' flight",
                    "- Use Knuckles' strength",
                    "- Reach the exit after collecting all rings",
                    "- 0 HP or time out = Game Over"
                };

                float textX = horizontal_x * 0.42f;
                float y = vertical_y * 0.25f + 7.f;
                const int lineCount = sizeof(lines) / sizeof(lines[0]);

                for (int i = 0; i < lineCount; i++)
                {
                    Text tip(lines[i], subMenuFont, 36);
                    tip.setFillColor(Color::Black);
                    tip.setOutlineColor(Color::Blue);
                    tip.setOutlineThickness(2.f);
                    tip.setStyle(Text::Bold);
                    tip.setPosition(textX, y);
                    window.draw(tip);
                    y += 55;
                }

            }

            else if (currentSubMenuPage == 2) // Controls
            {
                window.draw(controlsSp);

                Text heading("CONTROLS", subMenuFont, 64);
                heading.setFillColor(Color::Blue);
                heading.setStyle(Text::Bold | Text::Underlined);
                heading.setPosition(horizontal_x * 0.07f, vertical_y * 0.15f);
                window.draw(heading);
          
                string controlLines[] = {
                    "Arrows    :  Move",
                    "Z       :  Switch Character",
                    "Space       :  Jump / Fly",
                    "S       :  Special Ability",
                    "Enter  :  Select",
                    "Esc / M :  Back"
                };

                float x = horizontal_x * 0.07f;
                float y = vertical_y * 0.27f;
                const int controlCount = sizeof(controlLines) / sizeof(controlLines[0]);

                for (int i = 0; i < controlCount; i++)
                {
                    Text control(controlLines[i], subMenuFont, 42);
                    control.setFillColor(Color::White);
                    control.setOutlineColor(Color::Blue);
                    control.setOutlineThickness(2.f);
                    control.setStyle(Text::Bold);
                    control.setPosition(x, y);
                    window.draw(control);
                    y += 58;  
                }

            }


            else if (currentSubMenuPage == 3)
            {
                window.draw(creditsSp);

                Text heading("CREDITS", subMenuFont, 64);
                heading.setFillColor(Color::Blue);
                heading.setStyle(Text::Bold | Text::Underlined);
                heading.setPosition(horizontal_x * 0.52f, vertical_y * 0.15f);
                window.draw(heading);

                string creditLines[] = {
                    "- Muhammad Hamza Sultan",
                    "- 24i0800",
                    "",
                    "- Muhammad Hamza",
                    "- 24i0786",
                    "",
                    "-Built with C++ & SFML using OOP"
                };

                float x = horizontal_x * 0.40f;
                float y = vertical_y * 0.27f;
                const int creditCount = sizeof(creditLines) / sizeof(creditLines[0]);

                for (int i = 0; i < creditCount; i++)
                {
                    Text credit(creditLines[i], subMenuFont, 42);
                    credit.setFillColor(Color::White);
                    credit.setOutlineColor(Color::Blue);
                    credit.setOutlineThickness(2.f);
                    credit.setPosition(x, y);
                    window.draw(credit);
                    y += 50;  
                }


            }

            else if (currentSubMenuPage == 4)
            {
                window.draw(levelSelectSp); 

                Text heading("CHOOSE LEVEL", subMenuFont, 52);
                heading.setFillColor(Color::Blue);
                heading.setOutlineColor(Color::White);
                heading.setOutlineThickness(2.f);
                heading.setStyle(Text::Bold | Text::Underlined);
                heading.setPosition(horizontal_x * 0.70f - heading.getGlobalBounds().width / 2.f, vertical_y * 0.16f);
                window.draw(heading);

                for (int i = 0; i < totalLevels; i++) {

                    levelTexts[i].setPosition(levelLabelX[i] + 50.f, levelLabelY[i]);
                    levelTexts[i].setScale(levelLabelScaleX[i], levelLabelScaleY[i]);

                    if (i == selectedLevelIndex) {
                        labelBgSprite.setScale(levelLabelScaleX[i], levelLabelScaleY[i]);
                        labelBgSprite.setPosition(levelLabelX[i] + 12.f, levelLabelY[i]);
                        window.draw(labelBgSprite);
                    }
                
                    window.draw(levelTexts[i]);
                }
            }
        }

        else if (leaderboardState)
        {
            window.draw(backgroundSprite);
            leaderboard->draw(window);
        }
        if(!currentMenuLevel && !enteringName && !leaderboardState && !showLoadedScreen && !showContinueScreen)
        {
            window.draw(Sonic);
            window.draw(menuSprites[selectedOption]);
            for (int i = 0; i < totalMenuOptions; i++)
            {
                string label = menuOptions[i];
                if (i == selectedOption)
                {
                    label = "> " + label + " <";

                }
                text[i].setString(label);
                window.draw(text[i]);

            }
        }
        if (showLoadedScreen && loadScreenClk.getElapsedTime().asMilliseconds() < 2000)
        {
            int rem = 2 - loadScreenClk.getElapsedTime().asSeconds();
            backTomainMenu.setString("Back  To  Main  Menu  in  (  " + to_string(rem) + "  )");
            window.draw(backTomainMenu);
            //window.draw(level)
            window.draw(loadGameText);
            
        }
        else if (loadScreenClk.getElapsedTime().asMilliseconds() > 2000)
            showLoadedScreen = false;
        if (showContinueScreen && continueClk.getElapsedTime().asMilliseconds() < 2000)
        {
            if(!gameLoaded)
            {
                int rem = 2 - continueClk.getElapsedTime().asSeconds();
                backTomainMenu.setString("Back  To  Main  Menu  in  (  " + to_string(rem) + "  )");
                window.draw(backTomainMenu);
            }
            continueText.setString(continueStrings[gameLoaded]);
            window.draw(continueText);

        }
        else if (continueClk.getElapsedTime().asMilliseconds() > 2000 && showContinueScreen)
        {

            showContinueScreen = false;
            if (gameLoaded)
            {
                gameState = 1;
                return;
            }
        }

    }


    void work(RenderWindow& window, Event& event,Game* game)
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        if (isEnteringName() && gameState != 1)
        {
            while (window.pollEvent(event))
            {

                if (event.type == Event::Closed)
                {
                    window.close();
                }

                update(window, event);
                if (gameState)
                    return;
                    //break;
            }
            update(window,game);
            draw(window);
        }

        else if (!isGameStateActive())
        {
            update(window,game);
            draw(window);
        }
    }
	int getLevel()
	{
		return level;
	}

};