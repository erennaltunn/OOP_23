#include "Mario.h"

Mario::Mario() {
    this->textures[0].loadFromFile("../assets/mario1.png");
    this->textures[1].loadFromFile("../assets/mario2.png");
    this->textures[2].loadFromFile("../assets/mario3.png");
    this->textures[3].loadFromFile("../assets/mario4.png");
    this->textures[4].loadFromFile("../assets/mario6.png");
    this->textures[5].loadFromFile("../assets/mario5.png");
    this->textures[6].loadFromFile("../assets/mario7.png");


    this->sprite.setTexture(this->textures[0]);
    this->sprite.setPosition(0, 550);
}

//Decrease life.
int Mario::killMario()
{
    life--;

    if (life <= 0)
    {
        life = 0;
    }

    return life;
}

//Set the correct texture based on the frame count.
void Mario::setAnimation(int frame_count, int mode) {
    //Standing.
    if (mode == 0) {
        this->sprite.setTexture(this->textures[0]);

    }
    //Walking animation.
    else if (mode == 1)
    {
        this->sprite.setTexture(this->textures[frame_count + 1]);
    }
    //Sliding
    else if (mode == 2)
    {
        this->sprite.setTexture(this->textures[5]);
    }
    //Die
    else if (mode == -1)
    {
        this->sprite.setTexture(this->textures[6]);
    }
}