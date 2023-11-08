

二分答案+拓扑排序

每次check时重新建图，只将$a[i] <= m$的节点加入到新图中。利用拓朴排序检查改图中是否有环，如果有环就返回$true$，没有环就检查图中是否有长于$k$的链，有则返回$true$，没有就返回$false$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5 + 100;
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
	// ll T;
	// for (cin >> T; T--;)
	solve();
	// f()
	cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

void solve()
{
	ll n, m, k;
	cin >> n >> m >> k;
	vector<vector<int>> G(n + 1);
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
	}
	function<bool(ll)> check = [&](ll m)
	{
		vector<vector<int>> g(n + 1);
		vector<int> deg(n + 1);
		vector<int> dep(n + 1, 1);
		for (int u = 1; u <= n; ++u)
		{
			if (a[u] <= m)
			{
				for (auto &v : G[u])
				{
					if (a[v] <= m)
						g[u].push_back(v), deg[v]++;
				}
			}
		}

		stack<int> st;
		for (int i = 1; i <= n; ++i)
			if (!deg[i])
				st.push(i);

		while (!st.empty())
		{
			int u = st.top();
			st.pop();
			for (auto &v : g[u])
			{
				dep[v] = max(dep[v], dep[u] + 1);
				deg[v]--;
				if (!deg[v])st.push(v);
			}
		}

		for (int i = 1; i <= n; ++i)
		{
			if(a[i] > m)continue;
			if (deg[i] || dep[i] >= k)
				return true;
		}
		return false;
	};

	ll l = 0, r =INT_MAX;
	ll ans = 1e15;
	while (l <= r)
	{
		ll m = (l + r) >> 1;
		if (check(m))
		{
			r = m - 1;
			ans = min(ans, m);
		}
		else l = m + 1;
	}
	if(r == INT_MAX) return cout << "-1\n",void();
	cout << ans << '\n';
}
```