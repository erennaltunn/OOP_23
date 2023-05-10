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


};

