#include <SFML/Graphics.hpp>
#define NOMINMAX
#include <Windows.h>
#include <random>
#include <math.h>


const float PARTICLE_MASS = 300000000;
const float PMS = PARTICLE_MASS * PARTICLE_MASS;
const float G = 6.67384e-11;
const int WIN_SIZE = 800;

const int POINTS_NUMBER = 2000;

// create the particle system
sf::VertexArray points(sf::Points, POINTS_NUMBER);
std::vector<sf::Vector2f> vel(POINTS_NUMBER);

inline float lenth(const sf::Vector2f& v1)
{
    return sqrt( (v1.x* v1.x) + (v1.y * v1.y) );
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WIN_SIZE, WIN_SIZE), "Particles", sf::Style::Close, settings);

    std::normal_distribution<> ndstr((float)WIN_SIZE/2.0, 50.0);
    std::uniform_real_distribution<> dstr(0.0, (float)WIN_SIZE);
    std::default_random_engine eng(time(NULL));

    for (size_t i = 0; i < points.getVertexCount(); ++i)
    {
        auto& point = points[i];

        point.position = { (float)ndstr(eng), (float)ndstr(eng) };
        vel[i] = { 0.0, 0.0 };
    }

    sf::Clock time;

    while (window.isOpen())
    {

        float dt = time.getElapsedTime().asSeconds() * 10;
        time.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }       

        for (int i = 0; i < vel.size(); i++)
        {
            sf::Vector2f f{};
            for (int j = 0; j < vel.size(); j++)
            {
                if (i == j) continue;

                sf::Vector2f pathVec = points[j].position - points[i].position;

                float dist = lenth(points[j].position - points[i].position) + 1;
                float dist_c = dist * dist * dist;

                //if (dist < 1.5) continue;

                pathVec.x /= dist_c;
                pathVec.y /= dist_c;

                f += pathVec;
            }

            f.x *= G * PARTICLE_MASS;
            f.y *= G * PARTICLE_MASS;
            
            vel[i] += f;

            points[i].position += {vel[i].x * dt, vel[i].y * dt};
        }

        window.clear(sf::Color(0, 0, 30, 255));
        window.draw(points);
        window.display();
    }

    return 0;
}