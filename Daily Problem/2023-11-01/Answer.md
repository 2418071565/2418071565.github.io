
预处理出每一行的最长非递减子数组的长度。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 5e5 + 100;
typedef long long ll;
const int mod = 1e9 + 7;

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
	//int T;
	//for (cin >> T; T--;)
		solve();
	// f()
	cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

string ans[] = {"No\n","Yes\n"};
void solve()
{
	int n,m,q;
	cin >> n >> m;
	vector<vector<int>> g(n + 1,vector<int>(m + 1));
	for(int i = 0;i < n;++i)
		for(int j = 0;j < m;++j)
			cin >> g[i][j];
	vector<vector<int>> len(n + 1,vector<int>(m + 1));

	for(int j = m - 1;j >= 0;--j)
	{
		for(int i = n - 2;i >= 0;--i)
		{
			if(g[i][j] <= g[i + 1][j])
				len[i][j] = len[i + 1][j] + 1;
		}
	}
	for(int i = 0;i < n; ++i)
	{
		for(int j = m - 2;j >= 0;--j)
		{
			len[i][j] = max(len[i][j],len[i][j + 1]);
		}
	}
	cin >> q;
	while(q--)
	{
		int l, r;
		cin >> l >> r;
		cout << ans[l + len[l - 1][0] >= r];
	}
	
}
```