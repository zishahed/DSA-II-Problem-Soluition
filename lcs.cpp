#include <bits/stdc++.h>
using namespace std;

string lcs(string &s1, string &s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    string lcs_str;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs_str += s1[i - 1];
            --i; --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }
    reverse(lcs_str.begin(), lcs_str.end()); 
    return lcs_str;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    string lcs_result = lcs(s1, s2);
    cout << "Length: " << lcs_result.length() << "\n";
    cout << "LCS: " << lcs_result << "\n";
    return 0;
}
