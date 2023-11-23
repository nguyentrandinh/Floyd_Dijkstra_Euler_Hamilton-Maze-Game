//
// Created by Admin on 10/3/2023.
//
#include<iostream>
#include<vector>
#include<iomanip>
#include<fstream>
#include<queue>
#include<stack>
#include<algorithm>
#include<numeric>
#include<stdlib.h>
#include<list>
#define INF 1e9
#pragma once
using namespace std;
vector<vector<int>> dmatrix;
vector<vector<int>> matrixx;
vector<vector<int>> matrixxx;
vector<vector<int>> shortestDistances;
vector<vector<int>> Luuvetpath;
queue<int> Way;
int startchoiceLuuvet=0;
int endchoiceLuuvet=0;
bool resultofway = false;

int startchoiceMinLength=0;
int endchoiceMinLength=0;
bool resultofmin=false;

//size of matrix
 int nn;
 //value input matrix's size when manual input
 int tmpnn = 0;

int isDigit(string a)
{
    if (a[0] == '-')
        a.erase(0, 1);
    for (char c : a)
        if (!isdigit(c))
            return false;
    return true;
}
queue<int> Truyvet(int u,int v)
{
    queue<int> Way;
    int tmp=u;
    if (Luuvetpath[u-1][v-1]!=0)
    {
        while (tmp != v)
        {
            Way.push(tmp);
            tmp = Luuvetpath[tmp - 1][v - 1];
        }
        Way.push(v);
     }
     else
        Way.push(0);
     return Way;
}
int Min_length(int u, int v)
{
    u -= 1;
    v -= 1;
    int value;
    value = shortestDistances[u][v];
    return value;
}
void FloydWarshall(const vector<vector<int>>& graph)
{
    int n = graph.size();
    vector<vector<int>> Length(n, vector<int>(n, INF));
    vector<vector<int>> Luuvett(n, vector<int>(n, INF));
    // Khởi tạo ma trận khoảng cách ban đầu
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            Length[i][j] = graph[i][j];
            if (Length[i][j] != 0 && Length[i][j] != INF)
                Luuvett[i][j] = j + 1;
            else
                Luuvett[i][j] = 0;
            if (Length[i][j] == 0 && i != j)
                Length[i][j] = INF;
        }
    }

    // Thuật toán Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (Length[i][j] > (Length[i][k] + Length[k][j]))
                {
                    Length[i][j] = Length[i][k] + Length[k][j];
                    Luuvett[i][j] = Luuvett[i][k];
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (Length[i][j] == INF)
                Length[i][j] = 0;
            
        }
    }
    shortestDistances = Length;
    Luuvetpath = Luuvett;
}
vector<vector<int>> readMatrixFromFile(const string& filename)
{
    ifstream file(filename);
    vector<vector<int>> matrix;
    if (!file.is_open()) {
        cerr << "Khong the mo tep " << filename << endl;
        return {};
    }
    int n;
    file >> n;  // Đọc kích thước của ma trận
    nn = n;
    // Khởi tạo ma trận với kích thước n x n và đọc giá trị từ tệp
    matrix.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> matrix[i][j];
        }
    }
    file.close();
    return matrix;
}
