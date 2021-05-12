#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace sf;
using namespace std;

bool imp_alg = 0;
const double VERTEX_SIZE = 15; // Радіус вершини в пікселях
Font font;
Text info;
vector<vector<int>> incidenceMatrix; // матриця інцидентності, необхідна для валідного відображення результату
vector<vector<int>> adjancencyMatrix; // матриця суміжності графа
vector<vector<int>> edges_list;

void draw_verts(vector<CircleShape>, RenderWindow&);
void show_path(vector<int>&, VertexArray&, vector<CircleShape>&);
void hide_path(vector<int>&, VertexArray&, vector<CircleShape>&);
void add_vert();
void add_edge_to_matrix(vector<vector<int>>&);
int find_path(int, int, vector<int>&);
void add_element(RenderWindow&, vector<CircleShape>&, VertexArray&, VertexArray&, bool&, int*);
bool define_path(int*, vector<CircleShape>&, RenderWindow& );
void reset_path_markers(vector<CircleShape>&, int*);
void mark_path(vector<CircleShape>&, int*, Vector2i, int);
void print_stack(vector<int>);
void cut_stack(vector<int>&);
void generate_graph_randomly(vector<CircleShape>&, VertexArray &);
bool is_mouse_on_vert(vector<CircleShape>, Vector2i, int mult = 2);
Vector2f get_vert_position(Vector2i, vector<CircleShape>, int & );
void print_matrix(vector<vector<int>>);



int main()
{
    
    int newEdge[2] = { 0,0 };
    int st_fn[] = {-1, -1};
    bool creatingEdge = false;

    vector<int> stack; // стек, що зберігає маршрут

    vector<CircleShape> verts; // вершини графа

    VertexArray edges(Lines, 0); // ребра графа
    VertexArray activeEdge(Lines, 2);
    activeEdge[0].color = Color(255,255,255);
    activeEdge[1].color = Color(255, 255, 255);

    // задній фон
    RectangleShape backGround(Vector2f(600.f,600.f));
    RectangleShape infoBlock(Vector2f(400, 600));
    infoBlock.setPosition(Vector2f(600, 0));
    backGround.setPosition(Vector2f(0,0));
    infoBlock.setFillColor(Color(211, 211, 211));
    backGround.setFillColor(Color(192, 192, 192));

    // необхідний для затримки часу при створені вершин
    Clock time;
    Time elapsed;
    time.restart();

    // завантажуємо шрифт
    if (!font.loadFromFile("../fonts/font1.otf"))
    {
        cout << "Failed to load font!" << endl;
    }  


    // блок тексту з інструкцією
    info.setFont(font);
    info.setString("R     - generate graph\nI     - use improved algorithm\nLMB   - create vertex/edge \nRMB   - define path \nTAB   - clear everything \nENTER - find path");
    info.setCharacterSize(20);
    info.setFillColor(Color(128, 128, 128));
    info.setPosition(Vector2f(610, 10));

    // анізотропна фільтрація
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    // створюємо вікно
    RenderWindow window(VideoMode(1000, 600), "Graph", Style::Default, settings);
    window.setFramerateLimit(30);

    // головний цикл програми
    while (window.isOpen())
    {
        // опрацювання подій
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // видалення графа
        if (Keyboard::isKeyPressed(Keyboard::Tab)) {
            elapsed = time.getElapsedTime();
            if (elapsed.asMilliseconds() > 200)
            {       
                if (verts.size() > 0);
                reset_path_markers(verts, st_fn);
                creatingEdge = false;
                activeEdge[0].position = Vector2f(-1, -1);
                verts.clear();
                edges.clear();
                edges_list.clear();
                adjancencyMatrix.clear();
                stack.clear();
                time.restart();
            }
        }

        // переключитись на покращений алгоритм
        if (Keyboard::isKeyPressed(Keyboard::I)) {
            elapsed = time.getElapsedTime();
            if (elapsed.asMilliseconds() > 200)
            {
                if (imp_alg)
                {
                    imp_alg = 0;
                }
                else {
                    imp_alg = 1;
                }               
                time.restart();
            }
        }

        // згенерувати випадковий граф
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            elapsed = time.getElapsedTime();
            if (elapsed.asMilliseconds() > 200)
            {
                if (verts.size() > 0);
                reset_path_markers(verts, st_fn);
                creatingEdge = false;
                activeEdge[0].position = Vector2f(-1, -1);
                verts.clear();
                edges.clear();
                edges_list.clear();
                adjancencyMatrix.clear();
                stack.clear();
                generate_graph_randomly(verts, edges);
                time.restart();
            }
        }

        // пошук маршруту
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            elapsed = time.getElapsedTime();
            if (elapsed.asMilliseconds() > 200)
            {
                if (stack.size())
                {
                    stack.clear();
                }
                if (st_fn[0] != -1 && st_fn[1] != -1)
                {
                    if (!find_path(st_fn[0], st_fn[1], stack)) {
                        show_path(stack, edges, verts);
                    }
                }
                time.restart();
            }
        }

        // створення нової вершини / нового ребра
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            elapsed = time.getElapsedTime();
            if (elapsed.asMilliseconds() > 200)
            {
                add_element(window,verts,edges,activeEdge,creatingEdge,newEdge);
                time.restart();
            }
        }

        // визначення початку та кінця маршруту
        if (Mouse::isButtonPressed(Mouse::Right))
        {
            elapsed = time.getElapsedTime();
            if (elapsed.asMilliseconds() > 200)
            {
                if (define_path(st_fn, verts, window) && stack.size() != 0)
                {
                    hide_path(stack, edges, verts);
                    stack.clear();
                }
                time.restart();
            }
        }

        // слідування лінії за курсором при створені нового ребра
        if (creatingEdge)
        {
            Vector2i mp = Mouse::getPosition(window);
            activeEdge[1].position = Vector2f(mp.x, mp.y);
        }else{
            activeEdge[0].position = Vector2f(-1, -1);
            activeEdge[1].position = Vector2f(-1, -1);
        }

        // відображення всіх елементів
        window.clear();
        window.draw(backGround);
        window.draw(infoBlock);
        window.draw(info);
        window.draw(edges);
        window.draw(activeEdge);
        draw_verts(verts, window);
        window.display();
    }
    
    /*print_matrix(adjancencyMatrix);
    cout << "==========\n";
    print_matrix(incidenceMatrix);
    cout << "==========\n";
    print_matrix(edges_list);*/


    return 0;
}



