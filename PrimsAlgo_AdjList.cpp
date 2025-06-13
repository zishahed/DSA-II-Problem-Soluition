#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
typedef pair<int, int> pii;

const int vertix = 5, edge = 6, INF = 1e9 + 10;

vector<vector<pii>> graph(vertix);
vector<int> min_weight(vertix, INF), parent(vertix, -1), visited(vertix, 0), edge_weight(vertix, INF);

void printMST()
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < vertix; ++i)
    {
        cout << parent[i] << " - " << i << "\t  " << edge_weight[i] << '\n';
    }
}

void PrimsAlgo()
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});
    min_weight[0] = 0;

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int p = pq.top().second;
        pq.pop();

        if (!visited[p])
        {
            visited[p] = 1;
            for (auto &[v, wt] : graph[p])
            {
                if (!visited[v] && wt < min_weight[v])
                {
                    min_weight[v] = wt;
                    parent[v] = p;
                    edge_weight[v] = wt;
                    pq.push({wt, v});
                }
            }
        }
    }
    printMST();
}

int main()
{
    for (int i = 0; i < edge; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        graph[u].push_back({v, wt});
        graph[v].push_back({u, wt});
    }
    PrimsAlgo();
}
