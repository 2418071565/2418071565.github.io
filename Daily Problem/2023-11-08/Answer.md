
将$b$倒叙排列，再与$a$和并即可，合并时优先放大的。

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
	int n,m;
	cin >> n >> m;
	vector<int>a(n);
	vector<int> b(m);
	for(int i = 0;i < n;++i)cin >> a[i];
	for(int i = 0;i < m;++i)cin >> b[i];
	sort(b.begin(),b.end(),greater<int>());
	int la = 0,lb = 0;
	while(la < a.size() && lb < b.size())
	{
		if(a[la] > b[lb])cout << a[la++] << ' ';
		else cout << b[lb++] << ' ';
	}						
	while(la < a.size())cout << a[la++] << ' ';
	while(lb < b.size())cout << b[lb++] << ' ';
	cout << '\n';
}
```