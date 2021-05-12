#include "func.h"

Player::Player(double x, double y, double spd) {
    cords.x = x;
    cords.y = y;
    speed = spd;
    health = 100;
}

void Player::move_player(int way) {
    // way = -1 (backward)
    // way =  1 (forward)
    cords.x += speed * way * cos(dir);
    cords.y += speed * way * sin(dir);
}

void Player::rotate_player(int side)
{
    // side = -1 (turn left)
    // side =  1 (turn right)
    dir += side * rotationSpeed;
    if (dir > PI * 2)
    {
        dir -= 2 * PI;
    }
    else if (dir < 0)
    {
        dir += 2 * PI;
    }
}

void Player::get_info()
{
    cout << "X:\t" << cords.x << endl;
    cout << "Y:\t" << cords.y << endl;
    cout << "Dir\t" << dir << endl;
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}


// ����� ������� 

void start_game() {
 
    
    // ����������� ����� ����
    int** level = load_map_plan();

    print_matrix(level, 16);
    // ��������� ������
    Player player(500.0, 500.0, 0.1);

    // ����� ������ �������
    int* rays = new int[WIN_WIDTH];

    // test
    VertexArray line(Lines, 2);
    line[0].color = Color(255,0,0);
    line[1].color = Color(255, 0, 0);
    line[0].position = Vector2f(0,0);
    line[1].position = Vector2f(0, 200);


    // ����� ������ ����������
    VertexArray projection(Lines, WIN_WIDTH * 2);

    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // ��������� ����
    RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "RayCastingGameEngine", Style::Default, settings);
    window.setFramerateLimit(60);

    // �������� ���� ��������
    while (window.isOpen())
    {
        // ������� ����
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if      (Keyboard::isKeyPressed(Keyboard::W)) player.move_player(1);        
        else if (Keyboard::isKeyPressed(Keyboard::S)) player.move_player(-1);
        
        if      (Keyboard::isKeyPressed(Keyboard::A)) player.rotate_player(-1);       
        else if (Keyboard::isKeyPressed(Keyboard::D)) player.rotate_player(1);      

        if (Keyboard::isKeyPressed(Keyboard::P)) player.get_info();

        // ��������� ����������
        window.clear();
        window.draw(projection);
        window.draw(line);
        window.display();
    }
}

int** load_map_plan()
{
    ifstream file;
    string n_str; // ����� ���� ������
    string cell_str;
    int cell;
    int level_size; // ����� ���� 
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


void  horizontal_intersections(Player p, int** map, int* hor_width)
{
    double a = p.dir - FOV / 2;

    for (int i = 0; i < WIN_WIDTH; i++)
    {
        if (a <= PI)
        {

        }
    }
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

template<typename T>
void print_vector(T* vct, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << vct[i] << "\t";
    }
    cout << endl;
}
