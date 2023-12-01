```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e6 + 100;
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
	for(cin >> T;T--;)
	solve();

	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}


void solve()
{
	int n;
	cin >> n;
	vector<int>ls(n + 1),rs(n + 1);
	vector<char> d(n + 1);
	for(int i = 1;i <= n;++i)
		cin >> d[i];
	for(int i = 1;i <= n;++i)
		cin >> ls[i] >> rs[i];
	
	function<int(int)> dfs = [&](int u)
	{
		if(u == 0)return INT_MAX - 10;
		if(ls[u] == rs[u])return 0;
		return min(dfs(ls[u]) + int(d[u] != 'L'),dfs(rs[u]) + int(d[u] != 'R'));
	};
	cout << dfs(1) << '\n';
}	
```