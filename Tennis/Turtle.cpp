#include "Turtle.h"

Turtle::Turtle() {
    this->textures[0].loadFromFile("../assets/turtle1.png");
    this->textures[1].loadFromFile("../assets/turtle2.png");
    this->textures[2].loadFromFile("../assets/turtle3.png");
    this->textures[3].loadFromFile("../assets/turtle4.png");
    this->textures[4].loadFromFile("../assets/turtle5.png");
    this->sprite.setTexture(this->textures[0]);
    this->sprite.setPosition(100, 60);

}

//sets the correct texture based on the frame changes.
void Turtle::setAnimation(int frame_count) {
    if (isDead == 0) {
        //Turtles has 3 different images so we get the tripartite remainder.
        frame_count = frame_count % 3;
        this->sprite.setTexture(this->textures[frame_count]);
    }

    //turtle dead texture.
    else if (isDead)
    {
        this->sprite.setTexture(this->textures[4]);
    }

}
