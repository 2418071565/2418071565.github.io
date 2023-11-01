
**后缀和**;考虑每个b数组的开始和结束位置。

对于开始位置如果它之前不存在与它相同的数，那么它就可以作为b数组的开始。

对应结束位置，如果它之后没有与它相同的数，那么它就可以作为b数组的结尾。

用后缀和数组处理出每个位置之后可以作为结束位置的个数，累加即可得到答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 5e5 + 100;
typedef long long ll;
const ll mod = 1e9 + 7;

void solve();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // clock_t c1 = clock();
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    int T;
    for (cin >> T; T--;)
        solve();
    // f()
    // cerr << "Time Used: " << clock() - c1 << " ms\n";
    return 0;
}

int n;
int a[MAX];
bool l[MAX];
void solve()
{
    cin >> n;
    for(int i = 1;i <= n;++i)
        cin>>a[i];

    set<int> lst,rst;
    vector<ll> ed(n + 2,0);
    for(int i = 1;i <= n;++i)
    {
        if(lst.find(a[i]) == lst.end())
            l[i] = true,lst.insert(a[i]);
        else l[i] = false;
        if(rst.find(a[n - i + 1]) == rst.end())
            ed[n - i + 1] = ed[n - i + 2] + 1,rst.insert(a[n - i + 1]);
        else ed[n - i + 1] = ed[n - i + 2];
    }
    ll ans = 0;
    for(int i = 1;i <= n;++i)
        if(l[i]) ans += ed[i];
    cout<< ans << '\n';
}
```