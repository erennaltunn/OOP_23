#pragma once
#include "Object.h"
class Turtle :
    public Object
{

    sf::Sprite sprite;
    sf::Texture texture[8];
    float flPreviousTime = 0;
    float flCurrentTime = 0;
    float dt;
public:
    Turtle() {
        this->texture[0].loadFromFile("../assets/turtle1.png");
        this->texture[1].loadFromFile("../assets/turtle2.png");
        this->texture[2].loadFromFile("../assets/turtle3.png");
        this->texture[3].loadFromFile("../assets/turtle4.png");
        this->texture[4].loadFromFile("../assets/turtle5.png");
        this->sprite.setTexture(this->texture[0]);
        this->sprite.setPosition(100, 60);

    }
    float vy;
    float vx;
    bool isDead = 0;

    void draw(sf::RenderWindow* window)
    {
        window->draw(sprite);
    }

    void move(sf::Vector2f vel)
    {

        this->sprite.move(vel);
    }
    //objecte çek
    sf::Sprite& getSprite()
    {
        return sprite;
    }

    sf::Vector2f getPosition() {
        return this->sprite.getPosition();
    }

    void setPosition(sf::Vector2f pos) {
        this->sprite.setPosition(pos);
    }

    void setAnimation(int frame_count) {
        if (isDead == 0) {
            frame_count = frame_count % 3;
            this->sprite.setTexture(this->texture[frame_count]);

        }

        else if (isDead)
        {
            this->sprite.setTexture(this->texture[4]);

        }



    }

};

