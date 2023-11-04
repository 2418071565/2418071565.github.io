我们发现，一段连续的非$0$数可以花费一个金币把它们全染成红色，如果这段数里有$2$就可以把两端的$0$也染红，否则只能把一端的$0$染红。

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int MAX = 1e6 + 100;
typedef long long ll;

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
	// int T = read();
	// for (; T--;)
	solve();
	// f()
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}
int ans = 0;
void op(vector<int> &now)
{
	bool is2 = 0;
	int cnt = 0, c0 = 0;
	for (int j = 0; j < now.size(); ++j)
	{
		if (now[j] == 0)c0++, cnt += j ? 1 : 0;
		if (now[j] == 2)is2 = 1;
	}
	if (now.back())cnt++;
	if (cnt >= c0 || is2)ans += cnt;
	else ans += cnt + 1;
	now.clear();
}

void solve()
{
	int n,cnt0 = 0;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	vector<int> now;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i] == 0)cnt0++;
		else cnt0 = 0;
		if (cnt0 == 2)
		{
			cnt0 = 0;
			op(now);
		}
		now.push_back(a[i]);
	}
	op(now);
	cout << ans << '\n';
}
```