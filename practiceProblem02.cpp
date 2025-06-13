#include <bits/stdc++.h>
using namespace std;
unordered_map<string, int> village = {{"Delduar", 0}, {"Elasin", 1}, {"Pathrail", 2}, {"Lauhati", 3}, {"Atia", 4}, {"Deuliya", 5}, {"Gharinda", 6}};
unordered_map<int, string> village_rev = {{0, "Delduar"}, {1, "Elasin"}, {2, "Pathrail"}, {3, "Lauhati"}, {4, "Atia"}, {5, "Deuliya"}, {6, "Gharinda"}};
vector<int> parent, rank_set;
const int edge = 10, vertix = 7;
struct Edge
{
    int u, v, wt;
    Edge(int u, int v, int wt)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
    bool operator<(Edge const &other)
    {
        return wt < other.wt;
    }
};

void make_set(int v);
int find_set(int v);
void union_sets(int a, int b);
void kruskalMST(vector<Edge> &g, int v);

void printMST(vector<Edge> &mst)
{
    int totalWeight = 0;
    cout << "\nEdges in the MST:\n";
    for (Edge e : mst)
    {
        cout << village_rev[e.u] << " - " << village_rev[e.v] << " (weight: " << e.wt << ")\n";
        totalWeight += e.wt;
    }
    cout << "\nTotal weight of MST: " << totalWeight << endl;
}

int main()
{
    vector<Edge> connections;
    for (int i = 0; i < 10; i++)
    {
        string fir, sec; int weight;
        cin >> fir >> sec >> weight;
        connections.push_back({village[fir], village[sec], weight});
        connections.push_back({village[sec], village[fir], weight});
    }
    kruskalMST(connections, vertix);
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


/*

Delduar Elasin 5
Delduar Pathrail 2
Elasin Pathrail 3
Elasin Lauhati 6
Pathrail Atia 4
Lauhati Atia 7
Lauhati Deuliya 1
Atia Deuliya 2
Deuliya Gharinda 3
Atia Gharinda 6

*/