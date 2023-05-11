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
#define TOTAL_CHAR 5
#define VELOCITY 5
#define GRAVITY 0.25f
#define FLOOR_LEVEL 720
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1000

constexpr std::chrono::microseconds FRAME_DURATION(16667);
constexpr float MARIO_ACCELERATION = 1.0f;
constexpr float MARIO_WALK_SPEED = 4;

class Game
{
private:

	Mario mario;
	Turtle turtle1;
	Turtle turtle2;
	Turtle turtle3;
	Turtle turtle4;
	Turtle turtle5;

	int current_frame;
	sf::Texture textures[8];
	sf::Sprite sprites[8];
	std::vector<sf::Sprite> bricks;
	std::vector<Turtle> turtles;
	sf::Event event;
	sf::RenderWindow *window;
	std::chrono::steady_clock::time_point previous_time;
	

public:
	Game(sf::Texture *texture) {
		this->textures[0] = texture[0];
		this->textures[1] = texture[1];
		this->textures[2] = texture[2];
		this->bricks.resize(BRICK_SIZE3);
		this->turtles.resize(TOTAL_CHAR);
		this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");
		
		turtles[0] = turtle1;
		turtles[0].setPosition({100, 50});

		turtles[1] = turtle2;
		turtles[1].setPosition({ 900, 50 });

		turtles[2] = turtle3;
		turtles[2].setPosition({ 100, 50 });

		turtles[3] = turtle4;
		turtles[3].setPosition({ 900, 50 });
		
		turtles[4] = turtle5;
		turtles[4].setPosition({ 100, 50 });




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
		sprites[2].setPosition(WINDOW_WIDTH, 55);

		sprites[3].setTexture(textures[3]);
		sprites[3].scale(-1.0, 1.0);
		sprites[3].setPosition(0 + sprites[3].getGlobalBounds().width, FLOOR_LEVEL - sprites[3].getGlobalBounds().height);

		sprites[4].setTexture(textures[3]);
		sprites[4].setPosition(WINDOW_WIDTH - sprites[4].getGlobalBounds().width, FLOOR_LEVEL - sprites[4].getGlobalBounds().height);

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
		int z = 0;
		while (window->isOpen())
		{
			std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()- previous_time);
			lag+= delta_time;
			previous_time += delta_time;
			

			while(FRAME_DURATION<=lag)
			{
				
				lag-= FRAME_DURATION;

				if (z++ % 4 == 0) {
					current_frame = (current_frame + 1) % 4;
				}

				this->move();


				mario.isOnFloor = 0;
				//turtle.isOnFloor = 0;

				
				
				for(int k(0); k < bricks.size(); k++)
				{
					if(check_Collusion_for_Bricks(&mario, bricks.at(k)))
					{

						mario.isOnFloor = 1;

						sf::FloatRect marioBounds = mario.getSprite().getGlobalBounds();
						sf::FloatRect brickBounds = bricks.at(k).getGlobalBounds();

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

				
				for (int i = 0; i < 5; i++)
				{
					sf::Vector2f turtle_pos = turtles[i].getPosition();

					turtles[i].isOnFloor = 0;

					for (int j(0); j < bricks.size(); j++) {
						if (checkCollusion_for_Turtle(&turtles[i], bricks.at(j))) {
							turtles[i].isOnFloor = 1;
						}
					}
					//continue
					if (turtles[i].isOnFloor) {
						turtles[i].move({ turtles[i].vx, 0 });
					}
					//if left top
					else if (turtle_pos.x < 200 && turtle_pos.y < 200) {
						turtles[i].vx = turtles[i].vx + 0.03;
						turtles[i].move({ turtles[i].vx, 0 });
					}
					//right top
					else if (turtle_pos.x >= 800 && turtle_pos.y < 200) {
						turtles[i].getSprite().setTextureRect(sf::IntRect(68, 0, -68, 66));
						turtles[i].vx = turtles[i].vx - 0.03;
						turtles[i].move({ turtles[i].vx, 0 });
					}
					//floor level
					else if (turtles[i].getPosition().y >= FLOOR_LEVEL - 66) {
						turtles[i].move({ turtles[i].vx, 0 });
					}
					//no collision
					else {
						turtles[i].vy = std::min(GRAVITY + turtles[i].vy, 8.0f);
						turtles[i].move({ turtles[i].vx, turtles[i].vy });
					}

					//edges
					if (turtles[i].getPosition().x >= WINDOW_WIDTH - 68) {
						turtles[i].getSprite().setTextureRect(sf::IntRect(68, 0, -68, 66));
						turtles[i].vx = -turtles[i].vx;
						if (turtles[i].getPosition().y > 650) {
							turtles[i].getSprite().setTextureRect(sf::IntRect(0, 0, 68, 66));
							turtles[i].vx = -turtles[i].vx;
							turtles[i].setPosition({ 100,50 });
						}
						
					}
					else if (turtles[i].getPosition().x <= 0) {
						turtles[i].getSprite().setTextureRect(sf::IntRect(0, 0, 68, 66));
						turtles[i].vx = -turtles[i].vx;
						if (turtles[i].getPosition().y > 650) {
							turtles[i].getSprite().setTextureRect(sf::IntRect(68, 0, -68, 66));
							turtles[i].vx = -turtles[i].vx;
							turtles[i].setPosition({ 900,50 });
						}
					}



				}
					
				//std::cout << mario.vy << std::endl;
				mario.vy = std::min(GRAVITY + mario.vy, 8.0f);

				
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
				if (mario.getPos().x >= WINDOW_WIDTH-66)
				{
					//std::cout << mario.getPos().x << std::endl;
					mario.getSprite().setPosition(WINDOW_WIDTH-66, mario.getPos().y);
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

		turtles[0].draw(window);
		turtles[1].draw(window);
		turtles[2].draw(window);
		turtles[3].draw(window);
		turtles[4].draw(window);

		//pipes
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
		

	}

	//bool onFloor(Object* obj) {
	//	if (obj->vy == 8.0) {
	//		obj->isOnFloor = 1;
	//		return 1;
	//	}
	//	else {
	//		obj->isOnFloor = 0;
	//		return 0;
	//	}
	//}

	bool checkCollusion_for_Turtle(Turtle *t, sf::Sprite brick)
	{
		if (t->getSprite().getGlobalBounds().intersects(brick.getGlobalBounds()))
		{
			return true;
		}
		return false;
	}

	bool checkCollusion(Object *o, sf::Sprite brick)
	{

		if (o->getSprite().getGlobalBounds().intersects(brick.getGlobalBounds()))
		{
			return true;
		}
		return false;
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