void draw_verts(vector<CircleShape> verts, RenderWindow& window) {
    Text text;
    text.setCharacterSize(VERTEX_SIZE * 1.5);
    text.setFont(font);
    text.setFillColor(Color(255,255,255));
    int count = 0;

    for (auto i = verts.begin(); i != verts.end(); ++i)
    {
        text.setPosition(Vector2f((*i).getPosition().x + VERTEX_SIZE / 10, (*i).getPosition().y));
        text.setString((count < 10 ? "0" : "") + to_string(count));
        window.draw(*i);
        window.draw(text);
        count++;
    }
}

bool is_mouse_on_vert(vector<CircleShape> verts, Vector2i m_pos, int mult)
{
    int dx, dy;
    double dist; // відстань від курсора до найближчої вершини

    for (auto i = verts.begin(); i != verts.end(); ++i)
    {
        dx = (*i).getPosition().x - m_pos.x + VERTEX_SIZE;  
        dy = (*i).getPosition().y - m_pos.y + VERTEX_SIZE;
        dist = pow(dx*dx + dy*dy, 0.5);
        if (dist <= VERTEX_SIZE * mult + 2)
        {
            return true;
        }       
    }
    return false;
}

Vector2f get_vert_position(Vector2i m_pos, vector<CircleShape> verts, int & newEdge) {
    int dx, dy;
    int vert_index = 0;
    double dist; // відстань від курсора до найближчої вершини

    for (auto i = verts.begin(); i != verts.end(); ++i)
    {
        dx = (*i).getPosition().x - m_pos.x + VERTEX_SIZE;
        dy = (*i).getPosition().y - m_pos.y + VERTEX_SIZE;
        dist = pow(dx * dx + dy * dy, 0.5);

        if (dist <= VERTEX_SIZE+ 2)
        {
            newEdge = vert_index;
            return (*i).getPosition();
        }

        vert_index++;
    }
}

