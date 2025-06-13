#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef pair<string, int> psi;
const int INF = 1e9 + 10;

int vertex, edge, source, destination, mcm;
bool flag = false;

vector<int> dist, parent, matrix;
vector<vector<pii>> graph;
vector<vector<psi>> dp;

void initDP(int n)
{
    dp = vector<vector<psi>>(n, vector<psi>(n, {"", 0}));
}

void MatrixMultiplication()
{
    for (int i = 0; i < mcm; i++)
    {
        string temp = "";
        temp += char('A' + i);
        dp[i][i] = {temp, 0};
    }
    for (int len = 2; len < mcm; len++)
        for (int i = 0; i < mcm - len; i++)
        {
            int j = i + len - 1, cost = INF;
            string str;
            for (int k = i + 1; k <= j; k++)
            {
                int currCost = dp[i][k - 1].second + dp[k][j].second + matrix[i] * matrix[k] * matrix[j + 1];
                if (currCost < cost)
                {
                    cost = currCost;
                    str = "(" + dp[i][k - 1].first + dp[k][j].first + ")";
                }
            }
            dp[i][j] = {str, cost};
        }
}

void bellman_ford()
{
    dist.assign(vertex + 1, INF);
    parent.assign(vertex + 1, -1);
    dist[source] = 0;
    for (int i = 0; i < vertex; i++)
        for (int u = 0; u < vertex; u++)
            for (auto &[v, wt] : graph[u])
                if (dist[u] != INF && dist[u] + wt < dist[v])
                {
                    parent[v] = u;
                    dist[v] = dist[u] + wt;
                }
    for (int u = 0; u < vertex; u++)
        for (auto &[v, wt] : graph[u])
            if (dist[u] != INF && dist[u] + wt < dist[v])
                return;
    flag = true;
}

void printPath()
{
    if (dist[destination] == INF)
    {
        cout << "No path exists from source to destination.\n";
        return;
    }
    vector<int> path;
    for (int v = destination; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    cout << "Path from source to destination: ";
    for (int node : path)
        cout << node << " ";
    cout << "\n";
    cout << "Total distance: " << dist[destination] << "\n";
}

int main()
{
    cout << "Enter Vertex and Edge: ";
    cin >> vertex >> edge;
    graph.assign(vertex + 1, {});
    cout << "Enter each edge as: from to weight\n";
    for (int i = 0; i < edge; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        graph[u].push_back({v, wt});
    }
    cout << "Enter the source and destination: ";
    cin >> source >> destination;
    bellman_ford();
    if (flag)
    {
        printPath();
        cout << "Enter the number of matrix: ";
        cin >> mcm;
        mcm++;
        matrix.resize(mcm);
        cout << "Enter the dimensions: ";
        for (int i = 0; i < mcm; i++)
        {
            int x;
            cin >> x;
            matrix[i] = x;
        }
        initDP(mcm);
        MatrixMultiplication();
        cout << "Minimum cost: " << dp[0][mcm - 2].second << endl;
        cout << "To achieve it we should multiply like: " << dp[0][mcm - 2].first << endl;
    }
    else
        cout << "Negative weight cycle detected. No valid shortest path.\n";
    return 0;
}
