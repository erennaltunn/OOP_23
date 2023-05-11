#pragma once
#include "Object.h"
class Turtle :
    public Object
{

    sf::Sprite sprite;
    sf::Texture texture;
    float flPreviousTime = 0;
    float flCurrentTime = 0;
    float dt;
public:
    Turtle() {
        this->texture.loadFromFile("../assets/turtle2.png");
        this->sprite.setTexture(this->texture);
        this->sprite.setPosition(100, 60);

    }
    float vy;
    float vx;

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

    //void setAnimation(int frame_count, int moving) {
    //    if (moving == 0) {
    //        this->sprite.setTexture(this->texture[0]);

    //    }
    //    else if (moving == 1)
    //    {
    //        this->sprite.setTexture(this->texture[frame_count + 1]);
    //    }

    //}

};

