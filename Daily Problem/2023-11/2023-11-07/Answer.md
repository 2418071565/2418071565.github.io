

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int MAX = 6e5 + 100;
typedef long long ll;
const ll mod = 1e9 + 7;
void solve();
ll fib[50];
void init()
{
	fib[1] = 1;
	fib[2] = 2;
	for(int i = 3;i <= 45; ++i)
		fib[i] = fib[i - 1] + fib[i - 2];
}
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
	init();
	for (cin >> T; T--;)
		solve();
	// f()
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}



void solve()
{
	ll n,x,y;
	cin >> n >> x >> y;
	ll l = fib[n],r = fib[n + 1];
	while(n > 1)
	{
		if(y > fib[n]) y -= fib[n];
		swap(x,y);
		n--;
	}
	if(x == 1 && (y == 1 || y == 2))cout << "Yes\n";
	else cout << "No\n";
}
```