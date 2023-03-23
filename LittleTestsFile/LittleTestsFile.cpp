#include <iostream>
#include <cstring>
#include <vector>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Asteroid.h"
#include "FPS.h"
#include "PhysicsEngine.h"

using namespace std;


void main()
{
	srand(130);
	sf::RenderWindow window(sf::VideoMode(500, 500), "Space simulation");
 
	sf::Event event;

	std::vector<Asteroid> asteroids;
	asteroids.reserve(100);

	PhysicsEngine::init();

	FPS fps(60);

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && asteroids.size() < 100)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
				{
					asteroids.emplace_back(
						sf::Vector2f(
							(rand() % 450) + 25,
							(rand() % 450) + 25
						), 1, 1);

						PhysicsEngine::addAsteroid(&asteroids.back());
				}
				else
				{
					asteroids.emplace_back(
						sf::Vector2f(
							(rand() % 480) + 10,
							(rand() % 480) + 10
						), 5, 0);

					PhysicsEngine::addAsteroid(&asteroids.back());
				}
			}
		}

		
		PhysicsEngine::update();

		float dt = fps.getDelta();

		for (auto& ast : asteroids)
		{
			ast.update();
			ast.move(dt);
		}

		window.clear();
		for (auto& ast : asteroids)
			ast.draw(window);
		window.display();
	}
}