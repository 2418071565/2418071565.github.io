
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
	int T;
	for (cin >> T; T--;)
	solve();
	// f()
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

void change(char& now)
{
	now = now =='R'?'B':'R';
}

void solve()
{
	int n;
	cin >> n;
	vector<ll> a(n);
	vector<ll> b(n);
	ll sum = 0;
	ll mia = inf,mab = 0;
	for(int i = 0;i < n;++i)cin >> a[i];
	for(int i = 0;i < n;++i)
	{
		cin >> b[i];
		if(a[i] < b[i])swap(b[i],a[i]);
		mia = min(mia,a[i]);
		mab = max(mab,b[i]);
		sum += a[i] - b[i];
	}
	if(mia < mab)sum += 2 * (mab - mia);
	cout << sum << '\n';
}
```