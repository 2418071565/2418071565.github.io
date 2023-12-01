
$DAG$ 上的背包问题，我们设 $dp[i][j]$ 表示从 $1$ 走到 $i$ 节点走过 $j$ 个顶点花费的最少时间。

由此我们可以列出如下递推式：

$$
dp[v][j] = dp[u][j - 1] + w_{u,v}
$$

其中 $u$ 是 $v$ 节点的前驱。

在递推时，我们要保证前驱节点的状态是不会该变的，即前驱节点的前驱已经都计算完之后，才可以用前驱节点更新当前节点的答案。所以我们可以利用拓扑排序，在排序的过程中处理队列中的节点即可。

时间复杂度为 $O(n^2)$，该题会卡内存，如果 $dp$ 开 $ll$ 会 $MLE$ ，只能开 $int$

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
	//int T;
	//for (cin >> T; T--;)
	solve();
	// f()
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}


struct ED
{
	int to,w;
};

void solve()
{
	int n,m,t;
	cin >> n >> m >> t;
	vector<vector<ED>>g(n + 1);
	vector<vector<int>> dp(n + 1,vector<int>(n + 1,INT_MAX));
	vector<vector<int>> pre(n + 1,vector<int>(n + 1));
	vector<int> deg(n + 1);
	while(m--)
	{
		int u,v,w;
		cin >> u >> v >> w;
		g[u].push_back({v,w});
		deg[v]++;
	}

	queue<int> que;
	for(int i = 1;i <= n;++i)
		if(!deg[i])que.push(i);
	dp[1][1] = 0;
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		for(auto& x:g[u])
		{
			int v = x.to,w = x.w;
			deg[v]--;
			for(int i = 1;i <= n;++i)
			{
				if(dp[u][i - 1] == INT_MAX)continue;
				if(dp[u][i - 1] + w > t)continue;
				if(dp[v][i] > dp[u][i - 1] + w)
				{
					pre[v][i] = u;
					dp[v][i] = dp[u][i - 1] + w;
				}
			}
			if(!deg[v])
				que.push(v);
		}
	}
	for(int i = n;i >= 1;--i)
	{
		if(dp[n][i] <= t)
		{
			cout << i << '\n';
			vector<int> ans;
			int now = n;
			while(now)
			{
				ans.push_back(now);
				now = pre[now][i];
				i--;
			}
			for(int i = ans.size() - 1;i >= 0;--i)
				cout << ans[i] << " \n"[i == 0];
			return;
		}
	}
}
```