/*
以题目I Hate It为例给出树状数组如理RMQ问题的模板
https://acm.hdu.edu.cn/showproblem.php?pid=1754
*/

#include <bits/stdc++.h>
using namespace std;
#define MAX int(2e5+7)
typedef long long ll;

int f[MAX],a[MAX], n, m;
inline int lowbit(int x) {return x & -x;}

// 单点修改
void update(int x, int d) { 
    while (x <= n) {
        f[x] = max(d,a[x]);
        // 用当前节点的子节点更新当前节点
        for (int i = 1; i < lowbit(x); i <<= 1)
            f[x] = max(f[x], f[x - i]);
        x += lowbit(x);
    }
}

// 查询区间最值
int ask(int l,int r) {
    int res = 0;
    while (l <= r) {
        // 如果当前节点维护的区间超过查询区间，就用原数组该位置的值修改答案
        if (lowbit(r) > r - l + 1)
            res = max(res, a[r]),--r;
        // 没超过就直接用当前节点的区间修改答案
        else 
            res = max(res, f[r]),r -= lowbit(r);
    }
    return res;
}


void solve() {
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            update(i, a[i]);
        }
        for (int i = 0; i < m; ++i) {
            char op;
            int x, y;
            cin >> op >> x >> y;
            if (op == 'Q')cout << ask(x, y) << '\n';
            else a[x] = y, update(x, y);
        }
    }
}

int main() {
    ios::sync_with_stdio(false); //int T;
    //for (cin >> T; T--;) 
    solve();
    return 0;
}