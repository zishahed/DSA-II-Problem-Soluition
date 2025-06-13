#include <bits/stdc++.h>
using namespace std;
typedef pair<int, pair<int, int>> pii;
unordered_map<string, int> dept = {
    {"CS", 1}, {"EEE", 2}, {"ME", 3}, {"CE", 4}, {"Arch", 5}, {"BBA", 6}, {"English", 7}};
unordered_map<int, string> dept_rev;

const int vertix = 7, edge = 9;

vector<vector<pair<int, int>>> adj(vertix + 1);
vector<bool> visited(vertix + 1, false);

void reversemap()
{
    for (auto &p : dept)
        dept_rev[p.second] = p.first;
}

void printMST(vector<tuple<int, int, int>> &mst)
{
    int totalWeight = 0;
    cout << "\nEdges in the MST:\n";
    for (auto &[u, v, wt] : mst)
    {
        cout << dept_rev[u] << " - " << dept_rev[v] << " (weight: " << wt << ")\n";
        totalWeight += wt;
    }
    cout << "\nTotal weight of MST: " << totalWeight << endl;
}

void primMST(int start)
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<tuple<int, int, int>> mst;

    pq.push({0, {start, -1}}); // {weight, {current, parent}}

    while (!pq.empty())
    {
        auto [wt, nodes] = pq.top();
        pq.pop();
        int u = nodes.first;
        int parent = nodes.second;

        if (visited[u])
            continue;
        visited[u] = true;

        if (parent != -1)
            mst.push_back({parent, u, wt});

        for (auto &[v, w] : adj[u])
            if (!visited[v])
                pq.push({w, {v, u}});
    }

    printMST(mst);
}

int main()
{
    reversemap();

    for (int i = 0; i < edge; i++)
    {
        string fir, sec;
        int weight;
        cin >> fir >> sec >> weight;
        int u = dept[fir], v = dept[sec];
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    primMST(dept["CS"]);
    return 0;
}

/*
CE EEE 2
CS ME 3
EEE ME 1
ME CE 4
CE Arch 2
Arch BBA 5
BBA English 2
ME BBA 6
CE English 7
*/
