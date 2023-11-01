

统计 a 中每个数出现了多少次，记到 cnt 数组中。

如果 x 只出现一次，那么不用改。

如果 x 出现多次，那么要改 cnt[x]-1 个数。

遍历 a，如果当前元素只剩下一个，肯定不用改。
如果还有多个。
1. 如果要改成一个比 a[i] 小的数，直接改。
2. 如果要改成一个比 a[i] 大的数：

3. 如果第一次遇到 a[i]，跳过，改后面的数。
4. 如果不是第一次遇到，一定要改。
用一个布尔数组记录跳过的数。


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
    // int T;
    // for (cin >> T; T--;)
        solve();
    // f()
    cerr << "Time Used: " << clock() - c1 << " ms\n";
    return 0;
}



int n;
bool fg[MAX];
void solve()
{
    cin >> n;
    priority_queue<int> que;
    vector<int> a(n + 1);
    vector<int> pos;
    map<int,int> mp;
    for(int i = 1;i <= n;++i)
    {
        cin >> a[i];
        mp[a[i]]++;
    }
    for(int i = 1;i <= n;++i)
    {
        if(mp[a[i]] >= 2) pos.push_back(i);
        if(mp[i] == 0) que.push(-i);
    }
    memset(fg,0,sizeof fg);
    cout << que.size() << '\n';
    for(int i = 0;i<pos.size();++i)
    {
        if(que.empty())break;
        int now = -que.top();
        que.pop();
        while( mp[a[pos[i]]] == 1||(now > a[pos[i]] && !fg[a[pos[i]]]))
        {
            fg[a[pos[i]]] = true;
            ++i;
        }
        mp[a[pos[i]]]--;
        a[pos[i]] = now;
    }
    for(int i = 1;i <= n;++i)
        cout << a[i] << " \n"[i==n];
}
```