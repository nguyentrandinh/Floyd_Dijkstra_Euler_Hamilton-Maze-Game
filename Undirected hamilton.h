#include <iostream>
#include<vector>
using namespace std;
bool resultofhamilton = false;
bool call = false;
int num_rows=0;
vector<vector<int>> pathofhamiltonpath; // Lưu đường đi Hamilton
vector<vector<int>> matrixofhamilton(nn, vector<int>(nn, 0));
void complete() {

    for (int i = 0; i < pathofhamiltonpath.size(); i++) {

        for (int j = 0; j < pathofhamiltonpath[i].size(); j++)
        {
            pathofhamiltonpath[i][j]++;
        }
    }
}
bool hashamiltoncycle_DIRAC(vector<vector<int>> graph) {
    if (nn < 3)
        return false;
    for (int i = 0; i < nn; i++)
    {
        int dg = 0;
        for (int j = 0; j < nn; j++)
        {
            if (graph[i][j] != 0)
                dg++;
        }
        if (dg < (int)nn / 2||dg<2)
            return false;
    }
    return true;
}
bool hashamiltoncycle_ORE(vector<vector<int>> graph)
 {
    if (nn < 2)
        return false;
    int n = graph.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!graph[i][j]) {
                int degree_i = 0, degree_j = 0;
                for (int k = 0; k < n; ++k) {
                    if (graph[i][k]!=0) ++degree_i;
                    if (graph[j][k]!=0) ++degree_j;
                }
                if (degree_i + degree_j >= n)
                {
                    return true;
                    break;
                }
            }
        }
    }
    return false;
}
void hamiltonPathUtil(vector<int>& path, int pos) {
    if (pos == nn) {
        pathofhamiltonpath.push_back(path);
        return;
    }

    for (int v = 0; v < nn; v++) {
        if (matrixofhamilton[path[pos - 1]][v] != 0) {
            bool isVisited = false;
            for (int i = 0; i < pos; i++) {
                if (path[i] == v) {
                    isVisited = true;
                    break;
                }
            }
            if (!isVisited) {
                path[pos] = v;
                hamiltonPathUtil(path, pos + 1);
                path[pos] = -1;
            }
        }
    }
}

void findAllHamiltonPaths() {
    vector<int> path(nn, -1);
    for (int start = 0; start < nn; start++) {
        path[0] = start;
        hamiltonPathUtil(path, 1);
        path[0] = -1;
    }
}