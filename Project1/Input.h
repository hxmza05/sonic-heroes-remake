#pragma once
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Input {

private:

    bool muteMusic = false;
    bool muteSFX = false;

public:

    bool isKeyPressedUp() {
        return Keyboard::isKeyPressed(Keyboard::Up);
    }
    bool isKeyPressedDown() {
        return Keyboard::isKeyPressed(Keyboard::Down);
    }
    bool isKeyPressedEnter() {
        return Keyboard::isKeyPressed(Keyboard::Enter);
    }

    void toggleMusic(sf::Music& music) {
        muteMusic = !muteMusic;
        music.setVolume(muteMusic ? 0 : 50);
    }

    void toggleSFX(sf::Sound& sound) {
        muteSFX = !muteSFX;
        sound.setVolume(muteSFX ? 0 : 100);
    }

};