bool define_path(int* st_fn, vector<CircleShape> &verts, RenderWindow& window)
{
    Vector2i mouse_pos = Mouse::getPosition(window);
    if (mouse_pos.x >= VERTEX_SIZE && mouse_pos.x < 600 - VERTEX_SIZE && mouse_pos.y >= VERTEX_SIZE && mouse_pos.y < 600 - VERTEX_SIZE)
    {
        if (is_mouse_on_vert(verts, mouse_pos, 1))
        {
            if (st_fn[0] == -1)
            {
                // створити початок  маршруту                                               
                mark_path(verts, st_fn, mouse_pos, 0);
            }
            else if (st_fn[1] == -1) {
                // створити кінець маршруту
                mark_path(verts, st_fn, mouse_pos, 1);
            }
        }
        else {
            reset_path_markers(verts, st_fn);
            return 1;
        }
    }
    return 0;
}

void reset_path_markers(vector<CircleShape> &verts, int* st_fn)
{
    if (st_fn[0] != -1) {
        verts[st_fn[0]].setFillColor(Color(255, 153, 0));
    }

    if (st_fn[1] != -1) {
        verts[st_fn[1]].setFillColor(Color(255, 153, 0));
    }

    st_fn[0] = -1;
    st_fn[1] = -1;
}

void mark_path(vector<CircleShape> & verts, int* st_fn, Vector2i m_pos, int v_index)
{
    int dx, dy;
    int count = 0;
    double dist; // відстань від курсора до найближчої вершини

    for (auto i = verts.begin(); i != verts.end(); ++i, count++)
    {
        dx = (*i).getPosition().x - m_pos.x + VERTEX_SIZE;
        dy = (*i).getPosition().y - m_pos.y + VERTEX_SIZE;
        dist = pow(dx * dx + dy * dy, 0.5);

        if (dist <= VERTEX_SIZE + 2)
        {
            st_fn[v_index] = count;
            (*i).setFillColor(v_index ? Color(255, 102, 153) : Color(102, 255, 51));
        }
    }
}

int find_path(int start, int finish, vector<int> & stack)
{
    int n = adjancencyMatrix.size();
    int col, row;

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = adjancencyMatrix[i][j];
        }
    }

    //cout << "  N  | [row][col] | stack\t\t \n";

    int num = 0;
    row = start;
    col = 0;
    while (row!=finish)
    {/*
        cout << " " << setw(3) << num << " | ";
        cout << '[' << setw(3) << row << "][" << setw(3) << col << "] | ";*/

        if (matrix[row][col])
        {
            matrix[row][col] = 0;
            matrix[col][row] = 0;
            stack.push_back(row);
            row = col;
            col = 0;
        }
        else if (col == n-1)
        {
            if (!stack.size())
            {
                cout << "\a Failed to find path!";
                return 1;
            }
            row = stack[stack.size() - 1];
            col = 0;
            stack.pop_back();
        }
        else {
            col++;
        }
        //print_stack(stack);
        //cout << "\n";
        num++;
    }

    stack.push_back(finish);    
    
    cout << endl;
    cout << "full path: ";
    print_stack(stack);
    cout << endl;


    if (imp_alg)
    {
        cut_stack(stack);
        cout << "Shortcut: ";
        print_stack(stack);
        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
         delete[] matrix[i];      
    }
    delete[] matrix;
    
    return 0;
}

