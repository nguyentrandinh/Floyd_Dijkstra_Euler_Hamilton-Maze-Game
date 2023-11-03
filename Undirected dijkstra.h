#pragma once
#include<string>
vector<int>dist1;
vector<vector<string>> waytodo;
int startchoicedijkstra = 0;
bool resultofdijkstra = false;
#define INF 1e9

int minDistance(vector<int>dist, vector<bool>sptSet)
{
    int min = INF;
    int min_index;
    int n = dist.size();
    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}
void dijkstra(const vector<vector<int>>& graph, int src)
{
    int n = graph.size();
    src -= 1;
    vector<int>dist(n, INF);
    vector<bool>marked(n, false);
    vector<bool>markedcout(n, false);
    vector<int>path(n, -1);
    vector<vector<string>> wayy(n, vector<string>(n, "(vc,-)"));
    dist[src] = 0;
    for (int vong1 = 0; vong1 < n; vong1++)
    {
        int current = minDistance(dist, marked);
        marked[current] = true;
        if (src == vong1)
            wayy[src][vong1] = "(0,1)";
        else
            wayy[src][vong1] = "(vc,-)";
        if (vong1 != n - 1)
        {
            for (int i = 0; i < n; i++)
            {
                if (marked[i] == false)
                {
                    if (graph[current][i] && dist[current] != INF && dist[current] + graph[current][i] < dist[i])
                    {
                        dist[i] = dist[current] + graph[current][i];
                        path[i] = current;
                    }
                }if (dist[i] != INF)
                {
                    string abc;
                    abc = "";
                    if (path[i] != -1)
                    {
                        abc = "(" + to_string(dist[i]) + "," + to_string(path[i] + 1) + ")";
                        markedcout[i] = true;
                    }
                    if (marked[i] == false)
                        wayy[vong1 + 1][i] = abc;
                    else
                        wayy[vong1 + 1][i] = "";
                }

            }
        }

    }
    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INF)
            dist[i] = 0;
    }
    waytodo = wayy;
    dist1 = dist;
}

