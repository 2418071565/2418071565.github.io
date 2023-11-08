
维护一个滑动窗口，满足窗口中最大值和最小值差值为$m$，且窗口中不同的元素个数有$m$，然后每个元素的个数累乘起来就是当前窗口的答案。


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


ll qpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
ll inv(ll a){
    return qpow(a,mod-2);
}


void solve()
{
	int n,m;
	cin >> n >> m;
	map<int,ll> mp;
	vector<int> a;
	for(int i = 1;i <= n;++i)
	{
		int x;
		cin >> x;
		mp[x]++;
	}
	for(auto& x:mp)
		a.push_back(x.first);
	int l = 0,r = 0;
	ll ans = 0, sum = 1;
	while(r < a.size())
	{
		while(r < a.size() && a[r] - a[l] < m)
		{
			(sum *= mp[a[r]]) %= mod;
			r++;
		}
		if(r - l == m)
			(ans += sum) %= mod;
		(sum *= inv(mp[a[l]])) %= mod;
		l++;
	}
	cout << ans << '\n';
}
```