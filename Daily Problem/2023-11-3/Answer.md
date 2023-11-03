
首先当一个序列全是整数或全是负数时，我们只需要将序列正向累加或反向累加即可完成非递减，花费$n-1$步，那么我们就可以想办法构造一个全是整数或全是负数的序列。

对于一个有正有负的序列，如果我们要将一个序列构造成全正的，就要找到一个比所有负数都大的整数，如果没有我们就自己构造一个，然后将所有负数加成正数；构造负数序列也是类似的。

这样我们只要在构造正数序列和负数序列里找一个步数不超过$31$的输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 5e4 + 100;
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
	ll T;
	for (cin >> T; T--;)
		solve();
	// f()
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n + 1);
	vector<pair<int,int>> z, f;
	int ma = 0, mi = 0;
	int mai, mii;
	int cntf = 0, cntz = 0;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		if (mi > a[i])mi = a[i], mii = i;
		if (ma < a[i])ma = a[i], mai = i;
		if (a[i] > 0)cntz++;
		if (a[i] < 0)cntf++;
	}
	if (ma < abs(mi) && ma)
		while (ma <= abs(mi))
			z.push_back({mai,mai}),ma += ma;
	else if (ma > abs(mi) && mi)
		while (abs(mi) <= ma)
			f.push_back({mii,mii}),mi += mi;

	if(ma && cntf + n - 1 + z.size() <= 31)
	{
		for(int i = 1;i <= n;++i)
			if(a[i] < 0)z.push_back({i,mai});
		for(int i = 1;i < n;++i)
			z.push_back({i + 1,i});
		cout << z.size() << '\n';
		for(int i = 0;i < z.size();++i)
			cout << z[i].first << ' '<< z[i].second << "\n";
	}
	else if(mi && cntz + n - 1 + f.size() <= 31)
	{
		for(int i = 1;i <= n;++i)
			if(a[i] > 0)f.push_back({i,mii});
		for(int i = n;i > 1;--i)
			f.push_back({i - 1,i});
		cout << f.size() << '\n';
		for(int i = 0;i < f.size();++i)
			cout << f[i].first << ' '<< f[i].second << "\n";
	}
	else cout << "0\n";
}
```