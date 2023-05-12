#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>


class Mario : public Object
{
    private:


        bool canJump = 0;
        float jumpCurrentPosition = 0;
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point finishTime;
        sf::Clock clock;
        sf::Sprite sprite;
        sf::Texture texture[8];
        float flPreviousTime = 0;
        float flCurrentTime = 0;
        float dt;  
        bool keyRel = false;  
        int life = 3;

    public:


        Mario() {
            this->texture[0].loadFromFile("../assets/mario1.png");
            this->texture[1].loadFromFile("../assets/mario2.png");
            this->texture[2].loadFromFile("../assets/mario3.png");
            this->texture[3].loadFromFile("../assets/mario4.png");
            this->texture[4].loadFromFile("../assets/mario6.png");
            this->texture[5].loadFromFile("../assets/mario5.png");
            this->texture[6].loadFromFile("../assets/mario7.png");


            this->sprite.setTexture(this->texture[0]);
            this->sprite.setPosition(0, 550);
        }
        void move();
        void jump(bool down);
        void fall(void);
        int flip = 0;
        bool isDead = 0;

        void draw(sf::RenderWindow *window)
        {
            window->draw(sprite);
        };

        void moveLeft(sf::Vector2f vel)
        {

            this->sprite.move(vel);
        }
        void moveRight(sf::Vector2f vel)
        {
            this->sprite.move(vel);
        }
        void moveTop(sf::Vector2f vel)
        {

            this->sprite.move({vel});
        }


        void moveBottom(sf::Vector2f vel)
        {
            this->sprite.move({vel});
        }

        sf::Sprite& getSprite()
        {
            return sprite;
        }
        
        sf::Vector2f getPos()
        {
            return sprite.getPosition();
        }

        int killMario()
        {
            life--;

            if (life <= 0)
            {
               life = 0;
            }

            return life;
        }

        int getLife()
        {
            return life;
        }



        void setAnimation(int frame_count, int mode) {
            if (mode == 0) {
                this->sprite.setTexture(this->texture[0]);
 
            }
            else if (mode == 1)
            {
                this->sprite.setTexture(this->texture[frame_count + 1]);
            }

            else if (mode == 2)
            {
                this->sprite.setTexture(this->texture[5]);
            }
            else if(mode == -1)
            {
                this->sprite.setTexture(this->texture[6]);
            }

        }
};

