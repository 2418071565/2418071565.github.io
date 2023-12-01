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
	for (cin >> T; T--;)
		solve();

	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

struct A
{
	int id, a;
	bool operator<(A &e) { return a < e.a; }
};

void solve()
{
	int n, x;
	cin >> n >> x;
	vector<A> a(n);
	vector<int> b(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i].a, a[i].id = i;
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int now = 0;
	vector<int> ans(n);
	for (int i = n - x; i < n; ++i)
		ans[a[i].id] = b[now++];
	for (int i = 0; i < n - x; ++i)
		ans[a[i].id] = b[now++];
	int cnt = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i].a > ans[a[i].id])
			cnt++;
	}
	if (cnt != x)
		return cout << "No\n", void();
	cout << "Yes\n";
	for (int i = 0; i < n; ++i)
		cout << ans[i] << " \n"[i == n - 1];
}
```