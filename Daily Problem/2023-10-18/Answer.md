[灵神的题解](https://www.luogu.com.cn/blog/endlesscheng/solution-at-arc147-c)

让我们按照从小到大的顺序排列 s的所有符号，并构造一个答案 tmax。

设当前符号为 x。

如果至少有 2剩余符号等于 x，我们应该将它们添加到 tmax的当前前缀和后缀中并继续。

如果最多还有一个符号，则剩余 y（在 s中还有 x和 c次 y）我们应该添加 ⌈c2⌉符号 y，符号 x和 ⌊c2⌋符号 y到前缀 tmax和中断。

否则，我们应该将 s的所有剩余符号（不包括 x）按排序顺序添加到 tmax的前缀中，然后添加符号 x。



```cpp
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
const int MAX = 5e5 + 100;
typedef long long ll;
// const ll p = 998244353;
string solve();
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
        cout << solve() << '\n';
    // f()
    cerr << "Time Used: " << clock() - c1 << " ms\n";
    return 0;
}

string s;

string solve()
{
    cin >> s;
    int n = s.size();
    int mp[130] = {0};
    char ma = 0;
    for (int i = 0; i < n; ++i)
        mp[s[i]]++,ma = max(ma,s[i]);

    string ans(n, ' ');
    int l = 0, r = n - 1;
    char now = ' ';
    bool fg = true;
    for (int i = 'a'; i <= 'z'; ++i)
    {
        if (!mp[i]) continue;
        if (now != ' ' && i != ma)
        {
            ans[r--] = now;
            mp[now]--;
            fg = false;
            break;
        }
        int cnt = mp[i] / 2;
        while (cnt--)
        {
            ans[l++] = i;
            ans[r--] = i;
        }
        if (mp[i] & 1)now = i;
        mp[i] -= mp[i] / 2 * 2
    }
    if (fg)
    {
        for (int i = 'a'; i <= 'z'; ++i)
            if (mp[i])
            {
                ans[r--] = i;
                mp[i]--;
                break;
            }
    }
    for (int i = 'a'; i <= 'z'; ++i)
        while (mp[i]--)
            ans[l++] = i;
    return ans;
}

```