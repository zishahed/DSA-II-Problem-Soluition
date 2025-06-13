#include <bits/stdc++.h>
using namespace std;
vector<int> dp, wt, val;
void knapsack(int W)
{
    dp.assign(W + 1, 0);
    cout << "\nSimulation for the DP memo table \n";
    for (int i = 0; i <= wt.size(); i++)
    {
        for (int j = W; j >= wt[i - 1]; j--)
        {
            dp[j] = max(dp[j], dp[j - wt[i - 1]] + val[i - 1]);
            cout << dp[j] << " ";
        }
        cout << '\n';
    }
}

int main()
{
    int n, W;
    cin >> n >> W;
    wt.resize(n);
    val.resize(n);
    for (int i = 0; i < n; i++)
        cin >> wt[i];
    for (int i = 0; i < n; i++)
        cin >> val[i];
    knapsack(W);
    cout << "Maximum possible Knapsack: " << dp[W] << '\n';
    return 0;
}
