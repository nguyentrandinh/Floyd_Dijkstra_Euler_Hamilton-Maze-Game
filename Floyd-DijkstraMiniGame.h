#pragma once
#include<iostream>
#include<vector>
#include<utility>
#include<GL/glut.h>
#include"gamefunction.h"
#include<thread>
#include<chrono>
#include<queue>
using namespace std;
pair<int, int>position;
Graph G;
int siizze;
pair<int, int> StartGame;
int number = 12;
vector<pair<int,int>>EndGame(number);
vector<vector<int>>Maze;
vector<vector<int>>movi;
vector<vector<pair<int, int>>> pathss;
bool moving = false;
struct Node {
    int x, y, distance;

    // Dịch chuyển toán tử so sánh từ các cặp khoảng cách
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};
void renderBitmapString1(float x, float y, void* font, string string1, int a, int b, int c)
{
    glColor3f(a, b, c);
    glRasterPos2f(x, y);
    for (char c : string1)
    {
        glutBitmapCharacter(font, c);
    }
}
void drawbox(pair<int, int>x1, pair<int, int>x2, int a)
{
    if (a == 1)
        glColor3f(1, 1, 1);
    else if (a == 0)
        glColor3f(0, 0, 0);
    else if (a == 2)
        glColor3f(1, 1, 0.5);
    else if (a == 3)
        glColor3f(1, 0, 0);
    else if (a == 4)
        glColor3f(0,1,0);
    glRectf(x1.first, x1.second, x2.first, x2.second);
}
void drawMap(int nsize, vector<vector<int>> matrix)
	{
    
		pair<int, int>x1 = make_pair<int, int>(-320, 200);
		pair<int, int>x2 = make_pair<int, int>(-340, 220);
        
            for (int i = 0; i < nsize; ++i)
            {
                for (int j = 0; j < nsize; ++j)
                {
                    if (matrix[i][j] == 1)
                        drawbox(x1, x2, 1);
                    if (matrix[i][j] == 0)
                        drawbox(x1, x2, 0);
                    
                    if (StartGame.first == i && StartGame.second == j)
                        drawbox(x1, x2, 2);
                    for (int aa = 0; aa < EndGame.size(); ++aa)
                    {
                        if (EndGame[aa].first == i && EndGame[aa].second == j)
                            drawbox(x1, x2, 3);
                    }
                    if (movi[i][j] == 1)
                    {
                        //std::this_thread::sleep_for(std::chrono::milliseconds(250));
                        drawbox(x1, x2, 4);
                    }
                    x1.first += 21;
                    x2.first += 21;
                }
                x1.first = -320;
                x2.first = -340;
                x1.second -= 21;
                x2.second -= 21;
            }
            
	}
void drawWay(int value)
{
    if (number > 0&&!pathss.empty())
    {
        pair<int, int>a;
        for (int i = 0; i < pathss.size(); ++i) {

            cout << "Path " << i + 1 << ": ";
            for (int j = 0; j < pathss[i].size(); ++j) {
                //drawMap(siizze, Maze);

                cout << "(" << pathss[i][j].first << ", " << pathss[i][j].second << ") ";

                movi[a.first][a.second] = 0;

                a.first = pathss[i][j].first;
                a.second = pathss[i][j].second;
                movi[pathss[i][j].first][pathss[i][j].second] = 1;
                auto it = std::find(EndGame.begin(), EndGame.end(), pathss[i][j]);
                if (it != EndGame.end()) {
                    EndGame.erase(it);
                    StartGame = pathss[i][j];
                }
                drawMap(siizze, Maze);

                this_thread::sleep_for(std::chrono::milliseconds(500));
                glutPostRedisplay();
                glutSwapBuffers();
            }
            cout << "\n";
            number--;
        }
        movi[StartGame.first][StartGame.second] = 0;
        glutTimerFunc(1000, drawWay, 0);
    }
}

bool isValid(int x, int y, const vector<vector<int>>& matrix) {
    return x >= 0 && x < siizze && y >= 0 && y < siizze && matrix[x][y] != 0;
}

vector<pair<int, int>> findShortestPath(vector<vector<int>>& matrix, Node source, Node destination) {
    
    vector<vector<bool>> visited(siizze, vector<bool>(siizze, false));
    vector<vector<int>> distance(siizze, vector<int>(siizze, INF));
    pair<int, int>paths;
    distance[source.x][source.y] = 0;
    vector<pair<int, int>>pathhhh;
    // Sử dụng greater để đảo ngược thứ tự ưu tiên, vì ta muốn ưu tiên node có distance nhỏ hơn
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(source);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        visited[current.x][current.y] = true;

        if (current.x == destination.x && current.y == destination.y) {
           //cout << "Shortest path found. Distance: " << distance[current.x][current.y] << endl;
           //cout << "Path: ";

            while (current.x != source.x || current.y != source.y) {
                paths.first = current.x;
                paths.second = current.y;
                pathhhh.push_back(paths);
                //cout << "(" << current.x << ", " << current.y << ") <- ";
                current = { matrix[current.x][current.y] / siizze, matrix[current.x][current.y] % siizze };
                
            }
            paths.first = source.x;
            paths.second = source.y;
            pathhhh.push_back(paths);
            //cout << "(" << source.x << ", " << source.y << ")" << endl;
            reverse(pathhhh.begin(), pathhhh.end());
            return pathhhh;
        }

        int dx[] = { -1, 0, 1, 0 };
        int dy[] = { 0, 1, 0, -1 };

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            if (isValid(newX, newY, matrix) && !visited[newX][newY]) {
                int newDistance = distance[current.x][current.y] + 1; // Di chuyển từ một ô sang một ô có khoảng cách là 1

                if (newDistance < distance[newX][newY]) {
                    distance[newX][newY] = newDistance;
                    pq.push({ newX, newY, newDistance });
                    matrix[newX][newY] = current.x * siizze + current.y;
                }
            }
        }
    }

    cout << "No path found!" << endl;
    return {};
}


