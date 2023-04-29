#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game
{
private:

	sf::Texture floor_texture;
	sf::Sprite floor_sprite;


public:
	Game(sf::Texture texture) {
		this->floor_texture = texture;
	}

	void drawBackground(sf::RenderWindow& window)
	{

		if (!floor_texture.loadFromFile("../assets/floor.png"))
		{
			//cout << "File could not be found!" << endl;
		}
		
		floor_sprite.setTexture(floor_texture);

		floor_sprite.setPosition(0, 600);
		
	}

	void run(sf::RenderWindow* window) {
		while (window->isOpen())
		{
			this->drawBackground(*window);
			this->render(window);	
			
		}
	}


	void render(sf::RenderWindow* window)
	{
		window->clear();

		window->draw(floor_sprite);

		// follow mario to display in right place when called
		//gameInfo.followMario(view.getCenter().x);
		//menu.followMario(mario.getPosition().x);

		//gameInfo.draw(*window, view.getCenter().x);

		//if (mario.getIsAlive())
		//window->draw(mario);

		//drawMobs();

		window->display();
		sf::sleep(sf::milliseconds(1));
	}
};

