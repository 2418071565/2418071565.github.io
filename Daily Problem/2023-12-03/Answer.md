线段树维护区间最大字段和

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e6 + 100;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 998244353;
const ll inf = 0x3f3f3f3f3f3fll;
const double pi = 3.1415926535;
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
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

struct	S
{
	int l, r;
	ll sum;
	ll ls,rs,ms;
	S operator+(const S& b)const
	{
		S res;
		res.sum = sum + b.sum;
		res.ls = max(ls,sum + b.ls);
		res.rs = max(b.rs,b.sum + rs);
		res.ms = max(rs + b.ls,max(ms,b.ms));
		res.l = l;
		res.r = b.r;
		return res;
	}
} f[MAX << 2];
// 求左右子节点的函数和区间折半的函数
inline int ls(int k) { return k << 1; }
inline int rs(int k) { return k << 1 | 1; }
inline int md(int l, int r) { return (l + r) >> 1; }
int n, m;
// 从下向上传递区间值
void push_up(int k)
{
	f[k] = f[ls(k)] + f[rs(k)];
}

// 递归的构建线段树
void build(int k, int l, int r)
{
	f[k].l = l, f[k].r = r; 
	if (l == r)
	{
		f[k].sum = f[k].ls = f[k].rs = f[k].ms = 0;
		return;
	}
	int m = md(l, r); // 分治：折半
	build(ls(k), l, m);
	build(rs(k), m + 1, r);
	push_up(k);
}


// 区间修改
void update(int k, int pos, ll x)
{
	if (f[k].l == f[k].r)
	{
		f[k].sum += x;
		f[k].ls += x;
		f[k].rs += x;
		f[k].ms += x;
		return;
	}
	int m = md(f[k].l, f[k].r);
	if (pos <= m)update(ls(k), pos, x);
	if (pos > m)update(rs(k), pos, x);
	push_up(k);					
}

S ask(int k, int l, int r)
{
	if (l <= f[k].l && r >= f[k].r)
		return f[k];
	int m = md(f[k].l, f[k].r);
	S res;
	if (r <= m)res = ask(ls(k), l, r);
	else if (l > m)res = ask(rs(k), l, r);
	else res = ask(ls(k), l, m) + ask(rs(k), m + 1, r);
	return res;
}


struct CH
{
	int pos, s, x;
};

struct Q
{
	int k, s, t, id;
};



void solve()
{
	cin >> n >> m;
	vector<CH> change;
	for (int i = 0; i < m; ++i)
	{
		int l, r, x;
		cin >> l >> r >> x;
		change.push_back({l, i + 1, x});
		change.push_back({r + 1, i + 1, -x});
	}
	int qq;
	cin >> qq;
	vector<Q> q(qq);
	for (int i = 0; i < qq; ++i)
		cin >> q[i].k >> q[i].s >> q[i].t, q[i].id = i;
	vector<ll> ans(qq);
	build(1, 1, m);
	int pch = 0, pq = 0;

	sort(change.begin(), change.end(), [&](CH &e1, CH &e2)
		 { return e1.pos < e2.pos; });

	sort(q.begin(), q.end(), [&](Q &e1, Q &e2)
		 { return e1.k < e2.k; });

	for (int i = 1; i <= n; ++i)
	{
		while (pch < change.size() && change[pch].pos == i)
		{
			update(1, change[pch].s, change[pch].x);
			pch++;
		}
		while (pq < q.size() && q[pq].k == i)
		{
			S res = ask(1,q[pq].s,q[pq].t);
			ans[q[pq].id] = max(max(res.ms,res.sum),max(res.ls,res.rs));
			pq++;
		}
	}
	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] << '\n';
}
```