#include "PhysicsEngine.h"
#include <iostream>

#define PI 3.14159

std::vector<Asteroid*> PhysicsEngine::asteroids;

void PhysicsEngine::init()
{ 
	asteroids.reserve(100);
}

void PhysicsEngine::addAsteroid(Asteroid* asteroid)
{
	asteroids.push_back(asteroid);
}

void PhysicsEngine::update()
{
	int size = asteroids.size();
	for (int i = 0; i < size; i++)
	{
		outOfBounds(asteroids[i]);  

		for (int j = i+1; j < size; j++)
		{
			checkCollision(asteroids[i], asteroids[j]);
		}
	}
}

float PhysicsEngine::dot(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

void PhysicsEngine::checkCollision(Asteroid* first, Asteroid* second)
{
	if (dist(first->getPosition(), second->getPosition()) <= first->getRadius() + second->getRadius())
	{
		sf::Vector2f aPos = first->getPosition();
		sf::Vector2f bPos = second->getPosition();
		sf::Vector2f cPos = aPos - bPos;


		float caDirection = atan(cPos.y / cPos.x);

		if (dot(cPos, sf::Vector2f(1, 0)) < 0)
			caDirection += PI;

		first->setDirection(caDirection);
		second->setDirection(caDirection + PI);
	}
}

float PhysicsEngine::dist(const sf::Vector2f& firstPos, const sf::Vector2f& secondPos)
{
	return sqrt((firstPos.x - secondPos.x) * (firstPos.x - secondPos.x) + (firstPos.y - secondPos.y) * (firstPos.y - secondPos.y));
}
void PhysicsEngine::outOfBounds(Asteroid* asteroid)
{
	sf::Vector2f pos = asteroid->getPosition();
	float r = asteroid->getRadius();

	if (pos.x > 500) pos.x -= 500;
	else if (pos.x < 0) pos.x += 500;

	if (pos.y > 500) pos.y -= 500;
	else if (pos.y < 0) pos.y += 500;

	asteroid->setPosition(pos);
}
