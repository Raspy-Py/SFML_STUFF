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
const int FOV = 60;
const int WTP = WIN_WIDTH / ( 2 * tan(FOV * PI / 360) ); // ³������ �� ������ �� ������� ������������ ����������
const double ABR = 60 / 320; // ��� �� ������� ���������

template <typename T>
void print_matrix(T** arr, int n); // ������� ��� ������������
double lerp(double A, double B, double t); // ������������ (���� ������)
void start_game(); // ������� ������� ��� 
int** load_map_plan(); // ������������ ���� � ����� � ���������� ���'���
