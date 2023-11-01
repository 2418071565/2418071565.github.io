请注意，如果 $a_i$ 能被 $a_k$ 整除， $a_j$ 能被 $a_k$ 整除，那么 $\gcd(a_i, a_j)$ 也能被 $a_k$ 整除。我们来计算数组中每个 $g$ 的对数，这样 $\gcd$ 就等于 $g$ 。

为此，我们将创建 $dp_g$ - $\gcd$ 等于 $g$ 的数组对数。为此，我们需要一个计数数组-- $cnt_x$ ，即数组中数字 $x$ 的出现次数。要计算 $dp_g$ ，我们需要知道有多少个数字能被 $g$ 整除，特别是和 $s = cnt_g + cnt_{2g} + \ldots + cnt_{kg}$ ，其中 $kg \leq n$ 。因此， $\gcd$ 等于 $g$ 的数对的个数是 $\frac{s \cdot (s - 1)}{2}$ 。但是，并不是所有的 $\gcd$ 都等于 $g$ ，它可以等于 $g$ 的倍数。因此， $dp_g = \frac{s \cdot (s - 1)}{2} - dp_{2g} - \ldots - dp_{kg}$ 。这种动态程序设计可以在 $O(n \log n)$ 时间内完成计算。

现在我们来了解一下哪些 $\gcd$ 值不合适。如果数组中有一个数字 $x$ （即 $cnt_x > 0$ ），那么所有 $g$ 的倍数 $x$ 都不合适。这也可以在 $O(n \log n)$ 时间内计算出来。最后，我们只需将所有 $dp_g$ 值求和，其中数字 $g$ 不能被数组中的任何数字整除。

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

int n;
void solve()
{
	cin >> n;
	vector<ll> fg(n + 1,1);
	vector<ll> dp(n + 1);
	vector<ll> a(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		int x;
		cin >> x;
		a[x]++;
	}

	for (int i = n; i >= 1; --i)
	{
		ll sum = 0, pf = 0;
		for(int j = i;j <= n;j += i)
			sum += a[j],pf += dp[j];
		dp[i] = sum * (sum - 1) / 2 - pf;
	}

	for (int i = 1; i <= n; ++i)
	{
		if (a[i] != 0)
			for (int j = i; j <= n; j += i)
				fg[j] = false;
	}
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
		if (fg[i])ans += dp[i];
	cout << ans << '\n';
}
```