#pragma once
#include <SFML/Graphics.hpp>

class FPS
{
public:
	FPS(int fps);

	float getDelta();

private:
	float dt;
	sf::Time elapsed;
	sf::Clock time;

};

