#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Mario.h"

using namespace std;

const float GRAVITY = 1000.0f;
const float JUMP_VELOCITY = 1000.0f;
const float MOVE_SPEED = 1.0f;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tennis Ball");

    sf::Texture floor_texture;
    if (!floor_texture.loadFromFile("../assets/floor.png"))
    {
        cout << "File could not be found!" << endl;
    }

    sf::Sprite floor_sprite;
    floor_sprite.setTexture(floor_texture);

    sf::Sprite floor2(floor_texture);


    Mario mario(&window);

    // create a clock to measure elapsed time
    sf::Clock clock;

    // set initial positions of mario and floor
    floor_sprite.setPosition(0, 488);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;


        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:

                if (event.key.code == sf::Keyboard::Left)
                {
                    mario.vx = -MOVE_SPEED;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    mario.vx = MOVE_SPEED;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    // make mario jump
                    if (mario.getPosition().y == 450)
                    {
                        mario.vy = JUMP_VELOCITY;

                    }
                    
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                {
                    mario.vx = 0.0f;
                }
                break;

            }

        }

        // update game logic
        float deltaTime = clock.restart().asSeconds();

        // apply gravity to mario's velocity
        mario.vy += GRAVITY * deltaTime;


        // move mario based on velocity
        mario.move();


        // check if mario hits the floor
        if (mario.getPosition().y < 450)
        {
            mario.setPosition(sf::Vector2f(mario.getPosition().x, mario.vy));
        }

        if (mario.getPosition().y > 450)
        {
            mario.setPosition(sf::Vector2f(mario.getPosition().x, 0));
        }
        

        window.clear();

        window.draw(floor_sprite);

        mario.draw(window);

        window.display();
        printf("%f, %f \n", mario.getPosition().x, mario.getPosition().y);

        sf::sleep(sf::milliseconds(1));

    }


    

    return 0;

}