

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
	int T;
	for (cin >> T; T--;)
		solve();
	// f()
	cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}




void solve()
{
	ll n,c;
	cin >> n >> c;
	vector<ll> a(n + 1);
	vector<pair<ll,ll>> b(n + 1);
	for(ll i = 1;i <= n;++i)
	{
		cin >> a[i];
		b[i].first = i * c - a[i];
		b[i].second = i;
	}
	sort(b.begin() + 2,b.end());
	ll sum = a[1];
	for(ll i = 2;i <= n;++i)
	{
		if(sum >= b[i].first)sum += a[b[i].second];
		else 
		{
			cout << "No\n";
			return;
		}
	}
	cout << "Yes\n";
}
```