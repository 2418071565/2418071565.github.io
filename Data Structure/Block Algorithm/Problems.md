Exercise
=================
|题目|难度|AC代码|知识|
|:-:|:-:|:-:|:-:|
|[P2801](https://www.luogu.com.cn/problem/P2801)|提高+/省选−|P2801.cpp|区间k大值|
|[P3203](https://www.luogu.com.cn/problem/P3203)|省选/NOI−|P3203.cpp|分块单点修改，单点查询|



#### P2801.cpp
```cpp
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
const int MAX = 1e6 + 100;
typedef long long ll;
// const ll p = 998244353;
void solve();
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    clock_t c1 = clock();
#ifdef LOCAL
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    // int T;
    // for (cin >> T; T--;)
    solve();
    // f()
    cerr << "Time Used: " << clock() - c1 << " ms\n";
    return 0;
}

ll a[MAX], b[MAX];
int n, m;
int st[MAX], ed[MAX];
ll add[MAX];
int pos[MAX];
int block, t;
void init()
{
    block = sqrt(n);
    t = (n + block - 1) / block;
    for (int i = 1; i <= n; ++i)
        pos[i] = (i + block - 1) / block;
    for (int i = 1; i <= t; ++i)
    {
        ed[i] = i * block;
        st[i] = (i - 1) * block + 1;
    }
    ed[t] = n;
}

void Sort(int k)
{
    for (int i = st[k]; i <= ed[k]; ++i)
        b[i] = a[i];
    sort(b + st[k], b + ed[k] + 1);
}

void update(int l, int r, ll d)
{
    int p = pos[l], q = pos[r];
    if (p == q)
    {
        // 块内操作
        for (int i = l; i <= r; ++i)
            a[i] += d;
        Sort(p);
    }
    else
    {
        // 对整块操作
        for (int i = p + 1; i <= q - 1; ++i)
            add[i] += d;

        // 左边多出的部分
        for (int i = l; i <= ed[p]; ++i)
            a[i] += d;

        // 右边多出的部分
        for (int i = st[q]; i <= r; ++i)
            a[i] += d;
        Sort(p), Sort(q);
    }
}

ll ask(int l, int r, ll c)
{
    int p = pos[l], q = pos[r];
    ll cnt = 0;
    if (p == q)
    {
        for (int i = l; i <= r; ++i)
            if (a[i] >= c - add[p])
                cnt++;
    }

    else
    {
        for (int i = p + 1; i <= q - 1; ++i)
            cnt += ed[i] - (lower_bound(b + st[i], b + ed[i] + 1, c - add[i]) - b) + 1;

        for (int i = l; i <= ed[p]; ++i)
            if (a[i] >= c - add[p])
                cnt++;
        for (int i = st[q]; i <= r; ++i)
            if (a[i] >= c - add[q])
                cnt++;

    }
    return cnt;
}

void solve()
{
    cin >> n >> m;
    memset(add, 0, sizeof add);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    init();
    for (int i = 1; i <= t; ++i)
        Sort(i);

    for (int i = 0; i < m; ++i)
    {
        char op;
        int l, r, x;
        cin >> op >> l >> r >> x;
        if (op == 'M')
            update(l, r, x);
        else
            cout << ask(l, r, x) << '\n';
    }
}
```

#### P3203.cpp
```cpp
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
const int MAX = 1e6 + 100;
typedef long long ll;
// const ll p = 998244353;
void solve();
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	clock_t c1 = clock();
#ifdef LOCAL
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	// int T;
	// for (cin >> T; T--;)
	solve();
	// f()
	cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

int t, block;
int n, m;
int a[MAX];
int step[MAX], to[MAX];
int b[MAX], pos[MAX], st[MAX], ed[MAX];

void op(int k)
{
	for (int i = ed[k]; i >= st[k]; --i)
	{
		if (i + a[i] > ed[k]) step[i] = 1, to[i] = i + a[i];
		else step[i] = step[i + a[i]] + 1, to[i] = to[i + a[i]];
	}
}

void init()
{
	block = sqrt(n);
	t = (n + block - 1) / block;

	for (int i = 1; i <= n; ++i)
		pos[i] = (i + block - 1) / block;

	for (int i = 1; i <= t; ++i)
	{
		st[i] = (i - 1) * block + 1;
		ed[i] = vector<int>({i * block, n})[i == t];
		op(i);
	}
}

void update(int x, int k)
{
	a[x] = k;
	op(pos[x]);
}

int ask(int x)
{
	int cnt = 0;
	for (int pos = x; pos <= n; pos = to[pos])
		cnt += step[pos];
	return cnt;
}

void solve()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];

	init();
	cin >> m;
	for (int i = 0; i < m; ++i)
	{
		int op, x, k;
		cin >> op >> x;
		if (op == 1)cout << ask(x + 1) << '\n';
		else cin >> k, update(x + 1, k);
	}
}
```