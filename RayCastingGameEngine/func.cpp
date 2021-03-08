#include "func.h"

class Player {

public:
    Player(double, double, double);
    void move_player(int);
    void rotate_player(int);
    void get_info();

private:
    vector<double> cords;
    double speed;
    double dir = 0;
    double rot_speed = 1 * PI / 180;
};

Player::Player(double x, double y, double spd) {
    cords.push_back(x);
    cords.push_back(y);
    speed = spd;
}

void Player::move_player(int way) {
    // way = -1 (backward)
    // way =  1 (forward)
    cords[0] += speed * way * cos(dir);
    cords[1] += speed * way * sin(dir);

    get_info();
}

void Player::rotate_player(int side)
{
    // side = -1 (turn left)
    // side =  1 (turn right)
    dir += side * rot_speed;
    if (dir > PI * 2)
    {
        dir = 0.001;
    }
    else if (dir < 0)
    {
        dir = 2 * PI - 0.001;
    }

    get_info();
}

void Player::get_info()
{
    cout << "X:\t" << cords[0] << endl;
    cout << "Y:\t" << cords[1] << endl;
    cout << "Dir\t" << dir << endl;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void start_game() {
 
    // Завантажуємо схему рівня
    int** level = load_map_plan();
    Player player(50.0, 50.0, 0.1);

    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Створюємо вікно
    RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "RayCastingGameEngine", Style::Default, settings);

    // Головний цикл програми
    while (window.isOpen())
    {
        // Обробка подій
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            player.move_player(1);
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
            player.move_player(-1);
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            player.rotate_player(-1);
        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
            player.rotate_player(1);
        }

        // Оновлюємо зображення
        window.clear();
        window.display();
    }

}

int** load_map_plan()
{
    ifstream file;
    string n_str; // Розмір рівня рядком
    string cell_str;
    int cell;
    int level_size; // Розмір рівня 
    int** level;
    

    file.open("../data/map.csv");

    if (!file.is_open()) {
        cout << "Failed to load game map! File opening error.\n";
        return nullptr;
    }

    getline(file, n_str,'\n');
    level_size = stoi(n_str);

    level = new int* [level_size];

    for (int i = 0; i < level_size; i++)
    {
        level[i] = new int[level_size];

        for (int j = 0; j < level_size - 1; j++)
        {
            getline(file, cell_str, ',');
            cell = stoi(cell_str);
            level[i][j] = cell;
        }
        getline(file, cell_str, '\n');
        cell = stoi(cell_str);
        level[i][level_size - 1] = cell;
    }
    file.close();

    return level;
}

template <typename T>
void print_matrix(T** arr, int n) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

