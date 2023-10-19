[灵神的题解](https://www.luogu.com.cn/blog/endlesscheng/solution-at-arc147-c)


对左端点和右端点进行排序，左端点从小到大，右端点从大到小，让后让后让其作为最终答案的x，计算即可。

```cpp
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
const int MAX = 5e5 + 100;
typedef long long ll;
// const ll p = 998244353;
ll solve();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    clock_t c1 = clock();
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    // int T;
    // for (cin >> T; T--;)
    cout << solve() << '\n';
    // f()
    cerr << "Time Used: " << clock() - c1 << " ms\n";
    return 0;
}

int n;
struct s
{
    ll x,id;
} l[MAX], r[MAX];
bool cmp1(const s &a, const s &b) { return a.x > b.x;}
bool cmp2(const s &a, const s &b) { return a.x < b.x;}
ll solve()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> r[i].x >> l[i].x;
        r[i].id = l[i].id = i;
    }
    sort(l + 1, l + 1 + n, cmp2);
    sort(r + 1, r + 1 + n, cmp1);
    ll ans = 0, sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (r[i].x <= l[i].x) break;
        ans += (n + 1 - i * 2) * (r[i].x - l[i].x);
    }
    return ans;
}

```