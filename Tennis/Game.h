#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"
#include <iostream>
#include <vector>
#include <chrono>


#define BRICK_WIDTH 30
#define BRICK_SIZE 10
#define BRICK_SIZE2 20
#define BRICK_SIZE3 100
#define TOTAL_CHAR 6
#define VELOCITY 5
#define GRAVITY 0.25f
#define FLOOR_LEVEL 720

constexpr std::chrono::microseconds FRAME_DURATION(16667);
constexpr float MARIO_ACCELERATION = 1.0f;
constexpr float MARIO_WALK_SPEED = 4;

class Game
{
private:

	Mario mario;
	int current_frame;
	sf::Texture textures[8];
	sf::Sprite sprites[8];
	std::vector<sf::Sprite> bricks;
	std::vector<Object> objs;
	sf::Event event;
	sf::RenderWindow *window;
	std::chrono::steady_clock::time_point previous_time;
	

public:
	Game(sf::Texture *texture) {
		this->textures[0] = texture[0];
		this->textures[1] = texture[1];
		this->textures[2] = texture[2];
		this->bricks.resize(BRICK_SIZE3);
		this->objs.resize(TOTAL_CHAR);
		this->window = new sf::RenderWindow(sf::VideoMode(1024, 768), "Mario");

	}

	~Game() {
		delete this->window;
	}

	void drawBackground()
	{
		textures[0].loadFromFile("../assets/floor.png");
		textures[1].loadFromFile("../assets/brick.png");
		textures[2].loadFromFile("../assets/pipeS.png");
		textures[3].loadFromFile("../assets/pipe.png");

		sprites[0].setTexture(textures[0]);
		sprites[0].setPosition(0, FLOOR_LEVEL);

		sprites[1].setTexture(textures[2]);
		sprites[1].setPosition(0, 55);

		sprites[2].setTexture(textures[2]);
		sprites[2].scale(-1.0, 1.0);
		sprites[2].setPosition(1024, 55);

		sprites[3].setTexture(textures[3]);
		sprites[3].scale(-1.0, 1.0);
		sprites[3].setPosition(0 + sprites[3].getGlobalBounds().width, FLOOR_LEVEL - sprites[3].getGlobalBounds().height);

		sprites[4].setTexture(textures[3]);
		sprites[4].setPosition(1024 - sprites[4].getGlobalBounds().width, FLOOR_LEVEL - sprites[4].getGlobalBounds().height);

		for(int i(0); i< 14 ; i++)
		{
			bricks.at(i).setTexture(textures[1]);
			bricks.at(i).setPosition(BRICK_WIDTH*(i), 200);
		}

		for (int i(14); i < 28; i++)
		{
			bricks.at(i).setTexture(textures[1]);
			bricks.at(i).setPosition(BRICK_WIDTH * (i + 6), 200);
		}

		for (int i(28); i < 32; i++)
		{
			bricks.at(i).setTexture(textures[1]);
			bricks.at(i).setPosition(BRICK_WIDTH * (i-28), 400);
		}

		for (int i(32); i < 36; i++)
		{
			bricks.at(i).setTexture(textures[1]);
			bricks.at(i).setPosition(BRICK_WIDTH * (i - 2), 400);
		}

		for (int i(36); i < 52; i++)
		{
			bricks.at(i).setTexture(textures[1]);
			bricks.at(i).setPosition(BRICK_WIDTH * (i - 27), 380);
		}

		for (int i(52); i < 64; i++)
		{
			bricks.at(i).setTexture(textures[1]);
			bricks.at(i).setPosition(BRICK_WIDTH * (i - 52), 565);
		}

		for (int i(64); i < 76; i++)
		{
			bricks.at(i).setTexture(textures[1]);
			bricks.at(i).setPosition(BRICK_WIDTH * (i - 52 + 10), 565);
		}



		

	}