void add_element(RenderWindow& window, vector<CircleShape> &verts, VertexArray &edges, VertexArray &activeEdge, bool &creatingEdge, int* newEdge) {

    Vector2i mouse_pos = Mouse::getPosition(window);

    // перевіряємо чи знаходиться курсор на робочому полі
    if (mouse_pos.x >= VERTEX_SIZE && mouse_pos.x < 600 - VERTEX_SIZE && mouse_pos.y >= VERTEX_SIZE && mouse_pos.y < 600 - VERTEX_SIZE) 
    {
        // перевіряємо чи можна розмістити вершину на цих координатах
        // якщо не можна, спробуємо створити початок/кінець ребра
        if (is_mouse_on_vert(verts, mouse_pos))
        {
            if (!creatingEdge && is_mouse_on_vert(verts, mouse_pos, 1))
            {
                // створити початок ребра                                               
                Vector2f start = get_vert_position(mouse_pos, verts, newEdge[0]);
                activeEdge[0].position = Vector2f(start.x + VERTEX_SIZE, start.y + VERTEX_SIZE);
                Vertex dot;
                edges.append(dot);
                edges[edges.getVertexCount() - 1].position = Vector2f(start.x + VERTEX_SIZE, start.y + VERTEX_SIZE);
                creatingEdge = true;
            }
            else if (is_mouse_on_vert(verts, mouse_pos, 1)) {
                // створити кінець ребра
                Vector2f start = get_vert_position(mouse_pos, verts, newEdge[1]);
                Vertex dot;

                if (!(Vector2f(start.x + VERTEX_SIZE, start.y + VERTEX_SIZE) == edges[edges.getVertexCount() - 1].position))
                {
                    edges.append(dot);
                    edges[edges.getVertexCount() - 1].position = Vector2f(start.x + VERTEX_SIZE, start.y + VERTEX_SIZE);
                    creatingEdge = false;
                }
                adjancencyMatrix[newEdge[0]][newEdge[1]] = 1;
                adjancencyMatrix[newEdge[1]][newEdge[0]] = 1;

                vector<int> temp = {-1, -1}; // нове ребро
                
                int c = 0;
                for (auto i = incidenceMatrix.begin() ; i != incidenceMatrix.end(); ++i, ++c)
                {
                    (*i).push_back((c == newEdge[0] || c == newEdge[1]) ? 1 : 0);
                }

                temp[0] = newEdge[0];
                temp[1] = newEdge[1];

                edges_list.push_back(temp);
            }
        }
        else {
            if (creatingEdge)
            {
                // відмінити створення ребра
                edges.resize(edges.getVertexCount() - 1);
                creatingEdge = false;
            }
            else {
                // створити нову вершину
                add_vert();
                CircleShape temp(VERTEX_SIZE);
                temp.setFillColor(Color(255, 153, 0));
                temp.setPosition(Vector2f(mouse_pos.x - VERTEX_SIZE, mouse_pos.y - VERTEX_SIZE));
                temp.setOutlineThickness(2.f);
                temp.setOutlineColor(Color(128, 128, 128));
                verts.push_back(temp);
            }
        }
    }
}

void add_vert() {

    vector<int> temp;

    for (int i = 0; i < adjancencyMatrix.size(); i++)
    {
        temp.push_back(0);
    }

    adjancencyMatrix.push_back(temp);
    temp.clear();

    if (!incidenceMatrix.size())
    {
        incidenceMatrix.push_back(temp);
    }
    else {
        for (int i = 0; i < incidenceMatrix[0].size(); i++)
        {
            temp.push_back(0);
        }
        incidenceMatrix.push_back(temp);
    }
    

    for (auto i = adjancencyMatrix.begin(); i != adjancencyMatrix.end(); ++i)
    {
        (*i).push_back(0);
    }

}

void print_matrix(vector<vector<int>> matrix)
{
    for (auto i = matrix.begin(); i != matrix.end(); ++i)
    {
        for (auto j = (*i).begin(); j != (*i).end(); ++j)
        {
            cout << *j << " ";
        }
        cout << endl;
    }
}

void show_path(vector<int>& stack, VertexArray& edges, vector<CircleShape>& verts) {

    for (auto i = stack.begin() + 1; i != stack.end()-1 ; ++i)
    {
        if (verts[(*i)].getFillColor() == Color(255, 153, 0)) {
            verts[(*i)].setFillColor(Color(0, 153, 255));
        }
    }


    int count;
    for (int i = 0; i != stack.size() - 1; ++i)
    {
        count = 0;
        for (int j = 0; j < edges_list.size(); ++j)
        {
            if (edges_list[j][0] == stack[i] && edges_list[j][1] == stack[i + 1])
            {                
                edges[count * 2].color = Color(0, 122, 204);
                edges[count * 2 + 1].color = Color(0, 122, 204);                
                break;               
            }
            if (edges_list[j][0] == stack[i+1] && edges_list[j][1] == stack[i])
            {                
                edges[count * 2].color = Color(0, 122, 204);
                edges[count * 2 + 1].color = Color(0, 122, 204);               
                break;
            }
            count++;
        }
    }
}

