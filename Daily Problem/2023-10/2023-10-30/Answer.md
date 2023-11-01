
树形$dp$
把 $floor(coins[i] / 2)$ 看成右移操作。

一个数最多右移多少次，就变成 $0$ 了？在本题的数据范围下，这至多是 $14$ 次。

同时，右移操作是可以叠加的，我们可以记录子树中的节点值右移了多少次。

所以可以定义 $dp[i][j]$表示子树 $i$ 在已经右移 $j$ 次的前提下，最多可以得到多少积分。

用「选或不选」来思考，即是否右移：

- 不右移：答案为 $(coins[i]>>j)−k$ 加上每个子树 $ch$ 的 $dp[ch][j]$。
- 右移：答案为 $coins[i]>>(j+1)$ 加上每个子树 $ch$ 的 $dp[ch][j+1]$。

```cpp
class Solution
{
public:
	int maximumPoints(vector<vector<int>> &edges, vector<int> &coins, int k)
	{
		int n = coins.size() + 1;
		vector<vector<int>> g(n);
		for (int i = 0; i < edges.size(); ++i)
		{
			g[edges[i][0]].push_back(edges[i][1]);
			g[edges[i][1]].push_back(edges[i][0]);
		}
		vector<vector<int>> dp(n + 1, vector<int>(20));
		function<void(int, int, int)> dfs = [&](int u, int fa, int dep)
		{
			vector<int> t1(20);
			vector<int> t2(20);
			for (auto &v : g[u])
			{
				if (v == fa)continue;
				dfs(v, u, dep + 1);
				for (int i = 0; i <= min(dep, 14); ++i)
					t1[i] += dp[v][i], t2[i] += dp[v][i + 1];
			}
			for (int i = 0; i <= min(dep, 14); ++i)
				dp[u][i] = max(t1[i] + (coins[u] >> i) - k, t2[i] + (coins[u] >> (i + 1)));
		};
		dfs(0, 0, 1);
		return dp[0][0];
	}
};
```