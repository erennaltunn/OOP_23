#pragma once
#include "Object.h"




class Mario : public Object
{
	public:
        // Attributes
        float vx;
        float vy;
        bool isOnGround;
        const float GRAVITY = 1000.0f;

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

        //void fall() {
        //    // Mario-specific fall implementation
        //    pos.y += vy;
        //    setPosition(pos);
        //}

        //void jump(bool down) {
        //    // Mario-specific jump implementation
        //    if (down) {
        //        vy = -vy;
        //    }
        //    else {
        //        vy = -abs(vy);
        //    }
        //    //fall();
        //}

        void fall() {
            // Mario-specific fall implementation
            vy += GRAVITY;
            pos.y += vy;
            setPosition(pos);

            checkGroundCollision();
        }

        void jump(bool down) {
            // Mario-specific jump implementation
            if (!isOnGround || down) {
                return; // Don't jump if not on the ground or if 'down' is true
            }

            const float jumpStrength = 20.0f; // Adjust this value to control the jump height
            vy = -jumpStrength;
            fall();
        }

        void update(float deltaTime) {
            // Update Mario's position based on the elapsed time
            pos.x += vx * deltaTime;
            pos.y += vy * deltaTime;
            setPosition(pos);

            // Apply gravity
            vy += GRAVITY * deltaTime;

            // Check for collision with the ground
            checkGroundCollision();
        }

        void checkGroundCollision() {
            // Check if Mario has landed on the ground
            if (pos.y >= 450) {
                pos.y = 450;
                setPosition(pos);
                isOnGround = true;
                vy = 0; // Reset the vertical velocity
            }
            else {
                isOnGround = false;
            }
        }

};





