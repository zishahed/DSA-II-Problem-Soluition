#include <bits/stdc++.h>
using namespace std;
typedef pair<string, int> psi;

int result;

string matrixChainOrder(vector<int> &arr)
{
    int n = arr.size();
    vector<vector<psi>> dp(n, vector<psi>(n, {"", 0}));
    for (int i = 0; i < n; i++)
    {
        string temp = "";
        temp += char('A' + i);
        dp[i][i] = {temp, 0};
    }
    for (int len = 2; len < n; len++)
    {
        for (int i = 0; i < n - len; i++)
        {
            int j = i + len - 1;
            int cost = INT_MAX;
            string str;
            for (int k = i + 1; k <= j; k++)
            {
                int currCost = dp[i][k - 1].second + dp[k][j].second + arr[i] * arr[k] * arr[j + 1];
                if (currCost < cost)
                {
                    cost = currCost;
                    str = "(" + dp[i][k - 1].first + dp[k][j].first + ")";
                }
            }
            dp[i][j] = {str, cost};
        }
    }
    result = dp[0][n - 2].second;
    return dp[0][n - 2].first;
}

int main()
{
    vector<int> arr = {10, 20, 30, 5, 60};
    // vector<int> arr = {40, 20, 30, 10, 30};
    cout << matrixChainOrder(arr) << endl;
    cout << result;
    return 0;
}