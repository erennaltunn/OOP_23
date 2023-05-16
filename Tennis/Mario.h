#pragma once
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <chrono>

class Mario : public Object
{
    private:
        //3 chances to play.
        int life = 3;

    public:
        //Constructer
        Mario();

        int getLife()
        {
            return life;
        }

        int killMario();

        //Set the correct texture based on the frame count.
        void setAnimation(int frame_count, int mode);
};

