
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
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	// clock_t c1 = clock();
#ifdef LOCAL
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	//int T;
	//for(cin >> T;T--;)
	solve();

	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}



void solve()
{
	int n,x;
	cin >> n;
	vector<int> a(n + 1);
	vector<int> r(n + 2),l(n + 1);
	for(int i = 1;i <= n;++i)
	{
		cin >> a[i];
		if(a[l[i - 1]] - l[i - 1] < a[i] - i)
			l[i] = i;
		else l[i] = l[i - 1];
	}
	r[n] = n;
	for(int i = n - 1;i >= 1;--i)
	{
		if(a[r[i + 1]] + r[i + 1] < a[i] + i)
			r[i] = i;
		else r[i] = r[i + 1];
	}
	int ans = 2e9;
	for(int i = 1;i <= n;++i)
	{
		int lma,rma;
		if(r[i] == i)rma = max(a[r[i]],a[r[i + 1]] + r[i + 1] - 1);
		else rma = a[r[i]] + r[i] - 1;
		if(l[i] == i)lma = max(a[l[i]],a[l[i - 1]] + n - l[i - 1]);
		else lma = a[l[i]] + n - l[i];
		ans = min(ans,max(rma,lma));
	}
	cout << ans << '\n';
}
```