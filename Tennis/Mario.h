#pragma once
#include "Object.h"


class Mario : public Object
{
	public:
        // Attributes
        float vx;
        float vy;

		Mario(sf::RenderWindow* win) : Object(win) , vx(0), vy(0) {
            textures[0].loadFromFile("../assets/mario2.png");
            sprite.setTexture(textures[0]);
            sprite.setPosition(sf::Vector2f(100.f, 100.f));

        }
		
        // Implement the abstract methods
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

        void jump(bool down) {
            // Mario-specific jump implementation
            if (down) {
                vy = -vy;
            }
            else {
                vy = -abs(vy);
            }
            fall();
        }
};





