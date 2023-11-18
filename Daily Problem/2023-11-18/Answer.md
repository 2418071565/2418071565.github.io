

一定存在一个时间 $T$ ，满足 $\forall t < T$，花费 $t$ 时间不能将所有节点感染；$\forall t \ge T$ ，花费 $t$ 时间可以将所有节点感染。满足单调性，可以二分答案。

那现在就要考虑如何写 $check$ 函数。

因为每个节点的子节点之间可以互相会传染，所以我们至少要对每个节点的子节点之一进行一次 $injection$ 操作。并且先对子节点数量较多的进行 $injection$ 一定是更好的。

所以我首先将所有节点的子节点个数处理出来，按降序排序，需要注意的是不要忘记根节点，它也需要一次 $injection$ 。我们将排完序的数组记为 $a[]$。

当我们花费 $m$ 时间进行感染时，我们可以 $injection$ 的节点数量也是 $m$，每一组子节点通过 $spreading$ 感染的节点数量是 $m - i$，$i$ 是在 $a[]$ 数组中的下标，因为每次 $injection$ 都会花 $1$ 秒，$injection$ 一组的子节点时，留给其他组的子节点可以 $spreading$ 的时间就少 $1$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 4e6 + 100;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 998244353;
const ll inf = 0x3f3f3f3f3f3fll;
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

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for(int i = 0;i < n - 1;++i)
	{
		int x;
		cin >> x;
		a[x]++;
	}
	a[0] = 1;
	sort(a.begin(),a.end(),greater<int>());
	function<bool(int)> check = [&](int m)
	{
		int cnt = m;
		for(int i = 0;a[i];++i)
		{
			cnt -= max(0,a[i] - m) + 1;
			m = max(0,m - 1);			
		}
		return cnt >= 0; 
	};
	int l = 1,r = 1e9;
	int ans = 1e9;
	while(l <= r)
	{
		int m = (l + r) >> 1;
		if(check(m))
		{
			ans = min(ans,m);
			r = m - 1;
		}
		else l = m + 1;
	}
	cout << ans << '\n';
}
```

