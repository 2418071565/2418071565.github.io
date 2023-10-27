

二分答案即可

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
struct s
{
	ll c,d;
}a[MAX];
void solve()
{
	cin >> n;
	bool fg = true;
	for(int i = 1;i <= n;++i)
	{
		cin >> a[i].c >> a[i].d;
		if(a[i].d == 2)fg = false; 
	}
	if(fg)
	{
		cout << "Infinity\n";
		return;
	}

	function<int(int)> check = [&](int m)
	{
		for(int i = n;i > 0;--i)
		{
			m -= a[i].c;
			if(a[i].d == 2 && m > 1899)return 1;
			if(a[i].d == 1 && m < 1900)return -1;
		}
		return  0;
	};

	ll l = -1e9,r = 1e9;
	ll ans = INT_MIN;
	while (l <= r)
	{
		ll m = (l + r) >> 1;
		int k = check(m);
		if(k <= 0)
		{
			if(k == 0)ans = max(ans,m);
			l = m + 1;
		}
		else r = m - 1;
	}
	if (ans == INT_MIN)cout << "Impossible\n";
	else cout << ans <<'\n';
}
```