[题解](https://codeforces.com/blog/entry/116527)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e5 + 100;
typedef long long ll;
void solve();
int main()
{
    ios::sync_with_stdio(false);
    clock_t c1 = clock();
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    int T;
    for (cin >> T; T--;)
        solve();
    cerr << "Time Used: " << clock() - c1 << " ms\n";
    return 0;
}

ll a[MAX], b[MAX];
int n;
int mp[635][MAX];
void solve()
{
    cin >> n;
    int lim = sqrt(2 * n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
    {
        cin >> b[i];
        if (a[i] <= lim)
            mp[a[i]][b[i]]++;
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if ((i + 1) <= lim && !((i + 1) & 1))
            ans += (mp[(i + 1)][(i + 1) * (i + 1) / 2] - 1ll) * mp[(i + 1)][(i + 1) * (i + 1) / 2] / 2ll;
        if (a[i] * a[i] - b[i] < b[i] && a[i] * a[i] - b[i] >= 1)
            ans += mp[a[i]][a[i] * a[i] - b[i]];
        for (int aj = 1; aj < a[i] && aj * a[i] <= 2 * n; ++aj)
            if (a[i] * aj - b[i] >= 1 && a[i] * aj - b[i] <= n)
                ans += mp[aj][a[i] * aj - b[i]];
    }
    for (int i = 0; i < n; i++)
        if (a[i] <= lim)
            mp[a[i]][b[i]] = 0;
    cout << ans << '\n';
}
```