void hide_path(vector<int>& stack, VertexArray& edges, vector<CircleShape>& verts) {

    for (auto i = stack.begin() + 1; i != stack.end() - 1; ++i)
    {
        verts[(*i)].setFillColor(Color(255, 153, 0));
    }


    int count;
    for (int i = 0; i != stack.size() - 1; ++i)
    {
        count = 0;
        for (int j = 0; j < edges_list.size(); ++j)
        {
            if (edges_list[j][0] == stack[i] && edges_list[j][1] == stack[i + 1])
            {
                edges[count * 2].color = Color(255,255,255);
                edges[count * 2 + 1].color = Color(255, 255, 255);                
                break;
            }
            if (edges_list[j][0] == stack[i + 1] && edges_list[j][1] == stack[i])
            {
                edges[count * 2].color = Color(255, 255, 255);
                edges[count * 2 + 1].color = Color(255,255,255);                
                break;
            }
            count++;
        }
    }
}

void print_stack(vector<int> stk) {
    for (int i = 0; i < stk.size(); i++)
    {
        cout << stk[i] << (i == stk.size() - 1 ? "" : ">");
    }
}

void cut_stack(vector<int>& stack) {
    int m;
    int k;

    for (int i = 0; i < stack.size(); ++i)
    {
        m = stack[i];
        k = 1;
        for (int j = i + 1; j < stack.size(); j++)
        {
            if (stack[j] == m)
            {
                for (int l = i; l < stack.size() - k; l++)
                {
                    stack[l] = stack[l + k];
                }
                stack.resize(stack.size()-k);
            }
            k++;
        }
    }
}

void generate_graph_randomly(vector<CircleShape>& verts, VertexArray& edges) {

    srand(time(NULL));

    int n;
    cout << "Enter number of verts: "; cin >> n;
  
    int m;
    int x, y;
    int c;
    vector<int> temp;
    vector<int> bin = {0, 0};
    
    // визначаємо матрицю суміжності
    for (int i = 0; i < n; i++)
    {
        temp.push_back(0);
    }
    for (int i = 0; i < n; i++)
    {
        adjancencyMatrix.push_back(temp);
    }

    // визначаємо матрицю інцидентності
    temp.clear();
    for (int i = 0; i < n; i++)
    {
        incidenceMatrix.push_back(temp);
    }

    // заповнюємо матриці суміжності та інцидентності + матрицю ребер
    for (int i = 1; i < n; i++)
    {
        c = 0;
        for (int j = 0; j < i; j++)
        {
            adjancencyMatrix[i][j] = (rand() % 101 < 400 / n ? 1 : 0);
            adjancencyMatrix[j][i] = adjancencyMatrix[i][j];

            bin[0] = i;
            bin[1] = j;
            if (adjancencyMatrix[i][j]) {
                edges_list.push_back(bin);
                c++;
            }

            if (!c)
            {
                adjancencyMatrix[i][rand() % int(j + 1)];
                adjancencyMatrix[j][i] = adjancencyMatrix[i][j];
            }

            for (int l = 0; l < n; l++)
            {
                incidenceMatrix[i].push_back((l == i && l == j ? 1 : 0));
            }
        }
    }

    // відображення в графіці
    for (int i = 0; i < n; i++)
    {
        do
        {
            x = rand() % int(600 - VERTEX_SIZE * 2) + VERTEX_SIZE;
            y = rand() % int(600 - VERTEX_SIZE * 2) + VERTEX_SIZE;
        } while (is_mouse_on_vert(verts, Vector2i(x, y), 3));

        CircleShape temp1(VERTEX_SIZE);
        temp1.setFillColor(Color(255, 153, 0));
        temp1.setPosition(Vector2f(x - VERTEX_SIZE, y - VERTEX_SIZE));
        temp1.setOutlineThickness(2.f);
        temp1.setOutlineColor(Color(128, 128, 128));
        verts.push_back(temp1);
    }

    for (auto it = edges_list.begin(); it != edges_list.end(); ++it)
    {
        Vertex dot;
        edges.append(dot);
        edges[edges.getVertexCount() - 1].position = Vector2f(verts[(*it)[0]].getPosition().x + VERTEX_SIZE, verts[(*it)[0]].getPosition().y + VERTEX_SIZE);
        edges[edges.getVertexCount() - 1].color = Color(255,255,255);

        Vertex dot1;
        edges.append(dot1);
        edges[edges.getVertexCount() - 1].position = Vector2f(verts[(*it)[1]].getPosition().x + VERTEX_SIZE, verts[(*it)[1]].getPosition().y + VERTEX_SIZE);
        edges[edges.getVertexCount() - 1].color = Color(255, 255, 255);
    }
}