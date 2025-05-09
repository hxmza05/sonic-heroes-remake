#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include"Leaderboard.h"
#include"Animation.h"
using namespace sf;
using namespace std;


class Menu 
{

private:

    static const int totalMenuOptions = 7;
    const char* menuOptions[totalMenuOptions] = { "New Game", "Load Game", "Continue", "Options", "Leader Board", "Difficulty", "Exit"};

	static const int totalMenuOptions2 = 5;
	const char* menuOptions2[totalMenuOptions2] = { "Tutorial", "Controls", "Credits", "", ""};
	Text text2[totalMenuOptions2];


    int horizontal_x;
    int vertical_y;
    int selectedOption;
    int currentMenuLevel;
	int currentMenuOption;
    int lastSelectedOption;
    int lastCurrentMenuOption;

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

    Clock mouseCursor;
    bool showCursor;
    RectangleShape nameBox;



    Animation** states;
    Sprite selector;
    Texture ringTexture;
    Clock selectorClock;
    int indexAnimation;
    int totalAnimations;


    SoundBuffer moveBuffer;
    SoundBuffer selectBuffer;
    SoundBuffer backBuffer;

    Sound moveSound;
    Sound selectSound;
    Sound backSound;

    Music menuMusic;


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
    float segaFrameDuration = 0.08; 

    Clock segaClock;
    bool showSegaIntro = true;
    bool segaSoundPlayed = false;
    float segaSoundDelay = 2.4f; // seconds
    bool segaStarted = false;

    Texture* islandTextures;
    Sprite islandSprite;

    Clock islandClock;
    float islandFrameDuration = 10.8f / 284.0f;
    const int islandFrameCount = 284;
    int currentIslandFrame = 0;

    bool showIslandIntro = false;
    bool islandInputReceived = false;
    bool islandStarted = false;
    float islandStartDelay = 0.5f;

    bool showBlackScreen = false;
    Clock transitionClock;
    float blackScreenDuration = 0.5f;







public:

    Menu(int screenWidth, int screenHeigth, Leaderboard* lb) : title("Sonic Classic Heroes", font, 64), leaderboard(lb) 
    {


        selectedOption = 0;
        currentMenuLevel = 0;
		currentMenuOption = 0;
        sfxVolume = 20;
        musicVolume = 5;
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


        backgroundTexture.loadFromFile("Menu/MenuBg.jpg"); 
        backgroundSprite.setTexture(backgroundTexture);

        //backgroundSprite.setRotation(180);
        //backgroundSprite.setOrigin(backgroundTexture.getSize().x, backgroundTexture.getSize().y);
        //backgroundSprite.setPosition(0, 0); 



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
            std::string filename = "Menu/Animation/frame_" + std::to_string(i) + ".png";
            islandTextures[i].loadFromFile(filename);
        }



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
        nameInputText.setFillColor(Color::Yellow);
        nameInputText.setPosition(300, 400);

        nameBox.setSize(Vector2f(400, 60));
        nameBox.setFillColor(Color(0, 0, 0, 150));
        nameBox.setOutlineColor(Color::Yellow);
        nameBox.setOutlineThickness(2);
        nameBox.setPosition(295, 395); 

        moveBuffer.loadFromFile("Audio/MenuButton.wav");
        selectBuffer.loadFromFile("Audio/Select.wav");
        backBuffer.loadFromFile("Audio/BackButton.wav");

        moveSound.setBuffer(moveBuffer);
        selectSound.setBuffer(selectBuffer);
        backSound.setBuffer(backBuffer);

		moveSound.setVolume(50);
		selectSound.setVolume(50);
		backSound.setVolume(50);


        menuMusic.openFromFile("Audio/MenuMusic.ogg");
        menuMusic.setLoop(true);
        menuMusic.setVolume(musicVolume);
        //menuMusic.play();



        ringTexture.loadFromFile("Sprites/rings.png");
        selectorClock.restart();
        indexAnimation = 0;
        totalAnimations = 1;

        states = new Animation * [totalAnimations];
        states[0] = new Animation(4);


        states[0]->getSprites()[0].setTexture(ringTexture);
        states[0]->getSprites()[0].setTextureRect(IntRect(0, 0, 66, 66));
        states[0]->getSprites()[0].setScale(0.5f, 0.5f);


        states[0]->getSprites()[1].setTexture(ringTexture);
        states[0]->getSprites()[1].setTextureRect(IntRect(66, 0, 56, 66));
        states[0]->getSprites()[1].setScale(0.5f, 0.5f);


        states[0]->getSprites()[2].setTexture(ringTexture);
        states[0]->getSprites()[2].setTextureRect(IntRect(122, 0, 32, 66));
        states[0]->getSprites()[2].setScale(0.5f, 0.5f);


