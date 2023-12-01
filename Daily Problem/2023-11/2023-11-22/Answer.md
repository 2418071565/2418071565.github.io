
二分答案，判断每个位置再加 $mid$ 的情况下，能不能满足非递减，并且每个位置都尽量小。

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
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);
	// clock_t c1 = clock();
#ifdef LOCAL
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	// int T;
	// for(cin >> T;T--;)
	solve();

	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}


void solve()
{
	int n,m;
	cin >> n >> m;
	vector<int> a(n + 1);
	int ans = INT_MAX;
	for(int i = 1 ;i <= n;++i)cin >> a[i];
	function<bool(int)> check = [&](int mid)
	{
		vector<int> ta(a);
		for(int i = 1;i <= n;++i)
		{
			if(ta[i] < ta[i - 1])
			{
				int now = ta[i] + mid;
				if(now >= m) now = m - 1; 
				if(now < ta[i - 1])return false;
				ta[i] = ta[i - 1];
			}
			else if(ta[i] + mid >= ta[i - 1] + m)
					ta[i] = ta[i - 1];
		}
		return true;
	};
	int l = 0,r = m;
	while(l <= r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			ans = min(ans,mid);
			r = mid - 1;
		}
		else l = mid + 1; 
	}
	cout << ans << '\n';
}
```