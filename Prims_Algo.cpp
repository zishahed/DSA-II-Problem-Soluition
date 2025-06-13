#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
int minWeightIndex(vector<int> &min_weight, vector<int> &visited, int v)
{
    int min = INF, min_Index;
    for (int i = 0; i < v; i++)
    {
        if (!visited[i] && min_weight[i] < min)
            min = min_weight[i], min_Index = i;
    }
    return min_Index;
}
void printMST(vector<int> &p, vector<vector<int>> &g)
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < g.size(); i++)
        cout << p[i] << " - " << i << " \t  " << g[p[i]][i] << " \n";
}
void primsMST(vector<vector<int>> &g, int &v)
{
    vector<int> parent(v), min_weight(v, INF), visited(v, 0);
    min_weight[0] = 0, parent[0] = -1;
    for (int i = 0; i < v - 1; i++) // MST is a Tree, having 'V-1' no. of edges
    {
        int u = minWeightIndex(min_weight, visited, v);
        visited[u] = 1;
        for (int i = 0; i < v; i++)
            if (g[u][i] && !visited[i] && g[u][i] < min_weight[i])
            // if graph has non zero weight, not visited and curr weight
            // is less than previous minimum weight...
            {
                parent[i] = u;
                min_weight[i] = g[u][i];
            }
    }
    printMST(parent, g);
}
int main()
{
    int V;
    cin >> V;
    vector<vector<int>> graph(V, vector<int>(V)); // init a 2D a vector
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];
    primsMST(graph, V);
}