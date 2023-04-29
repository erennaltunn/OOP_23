#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
class Mario : public Object
{

public:
    float vx;
    float vy;


    Mario(sf::RenderWindow* win) : Object(win), vx(0), vy(0) {
        this->pos = sf::Vector2f(0.0f, 540.f);
        textures[0].loadFromFile("../assets/mario2.png");
        sprite.setTexture(textures[0]);
        sprite.setPosition(sf::Vector2f(pos));
    }

    void move() {
        // Mario-specific move implementation
        pos.x += vx;
        setPosition(pos);
    }

    void fall() {
        // Mario-specific fall implementation
        pos.y += vy;
        setPosition(pos);
    }


};