        states[0]->getSprites()[3].setTexture(ringTexture);
        states[0]->getSprites()[3].setTextureRect(IntRect(154, 0, 53, 66));
        states[0]->getSprites()[3].setScale(0.5f, 0.5f);


        selector = states[0]->getSprites()[0];

        indexAnimation = 0;



        for (int i = 0; i < totalMenuOptions; i++)
        {
            Text temp(menuOptions[i], font, 42);

            float y = float(screenHeigth / 3.6) + float(i * screenHeigth / 12);
            FloatRect bounds = temp.getGlobalBounds();
            float x = (float(screenWidth) / 2) - bounds.width / 2;

            temp.setPosition(x, y);
            text[i] = temp;

            text[i].setFillColor(i == selectedOption ? Color::White : Color::Yellow);

        }

        for (int i = 0; i < totalMenuOptions2; i++) 
        {

            std::string label = menuOptions2[i];
            Text temp(label, font, 48);
            FloatRect bounds = temp.getGlobalBounds();
            float x = float(screenWidth) / 2 - bounds.width / 2;
            float y = float(screenHeigth / 3.6) + float(i * screenHeigth / 12);

            temp.setPosition(x, y);
            text2[i] = temp;

            text2[i].setFillColor(i == currentMenuOption ? Color::White : Color::Yellow);

        }


