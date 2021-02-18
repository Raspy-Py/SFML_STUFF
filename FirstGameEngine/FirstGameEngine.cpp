#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <cmath>

#define PI 3.14159
#define rad(x) ((x) / 180 * 3.14159)

using namespace sf;

const int RD = 2; // (Ray Density) к-ть променів на 1 градус
const int FPS = 60;
const int WOV = 100; // Максимальна довжина промення
const int FOV = 80; // Кут огляду
const int WIN_SIZE = 640; // Висота вікна
const int MAP_S = 32; // К-ть квадратиків в одному рядку\стовпцю карти
const int CELL_SIZE = WIN_SIZE / MAP_S; // Розмір одного квадратика в пікселях
const int CAMERA_SPEED = 1;
bool MAP[MAP_S][MAP_S] =
{
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};


int get_blocks_count();
VertexArray get_minimap();
void init_rays(VertexArray&, double, double);
void update_rays(VertexArray&, VertexArray&, double x, double y, double dir);
void move_camera(double& x, double& y, double dir, int);
Vector2f get_ray_end(double angle, double x0, double y0, double* hol);

int main()
{

    double cameraX = 240;
    double cameraY = 240;
    double cam_dir = 180;

    ContextSettings settings;
    settings.antialiasingLevel = 16;

    // Створюємо вікно
    RenderWindow window(VideoMode(WIN_SIZE * 2, WIN_SIZE), "RayCasting", Style::Default, settings);
    window.setFramerateLimit(FPS);

    // Мінікарта
    VertexArray blocksPoints = get_minimap();

    // Промені 
    VertexArray rays(Lines, FOV * 4);
    init_rays(rays, cameraX, cameraY);

    // Камера
    CircleShape camera(2.f);
    camera.setFillColor(Color(255, 50, 50));
    
    // Саме зображення
    VertexArray image(Quads, FOV * 8);

    // Небо
    RectangleShape sky(Vector2f(WIN_SIZE * 2, WIN_SIZE / 2));
    sky.setPosition(0, 0);
    sky.setFillColor(Color(212, 71, 44));

    // Підлога
    RectangleShape floor(Vector2f(WIN_SIZE * 2, WIN_SIZE / 2));
    floor.setPosition(0, WIN_SIZE / 2);
    floor.setFillColor(Color(149, 30, 14));

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

        // Рух

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            move_camera(cameraX, cameraY, cam_dir, 1);
        }else if(Keyboard::isKeyPressed(Keyboard::S))
        {
            move_camera(cameraX, cameraY, cam_dir, -1);
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            cam_dir -= CAMERA_SPEED * 2;
            cam_dir = cam_dir < 0 ? 356 : cam_dir;
        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
            cam_dir += CAMERA_SPEED * 2;
            cam_dir = cam_dir > 360 ? 4 : cam_dir;
        }

        camera.setPosition((cameraX - 8) / 4, (cameraY - 8) / 4);

        update_rays(rays, image, cameraX, cameraY, cam_dir);
 
        window.clear();
        window.draw(sky);
        window.draw(floor);
        window.draw(image);
        window.draw(rays);
        window.draw(blocksPoints);
        window.draw(camera);
        window.display();

    }

    return 0;
}

int get_blocks_count() {
    int activeMapBlocksCount = 0;

    for (size_t i = 0; i < MAP_S; i++)
    {
        for (size_t j = 0; j < MAP_S; j++)
        {
            if (MAP[i][j]) {
                activeMapBlocksCount++;
            }
        }
    }
    return activeMapBlocksCount;
}

