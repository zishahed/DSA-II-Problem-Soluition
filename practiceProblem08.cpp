#include <bits/stdc++.h>
using namespace std;

int vertex, edge, W, N;

vector<int> parent, rank_set, dp;

struct Items
{
    double weight, utility_score;
    string name;
    bool operator<(const Items &other) const
    {
        return weight < other.weight;
    }
    bool operator>(const Items &other) const
    {
        return weight > other.weight;
    }
};

struct Edge
{
    int u, v, wt;
    bool operator<(const Edge &other) const
    {
        return wt < other.wt;
    }
};

void knapsack(vector<Items> item)
{
    dp.assign(W + 1, 0);
    vector<vector<bool>> selected(N, vector<bool>(W + 1, false));
    for (int i = 0; i < N; i++)
        for (int w = W; w >= item[i].weight; w--)
        {
            int include = item[i].utility_score + dp[w - item[i].weight];
            if (include > dp[w])
            {
                dp[w] = include;
                selected[i][w] = true;
            }
        }
    cout << "Maximum weight that a drone can carry is: " << dp[W] << endl;

    vector<Items> chosenItems;
    int w = W;
    for (int i = N - 1; i >= 0; i--)
        if (selected[i][w])
        {
            chosenItems.push_back({item[i]});
            w -= item[i].weight;
        }

    cout << "Items that drone can carry are: \n";
    for (auto &ci : chosenItems)
        cout << "Item name: " << ci.name << " & Value: " << ci.utility_score << '\n';
    cout << endl;
}

void printMST(vector<Edge> mst)
{
    int totalW = 0;
    cout << "Edge \t  Weight: \n";
    for (auto &e : mst)
    {
        cout << e.u << " - " << e.v << '\t' << e.wt << '\n';
        totalW += e.wt;
    }
    cout << "Total Cost of the Routes: " << totalW << endl;
}

void make_set(int v);
int find_set(int v);
void union_set(int a, int b);
void kruskalAlgo(vector<Edge> &g);

int main()
{
    cout << "Enter the number of vertex and edge: ";
    cin >> vertex >> edge;
    vector<Edge> graph;
    cout << "Enter edges info: from to weight \n";
    for (int i = 0; i < edge; i++)
    {
        int u, v, wt;
        cin >> u >> v >> wt;
        graph.push_back({u, v, wt});
    }
    kruskalAlgo(graph);

    cout << "Enter the Max amount Drone can carry: ";
    cin >> W;
    cout << "Enter the number of items: ";
    cin >> N;
    vector<Items> item;
    cout << "Enter the info of Items: \n";
    for (int i = 0; i < N; i++)
    {
        double wt, ut;
        string name;
        cin >> name >> wt >> ut;
        item.push_back({wt, ut, name});
    }
    knapsack(item);
}

void make_set(int v)
{
    parent[v] = v;
    rank_set[v] = 0;
}

int find_set(int v)
{
    return (v == parent[v]) ? v : (parent[v] = find_set(parent[v]));
}

void union_set(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (rank_set[a] < rank_set[b])
            swap(a, b);
        parent[b] = a;
        if (rank_set[a] == rank_set[b])
            rank_set[a]++;
    }
}

void kruskalAlgo(vector<Edge> &g)
{
    vector<Edge> mst;
    parent.resize(vertex + 1);
    rank_set.resize(vertex + 1);
    for (int i = 0; i < vertex; i++)
        make_set(i);
    sort(g.begin(), g.end());
    for (Edge &e : g)
    {
        if (find_set(e.u) != find_set(e.v))
        {
            mst.push_back(e);
            union_set(e.u, e.v);
        }
    }
    printMST(mst);
}