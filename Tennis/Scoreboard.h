#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>

class Scoreboard
{
    private:
        int score;
        sf::Font font;
        sf::Text scoreText;
        sf::Texture healthTexture;
    
    public:
        //Contructer
        Scoreboard()
        {
            score = 0;
            if (!font.loadFromFile("../assets/font.ttf")) {
                std::cout << "Failed to load font!" << std::endl;
            }

            if(!healthTexture.loadFromFile("../assets/mariohead.png")){
                std::cout << "Failed to load mariohead!" << std::endl;
            }
            scoreText.setFont(font);
            scoreText.setCharacterSize(24);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(10, 10);

            updateScoreText();
        }

        void updateScore(int points)
        {
            score += points;
            updateScoreText();
        }

        void updateScoreText()
        {
            scoreText.setString("Score: " + std::to_string(score));
        }

        void draw(sf::RenderWindow *window)
        {
            window->draw(scoreText);
        }

        int getScore()
        {
            return score;
        }
    
};

