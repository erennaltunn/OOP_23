#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include "Scoreboard.h"
#include "Mario.h"
#define MAX_NUMBER_OF_ITEMS 4


enum class GameState
{
    Menu,
    Playing,
    GameOver
};


class Menu 
{

    int selectedOption = 0;
    
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    GameState gameState;

    public:

        sf::RenderWindow* window;

        Menu()
        {
            menu[0].setFont(font);
            menu[0].setFillColor(sf::Color::Red);
            menu[0].setString("Play Game");
            menu[0].setPosition({400, 380});

            menu[1].setFont(font);
            menu[1].setFillColor(sf::Color::Black);
            menu[1].setString("YOU WIN");
            menu[1].setPosition({390, 380});

            menu[2].setFont(font);
            menu[2].setFillColor(sf::Color::Black);
            menu[2].setString("YOU LOSE");
            menu[2].setPosition({390, 380});

        }

        void render(sf::RenderWindow& window, Scoreboard scoreboard, Mario mario) {

            sf::Texture texture;
            texture.loadFromFile("../assets/menuBack.png");
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition({300, 300});
            

            !font.loadFromFile("../assets/font.ttf");


            window.clear();

            window.draw(sprite);


            if (scoreboard.getScore() == 500)
            {
                window.draw(menu[1]);
            }
            else if (mario.getLife() == 0)
            {
                window.draw(menu[2]);
            }
            else if (gameState == GameState::Menu) {
                window.draw(menu[0]);
            }

            else
            {
                window.draw(menu[0]);
            }
            
            window.display();

        }

        void handleInput(sf::Event event)
        {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    if (selectedOption == 0) {
                        // "PLAY GAME" option selected
                        gameState = GameState::Playing; // Transition to the game state
                        selectedOption += 1;
                    }
                    if (gameState == GameState::GameOver && event.key.code == sf::Keyboard::Return)
                    {
                        std::cout << "trying" << std::endl;
                        gameState = GameState::Menu;


                    }
                }
            }
        }

        GameState& getState()
        {
            return gameState;
        }
    

};