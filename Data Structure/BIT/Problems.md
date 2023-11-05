# **Exercise**

|题目 | 难度|AC代码|知识|
|---|:---:|---|--|
|[P1908](https://www.luogu.com.cn/problem/P1908)|普及/提高-|[idle_person](https://www.luogu.com.cn/paste/itq65wlc)|逆序对模板|
|[P1774](https://www.luogu.com.cn/problem/P1774) | 普及/提高-|P1774|逆序对|
|[P4479](https://www.luogu.com.cn/problem/P4479)|省选/NOI- |P4479|离散化+树状数组|
|[No Pain No Game](https://acm.hdu.edu.cn/showproblem.php?pid=4630)|||离线+树状数组|
|[I Hate It](https://acm.hdu.edu.cn/showproblem.php?pid=1754)||[idle_perosn](https://www.luogu.com.cn/paste/y5l29q5r)|树状数组维护RMQ|
|[P4514](https://www.luogu.com.cn/problem/P4514)|省选/NOI-|P4514|二维树状数组|
|[P1966](https://www.luogu.com.cn/problem/P1966)|提高+/省选-|P1966|排序+树状数组|
|[P3605](https://www.luogu.com.cn/problem/P3605)|提高+/省选-|P3605|DFS+树状数组|
|[LC.100112](https://leetcode.cn/problems/maximum-balanced-subsequence-sum/description/)|困难||树状数组优化DP|



#### P1774
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(5e5+7)
typedef long long ll;

int f[MAX],n,a[MAX],newa[MAX];
inline int lowbit(int x){
    return x&-x;
}
void update(int x,int d){
    for(;x<=n;x+=lowbit(x))
        f[x]+=d;
}

int ask(int x){
    int sum=0;
    for(;x>0;x-=lowbit(x))
        sum+=f[x];
    return sum;
}

void solve() {
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        newa[i]=a[i];
    }
    sort(newa+1,newa+1+n);
    for(int i=1;i<=n;++i)
        a[i]=lower_bound(newa+1,newa+1+n,a[i])-newa;
    ll ans=0;
    for(int i=1;i<=n;++i){
        update(a[i],1);
        ans+=i-ask(a[i]);
    }
    cout<<ans<<'\n';
}

int main() {
    ios::sync_with_stdio(false); //int T;
    //for (cin >> T; T--;) 
        solve();


    return 0;
}
```

#### P4479
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(1e5+7)
typedef long long ll;
//const int p = 1e8 - 3;
typedef vector<int> vi;

inline ll input() {
    bool sym = false; ll res = 0; char ch = getchar();
    while (!isdigit(ch))sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch))res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}

pair<ll, ll> p[MAX], t[MAX];
ll ff[MAX], n, k, x[MAX], indx[MAX];
inline int lowbit(int x) {
    return x & -x;
}
void update(int x, int d) { for (; x <= n; x += lowbit(x))ff[x] += d; }
ll ask(int x) { ll sum = 0; for (; x > 0; x -= lowbit(x))sum += ff[x]; return sum;}

bool check(int kk) {
    for (int i = 1; i <= n; ++i)
        t[i].first = p[i].second - p[i].first * kk, t[i].second = indx[i];
    memset(ff, 0, (n + 1) * sizeof(ll));
    sort(t + 1, t + 1 + n);
    ll sum = 0;
    for (int i = 1; i <=n; ++i) {
        update(t[i].second, 1);
        sum += ask(t[i].second - 1);
    }
    return sum >= k;
}

void solve() {
    n = input(), k = input();
    for (int i = 1; i <= n; ++i)
        p[i].first = input(), p[i].second = input(), x[i] = p[i].first;
    sort(x + 1, x + 1 + n);
    for (int i = 1; i <= n; ++i)
        indx[i] = lower_bound(x + 1, x + 1 + n, p[i].first) - x;
    ll l = -2e8 - 7, r = 2e8 + 7, ans;
    while (l <= r) {
        ll m = (l + r) >> 1;
        if (check(m)) {
            l = m + 1;
            ans = m;
        }
        else r = m - 1;
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false); //int T;
    //for (cin >> T; T--;) 
        solve();


    return 0;
}
```

#### P4514
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(5e3+7)
typedef long long ll;
char op;
int f[4][MAX][MAX], n, m,a,b,c,d,delta;
inline int lowbit(int x){
    return x&-x;
}

void update(int x,int y,int d){
    for(int i=x;i<=n;i+=lowbit(i))
        for(int j=y;j<=m;j+=lowbit(j))
            f[0][i][j]+=d,f[1][i][j]+=d*x,f[2][i][j]+=y*d,f[3][i][j]+=x*y*d;
}

void update(int x1,int y1,int x2,int y2,int k){
    update(x1,y1,k),update(x1,y2+1,-k),update(x2+1,y1,-k),update(x2+1,y2+1,k);
}

int ask(int x,int y){
    int sum=0;
    for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
            sum+=(x+1)*(y+1)*f[0][i][j]-(y+1)*f[1][i][j]-(x+1)*f[2][i][j]+f[3][i][j];
    return sum;
}

int ask(int x1,int y1,int x2,int y2){
    return ask(x2,y2)-ask(x1-1,y2)-ask(x2,y1-1)+ask(x1-1,y1-1);
}

void solve() {
    cin>>op>>n>>m;
    while(cin>>op){
        cin>>a>>b>>c>>d;
        if(op=='L'){
            cin>>delta;
            update(a,b,c,d,delta);
        }
        else cout<<ask(a,b,c,d)<<'\n';
    }
}

int main() {
    ios::sync_with_stdio(false); //int T;
    //for (cin >> T; T--;) 
        solve();


    return 0;
}
```

#### P1966
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(2e5+7)
typedef long long ll;

ll f[MAX], n, a[MAX], b[MAX];
pi newa[MAX], newb[MAX];
inline int lowbit(int x) {
    return x & -x;
}

void update(int x, int d) {
    for (; x <= n; x += lowbit(x))
        f[x] += d;
}

ll ask(int x) {
    ll sum = 0;
    for (; x >= 1; x -= lowbit(x))
        sum += f[x];
    return sum;
}


void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i)cin >> a[i],newa[i].fi=a[i],newa[i].se=i;
    for (int i = 1; i <= n; ++i)cin >> b[i],newb[i].fi=b[i],newb[i].se=i;
    sort(newa + 1, newa + 1 + n);
    sort(newb + 1, newb + 1 + n);
    for (int i = 1; i <= n; ++i) 
        b[newb[i].se] = newa[i].se;
    ll ans = 0;
    for (ll i = 1; i <= n; ++i) {
        update(b[i], 1);
        ans = (ans % p + (i % p - ask(b[i]) % p) % p) % p;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); int T;
    //for (cin >> T; T--;) 
        solve();


    return 0;
}
```

#### P3605
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(1e5+7)
typedef long long ll;
//const int p = 10007;
typedef vector<int> vi;

struct ed {
    int v, next;
}edge[MAX];
int head[MAX], in[MAX], n, a[MAX], f[MAX], newa[MAX];
int ans[MAX], tot = 0;
void add(int u, int v) {
    edge[++tot].v = v;
    edge[tot].next = head[u];
    head[u] = tot;
}
inline int lowbit(int x) {return x & -x;}
void update(int x, int d) { for (; x <= n; x += lowbit(x))f[x] += d; }
int ask(int x) { int sum = 0; for (; x > 0; x -= lowbit(x))sum += f[x]; return sum; }
void dfs(int now) {
    update(a[now], 1);
    ans[now] = ask(n) - ask(a[now]);
    for (int i = head[now]; i; i = edge[i].next)
        dfs(edge[i].v);
    ans[now] = ask(n) - ask(a[now]) - ans[now];
}
void solve() {
    cin >> n;
    memset(head, 0, sizeof head);
    memset(edge, 0, sizeof edge);
    for (int i = 1; i <= n; ++i)cin>>a[i], newa[i] = a[i], ans[i] = 0;
    sort(newa + 1, newa + 1 + n);
    for (int i = 1; i <= n; ++i)
        a[i] = lower_bound(newa + 1, newa + 1 + n, a[i]) - newa;
    for (int i = 2; i <= n; ++i) {
        int v; cin >> v;
        add(v, i);
    }
    dfs(1);
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false); //int T;
    //for (scanf("%d", &T); T--;)
    solve();

    return 0;
}
```