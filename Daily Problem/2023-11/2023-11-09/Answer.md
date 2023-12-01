

$n$只有$5000$，暴力枚举每个位置做值域左端点和右端点的结果，记录最大值即可。

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int MAX = 6e5 + 100;
typedef long long ll;
const ll mod = 1e9 + 7;
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


void solve()
{
	int n,d;
	cin >> n >> d;
	vector<ll> a(n);
	for(int i = 0;i < n;++i) cin >> a[i];
	ll ans = 0;
	for(int i = 0;i < n;++i)
	{
		ll r = a[i],nowr = 0,nowl = 0;
		for(int j = 0;j < n - 1;++j)
		{
			ll nl = max(r - d,min(r,min(a[j],a[j + 1])));
			ll nr = min(r,max(r - d,max(a[j],a[j + 1])));
			nowr += abs(nr - nl);
			nl = max(r,min(r + d,min(a[j],a[j + 1])));
			nr = min(r + d,max(r,max(a[j],a[j + 1])));	
			nowl += abs(nr - nl);
		}
		ans = max(ans,max(nowl,nowr));
	}
	cout << ans << '\n';
}
```