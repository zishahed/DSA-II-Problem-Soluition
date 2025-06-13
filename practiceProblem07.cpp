#include <bits/stdc++.h>
using namespace std;

typedef pair<string, int> psi;

vector<vector<psi>> dp;
vector<int> arr;

const int INF = 1e9 + 10;

void initDP(int size)
{
    dp = vector<vector<psi>>(size, vector<psi>(size, {"", 0}));
}

void matrixMultiplication(int n)
{
    initDP(n);
    for (int i = 0; i < n; i++)
    {
        string temp;
        temp = char('A' + i);
        dp[i][i] = {temp, 0};
    }
    for (int len = 2; len < n; len++)
        for (int i = 0; i < n - len; i++)
        {
            int j = i + len - 1, cost = INF;
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

int main()
{
    int n;
    cout << "Enter the number of Matrices: ";
    cin >> n;
    arr.resize(n + 1);
    cout << "Enter the dimensions: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    matrixMultiplication(n);
    cout << "The minimum Multiplication needed: " << dp[0][n - 2].second << endl;
    cout << "& to achieve it we need to do: " << dp[0][n - 2].first << endl;
}