#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"
#include "Menu.h"
#include "Scoreboard.h"
#include "healthBar.h"
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
	Menu menu;
	Scoreboard scoreboard;
	HealthBar healthbar;
	int current_frame;
	sf::Texture textures[8];
	sf::Sprite sprites[8];
	std::vector<sf::Sprite> bricks;
	std::vector<Turtle> turtles;
	sf::Event event;
	sf::RenderWindow *window;
	std::chrono::steady_clock::time_point previous_time;
	
public:
	//Constructer
	Game();

	//Destructor
	~Game();

	//Draw the background including pipes, floor, bricks.
	void drawBackground();

	//Game Loop
	void run();

	//Update Mario position.
	void update();

	//clear and draw new game frame.
	void render();

	//overloading the checkCollision function for different items. Return true if there is a collision between the items.
	bool checkCollusion(Turtle* t, sf::Sprite brick);
	bool checkCollusion(Turtle* t, Mario* m);
	bool checkCollusion(Mario* m, sf::Sprite brick);
};
