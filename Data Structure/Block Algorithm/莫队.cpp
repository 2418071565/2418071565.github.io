/*
根据题目[P2709 小B的询问]给出莫队算法的模板
https://www.luogu.com.cn/problem/P2709
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 5e4 + 100;
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
	solve();
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

ll a[MAX];  
int n, m, k;    
ll ans[MAX];        // 记录对应编号的最终答案
ll cnt[MAX];        // 记录对应数字出现个数
ll res = 0;         // 当前区间的答案
struct S            // 记录询问
{
	int l, r, id;   // l询问左端点，r询问右端点，id询问编号
} s[MAX];
int pos[MAX];       // 记录下标为x所在的块

// 将x位置对答案的影响加到当前区间内
inline void add(int x){res += 2 * cnt[a[x]] + 1, cnt[a[x]]++;}

// 将x位置对答案的影响从当前区间减去
inline void sub(int x){res += 1 - 2 * cnt[a[x]], cnt[a[x]]--;}
void solve()
{
	cin >> n >> m >> k;
    // 对下标分块
	int block = sqrt(n);
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		pos[i] = (i + block - 1) / block;
	}
    // 记录查询
	for (int i = 1; i <= m; ++i)
	{
		cin >> s[i].l >> s[i].r;
		s[i].id = i;
	}

    // 这是莫队算法与暴力法唯一不同的地方
    // 对查询按莫队算法排序
	sort(s + 1, s + 1 + m, [](S &a, S &b)
		 { return pos[a.l] == pos[b.l] ? a.r < b.r : pos[a.l] < pos[b.l]; });


	int l = 1, r = 0;   // l,r维护当前所在区间
	for (int i = 1; i <= m; ++i)
	{
        // 移动区间完成查询
		while (s[i].l < l)add(--l);
		while (s[i].l > l)sub(l++);
		while (s[i].r > r)add(++r);
		while (s[i].r < r)sub(r--);
		ans[s[i].id] = res; //记录答案
	}
	for (int i = 1; i <= m; ++i)
		cout << ans[i] << '\n';
}