Exercise
=================
|题目|难度|AC|知识|
|:-:|:-:|:-:|:-:|
|[LC.1316](https://leetcode.cn/problems/distinct-echo-substrings/description/)|困难|√|暴力+字符串哈希|
|[CF1200E](https://codeforces.com/contest/1200/problem/E)|2000|√|暴力+字符串哈希|
|[CF1849C](https://codeforces.com/problemset/problem/1849/C)|1600|√|暴力+字符串哈希|

#### LC.1316

```cpp
typedef long long ll;
const int MAX = 3000;
const ll p[] = {29, 31};
const ll M[] = {int(1e9 + 9), 998244353};
struct SHash
{
	ll pM[2][MAX];
	ll hsh[2][MAX];
	int tot;
	SHash()
	{
		tot = 0;
		for(int i = 0;i < 2;++i)
		{
			pM[i][0] = 1;
			hsh[i][0] = 0;
		}
	}

	//
	void exend(char ch)
	{
		++tot;
		for(int i = 0;i < 2;++i)
		{
			pM[i][tot] = pM[i][tot - 1] * p[i] % M[i];
			hsh[i][tot] = (hsh[i][tot - 1] * p[i] + ll(ch)) % M[i];
		}
	}

	// 获取哈希值对
	// hsh[l,r] = hsh[r] - hsh[l - 1] * pM[r - l + 1]
	pair<ll,ll> getHash(int l,int r)
	{
		pair<ll,ll>h;
		h.first = (hsh[0][r] - hsh[0][l - 1] * pM[0][r - l + 1]) % M[0];
		(h.first += M[0]) %= M[0];
		h.second = (hsh[1][r] - hsh[1][l - 1] * pM[1][r - l + 1]) % M[1];
		(h.second += M[1]) %= M[1];
		return h;
	}
};


class Solution {
public:
    int distinctEchoSubstrings(string text) {
        SHash t;
        for(char& ch:text)t.exend(ch);
        int n = text.size();
        set<pair<ll,ll>>st;
        for(int i = 1;i <= n;++i)
        {
            for(int j = i;j <= n;++j)
            {
                int len = j - i + 1;
                if(j + len > n)break;
								pair<ll,ll> l = t.getHash(i,j);
								pair<ll,ll> r = t.getHash(j + 1,j + len);
                if(l == r)
									st.insert(l);
            }
        }
        return st.size();
    }
};
```

#### CF1200E
```cpp
#include <bits/stdc++.h>
#include <unordered_map>
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
	// int T;
	// for (cin >> T; T--;)
	solve();
	// f()
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

const ll p[] = { 29, 31 };
const ll M[] = { int(1e9 + 9), 998244353 };
struct SHash
{
	ll pM[2][MAX];		// 记录两组P^i
	ll hsh[2][MAX];		// 记录两组前缀哈希值
	int tot;			// 记录当前维护字符串长度

	// 初始化
	SHash()
	{
		tot = 0;
		for (int i = 0; i < 2; ++i)
		{
			pM[i][0] = 1;
			hsh[i][0] = 0;
		}
	}

	// 添加维护的字符
	void add(char ch)
	{
		++tot;
		// 双哈希的预处理
		for (int i = 0; i < 2; ++i)
		{
			pM[i][tot] = pM[i][tot - 1] * p[i] % M[i];
			hsh[i][tot] = (hsh[i][tot - 1] * p[i] + ll(ch)) % M[i];
		}
	}

	// 获取哈希值对
	// hsh[l,r] = hsh[r] - hsh[l - 1] * pM[r - l + 1]
	pair<ll, ll> getHash(int l, int r)
	{
		pair<ll, ll>h;
		// 计算第一个哈希值
		h.first = (hsh[0][r] - hsh[0][l - 1] * pM[0][r - l + 1]) % M[0];
		(h.first += M[0]) %= M[0];
		// 计算第二个哈希值
		h.second = (hsh[1][r] - hsh[1][l - 1] * pM[1][r - l + 1]) % M[1];
		(h.second += M[1]) %= M[1];
		return h;
	}
};


SHash now,tmp;
void solve()
{
	int n;
	cin >> n;
	string ans;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		new (&tmp)SHash();
		for (char& ch : s)tmp.add(ch);
		int mi = min(ans.size(), s.size());
		int nlen = 0;
		for (int len = mi; len >= 1; --len)
		{
			if (now.getHash(ans.size() - len + 1, ans.size()) == tmp.getHash(1,len))
			{
				nlen = len;
				break;
			}
		}
		for (int j = nlen; j < s.size(); j++)ans.push_back(s[j]), now.add(s[j]);
	}
	cout << ans << '\n';
}
```

#### CF1849C

```cpp
#include <bits/stdc++.h>
#include <unordered_map>
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