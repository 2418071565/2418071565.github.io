// 以维护区间和为例，给出分块的基本代码

#include <bits/stdc++.h>
using namespace std;
const int MAX = 5e5 + 100;
typedef long long ll;

ll a[MAX], b[MAX];
int n, m;
// st[i]代表第i个块开始的位置，ed[i]表示第i个块结束的位置
int st[MAX], ed[MAX], pos[MAX];
// add整块的增量，sum维护区间和
ll add[MAX], sum[MAX];
// block 块大小，t块个数
int block, t;
// 初始化分块
void init()
{
    //块大小
    block = sqrt(n);                      
    //块的个数 
    t = (n + block - 1) / block;            
    for (int i = 1; i <= n; ++i)
    {
        //第i个元素所在块
        pos[i] = (i + block - 1) / block;   
        //sum维护区间和
        sum[pos[i]] += a[i];                
    }
    for (int i = 1; i <= t; ++i)
    {
        ed[i] = i * block;
        st[i] = (i - 1) * block + 1;
        add[i] = 0;
    }
    //最后一个块可能不是整块
    ed[t] = n;                              
}

// 区间修改
void update(int l, int r, ll d)
{
    int p = pos[l], q = pos[r];
    // 修改区间在同一个块内
    if (p == q)
    {
        sum[p] += (r - l + 1) * d;
        for (int i = l; i <= r; ++i)
            a[i] += d;
    }
    else
    {
        // 修改整块
        for (int i = p + 1; i <= q - 1; ++i)
            add[i] += d;
        // 修改左边多余部分
        for (int i = l; i <= ed[p]; ++i)
            a[i] += d, sum[p] += d;
        // 修改右边多余部分
        for (int i = st[q]; i <= r; ++i)
            a[i] += d, sum[q] += d;
    }
}

// 区间查询
ll ask(int l, int r)
{
    int p = pos[l], q = pos[r];
    ll ans = 0;
    // 查询区间在同一个块内
    if (p == q)
    {
        for (int i = l; i <= r; ++i)
            ans += a[i] + add[p];
    }
    else
    {
        // 查询整块
        for (int i = p + 1; i <= q - 1; ++i)
            ans += sum[i] + add[i] * (ed[i] - st[i] + 1);

        // 查询两边多余部分
        for (int i = l; i <= ed[p]; ++i)
            ans += a[i] + add[p];

        for (int i = st[q]; i <= r; ++i)
            ans += a[i] + add[q];
    }
    return ans;
}

void solve()
{
    cin >> n >> m;
    memset(add, 0, sizeof add);
    memset(sum, 0, sizeof sum);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    init();

    for (int i = 0; i < m; ++i)
    {
        int op;
        int l, r, x;
        cin >> op >> l >> r;
        if (op == 1)
            cin >> x, update(l, r, x);
        else
            cout << ask(l, r) << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
