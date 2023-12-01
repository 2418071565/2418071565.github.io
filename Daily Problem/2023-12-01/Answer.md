表示 $s[l,r]$ 是 $l$ 至 $r$ 子数组的和。

如果存在总和为 $v\ge 2$ 的子数组，我们可以找到总和为 $v-2$ 的子数组。

证明假设 $s[l,r]=v$ ，考虑 3 种情况：

- $a[l]=2$ , 我们有 $s[l+1,r]=v-2$ .
- $a[r]=2$ , 我们有 $s[l,r-1]=v-2$ .
- $a[l]=a[r]=1$ ，我们有 $s[l+1,r-1]=v-2$ 。

因此，要检查是否存在总和等于 $v$ 的子数组，我们可以找出与 $v$ 奇偶性相同的最大子数组总和，并与 $v$ 进行比较。

在 $(s[1,n]-v)\%2=0$ 显而易见的情况下，假设出现相反的情况。如果数组 $a$ 充满了 $2$ /-s，那么答案就是 $\texttt{NO}$ 。否则，假设 $x$ 和 $y$ 是 $a$ 中第一个 $1$ 和最后一个 $1$ 的位置。任何包含 $l\le x\le y\le r$ 的子数组都会与 $v$ 具有不同的奇偶性。因此，我们将比较 $\max(s[x+1, n],s[1,y-1])$ 和 $v$ 得出答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e6 + 100;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 998244353;
const ll inf = 0x3f3f3f3f3f3fll;
const double pi = 3.1415926535;
void solve();
mt19937 rng((unsigned int)chrono::steady_clock::now().time_since_epoch().count());

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



void solve()
{
	int n,q;
	cin >> n >> q;
	vector<int> a(n + 1);
	vector<int> f(n + 1);
	function<int(int)> lowbit = [&](int x)
	{
		return x & -x;
	};
	function<void(int,int)> update = [&](int x,int d)
	{
		for(;x <= n;x += lowbit(x))f[x] += d;
	};
	function<int(int)> ask = [&](int x)
	{
		int sum = 0;
		for(;x > 0;x -= lowbit(x))
			sum += f[x];
		return sum;
	};

	set<int> s;
	for(int i = 1;i <= n;++i)
	{
		cin >> a[i];
		update(i,a[i]);
		if (a[i] == 1)
			s.insert(i);
	}
	while(q--)
	{
		int op,x,k;
		cin >> op >> x;
		if(op == 1)
		{
			if((s.size() & 1) == (x & 1))
			{
				if(ask(n) >= x)
					cout << "Yes\n";
				else 
					cout << "No\n";
			}
			else
			{
				if(s.empty())
				{
					cout << "No\n";
					continue;
				}
				int ma = max(ask(n) - ask(*s.begin()),ask(*s.rbegin() - 1));
				if(ma >= x) 
					cout << "Yes\n";
				else 
					cout << "No\n";
			}
		}
		else
		{
			cin >> k;
			if(a[x] == k)continue;
			update(x,k - a[x]);
			a[x] = k;
			if(k == 1)s.insert(x);
			else s.erase(x);
		}
	}
}

```