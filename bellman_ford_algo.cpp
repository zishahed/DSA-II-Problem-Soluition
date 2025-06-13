#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
vector<int> dist, parent;
bool flag = false;
void bellman_ford(const vector<vector<pair<int, int>>> &g, int n, int m, int src)
{
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[src] = 0;
    for (int i = 0; i < n - 1; i++)
        for (int u = 0; u < n; u++)
            for (auto &[v, w] : g[u])
                if (dist[u] != INF and dist[u] + w < dist[v])
                {
                    parent[v] = u;
                    dist[v] = dist[u] + w;
                }
    for (int u = 0; u < n; u++)
        for (auto &[v, w] : g[u])
            if (dist[u] != INF and dist[u] + w < dist[v])
                return;
    flag = true;
    return;
}
void printPath()
{
    int dest;
    cin >> dest;
    if (dist[dest] == INF)
    {
        cout << "No path to destination " << dest << "\n";
        return;
    }
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "Path: ";
    for (int v : path)
        cout << v << " ";
    cout << '\n';
}
void printDistances(int n, int src)
{
    cout << "The distance of each vertex from source: " << src << " is: \n";
    for (int i = 1; i < n; i++)
    {
        cout << "Vertex " << i << " -> Distance = ";
        cout << ((dist[i] == INF) ? "Unreachable" : to_string(dist[i])) << '\n';
    }
}
int main()
{
    int vertex, edge, source;
    cin >> vertex >> edge;
    vector<vector<pair<int, int>>> graph(vertex);
    for (int i = 0; i < edge; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    cin >> source;
    bellman_ford(graph, vertex, edge, source);
    if (flag)
    {
        printDistances(vertex, source);
        cout << "Enter destination to print path: ";
        printPath();
    }
    else
        cout << "Negative weight cycle detected!\n";
}