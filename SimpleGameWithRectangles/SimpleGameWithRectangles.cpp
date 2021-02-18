#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace sf;

double lerp(double A, double B, double t) {
    t = 3 * pow(t, 2) - 2 * pow(t, 3);
    return A * (1 - t) + B * t;
}

int main()
{
    srand(1373);

    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // create the window
    RenderWindow window(VideoMode(800, 200), "Particles", Style::Default, settings);

    // create the particle system
    VertexArray points(LinesStrip, 800);

    double A, B, t;
    double net[100];
    net[0] = 0;
    for (int i = 1; i < 100; i++)
    {
        net[i] = ((double)(rand() % 2001) - 1000) / 1000;
    }
    
    double s = 0, step = 0.1;
    int j;
    
    // run the main loop
    while (window.isOpen())
    {
        // handle events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        
        for (int i = 0; i < 800; i+=2)
        {
            j = i + s;
            A = net[j / 80] * (((double)j / 80) - j / 80);
            B = net[j / 80 + 1] * (((double)j / 80) - j / 80 - 1);
            t = ((double)(j % 80) / 80);
       
            points[i].position = Vector2f(i, 125 + 150 * lerp(A, B, t));
            points[i].color = Color(255, 255, 255, 255 * (pow((double)i / 800, 1.5)));
            points[i + 1].position = Vector2f(400, 0);
            points[i + 1].color = Color(255, 255, 255, 255 * (pow((double)i / 800, 1.5)));
        }
        s += step;
        if (s >= 7200 || s <= 0)
        {
            step *= -1;
        }

        // draw it
        window.clear();
        window.draw(points);
        window.display();
    }

    return 0;
}