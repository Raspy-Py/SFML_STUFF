#pragma once
#include <SFML/Graphics.hpp>
#include "configs.h"

class Asteroid : public sf::CircleShape
{
public:
	Asteroid(const sf::Vector2f& position, float speed, bool isBig);
	void update();
	void move(float dt = 1);
	void draw(sf::RenderWindow& window);
	void bounce(bool isVertical);

	void setDirection(float direction);

private:
	bool isBig;
	float direction;
	float speed;
};

