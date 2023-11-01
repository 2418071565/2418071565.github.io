
把 a 和 b 绑在一起，按照 a[i] 从小到大排序。
枚举 m=a[i]，所有下标 <=i 的 b[i] 就不用选了，所以 s 等于 b[i+1] 之后的所有元素之和。


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
    clock_t c1 = clock();
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    int T;
    for (cin >> T; T--;)
        solve();
    // f()
    cerr << "Time Used: " << clock() - c1 << " ms\n";
    return 0;
}



struct s{ ll a,b;};
int n;
void solve()
{
    cin >> n;
    vector<s> p(n + 2);
    for(int i = 1;i <= n;++i) cin >> p[i].a;
    for(int i = 1;i <= n;++i) cin >> p[i].b;
    sort(p.begin() + 1,p.end() - 1,[](auto& a,auto& b){return a.a > b.a;});
    ll pf = 0;
    ll ans = 0,i;
    for(i = 1;i <= n;++i)
    {
        if(pf + p[i].b > p[i].a)break;
        pf += p[i].b;
    }
    cout << max(p[i].a,pf) << '\n';
}
```