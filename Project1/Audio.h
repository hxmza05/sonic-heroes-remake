#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Audio {

private:

    SoundBuffer* sfxBuffers;
    Sound* sfx;
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

    int LEVEL1_MUSIC;
    int LEVEL2_MUSIC;
    int LEVEL3_MUSIC;
    int BOSS_MUSIC;
    int TOTAL_MUSIC;
    string musicPaths[4];


public:

    Audio() {

        LEVEL1_MUSIC = 0;
        LEVEL2_MUSIC = 1;
        LEVEL3_MUSIC = 2;
        BOSS_MUSIC = 3;
        TOTAL_MUSIC = 4;

        musicPaths[LEVEL1_MUSIC] = "Audio/Level1.ogg";
        musicPaths[LEVEL2_MUSIC] = "Audio/Level2.ogg";
        musicPaths[LEVEL3_MUSIC] = "Audio/Level3.ogg";
        musicPaths[BOSS_MUSIC] = "Audio/BossLevel.ogg";


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

        sfx = new Sound[TOTAL_SFX];
        sfxBuffers = new SoundBuffer[TOTAL_SFX];

    }


    int getMenuButton() {
        return MENU_BUTTON;
    }

    int getSelect() {
        return SELECT;
    }

    int getBackButton() {
        return BACK_BUTTON;
    }

    int getJump() {
        return JUMP;
    }

    int getFlying() {
        return FLYING;
    }

    int getSkidding() {
        return SKIDDING;
    }

    int getHurt() {
        return HURT;
    }

    int getOneUp() {
        return ONE_UP;
    }

    int getRing() {
        return RING;
    }

    int getTired() {
        return TIRED;
    }

    int getDestroy() {
        return DESTROY;
    }

    int getExplosion() {
        return EXPLOSION;
    }

    int getShot() {
        return SHOT;
    }

    int getBossHit() {
        return BOSS_HIT;
    }

    int getSpikes() {
        return SPIKES;
    }

    int getSignPost() {
        return SIGN_POST;
    }

    int getTimeWarp() {
        return TIME_WARP;
    }

    int getScoreAdd() {
        return SCORE_ADD;
    }

    int getScoreTotal() {
        return SCORE_TOTAL;
    }

    int getAchievement() {
        return ACHIEVEMENT;
    }

    int getSpecialWarp() {
        return SPECIAL_WARP;
    }

    int getGlassSmash() {
        return GLASS_SMASH;
    }

    int getCrumble() {
        return CRUMBLE;
    }

    int getTotalSfx() {
        return TOTAL_SFX;
    }

    int getLevel1Music() {
        return LEVEL1_MUSIC;
    }

    int getLevel2Music() {
        return LEVEL2_MUSIC;
    }

    int getLevel3Music() {
        return LEVEL3_MUSIC;
    }

    int getBossMusic() {
        return BOSS_MUSIC;
    }


    void loadAllSounds();
    void playSound(int Soundid);
    void playLevelMusic(const string& path);
    void setSFXVolume(float volume);
    void setMusicVolume(float volume);

    void playLevelMusicByIndex(int index) {

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


    ~Audio() {
        delete[] sfx;
        delete[] sfxBuffers;
    }

};



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
        sfx[i].setBuffer(sfxBuffers[i]);
        sfx[i].setVolume(sfxVolume);
    }
}
