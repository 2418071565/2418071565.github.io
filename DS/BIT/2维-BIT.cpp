#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e3 + 100;

inline int lowbit(int x)
{
    return x & -x;
}

// n代表二维数组的行，m代表二维树状数组的列
// f[]数组代表维护的数组
int n, m;
int f[MAX][MAX];

// 基础二维树状数组
// 支持单点修改，子矩阵查询
void update(int x, int y, int d)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            f[i][j] += d;
}

// 二维前缀和查询
int ask(int x, int y)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            sum += f[i][j];
    return sum;
}
// 子矩阵查询
int ask(int x1, int y1, int x2, int y2)
{
    return ask(x1, y1) - ask(x1, y2 - 1) - ask(x2 - 1, y1) + ask(x2, y2);
}

// 4*差分数组+二维树状数组
// 支持子矩阵修改，子矩阵查询
int f2[4][MAX][MAX];
// 子矩阵修改
void update(int x, int y, int d)
{
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= m; j += lowbit(j))
            f2[0][i][j] += d, f2[1][i][j] += d * x,
                f2[2][i][j] += y * d, f2[3][i][j] += x * y * d;
}
// 维护子矩阵和
void update(int x1, int y1, int x2, int y2, int k)
{
    update(x1, y1, k), update(x1, y2 + 1, -k),
        update(x2 + 1, y1, -k), update(x2 + 1, y2 + 1, k);
}

// 前缀和查询
int ask(int x, int y)
{
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        for (int j = y; j > 0; j -= lowbit(j))
            sum += (x + 1) * (y + 1) * f2[0][i][j] - (y + 1) * f2[1][i][j] - (x + 1) * f2[2][i][j] + f2[3][i][j];
    return sum;
}
// 查询子矩阵和
int ask(int x1, int y1, int x2, int y2)
{
    return ask(x2, y2) - ask(x1 - 1, y2) - ask(x2, y1 - 1) + ask(x1 - 1, y1 - 1);
}
