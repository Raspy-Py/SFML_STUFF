#define PI 3.14159
#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;

const int WIN_WIDTH = 320;
const int WIN_HEIGHT = 200;
const int CELL_SIZE = 64; // ����� ������ ����� �� ��� (���������� 64) 
const double FOV = 60 * PI / 180;
const double WTP = WIN_WIDTH / ( 2 * tan(FOV * PI / 360) ); // ³������ �� ������ �� ������� ������������ ����������
const double ABR = 60.0 / 320 * PI / 180; // ��� �� ������� ���������

template <typename T>
void print_matrix(T** arr, int n); // ������� ��� ������������
template <typename T>
void print_vector(T*, int);

double lerp(double A, double B, double t); // ������������ (���� ������)
void start_game(); // ������� ������� ��� 
int** load_map_plan(); // ������������ ���� � ����� � ���������� ���'���

class Player {

public:
    float health;
    double dir = 0;
    Vector2f cords;
    Player(double, double, double);
    void move_player(int);
    void rotate_player(int);
    void get_info();

private:
    double speed;
    double rotationSpeed = 1 * PI / 180;
};

//class Map
//{
//public:
//    int**
//	Map();
//	~Map();
//
//private:
//
//};
//
//Map::Map()
//{
//}
//
//Map::~Map()
//{
//}