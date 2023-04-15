#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

const float GRAVITY = 1000.0f;
const float JUMP_VELOCITY = -500.0f;
const float MOVE_SPEED = 300.0f;


int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Tennis Ball");

    sf::Texture floor_texture;
    if (!floor_texture.loadFromFile("../assets/floor.png"))
    {
        cout << "File could not be found!" << endl;
    }

    sf::Texture mario_texture;
    if (!mario_texture.loadFromFile("../assets/mario2.png"))
    {
        cout << "File could not be found!" << endl;
    }

    sf::Sprite floor_sprite;
    floor_sprite.setTexture(floor_texture);

    sf::Sprite floor2(floor_texture);


    sf::Sprite mario_sprite;
    mario_sprite.setTexture(mario_texture);

    // set initial positions of mario and floor
    floor_sprite.setPosition(0, 488);
    mario_sprite.setPosition(100, 338);

    // set initial velocity of mario
    sf::Vector2f velocity(0.0f, 0.0f);

    // create a clock to measure elapsed time
    sf::Clock clock;



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
                    velocity.x = -MOVE_SPEED;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    velocity.x = MOVE_SPEED;
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    // make mario jump
                    if (mario_sprite.getPosition().y == 450)
                    {
                        velocity.y = JUMP_VELOCITY;
                    }
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                {
                    velocity.x = 0.0f;
                }
                break;

            }

        }

        // update game logic
        float deltaTime = clock.restart().asSeconds();

        // apply gravity to mario's velocity
        velocity.y += GRAVITY * deltaTime;


        // move mario based on velocity
        mario_sprite.move(velocity * deltaTime);

        // check if mario hits the floor
        if (mario_sprite.getPosition().y >= 450)
        {
            mario_sprite.setPosition(mario_sprite.getPosition().x, 450);
            velocity.y = 0.0f;
        }

        window.clear();

        window.draw(floor_sprite);

        window.draw(mario_sprite);

        window.display();

        sf::sleep(sf::milliseconds(1));
    }

    return 0;
}