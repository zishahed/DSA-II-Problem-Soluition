#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
vector<int> dist, parent;

void dijkstra(const vector<vector<pair<int, int>>> &g, int n, int m, int src)
{
    dist.assign(n, INF);
    parent.assign(n, -1);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});
    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto &[v, w] : g[u])
        {
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void printDistances(int n, int src)
{
    cout << "Shortest distances from source " << src << ":\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "To " << i << " -> ";
        if (dist[i] == INF)
            cout << "Unreachable\n";
        else
            cout << dist[i] << '\n';
    }
}

void printPath(int dest)
{
    if (dist[dest] == INF)
    {
        cout << "No path to destination " << dest << '\n';
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
    dijkstra(graph, vertex, edge, source);
    printDistances(vertex, source);
    cout << "Enter destination node to print path: ";
    int dest;
    cin >> dest;
    printPath(dest);
    return 0;
}
