#pragma once
#include "Object.h"

class Turtle : public Object
{
    public:
        //Constructer.
        Turtle();

        //sets the correct texture based on the frame changes.
        void setAnimation(int frame_count);
};

