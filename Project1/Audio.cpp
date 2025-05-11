#include<iostream>
#include "Audio.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;



void Audio::playLevelMusicByIndex(int index) {

    if (index < 0 || index >= TOTAL_MUSIC) {
        return;
    }

    levelMusic.stop();

    if (levelMusic.openFromFile(musicPaths[index])) {
        levelMusic.setLoop(true);
        levelMusic.setVolume(musicVolume);
        levelMusic.play();
    }
}

bool Audio::isSoundPlaying(int index) const {
    if (index >= 0 && index < TOTAL_SFX) {
        return sfx[index].getStatus() == sf::Sound::Playing;
    }
    return false;
}


void Audio::setMusicVolume(float vol) {

    musicVolume = vol;
    levelMusic.setVolume(musicVolume);
}

void Audio::setSFXVolume(float vol) {

    sfxVolume = vol;

    for (int i = 0; i < TOTAL_SFX; i++) {
        sfx[i].setVolume(sfxVolume);
    }
}

void Audio::playLevelMusic(const string& path) {

    levelMusic.stop();

    if (levelMusic.openFromFile(path)) {
        levelMusic.setLoop(true);
        levelMusic.setVolume(musicVolume);
        levelMusic.play();
    }
}

void Audio::playSound(int id) {

    if (id < 0 || id >= TOTAL_SFX) {
        return;
    }

    if (sfx[id].getStatus() == Sound::Playing) {
        sfx[id].stop();
    }

    sfx[id].setVolume(sfxVolume);
    sfx[id].play();
}

void Audio::loadAllSounds() {

    string paths[23] = {
        "Audio/MenuButton.wav", "Audio/Select.wav", "Audio/BackButton.wav", "Audio/Jump.wav",
        "Audio/Flying.wav", "Audio/Skidding.wav", "Audio/Hurt.wav", "Audio/1Up.wav",
        "Audio/Ring.wav", "Audio/Tired.wav", "Audio/Destroy.wav", "Audio/Explosion.wav",
        "Audio/Shot.wav", "Audio/BossHit.wav", "Audio/Spikes.wav", "Audio/SignPost.wav",
        "Audio/TimeWarp.wav", "Audio/ScoreAdd.wav", "Audio/ScoreTotal.wav", "Audio/Achievement.wav",
        "Audio/SpecialWarp.wav", "Audio/GlassSmash.wav", "Audio/Crumble.wav"
    };

    for (int i = 0; i < TOTAL_SFX; i++) {
        sfxBuffers[i].loadFromFile(paths[i]);
        sfx[i].setBuffer(sfxBuffers[i]);
        sfx[i].setVolume(sfxVolume);;
    }
}
