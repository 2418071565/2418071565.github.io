#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e6 + 100;

inline int lowbit(int x)
{
    return x & -x;
}

// n代表维护的数组长度
// f[]数组代表维护的数组
int n;
int f[MAX];

// =====================================================================
// 基础树状数组
// 支持单点修改，区间查询

// 单点修改
inline void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        f[x] += d;
}

// 查询前缀[1,x]的和
inline int ask(int x)
{
    int sum = 0;
    for (; x > 0; x -= lowbit(x))
        sum += f[x];
    return sum;
}

// 求区间[l,r]的和
inline int ask(int l, int r)
{
    return ask(r) - ask(l - 1);
}

// =====================================================================
// 差分+树状数组
// 支持区间修改，单点查询

// 对差分数组单点修改
inline void update(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        f[x] += d;
}

// 区间修改，即修改差分数组的两个端点
// 在区间[l,r]上加上k
inline void change(int l, int r, int k)
{
    update(l, k);
    update(r + 1, -k);
}

// 单点查询，即求差分数组前缀和
inline int ask(int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        sum += f[i];
    return sum;
}

// =====================================================================
// 2*差分数组+数组数组
// 支持区间修改，区间查询

// 维护两个差分数组
int f1[MAX], f2[MAX];

// 区间查询
//  对两个差分数组求前缀和
inline int ask1(int x)
{
    int sum = 0;
    for (; x > 0; x -= lowbit(x))
        sum += f1[x];
    return sum;
}
inline int ask2(int x)
{
    int sum = 0;
    for (; x > 0; x -= lowbit(x))
        sum += f2[x];
    return sum;
}

// 区间查询
//ask(l,r) = sum(r) - sum(l-1)
inline int ask(int l, int r)
{
    return r * ask1(r) - ask2(r) - ((l - 1) * ask1(l - 1) - ask2(l - 1));
}

// 区间修改
// 对两个差分数组做修改
void update1(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        f1[x] += d;
}
void update2(int x, int d)
{
    for (; x <= n; x += lowbit(x))
        f2[x] += d;
}
//修改区间[l,r]
void change(int l, int r, int d)
{
    update1(l, d), update1(r + 1, -d);
    update2(l, (l - 1) * d), update2(r + 1, -r * d);
}

