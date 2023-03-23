#include "FPS.h"

FPS::FPS(int fps)
{
    time.restart();

    this->dt = 1000000.0f / fps;
}
#include<iostream>
float FPS::getDelta()
{
    sf::Time currentTime = time.getElapsedTime();
    float passed = currentTime.asMicroseconds();
    //std::cout << passed / dt << std::endl;
    time.restart();

    return passed / dt;
}