pair<int, int> findMinNextEnd(vector<vector<int>>& matrix, pair<int, int> StartGame, const vector<pair<int, int>>& EndGame) {
    //if (matrix.empty() != 0)
    {
        int minDistance = INF;
        pair<int, int> minNextEnd;
        vector<pair<int, int>> path1;
        for (const auto& end : EndGame) {
            Node source = { StartGame.first, StartGame.second, 0 };
            Node destination = { end.first, end.second, 0 };
            vector<pair<int, int>> path = findShortestPath(matrix, source, destination);
            // Kiểm tra nếu có đường đi từ StartGame đến EndGame
            if (!path.empty()) {
                int distance = path.size() - 1; // Kích thước của đường đi trừ điểm xuất phát
                if (distance < minDistance) {
                    minDistance = distance;
                    minNextEnd = end;
                }
            }


        }

        return minNextEnd;
    }
}
void MazeGame(vector<vector<int>>& matrix, pair<int, int> StartGame, const vector<pair<int, int>>& EndGame) {

    pair<int, int>minNextEnd;
    vector<vector<int>>M = matrix;
    vector<pair<int, int>>EndGame1 = EndGame;
    pathss.clear();
    while (!EndGame1.empty()) {
        pair<int, int> minNextEnd = findMinNextEnd(M, StartGame, EndGame1);

        vector<pair<int, int>> path = findShortestPath(M, { StartGame.first, StartGame.second, 0 }, { minNextEnd.first, minNextEnd.second, 0 });

        if (!path.empty()) {
            pathss.push_back(path);
        }

        // Cập nhật StartGame và loại bỏ EndGame đã đạt được
        StartGame = minNextEnd;
        auto it = std::find(EndGame1.begin(), EndGame1.end(), minNextEnd);
        if (it != EndGame1.end()) {
            EndGame1.erase(it);
        }
    }

    // In ra danh sách đường đi
    for (int i = 0; i < pathss.size(); ++i) {
        //cout << "Path " << i + 1 << ": ";
        for (int j = 0; j < pathss[i].size(); ++j) {
            //cout << "(" << pathss[i][j].first << ", " << pathss[i][j].second << ") ";
        }
        //cout << "\n";
    }
}
vector<vector<int>> InitWindoww()
{
    //EndGame.resize(siizze);
    queue<int>Way1;
    int mindis = -1;
    int tmp;
    queue<int>Way_tmp;
    vector<vector<int>>Maaze;
    srand(time(NULL));
    int size = 22;
    siizze = size;
    glColor3f(1, 1, 1);
    Maaze.resize(size, vector<int>(size, 0));
    //renderBitmapString1(-320, 190, GLUT_BITMAP_TIMES_ROMAN_24, "10", 1, 1, 1);
    glutPostRedisplay();
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            float randomValue = (float)(rand()) / RAND_MAX;  // Ngẫu nhiên từ 0 tới 1
            if (randomValue > 0.3)
                Maaze[i][j] = 1;  // Đặt là đường
        }
    }
    //renderBitmapString1(-320, 190, GLUT_BITMAP_TIMES_ROMAN_24, "20", 1, 1, 1);
    vector<vector<int>>Matrix(size * size, vector < int>(size * size, 0));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (Maaze[i][j] == 0)
                continue;
            int Current = size * i + j;
            if (i >= 1 && Maaze[i - 1][j])
            {
                Matrix[Current][size * (i - 1) + j] = Matrix[size * (i - 1) + j][Current] = 1;
            }
            if (i <= size - 2 && Maaze[i + 1][j])
            {
                Matrix[Current][size * (i + 1) + j] = Matrix[size * (i + 1) + j][Current] = 1;
            }
            if (j >= 1 && Maaze[i][j - 1])
            {
                Matrix[Current][size * (i)+j - 1] = Matrix[size * (i)+j - 1][Current] = 1;
            }
            if (j <= size - 2 && Maaze[i][j + 1])
            {
                Matrix[Current][size * i + j + 1] = Matrix[size * i + j + 1][Current] = 1;
            }
        }
    }
    //renderBitmapString1(-320, 190, GLUT_BITMAP_TIMES_ROMAN_24, "40", 1, 1, 1);
    G = Graph(size * size);
    G.Floyd(Matrix);
    int start[2];
    int number = 12;
    //renderBitmapString1(-320, 190, GLUT_BITMAP_TIMES_ROMAN_24, "60", 1, 1, 1);
    vector<pair<int, int>>end(number);
loop:
    do
    {
        start[0] = rand() % size;
        start[1] = rand() % size;
        StartGame.first = start[0];
        StartGame.second = start[1];
        position.first = start[0];
        position.second = start[1];
    } while (Maaze[start[0]][start[1]] == 0);
    for (int i = 0; i < number; i++)
    {
        do
        {
            end[i].first = rand() % size;
            end[i].second = rand() % size;
        } while (Maaze[end[i].first][end[i].second] == 0 || (end[i].first == start[0] && end[i].second == start[1]));
    }
    for (int i = 0; i < number; i++)
    {

        if (G.Length[start[0] * size + start[1]][end[i].first * size + end[i].second] == vc)
            goto loop;
    }
   
    //renderBitmapString1(-320, 190, GLUT_BITMAP_TIMES_ROMAN_24, "100", 1, 1, 1);
    movi.resize(siizze, vector<int>(siizze));
    EndGame.resize(number);
    EndGame = end;
    movi[position.first][position.second]=1;
    call = true;
    return Maaze;
    
}