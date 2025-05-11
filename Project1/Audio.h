#pragma once
#include <iostream>
#include"Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



class Audio {

private:

    SoundBuffer sfxBuffers[23];
    Sound sfx[23];
    Music levelMusic;

    float sfxVolume;
    float musicVolume;


    int MENU_BUTTON;
    int SELECT;
    int BACK_BUTTON;
    int JUMP;
    int FLYING;
    int SKIDDING;
    int HURT;
    int ONE_UP;
    int RING;
    int TIRED;
    int DESTROY;
    int EXPLOSION;
    int SHOT;
    int BOSS_HIT;
    int SPIKES;
    int SIGN_POST;
    int TIME_WARP;
    int SCORE_ADD;
    int SCORE_TOTAL;
    int ACHIEVEMENT;
    int SPECIAL_WARP;
    int GLASS_SMASH;
    int CRUMBLE;
    int TOTAL_SFX;


public:

    Audio() {

        MENU_BUTTON = 0;
        SELECT = 1;
        BACK_BUTTON = 2;
        JUMP = 3;
        FLYING = 4;
        SKIDDING = 5;
        HURT = 6;
        ONE_UP = 7;
        RING = 8;
        TIRED = 9;
        DESTROY = 10;
        EXPLOSION = 11;
        SHOT = 12;
        BOSS_HIT = 13;
        SPIKES = 14;
        SIGN_POST = 15;
        TIME_WARP = 16;
        SCORE_ADD = 17;
        SCORE_TOTAL = 18;
        ACHIEVEMENT = 19;
        SPECIAL_WARP = 20;
        GLASS_SMASH = 21;
        CRUMBLE = 22;
        TOTAL_SFX = 23;

        sfxVolume = 50;
        musicVolume = 50;

    }

    void loadAllSounds();
    void playSound(int Soundid);
    void playLevelMusic(const string& path);
    void setSFXVolume(float volume);
    void setMusicVolume(float volume);

};





void Audio::setMusicVolume(float vol) {
    musicVolume = vol;
    levelMusic.setVolume(musicVolume);
}


void Audio::setSFXVolume(float vol) {
    sfxVolume = vol;
    for (int i = 0; i < TOTAL_SFX; ++i) {
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

    if (id < 0 || id >= TOTAL_SFX) 
        return;

    if (sfx[id].getStatus() == Sound::Playing)
        sfx[id].stop();

    sfx[id].setVolume(sfxVolume); 
    sfx[id].play();

}


void Audio::loadAllSounds() {

    sfxBuffers[MENU_BUTTON].loadFromFile("Audio/MenuButton.wav");
    sfx[MENU_BUTTON].setBuffer(sfxBuffers[MENU_BUTTON]);

    sfxBuffers[SELECT].loadFromFile("Audio/Select.wav");
    sfx[SELECT].setBuffer(sfxBuffers[SELECT]);

    sfxBuffers[BACK_BUTTON].loadFromFile("Audio/BackButton.wav");
    sfx[BACK_BUTTON].setBuffer(sfxBuffers[BACK_BUTTON]);

    sfxBuffers[JUMP].loadFromFile("Audio/Jump.wav");
    sfx[JUMP].setBuffer(sfxBuffers[JUMP]);

    sfxBuffers[FLYING].loadFromFile("Audio/Flying.wav");
    sfx[FLYING].setBuffer(sfxBuffers[FLYING]);

    sfxBuffers[SKIDDING].loadFromFile("Audio/Skidding.wav");
    sfx[SKIDDING].setBuffer(sfxBuffers[SKIDDING]);

    sfxBuffers[HURT].loadFromFile("Audio/Hurt.wav");
    sfx[HURT].setBuffer(sfxBuffers[HURT]);

    sfxBuffers[ONE_UP].loadFromFile("Audio/1Up.wav");
    sfx[ONE_UP].setBuffer(sfxBuffers[ONE_UP]);

    sfxBuffers[RING].loadFromFile("Audio/Ring.wav");
    sfx[RING].setBuffer(sfxBuffers[RING]);

    sfxBuffers[TIRED].loadFromFile("Audio/Tired.wav");
    sfx[TIRED].setBuffer(sfxBuffers[TIRED]);

    sfxBuffers[DESTROY].loadFromFile("Audio/Destroy.wav");
    sfx[DESTROY].setBuffer(sfxBuffers[DESTROY]);

    sfxBuffers[EXPLOSION].loadFromFile("Audio/Explosion.wav");
    sfx[EXPLOSION].setBuffer(sfxBuffers[EXPLOSION]);

    sfxBuffers[SHOT].loadFromFile("Audio/Shot.wav");
    sfx[SHOT].setBuffer(sfxBuffers[SHOT]);

    sfxBuffers[BOSS_HIT].loadFromFile("Audio/BossHit.wav");
    sfx[BOSS_HIT].setBuffer(sfxBuffers[BOSS_HIT]);

    sfxBuffers[SPIKES].loadFromFile("Audio/Spikes.wav");
    sfx[SPIKES].setBuffer(sfxBuffers[SPIKES]);

    sfxBuffers[SIGN_POST].loadFromFile("Audio/SignPost.wav");
    sfx[SIGN_POST].setBuffer(sfxBuffers[SIGN_POST]);

    sfxBuffers[TIME_WARP].loadFromFile("Audio/TimeWarp.wav");
    sfx[TIME_WARP].setBuffer(sfxBuffers[TIME_WARP]);

    sfxBuffers[SCORE_ADD].loadFromFile("Audio/ScoreAdd.wav");
    sfx[SCORE_ADD].setBuffer(sfxBuffers[SCORE_ADD]);

    sfxBuffers[SCORE_TOTAL].loadFromFile("Audio/ScoreTotal.wav");
    sfx[SCORE_TOTAL].setBuffer(sfxBuffers[SCORE_TOTAL]);

    sfxBuffers[ACHIEVEMENT].loadFromFile("Audio/Achievement.wav");
    sfx[ACHIEVEMENT].setBuffer(sfxBuffers[ACHIEVEMENT]);

    sfxBuffers[SPECIAL_WARP].loadFromFile("Audio/SpecialWarp.wav");
    sfx[SPECIAL_WARP].setBuffer(sfxBuffers[SPECIAL_WARP]);

    sfxBuffers[GLASS_SMASH].loadFromFile("Audio/GlassSmash.wav");
    sfx[GLASS_SMASH].setBuffer(sfxBuffers[GLASS_SMASH]);

    sfxBuffers[CRUMBLE].loadFromFile("Audio/Crumble.wav");
    sfx[CRUMBLE].setBuffer(sfxBuffers[CRUMBLE]);

    for (int i = 0; i < TOTAL_SFX; ++i) {
        sfx[i].setVolume(sfxVolume);
    }
}
