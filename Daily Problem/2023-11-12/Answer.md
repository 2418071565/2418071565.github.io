```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int MAX = 6e5 + 100;
typedef long long ll;
typedef unsigned long long ull;
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
	string s;
	cin >> s;
	if(n & 1)return cout <<"-1\n",void();
	map<char,int>mp;
	for(int i = 0;i < s.size();++i)
		mp[s[i]]++;
	for(auto& x:mp)if(x.second > n / 2)return cout << "-1\n",void();
	mp.clear();
	int l = 0,r = n - 1,sum = 0;
	while(l < r)
	{
		if(s[l] == s[r])mp[s[l]]++,sum++;
		l++,r--;
	}
	for(auto& x:mp)
	{
		if(x.second * 2 >= sum)return cout << x.second << '\n',void();
	}
	cout << (sum + 1) / 2 << '\n';
}

```