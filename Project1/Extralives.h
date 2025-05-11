#pragma once
#include "Collectibles.h"

class ExtraLife : public Collectibles {

public:


    ExtraLife(int x, int y, Texture* tex) : Collectibles(x, y, false) {
        this->texture = tex;
        sprite.setTexture(*tex);
        sprite.setScale(2.f, 2.f);
    }

    void collect() override {
        collected = true;
        showEffect = false; 
    }

    bool handleCollision(Player& player, char** lvl, int cell_size, int& result) override {

        if (!isActive()) 
            return false;

        float life_x = x * cell_size;
        float life_y = y * cell_size + 32;

        if (player.getx() + player.getPwidth() > life_x && player.getx() < life_x + 64 && player.gety() + player.getPheight() > life_y && player.gety() < life_y + 64) {
            collect();
            result++;
            lvl[y][x] = 's';
            return true;
        }
        return false;
    }
};