        menuOptions2[3] = "SFX: 50";
        menuOptions2[4] = "Music: 50";



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
            if (transitionClock.getElapsedTime().asSeconds() >= 0.5f)
            {
                showBlackScreen = false;
                showIslandIntro = true;
                transitionClock.restart(); 
            }
            return;
        }

        // Island animation (exit on Right Shift)
        if (showIslandIntro && Keyboard::isKeyPressed(Keyboard::RShift))
        {
            showIslandIntro = false;
            menuState = true;
            return;
        }

        if (selectorClock.getElapsedTime().asSeconds() > 0.125f)
        {
            states[0]->RunAnimation();
            selector = states[0]->getSprites()[states[0]->getIndex()];
            selectorClock.restart();
        }

        Vector2f mousePos = (Vector2f)Mouse::getPosition(window);

        if (menuState && currentMenuLevel == 0)
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
                    selectSound.play();

                    if (selectedOption == 0) {
                        enteringName = true;
                    }
                    else if (selectedOption == 1) {
                        // Load Game 
                    }
                    else if (selectedOption == 2) {
                        // Continue
                    }
                    else if (selectedOption == 3) {
                        currentMenuLevel = 1;  // SUb menu
                    }
                    else if (selectedOption == 4) {
                        leaderboardState = true;
                        menuState = false;
                    }
                    else if (selectedOption == 5) {
                        // Difficult
                    }
                    else if (selectedOption == 6) {
                        window.close();
                    }
                    enter = true;
                }
            }
            else {
                enter = false;
            }

            for (int i = 0; i < totalMenuOptions; i++) {

                if (text[i].getGlobalBounds().contains(mousePos)) {

                    selectedOption = i;

                    //text[i].setFillColor(Color::Blue);

                    if (Mouse::isButtonPressed(Mouse::Left)) {

                        selectSound.play();

                        if (i == 0) enteringName = true;

                        else if (i == 1) {  }

                        else if (i == 2) {  }

                        else if (i == 3) currentMenuLevel = 1;

                        else if (i == 4) {
                            leaderboardState = true;
                            menuState = false;
                        }

                        else if (i == 5) {  }

                        else if (i == 6) window.close();
                    }
                }
            }

            if (selectedOption != lastSelectedOption)
            {
                moveSound.play();
                lastSelectedOption = selectedOption;
            }

            for (int i = 0; i < totalMenuOptions; i++) {
                text[i].setFillColor(i == selectedOption ? Color::Yellow : Color::White);
            }

            Vector2f finalPos = text[selectedOption].getPosition();
            selector.setPosition(finalPos.x - 60, finalPos.y + 12);
        }

        else if (menuState && currentMenuLevel == 1)
        {


            if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::M))
            {
                backSound.play();
                currentMenuLevel = 0;
            }


            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (!arrowUp)
                {
                    currentMenuOption--;

                    if (currentMenuOption < 0) {
                        currentMenuOption = totalMenuOptions2 - 1;
                    }

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
                    currentMenuOption++;

                    if (currentMenuOption >= totalMenuOptions2) {
                        currentMenuOption = 0;
                    }

                    arrowDown = true;
                }
            }

            else {
                arrowDown = false;
            }



            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                if (currentMenuOption == 3 && sfxVolume < 50)
                {
                    sfxVolume++;
                    moveSound.setVolume(sfxVolume);
                    selectSound.setVolume(sfxVolume);
                    backSound.setVolume(sfxVolume);
                }
                else if (currentMenuOption == 4 && musicVolume < 50)
                {
                    musicVolume++;
                    menuMusic.setVolume(musicVolume);

                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                if (currentMenuOption == 3 && sfxVolume > 0)
                {
                    sfxVolume--;
                    moveSound.setVolume(sfxVolume);
                    selectSound.setVolume(sfxVolume);
                    backSound.setVolume(sfxVolume);
                }
                else if (currentMenuOption == 4 && musicVolume > 0)
                {
                    musicVolume--;
                    menuMusic.setVolume(musicVolume);
                }
            }


            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if (!enter)
                {
                    selectSound.play();

                    if (currentMenuOption == 0) {
                        
                    }
                    else if (currentMenuOption == 1) {
                        
                    }
                    else if (currentMenuOption == 2) {
                        
                    }

                    enter = true;
                }
            }

            else {
                enter = false;
            }

            for (int i = 0; i < totalMenuOptions2; i++)
            {
                if (text2[i].getGlobalBounds().contains(mousePos))
                {

                    if (currentMenuOption != i)
                    {
                        moveSound.play();
                        currentMenuOption = i;
                    }

                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        selectSound.play();

                        if (i == 0) {
                           
                        }
                        else if (i == 1) {
                            
                        }
                        else if (i == 2) {
                            
                        }
                    }
                }
            }

            if (currentMenuOption != lastCurrentMenuOption)
            {
                moveSound.play();
                lastCurrentMenuOption = currentMenuOption;
            }


            for (int i = 0; i < totalMenuOptions2; i++) 
            {
                text2[i].setFillColor(i == currentMenuOption ? Color::Yellow : Color::White);
            }

            text2[3].setString("SFX: " + std::to_string(sfxVolume));
            text2[4].setString("Music: " + std::to_string(musicVolume));

            for (int i = 3; i <= 4; ++i)
            {
                FloatRect bounds = text2[i].getGlobalBounds();
                text2[i].setPosition((horizontal_x / 2) - bounds.width / 2, text2[i].getPosition().y);
            }


            Vector2f finalPos = text2[currentMenuOption].getPosition();
            selector.setPosition(finalPos.x - 60, finalPos.y + 12);



        }

        else if (leaderboardState)
        {

            if (Keyboard::isKeyPressed(Keyboard::M) || Keyboard::isKeyPressed(Keyboard::Escape))
            {
                backSound.play();
                leaderboardState = false;
                menuState = true;
            }
        }

        if (enteringName) {

            if (mouseCursor.getElapsedTime().asSeconds() >= 0.5f) {
                showCursor = !showCursor;
                mouseCursor.restart();
            }

            std::string displayName = playerName;
            if (showCursor && playerName.length() < 15) displayName += "_";
            nameInputText.setString(displayName);
        }

    }


    void update(RenderWindow& window, Event& event)
    {
        if (enteringName)
        {
            if (event.type == Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    char entered = static_cast<char>(event.text.unicode);
                    if (entered == '\b' && !playerName.empty()) {
                        playerName.pop_back();
                    }
                    else if ((isalnum(entered) || entered == ' ') && playerName.length() < 15) {
                        playerName += entered;
                    }
                    // Don't set nameInputText here — done in display logic
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

            if (frame >= segaFrameCount) {
                frame = segaFrameCount - 1;
            }

            segaSprite.setTextureRect(IntRect(0, frame * segaFrameHeight, segaFrameWidth, segaFrameHeight));
            segaSprite.setPosition((horizontal_x - segaSprite.getGlobalBounds().width) / 2.f, (vertical_y - segaSprite.getGlobalBounds().height) / 2.f);
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
            window.draw(title);
            window.draw(selector);
            for (int i = 0; i < totalMenuOptions; i++)
            {
                window.draw(text[i]);
            }
        }

        else if (menuState && currentMenuLevel == 1)
        {
            window.draw(backgroundSprite);
            window.draw(title);
            window.draw(selector);
            for (int i = 0; i < totalMenuOptions2; i++) 
            {
                window.draw(text2[i]);
            }
        }

        else if (leaderboardState)
        {
            window.draw(backgroundSprite);
            leaderboard->draw(window);
        }
    }
    void work(RenderWindow& window,Event&event)
    {
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
            }

            window.clear();

            if (isEnteringName())
            {
                while (window.pollEvent(event)) {

                    if (event.type == Event::Closed) {
                        window.close();
                    }

                    update(window, event);
                }
                update(window);
                draw(window);
            }
            else if (!isGameStateActive())
            {
                update(window);
                draw(window);
            }

            //window.display();
    }
};