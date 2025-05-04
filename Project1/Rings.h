#pragma once
#include<iostream>
#include"Collectibles.h"
using namespace std;
using namespace sf;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>



class Ring : public Collectibles {

private:

    Clock ringsClock;
    const float ringHeight;
    int ringAnimIndex = 0;
    

public:

    Ring(int x, int y, Texture* texture, Texture* afterEffect) : Collectibles(x, y, false), ringHeight(66.0) {

        this->texture = texture;
        this->afterEffect = afterEffect;
        totalAnimations = 2;
        indexAnimation = 0;
        ringsClock.restart();

        states = new Animation * [2];
        states[0] = new Animation(4);


        states[0]->getSprites()[0].setTexture(*texture);
        states[0]->getSprites()[0].setTextureRect(IntRect(0, 0, 66, ringHeight));
        states[0]->getSprites()[0].setScale(0.75f, 0.75f);


        states[0]->getSprites()[1].setTexture(*texture);
        states[0]->getSprites()[1].setTextureRect(IntRect(66, 0, 56, ringHeight));
        states[0]->getSprites()[1].setScale(0.75f, 0.75f);


        states[0]->getSprites()[2].setTexture(*texture);
        states[0]->getSprites()[2].setTextureRect(IntRect(122, 0, 32, ringHeight));
        states[0]->getSprites()[2].setScale(0.75f, 0.75f);


        states[0]->getSprites()[3].setTexture(*texture);
        states[0]->getSprites()[3].setTextureRect(IntRect(154, 0, 53, ringHeight));
        states[0]->getSprites()[3].setScale(0.75f, 0.75f);


        sprite = states[0]->getSprites()[0];

        ringAnimIndex = 0;

        states[1] = new Animation(4);

        for (int i = 0; i < 4; i++) {

            states[1]->getSprites()[i].setTexture(*afterEffect);
            states[1]->getSprites()[i].setTextureRect(IntRect(i * 32 + 16, 0, 16, 64));
            //states[1]->getSprites()[i].setOrigin(8.f, 32.f); 
            states[1]->getSprites()[i].setScale(2.5f, 2.5f);

        }




    }


    void collect() override {
        collected = true;
        showEffect = true;
        effectClock.restart();
        indexAnimation = 1;
        states[1]->reset();
    }


    void update() override {

        if (collected) {

            if (showEffect) {

                for (int i = 0; i < 4; i++) {
                    states[1]->getSprites()[i].setTextureRect(IntRect(i * 32 + 16, ringAnimIndex * 16, 16, 16));
                }

                states[1]->RunAnimation();
                sprite = states[1]->getSprites()[states[1]->getIndex()];
                sprite.setPosition(x * 64, y * 64 + 12);

                if (effectClock.getElapsedTime().asSeconds() > 0.9f) {
                    showEffect = false;
                }

            }

            return;
        }

        if (ringsClock.getElapsedTime().asSeconds() > 0.125f) {
            states[0]->RunAnimation();
            ringsClock.restart();
        }

        sprite = states[0]->getSprites()[states[0]->getIndex()];
        sprite.setPosition(x * 64, y * 64 + 12); 

    }


    float getRingHeight() {
        return ringHeight*0.75f;
    }

};