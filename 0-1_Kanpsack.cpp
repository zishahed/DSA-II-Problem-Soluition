#include <bits/stdc++.h>
using namespace std;
vector<int> dp, wt, val;
void knapsack(int W)
{
    dp.assign(W + 1, 0);
    vector<vector<bool>> selected(wt.size(), vector<bool>(W + 1, false));
    for (int i = 0; i < wt.size(); i++)
        for (int w = W; w >= wt[i]; w--)
        {
            int include = val[i] + dp[w - wt[i]];
            if (include > dp[w])
            {
                dp[w] = include;
                selected[i][w] = true;
            }
        }
    cout << "Maximum Value: " << dp[W] << endl;

    vector<int> chosenItems;
    int w = W;
    for (int i = wt.size() - 1; i >= 0; i--)
        if (selected[i][w])
        {
            chosenItems.push_back(val[i]);
            w -= wt[i];
        }

    cout << "The values of Chosen Items are: ";
    for (auto &c : chosenItems)
        cout << c << " ";
    cout << endl;
}

int main()
{
    int n, W;
    cout << "Enter the number of items and Total Knapsack: ";
    cin >> n >> W;
    wt.resize(n);
    val.resize(n);
    cout << "Enter the weight and values of items: \n";
    for (int i = 0; i < n; i++)
        cin >> wt[i];
    for (int i = 0; i < n; i++)
        cin >> val[i];
    knapsack(W);
    return 0;
}
