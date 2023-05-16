#include "Game.h"

//Constructer
Game::Game() {
	//set brick count
	this->bricks.resize(BRICK_SIZE3);
	//set turtle count
	this->turtles.resize(TOTAL_CHAR);

	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario Game");

	//Initialize turtles and set positions. 3 of them starts from left. 2 of them from right.
	turtles[0] = turtle1;
	turtles[0].setPosition({ 100, 50 });

	turtles[1] = turtle2;
	turtles[1].setPosition({ 900, 50 });

	turtles[2] = turtle3;
	turtles[2].setPosition({ 100, 50 });

	turtles[3] = turtle4;
	turtles[3].setPosition({ 900, 50 });

	turtles[4] = turtle5;
	turtles[4].setPosition({ 100, 50 });
}

//Destructor
Game::~Game() {
	delete this->window;
}

//Draw the background including pipes, floor, bricks.
void Game::drawBackground()
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

	for (int i(0); i < 14; i++)
	{
		bricks.at(i).setTexture(textures[1]);
		bricks.at(i).setPosition(BRICK_WIDTH * (i), 200);
	}

	for (int i(14); i < 28; i++)
	{
		bricks.at(i).setTexture(textures[1]);
		bricks.at(i).setPosition(BRICK_WIDTH * (i + 6), 200);
	}

	for (int i(28); i < 32; i++)
	{
		bricks.at(i).setTexture(textures[1]);
		bricks.at(i).setPosition(BRICK_WIDTH * (i - 28), 400);
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

//Game Loop
void Game::run() {

	std::chrono::microseconds lag(0);
	previous_time = std::chrono::steady_clock::now();

	this->drawBackground();
	int z = 0;
	int from_bottom = 0;


	while (window->isOpen())
	{
		//time to set frame rate.
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);
		lag += delta_time;
		previous_time += delta_time;

		//Fix the frame duration. So that the game is not faster in better CPU's. Game speed is set to internal clock.
		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			//get a number in range of 0-4 to animate between mario images based on frame count. 
			if (z++ % 4 == 0) {
				current_frame = (current_frame + 1) % 4;
			}

			//end game
			if (scoreboard.getScore() == 500 || mario.getLife() == 0)
			{
				menu.getState() = GameState::GameOver;
				menu.render(*window, scoreboard , mario);
			}

			this->update();

			if (!(menu.getState() == GameState::Playing))
			{
				break;
			}

			this->render();

			//parameter to prevent mario to jump more than one time.
			mario.isOnFloor = 0;

			for (int k(0); k < bricks.size(); k++)
			{
				if (checkCollusion(&mario, bricks.at(k)))
				{

					mario.isOnFloor = 1;

					sf::FloatRect marioBounds = mario.getSprite().getGlobalBounds();
					sf::FloatRect brickBounds = bricks.at(k).getGlobalBounds();

					float overlapLeft = marioBounds.left + marioBounds.width - brickBounds.left;
					float overlapRight = brickBounds.left + brickBounds.width - marioBounds.left;
					float overlapTop = marioBounds.top + marioBounds.height - brickBounds.top;
					float overlapBottom = brickBounds.top + brickBounds.height - marioBounds.top;

					// Determine which side of the brick Mario is colliding with.
					// Give negative of keyboard input to make mario collide the brick.

					// Mario is colliding with the left of the brick
					if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom)
					{
						mario.move({ -abs(mario.vx), 0 });
					}
					// Mario is colliding with the right of the brick
					else if (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom)
					{
						mario.move({ abs(mario.vx) ,0 });
					}
					// Mario is colliding with the top of the brick
					else if (overlapTop < overlapLeft && overlapTop < overlapRight && overlapTop < overlapBottom)
					{
						mario.move({ 0, -mario.vy });
					}
					// Mario is colliding with the bottom of the brick
					else if (overlapBottom < overlapLeft && overlapBottom < overlapRight && overlapBottom < overlapTop)
					{
						//hit the brick start falling.
						mario.vy = 0.0f;
						mario.move({ 0, GRAVITY + 10 });

						//hitting the turtle from down the brick.
						for (int t(0); t < 5; t++)
						{
							if (checkCollusion(&turtles[t], bricks.at(k)))
							{
								turtles[t].isDead = 1;
								turtles[t].setAnimation(current_frame);
								scoreboard.updateScore(100);
							}
						}

					}
				}

			}


			for (int i = 0; i < 5; i++)
			{
				sf::Vector2f turtle_pos = turtles[i].getPosition();

				turtles[i].setAnimation(current_frame);

				turtles[i].isOnFloor = 0;


				//if mario hits one of the 5 turtles.
				if (checkCollusion(&turtles[i], &mario) && !mario.isDead && !turtles[i].isDead) {

					sf::FloatRect marioBounds = mario.getSprite().getGlobalBounds();
					sf::FloatRect turtleBounds = turtles[i].getSprite().getGlobalBounds();

					float overlapLeft = marioBounds.left + marioBounds.width - turtleBounds.left;
					float overlapRight = turtleBounds.left + turtleBounds.width - marioBounds.left;
					float overlapTop = marioBounds.top + marioBounds.height - turtleBounds.top;
					float overlapBottom = turtleBounds.top + turtleBounds.height - marioBounds.top;

					// killing the turtle if mario is moving down on top of the turtle
					if (overlapTop <= 10 && mario.vy > 0 && !mario.isDead)
					{
						// Mario is colliding with the top of the turtle
						scoreboard.updateScore(100);
						turtles[i].isDead = 1;
						turtles[i].setAnimation(current_frame);
					}
					//otherwise kill mario.
					else
					{
						healthbar.decreaseHealth();
						mario.isDead = 1;
						mario.setAnimation(current_frame, -1);
						mario.killMario();

					}

				}

				// rebirth of mario. Mario falls down the window when dead. 
				//If it still has lives remaining set default posiiton for new try. 
				if (mario.isDead && mario.getSprite().getPosition().y > WINDOW_HEIGHT - 50 && mario.getLife() != 0)
				{
					mario.getSprite().setPosition(400, 550);
					mario.vx = 0;
					mario.isDead = 0;
					mario.setAnimation(current_frame, 0);
				}
				//If turtles die make them fall down the window.
				if (turtles[i].isDead == 1)
				{
					turtles[i].vy = turtles[i].vy + 0.05;
					turtles[i].getSprite().move({ 0, turtles[i].vy });
				}
				//control of turtles.
				else
				{
					for (int j(0); j < bricks.size(); j++) {
						if (checkCollusion(&turtles[i], bricks.at(j))) {

							sf::FloatRect turtleBounds = turtles[i].getSprite().getGlobalBounds();
							sf::FloatRect brickBounds = bricks.at(j).getGlobalBounds();

							float overlapTop = turtleBounds.top + turtleBounds.height - brickBounds.top;

							if (overlapTop <= 10)
							{
								// Turtle is colliding with the top of the brick
								turtles[i].isOnFloor = 1;
							}
						}
					}

					//continue
					if (turtles[i].isOnFloor) {
						turtles[i].move({ turtles[i].vx, 0 });
					}
					//if turtle is in the left top pipe zone, make it speed up.
					else if (turtle_pos.x < 200 && turtle_pos.y < 200) {
						turtles[i].vx = turtles[i].vx + (i + 1) * 0.01;
						turtles[i].move({ turtles[i].vx, 0 });
					}
					//if turtle is in the right top pipe zone, reverse its textureand make it speed up.
					else if (turtle_pos.x >= 800 && turtle_pos.y < 200) {
						turtles[i].getSprite().setTextureRect(sf::IntRect(68, 0, -68, 66));
						turtles[i].vx = turtles[i].vx - (i + 1) * 0.01;
						turtles[i].move({ turtles[i].vx, 0 });
					}
					//if turtle falls to ground. move forward on ground.
					else if (turtles[i].getPosition().y >= FLOOR_LEVEL - 66) {
						turtles[i].move({ turtles[i].vx, 0 });
					}
					//give gravity to make turtles fall in mid-air.
					else {
						turtles[i].vy = std::min(GRAVITY + turtles[i].vy, 8.0f);
						turtles[i].move({ turtles[i].vx, turtles[i].vy });
					}

					//reverse direction of turtle if hits the window right edge
					if (turtles[i].getPosition().x >= WINDOW_WIDTH - 68) {
						turtles[i].getSprite().setTextureRect(sf::IntRect(68, 0, -68, 66));
						turtles[i].vx = -turtles[i].vx;
						if (turtles[i].getPosition().y > 650) {
							turtles[i].getSprite().setTextureRect(sf::IntRect(0, 0, 68, 66));
							turtles[i].vx = -turtles[i].vx;
							turtles[i].setPosition({ 100,50 });
						}

					}
					//reverse direction of turtle if hits the window left edge
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
			}

			//Mario always has gravity. If it collides with bricks they give upward velocity. So, mario can stand on bricks.
			mario.vy = std::min(GRAVITY + mario.vy, 8.0f);

			//Set the vx, vy vectors to Mario.
			mario.getSprite().move(mario.vx, mario.vy);


			//Keep mario in window regions.
			if (mario.getPosition().y >= FLOOR_LEVEL - 80 && mario.isDead == 0)
			{
				mario.getSprite().setPosition(mario.getPosition().x, FLOOR_LEVEL - 80);
				mario.isOnFloor = 1;
			}
			if (mario.getPosition().y <= 0)
			{
				mario.vy = 0;
				mario.getSprite().setPosition(mario.getPosition().x, 0);
			}
			if (mario.getPosition().x <= 0)
			{
				mario.getSprite().setPosition(0, mario.getPosition().y);
			}
			if (mario.getPosition().x >= WINDOW_WIDTH - 66)
			{
				mario.getSprite().setPosition(WINDOW_WIDTH - 66, mario.getPosition().y);
			}

			window->display();
		}


	}
}

