

## **区间最值操作**

[Gorgeous Sequence](https://acm.hdu.edu.cn/showproblem.php?pid=5306)


有一个长度为 $n$ 的序列 $a$ 。我们使用 $a_i$ 来表示此序列中的 $i -th$ 元素。应对此序列执行以下三种类型的操作。

$0\ \ x\  \ y\  \ t$ ： 对于每个 $x≤i≤y$ ，我们使用 $min(a_i,t)$ 来替换原来的 $a_i$ 的值。

$1\ \ x\ \ y$ ： 打印 $a_i$ 的最大值 $x≤i≤y$ .

$2\  \ x\  \ y$ ： 打印 $a_i$ 的总和 $x≤i≤y$ .

线段树解题，解题要用到 $Lazy-Tag$ 标记来实现高效的修改。如何设计标记就是解题的关键。吉如一在其论文中提到的解决方法定义的四个标记，巧妙的将区间最值和区间和结合起来。

对于线段树的每个节点，我们定义四个标记；区间和 $sum$、区间最大值 $ma$，区间严格次大值 $se$，最大值个数 $cnt$ 。

当我们要用 $min(a_i,x)$对区间$[l,r]$进行修改时，在线段树上定位到对应区间后，有以下三种情况：

- 当 $ma\le x$ 时，这次修改不影响节点，不进行修改。
- 当 $se< x<ma$ 时，这次修改值影响最大值，更新 $sum=sum-cnt\times(ma -x)$，并且修改最大值 $ma=x$。
- 当 $se\ge x$ 时，无法直接修改这个节点，递归它的左右儿子。

上述算法的关键是严格次大值 $se$，他起到剪枝的作用。这样看似很暴力的操作，实际复杂度并不是很高，在吉如一的国家队论文中进行详细的证明，其时间复杂度是 $O(m\log n)$ 。


## **实现**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(1e6 + 7)
typedef long long ll;
const int mod = 1e9 + 7;
typedef vector<int> vi;
// 交hduoj加上注释代码才能过
// const int L = 1 << 20 | 1;
// char buffer[L], * S, * TT;
// #define getchar() ((S==TT&&(TT=(S=buffer)+fread(buffer,1,L,stdin),S==TT))?EOF:*S++)

// 快读模板
inline ll input()
{
    bool sym = false;ll res = 0;char ch = getchar();
    while (!isdigit(ch)) sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch)) res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
// 定义线段树
struct
{
    ll l, r, sum, cnt, ma, se;
} f[MAX << 2];
// 求左右子节点的函数
inline int ls(int k) { return k << 1; }
inline int rs(int k) { return k << 1 | 1; }
inline int md(int l, int r) { return (l + r) >> 1; }
int n, m;
// 合并区间，维护四个标记
inline void push_up(int k)
{
    f[k].sum = f[ls(k)].sum + f[rs(k)].sum;  // 维护区间和
    f[k].ma = max(f[ls(k)].ma, f[rs(k)].ma); // 维护区间最大值
    if (f[ls(k)].ma == f[rs(k)].ma)
    { // 维护区间次大值和最大值个数
        f[k].se = max(f[ls(k)].se, f[rs(k)].se);
        f[k].cnt = f[ls(k)].cnt + f[rs(k)].cnt;
    }
    else
    {
        f[k].se = max(f[ls(k)].se, f[rs(k)].se);
        f[k].se = max(f[k].se, min(f[ls(k)].ma, f[rs(k)].ma));
        f[k].cnt = f[ls(k)].ma > f[rs(k)].ma ? f[ls(k)].cnt : f[rs(k)].cnt;
    }
}
// 建树
void build(int k, int l, int r)
{
    f[k].l = l, f[k].r = r;
    if (l == r)
    {
        f[k].cnt = 1;
        f[k].se = -1;
        f[k].ma = f[k].sum = input();
        return;
    }
    int m = md(l, r);
    build(ls(k), l, m);
    build(rs(k), m + 1, r);
    push_up(k);
}

// 给节点打上标记
void add_tag(int k, int x)
{
    if (x >= f[k].ma) return;
    f[k].sum -= f[k].cnt * (f[k].ma - x);
    f[k].ma = x;
}

// 下传标记
void push_down(int k)
{
    add_tag(ls(k), f[k].ma);
    add_tag(rs(k), f[k].ma);
}
// 区间最值修改
void change(int k, int l, int r, ll x)
{
    if (x >= f[k].ma)
        return; // 大于区间最大值，直接退出递归
    if (l <= f[k].l && r >= f[k].r && x > f[k].se)
    { // 大于严格次大值，可以对区间进行修改
        add_tag(k, x);
        return;
    }
    // 不满足上面两种情况，递归左右子节点
    push_down(k);
    int m = md(f[k].l, f[k].r);
    if (l <= m) change(ls(k), l, r, x);
    if (r > m) change(rs(k), l, r, x);
    push_up(k);
}
// 查询区间和
ll ask1(int k, int l, int r)
{
    if (l <= f[k].l && r >= f[k].r)
        return f[k].sum;
    push_down(k);
    int m = md(f[k].l, f[k].r);
    ll res = 0;
    if (l <= m) res += ask1(ls(k), l, r);
    if (r > m) res += ask1(rs(k), l, r);
    return res;
}
// 查询区间最值
ll ask2(int k, int l, int r)
{
    if (l <= f[k].l && r >= f[k].r)
        return f[k].ma;
    push_down(k);
    int m = md(f[k].l, f[k].r);
    ll res = 0;
    if (l <= m) res = ask2(ls(k), l, r);
    if (r > m) res = max(res, ask2(rs(k), l, r));
    return res;
}

void solve()
{
    n = input(), m = input();
    build(1, 1, n);
    for (int i = 0; i < m; ++i)
    {
        ll op = input(), l = input(), r = input();
        if (op == 0) change(1, l, r, input());
        if (op == 1) printf("%lld\n", ask2(1, l, r));
        if (op == 2) printf("%lld\n", ask1(1, l, r));
    }
}

int main()
{
    ios::sync_with_stdio(false);
    ll T;
    for (T = input(); T--;)
        solve();

    return 0;
}
```