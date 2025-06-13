/*
    A message delivery robot moves between computers in a network.
    The network is represented as a GRAPH where:

    nodes / vertices = computer (numbered from 0 to N-1)
    edges = communication links between them with a positive transmission delay.
    a message word (string)

    You are given: A start computer and a end computer and A target keyword (string).
    THe robot must deliver a message from start to end, choosing the shortest possible path
    in terms of total delay. IN the shortest paths, the robot finds the concatenated message
    words along the path sharing the maximum LCS with the target keyword.

    Input:
    4 4
    0 1 2 abc
    1 2 2 de
    0 2 4 abd
    2 3 1 c
    0 aplbmcdpe 3

    Ouput:
    Minimum Delay: 5 
    Path: 2 3
    LCS with 'abdc': 3
*/
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 10;
vector<vector<tuple<int, int, string>>> graph;
string result = "";
vector<int> parent, dist;

void lcs(string message)
{
    int m = message.size(), n = result.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            if (message[i - 1] == result[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    string answer = "";
    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (message[i - 1] == result[j - 1])
        {
            answer += message[i - 1];
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
    reverse(answer.begin(), answer.end());
    cout << "LCS with '" << result << "' is: " << answer.size() << '\n';
}

void bellman_ford(int v, int src)
{
    dist.assign(v + 1, INF);
    parent.assign(v + 1, -1);
    dist[src] = 0;
    for (int i = 0; i < v; i++)
        for (auto &[child, wt, str] : graph[i])
            if (dist[i] + wt < dist[child])
            {
                dist[child] = dist[i] + wt;
                parent[child] = i;
            }
    return;
}

void printPath(int dest)
{
    vector<int> path;
    for (int i = dest; parent[i] != -1; i = parent[i])
        path.push_back(i);

    reverse(path.begin(), path.end());
    cout << "The path is: ";
    for (auto i : path)
    {
        cout << i << " ";
        for (auto &[child, wt, str] : graph[parent[i]])
            if (child == i)
                result += str;
    }
    cout << '\n';
}

int main()
{
    int vertix, edge, source, dest;
    string keyword;
    cin >> vertix >> edge;
    graph.resize(vertix);
    for (int i = 0; i < edge; i++)
    {
        int a, b, c;
        string str;
        cin >> a >> b >> c >> str;
        graph[a].push_back({b, c, str});
    }
    cin >> source;
    bellman_ford(vertix, source);
    cin >> keyword;
    cin >> dest;
    cout << "Minimum Delay: " << dist[dest] << '\n';
    printPath(dest);
    lcs(keyword);
}
