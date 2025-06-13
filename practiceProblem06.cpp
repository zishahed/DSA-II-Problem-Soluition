#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
vector<int> dist, parent, path, weight;
vector<pair<int, int>> cityID_val;

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
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "Path: ";
    for (int v : path)
        cout << v << " ";
    cout << '\n';
}

void knapsack(int W){
    int n = weight.size();
    vector<int> dp(W + 1, 0);
    vector<vector<bool>> selected(n, vector<bool>(W + 1, false));

    for (int i = 0; i < n; ++i) {
        for (int w = W; w >= weight[i]; --w) {
            int include = cityID_val[i].second + dp[w - weight[i]];
            if (include > dp[w]) {
                dp[w] = include;
                selected[i][w] = true;  
            }
        }
    }

    cout << "\nMaximum value: " << dp[W] << endl;

    vector<pair<int, int>> chosen_cities;
    int w = W;
    for (int i = n - 1; i >= 0; --i) {
        if (selected[i][w]) {
            chosen_cities.push_back(cityID_val[i]);
            w -= weight[i];
        }
    }

    cout << "\n";
    for (auto &[id, val]  : chosen_cities) 
        cout << "City (" << id << "): Value = "  << val << '\n';
    cout << endl;
}

int main()
{
    int vertex, edge, source = 0;
    cout << "Enter the number of vertex and edge: ";
    cin >> vertex >> edge;
    vector<vector<pair<int, int>>> graph(vertex);
    for (int i = 0; i < edge; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    dijkstra(graph, vertex, edge, source);
    printDistances(vertex, source);
    cout << "Enter destination node to print path: ";
    int dest;
    cin >> dest;
    printPath(dest);

    int T, W;
    cout << "\nNumber of Treasures: \n";
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int id, wt, val;
        cin >> id >> wt >> val;
        if (find(path.begin(), path.end(), id) != path.end())
        {
            weight.push_back(wt);
            cityID_val.push_back({id, val});
        }
    }
    cout << "Enter the W: ";
    cin >> W;
    knapsack(W);
    return 0;
}
