
先将数组 $a$ 拆位，考虑每一个二进程位对答案的献，对于第 $i$ 来说，只有一个区间中 $i$ 位有奇数个 $1$ 时才会对答案有贡献。

我可以维护每一位 $1$ 个数的前缀和 $pf[]$ ，只有 $pf[r] \oplus pf[l - 1]=1$ 时该位会对答案有贡献，那么我们可以记录 $pf[x]=1$ 前面 $pf[y]=0$ 的距离和， $pf[x]=0$ 前面 $pf[y]=1$ 的距离和。

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int MAX = 6e5 + 100;
typedef long long ll;
const ll mod = 998244353;
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
	int n;
	cin >> n;
	vector<ll> a(n + 1);
	for(int i = 1;i <= n;++i)cin >> a[i];
	ll ans = 0;
	for(int i = 0;i <= 31;++i)
	{
		ll res = 0;
		ll now = 0,cnt0 = 1,cnt1 = 0,dis0 = 0,dis1 = 0;
		for(int j = 1;j <= n;++j)
		{
			now ^= (a[j] >> i) & 1;
			dis1 += cnt1,dis0 += cnt0;
			if(now == 1)cnt1++,(res += dis0) %= mod;
			else cnt0++,(res += dis1) %= mod;
		}
		(ans += (1ll << i) % mod * res % mod) %= mod;
	}
	cout << ans << '\n';
}
```