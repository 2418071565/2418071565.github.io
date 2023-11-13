
我们发现把一个区间排完序后，这个$01$串可以分成以下这些部分
$$
s[1,l-1]+s_0+s_1+s[r+ 1,n]
$$
$s_0$表示只有$0$的串，$s_1$表示只有$1$的串。$s[1,l-1],s[r+1,n]$表示没有被排序的位置。

现在我们只需要知道一个排序区间里$0,1$的个数，就可以拼出排序完的字符串。我们可以用进制哈希，用进制哈希值表示拼出的串。

我们可以提前处理好各个长度的$s_0,s_1$的哈希值，对于每个排序将拼出的字符串哈希值插入到$set$里，最后输出$set$大小即可。

[字符串哈希详解](../../String/String%20Hash/)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e6 + 100;
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

const ll p = 31;
struct SHash
{
	ull pM[MAX];		// 记录两组P^i
	ull hsh[MAX];		// 记录两组前缀哈希值
	int tot;			// 记录当前维护字符串长度

	SHash()
	{
		tot = 0;
		for (int i = 0; i < 2; ++i)
		{
			pM[0] = 1;
			hsh[0] = 0;
		}
	}
	void add(char ch)
	{
		++tot;
		pM[tot] = pM[tot - 1] * p;
		hsh[tot] = (hsh[tot - 1] * p + ull(ch));
	}
	ull getHash(int l, int r)
	{
		if(l > r)return 0;
		ull h;
		h = hsh[r] - hsh[l - 1] * pM[r - l + 1];
		return h;
	}
};


SHash now,c0,c1;
void solve()
{
	int n,m;
	cin >> n >> m;
	set<ll> st;
	string s;
	cin >> s;
	new (&now)SHash();
	new (&c0)SHash();
	new (&c1)SHash();
	vector<int>cnt(n + 1);
	for(int i = 1;i <= n;++i)
	{
		if(s[i - 1]=='1')
			cnt[i] = cnt[i - 1] + 1; 
		else cnt[i] = cnt[i - 1];
	}
	for(char& ch:s)now.add(ch);
	for(int i = 0;i < n;++i)c0.add('0');
	for(int i = 0;i < n;++i)c1.add('1');
	while(m--)
	{
		int L,R;
		cin >> L >> R;
		int cnt1 = cnt[R] - cnt[L - 1];
		int cnt0 = R - L + 1 - cnt1;
		ull l = now.getHash(1,L - 1);
		ull m0 = c0.getHash(1,cnt0);
		ull m1 = c1.getHash(1,cnt1);
		ull r = now.getHash(R + 1,n);
		ull newh = l * now.pM[n - L + 1] + m0 * now.pM[n - L - cnt0 + 1] + m1 * now.pM[n - R] + r;
		st.insert(newh);
	}
	cout << st.size() << '\n';
}
```