//Update Mario position.
void Game::update()
{
	while (window->pollEvent(this->event))
	{
		menu.handleInput(event);

		if (!(menu.getState() == GameState::Playing))
		{
			menu.render(*window, scoreboard, mario);
			break;
		}

		if ((menu.getState() == GameState::Menu))
		{
			menu.render(*window, scoreboard, mario);
			break;
		}

		if (mario.isDead == 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == 0) {
				mario.setAnimation(current_frame, 0);
				mario.vx = 0;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == 0)
			{
				//std::cout << mario.vx << std::endl;
				if (mario.vx < 0)
				{
					mario.setAnimation(current_frame, 2);
				}
				else
				{
					mario.setAnimation(current_frame, 1);
				}
				mario.getSprite().setTextureRect(sf::IntRect(66, 0, -66, 88));

				mario.vx = std::min(mario.vx + MARIO_ACCELERATION, MARIO_WALK_SPEED);

				mario.move({ mario.vx, 0 });
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) == 0)
			{
				if (mario.vx > 0)
				{
					mario.setAnimation(current_frame, 2);
				}
				else
				{
					mario.setAnimation(current_frame, 1);
				}
				//std::cout << mario.vx << std::endl;

				mario.getSprite().setTextureRect(sf::IntRect(0, 0, 66, 88));
				mario.vx = std::max(mario.vx - MARIO_ACCELERATION, -MARIO_WALK_SPEED);

				mario.move({ mario.vx, 0 });
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && mario.isOnFloor)
			{
				mario.move({ 0, -10 + VELOCITY * 0.4 });
				mario.vy = -10;
				//std::cout << mario.vx << std::endl;
			}
		}
	}
}

//clear and draw new game frame.
void Game::render()
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

	healthbar.draw(window);



	for (int i(0); i < bricks.size(); i++)
	{
		window->draw(bricks.at(i));
	}

	mario.draw(window);
	scoreboard.draw(window);

}

//overloading the checkCollision function for different items. Return true if there is a collision between the items.
bool Game::checkCollusion(Turtle* t, sf::Sprite brick)
{
	if (t->getSprite().getGlobalBounds().intersects(brick.getGlobalBounds()))
	{
		return true;
	}
	return false;
}
bool Game::checkCollusion(Turtle* t, Mario* m)
{
	if (t->getSprite().getGlobalBounds().intersects(m->getSprite().getGlobalBounds()))
	{
		return true;
	}

	return false;
}
bool Game::checkCollusion(Mario* m, sf::Sprite brick)
{

	if (m->getSprite().getGlobalBounds().intersects(brick.getGlobalBounds()) && m->isDead == 0)
	{
		return true;
	}


	return false;

}

