#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>

class Object
{
    private:
        sf::Texture textures[8]; //assets for mario and turtles
        sf::Sprite sprite;
        float Width;
        float Height;
        float Velocity;

        sf::Vector2f velocity{ Velocity, Velocity };
    protected:
        

    public:
        Object() {}
        float vx;
        float vy;
        bool isOnFloor = 0;
        bool setStartPosition(Object *obj);
        //virtual void draw();

        float left();
        float right();
        float top();
        float bottom();

        void MovingDirectiongLeft() { velocity.x = -Velocity; }
	    void MovingDirectiongRight() { velocity.x = Velocity; }

        virtual sf::Sprite& getSprite()
        {
            return sprite;
        };



};
