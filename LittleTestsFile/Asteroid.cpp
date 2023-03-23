#include "Asteroid.h"
#include <iostream>

Asteroid::Asteroid(const sf::Vector2f& position, float speed, bool isBig)
{
	this->setPosition(position);
	this->setFillColor(isBig ? BIG_ASTR_COLOR : LITTLE_ASTR_COLOR);
	this->setRadius(isBig ? BIG_ASTR_RADIUS : LITTLE_ASTR_RADIUS);
	this->setOrigin(this->getRadius(), this->getRadius());
	 
	this->isBig = isBig;
	this->direction = float(rand() % 31416) / 5000.0;
	this->speed = speed;
}

void Asteroid::update()
{
}

void Asteroid::move(float dt)
{
	sf::Vector2f position = this->getPosition();

	position.x += speed * cos(direction) * dt;
	position.y += speed * sin(direction) * dt;

	this->setPosition(position);
}

void Asteroid::draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

void Asteroid::bounce(bool isVertical)
{
	if (isVertical)
		direction = 3.14159 - direction;
	else
		direction = 3.14159 * 2 - direction;
}

void Asteroid::setDirection(float direction)
{
	this->direction = direction;
}
