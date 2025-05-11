#pragma once
#include "Collectibles.h"

class SpecialBoost : public Collectibles {

public:

    SpecialBoost(int x, int y, Texture* tex) : Collectibles(x, y, false) {
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

        float boost_x = x * cell_size;
        float boost_y = y * cell_size + 32;

        if (player.getx() + player.getPwidth() > boost_x && player.getx() < boost_x + 64 &&player.gety() + player.getPheight() > boost_y && player.gety() < boost_y + 64) {

            collect();
            result = 1;
            lvl[y][x] = 's';
            return true;
        }
        return false;
    }
};
