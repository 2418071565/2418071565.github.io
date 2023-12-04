```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e6 + 100;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 998244353;
const ll inf = 0x3f3f3f3f3f3fll;
const double pi = 3.1415926535;
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
	// int T;
	// for (cin >> T; T--;)
	solve();
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

void solve()
{
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	map<pair<int, int>, vector<int>> mp;
	map<int, pair<int, int>> a;
	a[0] = {0,0};
	mp[{0,0}].push_back(0);
	int nx = 0, ny = 0;
	for (int i = 0; i < n; ++i)
	{
		if (s[i] == 'U')ny++;
		if (s[i] == 'R')nx++;
		if (s[i] == 'L')nx--;
		if (s[i] == 'D')ny--;
		mp[{nx, ny}].push_back(i + 1);
		a[i + 1] = {nx, ny};
	}
	for (int i = 0; i < q; ++i)
	{
		int x, y, l, r;
		cin >> x >> y >> l >> r;
		auto pos = lower_bound(mp[{x, y}].begin(), mp[{x, y}].end(), l);
		if (mp[{x, y}].size() != 0)
		{
			if (pos != mp[{x, y}].begin())
			{
				cout << "Yes\n";
				continue;
			}
			pos = upper_bound(mp[{x, y}].begin(), mp[{x, y}].end(), r);
			if (pos != mp[{x, y}].end())
			{
				cout << "Yes\n";
				continue;
			}
		}
		double dx = (a[l - 1].first + a[r].first) / 2.0;
		double dy = (a[l - 1].second + a[r].second) / 2.0;
		x = x + 2 * (dx - x);
		y = y + 2 * (dy - y);
		pos = lower_bound(mp[{x, y}].begin(), mp[{x, y}].end(), l - 1);
		if (pos != mp[{x, y}].end() && *pos <= r)
		{
			cout << "Yes\n";
			continue;
		}
		cout << "No\n";
	}
}
```