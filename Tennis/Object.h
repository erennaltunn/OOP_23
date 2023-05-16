#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>

class Object
{
    private:

    public:
        Object() {};

        sf::Texture textures[8];
        sf::Sprite sprite;
        //vx, vy speed vectors for mario and turtle.
        float vx;
        float vy;

        bool isDead = 0;
        bool isOnFloor = 0;

        sf::Sprite& getSprite()
        {
            return sprite;
        };

        void draw(sf::RenderWindow* window)
        {
            window->draw(sprite);
        };

        void move(sf::Vector2f vel)
        {
            this->sprite.move(vel);
        }

        sf::Vector2f getPosition() {
            return this->sprite.getPosition();
        }

        void setPosition(sf::Vector2f pos) {
            this->sprite.setPosition(pos);
        }

};
