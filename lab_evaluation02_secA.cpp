/*
    You are an adventure traveling through a map of cities connected by roads, Each road has
    a travel time. SOme cities contain treasure treasure. Each item has:
    A weight and a value.
    Your goal is: Reach the desatination city in minimum time, and Collect treasure treasure along
    the path keeping total weight <= you backpack limit and maximizing the total value of collected
    treasure.

    input:
    5 6
    0 1 2
    0 2 4
    1 2 1
    1 3 7
    2 3 2
    3 4 3
    3
    1 2 10
    2 3 20
    3 4 25
    0 4 5
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;
typedef pair<int, int> pii;

struct Treasure
{
    int weight, value;
};

int n, m, knapsack;
vector<vector<pii>> graph;
vector<Treasure> treasures;
vector<int> dist, selected_items;
vector<vector<int>> parents;

void dijkstra(int src)
{
    dist.assign(n, INF);
    dist[src] = 0;
    parents.assign(n, {});
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, src});
    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto [v, w] : graph[u])
        {
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                parents[v] = {u};
            }
            else if (dist[v] == dist[u] + w)
                parents[v].push_back(u);
        }
    }
}

void dfs(int u, vector<int> &path, vector<vector<int>> &all_paths)
{
    path.push_back(u);
    if (u == 0)
    {
        reverse(path.begin(), path.end());
        all_paths.push_back(path);
        reverse(path.begin(), path.end());
    }
    else
        for (int p : parents[u])
            dfs(p, path, all_paths);
    path.pop_back();
}

int PickItem(const vector<Treasure> &items, int cap)
{
    int n = items.size();
    vector<vector<bool>> choice(n + 1, vector<bool>(cap + 1));
    selected_items.reserve(n + 1);
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int wt = items[i - 1].weight, val = items[i - 1].value;
        for (int w = cap; w >= wt; w--)
        {
            if (dp[w] < dp[w - wt] + val)
            {
                dp[w] = dp[w - wt] + val;
                choice[i][w] = true;
            }
        }
    }
    int w = cap;
    for (int i = n; i > 0; --i)
    {
        if (choice[i][w])
        {
            selected_items.push_back(i);
            w -= items[i - 1].weight;
        }
    }
    return dp[cap];
}

int main()
{
    cin >> n >> m;
    graph.assign(n, {});
    for (int i = 0; i < m; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        graph[u].emplace_back(v, t);
    }
    treasures.assign(n, {0, 0});
    int treasure_count;
    cin >> treasure_count;
    for (int i = 0; i < treasure_count; i++)
    {
        int city_id, w, v;
        cin >> city_id >> w >> v;
        treasures[city_id] = {w, v};
    }
    int source, dest;
    cin >> source >> dest >> knapsack;
    dijkstra(source);
    vector<vector<int>> all_paths;
    vector<int> path;
    dfs(dest, path, all_paths);
    int best_value = 0;
    vector<int> best_path;
    vector<Treasure> items;
    for (auto &p : all_paths)
    {
        for (int city : p)
        {
            if (treasures[city].value > 0)
                items.push_back(treasures[city]);
        }
        int val = PickItem(items, knapsack);
        if (val > best_value)
        {
            best_value = val;
            best_path = p;
        }
    }
    cout << "Minimum Travel time: " << dist[dest] << endl;
    cout << "Max treasure value: " << best_value << endl;
    cout << "Path: ";
    for (int i : best_path)
        if (i != 0)
            cout << i << " ";
    cout << '\n';
    cout << "Items Picked: ";
    for (auto i : selected_items)
        cout
            << "city " << i << "(" << items[i - 1].value << "), ";
    cout << '\n';
    return 0;
}
