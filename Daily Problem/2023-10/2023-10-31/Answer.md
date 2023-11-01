
[题解链接](https://codeforces.com/blog/entry/116642)

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
	int T;
	for (cin >> T; T--;)
		solve();
	// f()
	cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}


void solve()
{
	int n;
	cin >> n;
	vector<ll> a(n);
	ll sum = 0,ma = 0;
	for(int i = 0;i < n; ++i)
	{
		cin >> a[i];
		sum += a[i];
		ma = max(ma,a[i]);
	}
	if(sum%n)return cout << "No\n",void();
	ll t = sum / n;
	unordered_map<ll,ll>mp;
	for(int i = 0;i <= 31;++i)mp[(1 << i)] = i;
	vector<int>bit(31);
	for(int r = 0;r < n; ++r)
	{
		if(a[r] == t)continue;
		bool fg = true;
		for(int i = 0;(1 << i) <= ma;++i)
		{
			ll d = t - a[r] + (1 << i);
			if(d < 0)continue;
			if(mp[d] || d == 1)
			{
				fg = false;
				bit[mp[d]]++,bit[i]--;
				break;
			}
		}
		if(fg)return cout << "No\n",void();
	}
	for(int i = 0;i<=30;++i)
		if(bit[i])return cout << "No\n" ,void();
	cout << "Yes\n";
}
```