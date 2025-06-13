/*
    Taking input of Adjacent Matrix makes Time Complexity: O(V^2)
    If we take input as List, then it becomes: 0((E+V)*logV)
*/

#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
vector<vector<pair<int, int>>> convertToAdjList(vector<vector<int>> &matrix, int v)
{
    vector<vector<pair<int, int>>> adjList(v);
    for (int i = 0; i < v; i++)
    {
        for (int j = i + 1; j < v; j++)
        {
            if (matrix[i][j])
            {
                adjList[i].push_back({j, matrix[i][j]}); // (neighbor, weight)
                adjList[j].push_back({i, matrix[i][j]}); // undirected graph
                // Prim & Kruskal doesn't work with directed graph
            }
        }
    }
    return adjList;
}
void printMST(vector<vector<pair<int, int>>> &g, vector<int> &p, int &V)
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; ++i) // i = 0 denotes, 0 - 0 edge, which is not needed
    {
        for (auto &[neighbor, weight] : g[p[i]])
        {
            if (neighbor == i)
            {
                cout << p[i] << " - " << i << "\t  " << weight << '\n';
                break;
            }
        }
    }
}
void primsMST(vector<vector<pair<int, int>>> &g, int ver)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> min_weight(ver, INF), parent(ver, -1), visited(ver, 0);
    pq.push({0, 0});
    while (!pq.empty())
    {
        auto p = pq.top().second;
        pq.pop();
        if (!visited[p])
        {
            visited[p] = 1;
            for (auto &[v, weight] : g[p])
            {
                if (!visited[v] && weight < min_weight[v])
                {
                    min_weight[v] = weight;
                    parent[v] = p;
                    pq.push({weight, v});
                }
            }
        }
    }
    printMST(g, parent, ver);
}
int main()
{
    int V;
    cin >> V;
    vector<vector<int>> g(V, vector<int>(V)); // init a 2D a vector
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> g[i][j];
    vector<vector<pair<int, int>>> graph;
    graph = convertToAdjList(g, V);
    primsMST(graph, V);
}