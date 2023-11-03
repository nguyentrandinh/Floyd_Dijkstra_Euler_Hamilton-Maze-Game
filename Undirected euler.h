#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>>b;
bool transl = false;
vector<int> path;
bool resultofeuler = false;
int totaledge = 0;
bool isUndirected(vector<vector<int>> matrix) {
    int n = matrix.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return false; // Không đối xứng, là đồ thị có hướng
            }
        }
    }
    return true; // Đối xứng, là đồ thị vô hướng
}
void total()
{
    for (int i = 0; i < nn; i++)
        for (int j = 0; j < nn; j++)
            if (dmatrix[i][j] != 0)
                totaledge++;
}

bool hasEulerCycle() {
    for (int i = 0; i < nn; i++) {
        int deg = 0;
        for (int j = 0; j < nn; j++) {
            if (dmatrix[i][j]!=0)
                deg++; // Tăng bậc khi tìm thấy cạnh kết nối
        }
        if (deg % 2 != 0||deg<1) // Khi bậc của đỉnh là lẻ
            return false; // Không có chu trình Euler
    }
    return true; // Có chu trình Euler
}
bool hasEulerPath() {
    int n = nn;
    int oddDegreeCount = 0;
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            if (dmatrix[i][j] != 0) {
                degree++;
            }
        }
        if (degree % 2 == 1) {
            oddDegreeCount++;
        }
        if (degree < 1)
            return 0;

    }
    if (oddDegreeCount <3&&oddDegreeCount>0)
        return 1;
    else
        return 0;
}
int edgecount()
{
    int count = 0;
    for (int i = 0; i < nn; i++)
        for (int j = i; j < nn; j++)
            if (b[i][j]!=0)
                count++;
    return count;
}

int findStartVert() {
    for (int i = 0; i < nn; i++) {
        int deg = 0;
        for (int j = 0; j < nn; j++) {
            if (dmatrix[i][j]!=0)
                deg++; // Tăng bậc khi tìm thấy cạnh kết nối
        }
        if (deg % 2 != 0) // Khi bậc của đỉnh là lẻ
        {
            return i; // i là đỉnh có bậc lẻ
        }
    }
    return 0; // Khi tất cả các đỉnh có bậc chẵn, bắt đầu từ đỉnh 0
}
bool isBridge(int u, int v) {
    int deg = 0;
    for (int i = 0; i < nn; i++)
        if (b[v][i] != 0)
            deg++;
    if (deg > 1) {
        return false; //the edge is not forming bridge
    }
    return true; //edge forming a bridge
}
static int edge = totaledge;
void fleuryAlgorithm(int start) {
     // Khởi tạo biến edge ở đây
    edge = edgecount();
    for (int v = 0; v < nn; v++) {
        if (b[start][v]!=0) { 
            if ((edge <= 1 || !isBridge(start, v))) {
                path.push_back(v + 1);
                b[start][v] = b[v][start] = 0; //remove edge from graph
                edge--; //reduce edge
                fleuryAlgorithm(v);

            }
        }
    }
}