	void run() {

		std::chrono::microseconds lag(0);
		previous_time = std::chrono::steady_clock::now();
		this->drawBackground();
		int i = 0;
		while (window->isOpen())
		{
			std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()- previous_time);
			lag+= delta_time;
			previous_time += delta_time;
			

			while(FRAME_DURATION<=lag)
			{
				
				lag-= FRAME_DURATION;

				if (i++ % 4 == 0) {
					current_frame = (current_frame + 1) % 4;
				}

				this->move();


				mario.isOnFloor = 0;

				for(int i(0); i< bricks.size(); i++)
				{
					if(check_Collusion_for_Bricks(&mario, bricks.at(i)))
					{

					mario.isOnFloor = 1;

					sf::FloatRect marioBounds = mario.getSprite().getGlobalBounds();
					sf::FloatRect brickBounds = bricks.at(i).getGlobalBounds();

					float overlapLeft = marioBounds.left + marioBounds.width - brickBounds.left;
					float overlapRight = brickBounds.left + brickBounds.width - marioBounds.left;
					float overlapTop = marioBounds.top + marioBounds.height - brickBounds.top;
					float overlapBottom = brickBounds.top + brickBounds.height - marioBounds.top;


					// Determine which side of the brick Mario is colliding with
					if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom)
					{
						
						mario.moveLeft({ -abs(mario.vx), 0 });
						
					}
					else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom)
					{
	
						mario.moveRight({ abs(mario.vx) ,0 });
						
					}
					else if (overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom)
					{
						// Mario is colliding with the top of the brick
						mario.moveTop({0, -mario.vy});
					}
					else if (overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop)
					{
						// Mario is colliding with the bottom of the brick
						mario.vy = 0.0f;
						mario.moveBottom({0, GRAVITY + 10});
						//std::cout << mario.getPos().x << "  " << mario.getPos().y << std::endl;
					}
					}
				}

				//bool isOnFloor = onFloor(&mario);
				

				mario.vy = std::min(GRAVITY + mario.vy, 8.0f);
				//std::cout << mario.vy << std::endl;
				


				mario.getSprite().move(mario.vx, mario.vy);


				if(mario.getPos().y >= FLOOR_LEVEL-80)
				{
					mario.getSprite().setPosition(mario.getPos().x, FLOOR_LEVEL - 80);
					mario.isOnFloor = 1;
				}
				if (mario.getPos().y <= 0)
				{
					mario.getSprite().setPosition(mario.getPos().x, 0);
				}

				if (mario.getPos().x <= 0)
				{
					mario.getSprite().setPosition(0, mario.getPos().y);
				}
				if (mario.getPos().x >= 1024-66)
				{
					//std::cout << mario.getPos().x << std::endl;
					mario.getSprite().setPosition(1024-66, mario.getPos().y);
				}


				this->render();
				window->display();
			}
	
		}
	}

	void move()
	{
		while (window->pollEvent(this->event))
		{
			{

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == 0) {
					mario.setAnimation(current_frame, 0);
						mario.vx = 0;


				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == 0)
				{
					//std::cout << mario.vx << std::endl;
					
					mario.getSprite().setTextureRect(sf::IntRect(66, 0 , -66, 88));
					mario.setAnimation(current_frame, 1);
					mario.vx = std::min(mario.vx + MARIO_ACCELERATION, MARIO_WALK_SPEED);

					mario.moveRight({ mario.vx, 0 });

					
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == 0)
				{

					//std::cout << mario.vx << std::endl;
					mario.setAnimation(current_frame, 1);
					mario.getSprite().setTextureRect(sf::IntRect(0, 0, 66, 88));
					mario.vx = std::max(mario.vx - MARIO_ACCELERATION, -MARIO_WALK_SPEED);

					
					mario.moveLeft({ mario.vx, 0 });
					
				}

				/*else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == 0) {
					mario.setAnimation(current_frame, 0);
					mario.vx = 0;
					std::cout << "asdasd" << std::endl;
					
				}*/



				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && mario.isOnFloor)
				{
					mario.moveTop({0, -10 + VELOCITY*0.4});
					mario.vy = -10;
					//std::cout << mario.vy << std::endl;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
				{
					
				}

			}
		}


	}


	void render()
	{
		window->clear();

		window->draw(sprites[0]);
		window->draw(sprites[1]);
		window->draw(sprites[2]);
		window->draw(sprites[3]);
		window->draw(sprites[4]);

		for(int i(0); i< bricks.size(); i++)
		{
			window->draw(bricks.at(i));
		}
		 
		mario.draw(window);

		// follow mario to display in right place when called
		//gameInfo.followMario(view.getCenter().x);
		//menu.followMario(mario.getPosition().x);

		//gameInfo.draw(*window, view.getCenter().x);

		//if (mario.getIsAlive())
		//window->draw(mario);

		//drawMobs();

	}

	bool onFloor(Object* obj) {
		if (obj->vy == 8.0) {
			obj->isOnFloor = 1;
			return 1;
		}
		else {
			obj->isOnFloor = 0;
			return 0;
		}
	}

	bool checkCollusion_for_Turtle(Turtle *t, Mario *m, int& side)
	{
		
	}

	bool check_Collusion_for_Bricks(Mario *m, sf::Sprite brick)
	{
		if(m->getSprite().getGlobalBounds().intersects(brick.getGlobalBounds()))
		{
			return true;
		}
		return false;
	}

	void update()
	{
		
	}


};

