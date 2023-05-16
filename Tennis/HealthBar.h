#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>

#define MAX_HEALTH 3

//Updating health bar.

class HealthBar {
public:
    HealthBar()
    {
        maxHealth = MAX_HEALTH;
        currentHealth = MAX_HEALTH;
        if(!healthTexture.loadFromFile("../assets/mariohead.png"))
        {
            std::cout << "Failed to load mario head" << std::endl;
        }

        healthSprite.setTexture(healthTexture);
    }

    void decreaseHealth()
    {
        if (currentHealth > 0) {
        currentHealth--;
        }
    }

    void setPosition(const sf::Vector2f& position)
    {
        healthSprite.setPosition(position);
    }
    
    void draw(sf::RenderWindow *window)
    {
        for (int i = 0; i < currentHealth; ++i) {
        //std::cout << i << std::endl;
        sf::Vector2f spritePosition = healthSprite.getPosition();
        spritePosition.x = (i + 22) * (healthSprite.getGlobalBounds().width + 5);
        healthSprite.setPosition(spritePosition);
        window->draw(healthSprite); // we can make it in render
        }
    }

private:
    int maxHealth;
    int currentHealth;
    sf::Sprite healthSprite;
    sf::Texture healthTexture;
};