VertexArray get_minimap() {
    int n = get_blocks_count() * 4;
    int curPointIndex = -1;

    VertexArray blocksPoints(Quads, n);

    for (int i = 0; i < MAP_S; i++)
    {
        for (int j = 0; j < MAP_S; j++)
        {
            if (MAP[i][j]) {
                blocksPoints[++curPointIndex].position = Vector2f(j * CELL_SIZE / 4, i * CELL_SIZE / 4);
                blocksPoints[curPointIndex].color = Color(255, 153, 0);
                blocksPoints[++curPointIndex].position = Vector2f((j + 1) * CELL_SIZE / 4, i * CELL_SIZE / 4);
                blocksPoints[curPointIndex].color = Color(255, 153, 0);
                blocksPoints[++curPointIndex].position = Vector2f((j + 1) * CELL_SIZE / 4, (i + 1) * CELL_SIZE / 4);
                blocksPoints[curPointIndex].color = Color(255, 153, 0);
                blocksPoints[++curPointIndex].position = Vector2f(j * CELL_SIZE / 4, (i + 1) * CELL_SIZE / 4);
                blocksPoints[curPointIndex].color = Color(255, 153, 0);
            }
        }
    }

    return blocksPoints;
}

void init_rays(VertexArray& rays, double y, double x) {
    for (size_t i = 0; i < FOV * 4; i++)
    {
        rays[i].color = Color(255, 255, 255);
    }
}

void update_rays(VertexArray& rays, VertexArray& image, double x, double y, double dir)
{
    double height_of_line;
    double angle;
    int color;
    int len;

    for (size_t i = 0; i < FOV * 4; i+=2)
    {
        // Обчислення променів
        rays[i].position = Vector2f(x / 4, y / 4);
        angle = dir - FOV / 2 + (float)(i / 2) / 2;
        rays[i + 1].position = get_ray_end(angle, x, y, &height_of_line);

        color = 127 * (1 - height_of_line);
        // Формування зображення
        if (height_of_line >= 0.9)
        {
            len = 0;
            color = 0;
        }
        else {
            len = WIN_SIZE / 2 * (1 - height_of_line * cos(rad(angle - dir)));
            color = 50 + 205 * (1 - height_of_line);
        }

        image[i * 2    ].position = Vector2f(i * 4,     WIN_SIZE / 2 + len);
        image[i * 2 + 1].position = Vector2f(i * 4 + 8, WIN_SIZE / 2 + len);
        image[i * 2 + 2].position = Vector2f(i * 4 + 8, WIN_SIZE / 2 - len);
        image[i * 2 + 3].position = Vector2f(i * 4,     WIN_SIZE / 2 - len);

        image[i * 2    ].color = Color(color, color, color);
        image[i * 2 + 1].color = Color(color, color, color);
        image[i * 2 + 2].color = Color(color, color, color);
        image[i * 2 + 3].color = Color(color, color, color);
    }
}

void move_camera(double& x, double& y, double dir, int forward)
{
    x += CAMERA_SPEED * cos(rad(dir)) * forward;
    y += CAMERA_SPEED * sin(rad(dir)) * forward;
    if (MAP[(int)y/CELL_SIZE][(int)x/CELL_SIZE])
    {
        x -= CAMERA_SPEED * cos(rad(dir)) * forward;
        y -= CAMERA_SPEED * sin(rad(dir)) * forward;
        /*if (cos(rad(dir)) >= sin(rad(dir)))
        {
            y -= CAMERA_SPEED * sin(rad(dir)) * forward;
        } else if (cos(rad(dir)) < sin(rad(dir)))
        {
            x -= CAMERA_SPEED * cos(rad(dir)) * forward;
        } else {
            x -= CAMERA_SPEED * cos(rad(dir)) * forward;
            y -= CAMERA_SPEED * sin(rad(dir)) * forward;
        }*/
    }
}

Vector2f get_ray_end(double angle, double x0, double y0, double* hol)
{
    double x = x0, y = y0;
    float step = 0.1;
 
    angle = rad(angle);

    for (float i = 0; i < WOV; i += step)
    {
        x += step * cos(angle);
        y += step * sin(angle);
        if (MAP[(int)y / CELL_SIZE][(int)x / CELL_SIZE]) {
            break;
        }
    }

    *hol = pow(((x - x0)* (x - x0) + (y - y0) * (y - y0)), 0.5) / WOV;

    //std::cout << "x = " << x << "\ty = " << y << "\n";
    return Vector2f(x / 4, y / 4);
}
