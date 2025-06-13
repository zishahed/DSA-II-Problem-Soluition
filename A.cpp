#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fo(i, n) for (int i = 0; i < n; i++)
#define rep(i, n) for (int i = 1; i <= n; i++)
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define pb push_back
void solve()
{
    int n;
    bool flag = true;
    cin >> n;
    vector<int> A, B, C;
    for (int i = 0; i < n; i++)
    {
        int l;
        cin >> l;
        A.push_back(l);
        if (l & 1)
            B.push_back(l);
        else
            C.push_back(l);
    }
    int Bsize = B.size(), Csize = C.size(), b, c;
    if (!Bsize || !Csize)
    {
        flag = false;
        if (!Bsize)
        {
            int m = C.back();
            C.pop_back();
            B.push_back(m);
        }
        else
        {
            int m = B.back();
            B.pop_back();
            C.push_back(m);
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (i <= Bsize)
            b = __gcd(B[i], B[i + 1]);
        if (i <= Csize)
            c = __gcd(C[i], C[i + 1]);
    }
    cout << ((b != c) ? "Yes" : "No") << endl;
    if (flag)
    {
        for (auto i : A)
        {
            if (i & 1)
                cout << "1 ";
            else
                cout << "2 ";
        }
        cout << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc = 1;
    cin >> tc;
    while (tc--)
    {
        solve();
    }
    return 0;
}