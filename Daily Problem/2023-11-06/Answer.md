
我们构造的$q$，有以下几种情况是满足条件的：
- $n = 1$时，可选任意两个相同的数字
- $n = 2$时，可以全是$2$，也可以是下面的情况
- $q$全为$0$
- $n$为偶数时，有 $n-1$ 个 $-1$ 和一个 $n$。

然后选择以上几种情况中距离最小的即可。


```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int MAX = 1e6 + 100;
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
	int T;
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
	vector<ll> a(2 * n + 1);
	for(int i = 1;i <= 2 * n;++i)cin >> a[i];
	if(n == 1)return cout << abs(a[2] - a[1]) << '\n',void();
	ll ans = accumulate(a.begin() + 1,a.end(),0ll,[](ll& x,ll& y){return x + abs(y);});
	if(n == 2) ans = min(accumulate(a.begin() + 1,a.end(),0ll,[](ll& x,ll& y){return x + abs(y - 2);}),ans);
	if(n & 1)return cout << ans << '\n',void();
	ll nsum = accumulate(a.begin() + 1,a.end(),0ll, [](ll& x,ll& y){return x + abs(y + 1);});
	for(int i = 1;i <= 2 * n;++i) ans = min(ans,nsum - abs(a[i] + 1) + abs(a[i] - n));
	cout << ans << '\n';
}
```