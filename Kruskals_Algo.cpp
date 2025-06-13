#include <bits/stdc++.h>
using namespace std;
vector<int> parent, rank_set;
struct Edge
{
    int u, v, weight;
    bool operator<(Edge const &other)
    {
        return weight < other.weight;
    }
};


void make_set(int v);
int find_set(int v);
void union_sets(int a, int b);
void kruskalMST(vector<Edge> &g, int v);
vector<Edge> convertToAdjList(vector<vector<int>> &matrix, int v)
{
    vector<Edge> result;
    for (int i = 0; i < v; i++)
        for (int j = i + 1; j < v; j++)
            if (matrix[i][j])
            {
                result.push_back({i, j, matrix[i][j]});
                result.push_back({j, i, matrix[i][j]}); /*instead of writig this
                line, j = 0 would also made this a undirected graph*/
            }
    return result;
}
void printMST(vector<Edge> &mst)
{
    int totalWeight = 0;
    cout << "Edges in the MST:\n";
    for (Edge e : mst)
    {
        cout << e.u << " - " << e.v << " (weight: " << e.weight << ")\n";
        totalWeight += e.weight;
    }
    cout << "Total weight of MST: " << totalWeight << endl;
}


int main()
{
    int V;
    cin >> V;
    // taking input as adjacency matrix and converting it into List...
    vector<vector<int>> graph(V, vector<int>(V));
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];
    vector<Edge> edges = convertToAdjList(graph, V);
    kruskalMST(edges, V);
}


void make_set(int v)
{
    parent[v] = v;
    rank_set[v] = 0;
}
int find_set(int v)   // path compression...
{
    return (v == parent[v]) ? v : (parent[v] = find_set(parent[v]));
}
void union_sets(int a, int b)
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


void kruskalMST(vector<Edge> &graph, int v)
{
    vector<Edge> mst;
    parent.resize(v + 1);
    rank_set.resize(v + 1);
    for (int i = 0; i < v; i++)
        make_set(i);
    sort(graph.begin(), graph.end());
    for (Edge e : graph)
    {
        if (find_set(e.u) != find_set(e.v))
        {
            mst.push_back(e);
            union_sets(e.u, e.v);
        }
    }
    printMST(mst);
}