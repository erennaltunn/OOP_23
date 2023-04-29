#pragma once

#include <SFML/Graphics.hpp>

class Object
{
	public:
        // Attributes
        sf::Texture textures[8];
        sf::Sprite sprite;
        sf::Vector2f pos;
        sf::RenderWindow* window;
        int state;
        int heading;

        // Constructor
        Object(sf::RenderWindow* win) : window(win) {}

        void setPosition(sf::Vector2f pos) {
            this->pos = pos;
            sprite.setPosition(pos);
        }

        sf::Vector2f getPosition() {
            return pos;
        }

        void draw(sf::RenderWindow& window) {
            window.draw(sprite);
        }

        sf::IntRect boundingBox();

        // Abstract methods to be overridden in derived classes
        virtual void move() = 0;
        virtual void fall() = 0;
        //virtual void jump() = 0;

        

};




