#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <chrono>
constexpr std::chrono::microseconds FRAME_DURATION(16667);
using namespace std;

const float GRAVITY = 0.981f;
const float JUMP_VELOCITY = -20.0f;
const float MOVE_SPEED = 10.0f;


int main()
{
    sf::Texture floor_texture;
    sf::Sprite floor_sprite;
    Game game(floor_texture);
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tennis Ball");
    game.run(&window);

    
    /*
    std::chrono::microseconds lag(0);
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


    // set initial positions of mario and floor
    floor_sprite.setPosition(0, 600);

    std::chrono::steady_clock::time_point previous_time;
    previous_time = std::chrono::steady_clock::now();

    // run the program as long as the window is open


    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

        lag += delta_time;
        previous_time += delta_time;


        while (FRAME_DURATION <= lag)

        {
            unsigned view_x;

            lag -= FRAME_DURATION;

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
                        if (mario.getPosition().y >= 540)
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




            mario.move();
            mario.vy = std::min(GRAVITY + mario.vy, 8.0f);
            mario.fall();

        }


        // check if mario hits the floor
        if (mario.getPosition().y >= 540)
        {
            mario.setPosition(sf::Vector2f(mario.pos.x, 540));
        }


        window.clear();

        window.draw(floor_sprite);

        mario.draw(window);

        window.display();

        sf::sleep(sf::milliseconds(1));
    }
    */
    return 0;
    
}