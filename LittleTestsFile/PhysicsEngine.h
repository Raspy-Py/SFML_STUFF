#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Asteroid.h"

class PhysicsEngine
{
public:
	static void init();
	static void addAsteroid(Asteroid* asteroid);
	static void update();
private:
	static float dot(sf::Vector2f a, sf::Vector2f b);
	static std::vector<Asteroid*> asteroids;
	static void checkCollision(Asteroid* first, Asteroid* second);
	static float dist(const sf::Vector2f& firstPos, const sf::Vector2f& secondPos);
	static void outOfBounds(Asteroid* asteroid);
};

