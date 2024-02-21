# __int128
```cpp
typedef __int128 int128;
inline int128 input(){
    bool sym = false; int128 res = 0; char ch= getchar();
    while (!isdigit(ch))sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch))res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
inline void print(int128 x){
 if(x<0)putchar('-'),x=-x;
 if(x>=10)print(x/10);
 putchar(x%10+'0');
}
```

# 并查集
```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int MAX =  1e6 + 7;
int fa[MAX];    // 记录每个节点的父节点
int n;          // 元素个数
int fa[MAX], n, m;
void init(int n)
{
    // 初始时将节点的根节点设为自己
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
}

int ask(int x)
{
    // 如果节点的父节点是其本身，说明已经到根节点了
    if (fa[x] == x)
        return x;
    // 将路径上节点的父节点都改成查询结果
    return fa[x] = ask(fa[x]);
}

void merge(int x, int y)
{
    int i = ask(x), j = ask(y);
    fa[j] = i;
}
```




# 树状数组
```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int MAX = 1e6 + 100;
inline int lowbit(int x)
{
    return x & -x;
}
int n;          // 元素个数
int f[MAX];     // 树状数组
```
##  单点修改，区间查询
```cpp
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
```
## 区间修改，单点查询
树状数组维护差分数组
```cpp
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
```

# 线段树

## 基础线段树维护区间和

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int MAX = 1e6 + 100;
// 定义线段树
struct
{
    int l, r;
    ll sum, tag;
} f[MAX << 2];
// 求左右子节点的函数和区间折半的函数
inline int ls(int k) { return k << 1; }
inline int rs(int k) { return k << 1 | 1; }
inline int md(int l, int r) { return (l + r) >> 1; }
int n; 
// 从下向上传递区间值
void push_up(int k) { f[k].sum = f[ls(k)].sum + f[rs(k)].sum; }

// 递归的构建线段树
void build(int k, int l, int r)
{
    f[k].l = l, f[k].r = r, f[k].tag = 0; // 初始化每个节点维护的区间和tag标记
    if (l == r)
    {
        cin >> f[k].sum;
        return;
    }
    int m = md(l, r); // 分治：折半
    build(ls(k), l, m);
    build(rs(k), m + 1, r);
    push_up(k);
}

// 给区间打标记，并更新该区间值
inline void add_tag(int k, ll x)
{
    f[k].sum += (f[k].r - f[k].l + 1) * x;
    f[k].tag += x;
}
// 下传标记
inline void push_down(int k)
{
    add_tag(ls(k), f[k].tag);
    add_tag(rs(k), f[k].tag);
    f[k].tag = 0;
}

// 区间修改
void update(int k, int l, int r, ll x)
{
    // 修改区间完全覆盖当前区间时，就对区间进行修改，不深入其子节点
    if (l <= f[k].l && r >= f[k].r)
    {
        add_tag(k, x);
        return;
    }
    push_down(k); // 下传标记
    int m = md(f[k].l, f[k].r);
    if (l <= m)
        update(ls(k), l, r, x); // 与左节点有重叠,递归左子树
    if (r > m)
        update(rs(k), l, r, x); // 与右节点右重叠,递归右子树
    push_up(k);                 // 更新
}

// 区间查询
ll ask(int k, int l, int r)
{
    // 查询区间完全覆盖当前区间时，直接返回区间值，不深入其子节点
    if (l <= f[k].l && r >= f[k].r)
        return f[k].sum;
    push_down(k); // 下传标记
    int m = md(f[k].l, f[k].r);
    ll res = 0;
    if (l <= m)
        res += ask(ls(k), l, r); // 与左节点有重叠,递归左子树
    if (r > m)
        res += ask(rs(k), l, r); // 与右节点右重叠,递归右子树
    return res;
}
```
## 吉司机线段树
```cpp
//定义线段树
struct {
    ll l, r, sum, cnt, ma, se;
}f[MAX << 2];
//求左右子节点的函数
inline int ls(int k) { return k << 1; }
inline int rs(int k) { return k << 1 | 1; }
inline int md(int l, int r) { return (l + r) >> 1; }
int n;
//从下向上传递维护四个标记
inline void push_up(int k) {
    f[k].sum = f[ls(k)].sum + f[rs(k)].sum;//维护区间和
    f[k].ma = max(f[ls(k)].ma, f[rs(k)].ma);//维护区间最大值
    if (f[ls(k)].ma == f[rs(k)].ma) {//维护区间次大值和最大值个数
        f[k].se = max(f[ls(k)].se, f[rs(k)].se);
        f[k].cnt = f[ls(k)].cnt + f[rs(k)].cnt;
    }
    else {
        f[k].se = max(f[ls(k)].se, f[rs(k)].se);
        f[k].se = max(f[k].se, min(f[ls(k)].ma, f[rs(k)].ma));
        f[k].cnt = f[ls(k)].ma > f[rs(k)].ma ? f[ls(k)].cnt : f[rs(k)].cnt;
    }
}
//建树
void build(int k, int l, int r) {
    f[k].l = l, f[k].r = r;
    if (l == r) {
        f[k].cnt = 1; f[k].se = -1;
        f[k].ma = f[k].sum = input();
        return;
    }
    int m = md(l, r);
    build(ls(k), l, m);
    build(rs(k), m + 1, r);
    push_up(k);
}

//给节点打上标记
void add_tag(int k, int x) {
    if (x >= f[k].ma)return;
    f[k].sum -= f[k].cnt * (f[k].ma - x);
    f[k].ma = x;
}

//下传标记
void push_down(int k) {
    add_tag(ls(k), f[k].ma);
    add_tag(rs(k), f[k].ma);
}
// 区间最值修改
void change(int k, int l, int r, ll x) {
    if (x >= f[k].ma)return;//大于区间最大值，直接退出递归
    if (l <= f[k].l && r >= f[k].r && x > f[k].se) {//大于严格次大值，可以对区间进行修改
        add_tag(k, x);
        return;
    }
    //不满足上面两种情况，递归左右子节点
    push_down(k);
    int m = md(f[k].l, f[k].r);
    if (l <= m)change(ls(k), l, r, x);
    if (r > m)change(rs(k), l, r, x);
    push_up(k);
}
//查询区间和
ll ask1(int k, int l, int r) {
    if (l <= f[k].l && r >= f[k].r)return f[k].sum;
    push_down(k);
    int m = md(f[k].l, f[k].r);
    ll res = 0;
    if (l <= m)res += ask1(ls(k), l, r);
    if (r > m)res += ask1(rs(k), l, r);
    return res;
}
//查询区间最值
ll ask2(int k, int l, int r) {
    if (l <= f[k].l && r >= f[k].r)return f[k].ma;
    push_down(k);
    int m = md(f[k].l, f[k].r);
    ll res = 0;
    if (l <= m)res = ask2(ls(k), l, r);
    if (r > m)res = max(res, ask2(rs(k), l, r));
    return res;
}
```

## 动态开点线段树
初始都是0，维护区间和
```cpp
class RangeModule {
    #define MAX 10010
public:
    int root,cnt;
    struct N
    {
        int ls,rs;
        int lazy;
        bool cover;
    }f[MAX << 7];

    RangeModule() {
        cnt = 0;
        root = 0;
        memset(f,0,sizeof f);
    }

    void addtag(int& k,int x)
    {
        if(!k)k = ++cnt;
        f[k].lazy = x;
        f[k].cover = (x == -1?false:true);
    }
    
    void push_up(int& k)
    {
        f[k].cover = f[f[k].ls].cover & f[f[k].rs].cover;
    }
    void push_down(int& k)
    {
        if(f[k].lazy)
        {
            addtag(f[k].ls,f[k].lazy);
            addtag(f[k].rs,f[k].lazy);
            f[k].lazy = 0;
        }
    }

    void update(int& k,int l,int r,int s,int t,int d)
    {   
        if(!k)k = ++cnt;
        if(s <= l && r <= t)
        {
            addtag(k,d);
            return;
        }
        int m = (l + r) >> 1;
        push_down(k);
        if(s <= m)update(f[k].ls,l,m,s,t,d);
        if(t > m)update(f[k].rs,m + 1,r,s,t,d);
        push_up(k);
    }

    bool ask(int& k,int l,int r,int s,int t)
    {
        if(!k)return false;
        if(s <= l && r <= t) 
            return f[k].cover;
        int m = (l + r) >> 1;
        push_down(k);
        bool res = true;
        if(s <= m)res &= ask(f[k].ls,l,m,s,t);
        if(t > m)res &= ask(f[k].rs,m + 1,r,s,t);
        return res;
    }

    void addRange(int left, int right) {
        update(root,1,1e9,left,right - 1,1);
    }
    
    bool queryRange(int left, int right) {
        return ask(root,1,1e9,left,right - 1);
    }
    
    void removeRange(int left, int right) {
        update(root,1,1e9,left,right - 1,-1);
    }
};

```

# 分块、莫队

## 分块数组维护区间和

```cpp
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
```

## 莫队
```cpp
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
```

# 字符串哈希

```cpp
// 字符串哈希模板
const ll p[] = { 29, 31 };
const ll M[] = { int(1e9 + 9), 998244353 };
struct SHash
{
    ll pM[2][MAX];  // 记录两组P^i
    ll hsh[2][MAX]; // 记录两组前缀哈希值
    int tot;        // 记录当前维护字符串长度

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

    // 获取子字符串哈希值对
    // hsh[l,r] = hsh[r] - hsh[l - 1] * pM[r - l + 1]
    pair<ll, ll> getHash(int l, int r)
    {
        if (l > r)
            return { 0, 0 };
        pair<ll, ll> h;

        // 计算第一个哈希值
        h.first = (hsh[0][r] - hsh[0][l - 1] * pM[0][r - l + 1]) % M[0];
        (h.first += M[0]) %= M[0];

        // 计算第二个哈希值
        h.second = (hsh[1][r] - hsh[1][l - 1] * pM[1][r - l + 1]) % M[1];
        (h.second += M[1]) %= M[1];
        return h;
    }
};
```

# 字典树

## 基础字典树

```cpp
struct Trie
{
	int tr[MAX][26];	// 记录下一个字符所在节点
	int cnt[MAX];		// cnt[p]表示以p节点为结尾的字符串出现的次数
	int tot = 0;		// 新分配的存储位置

	// 初始化，全部置零
	Trie()
	{
		memset(tr,0,sizeof(tr));
		memset(cnt,0,sizeof(cnt));
	}

	// 将字符串插入到字典树中
	void insert(const char* s)
	{
		int p = 0;
		while(*s)
		{
			int now = *s - 'a';
			s++;
			// 如果节点不存在，就创建节点
			if(!tr[p][now])	
				tr[p][now] = ++tot;
				
			//移动到下一个节点
			p = tr[p][now];
		}
		cnt[p]++;
	}

	// 询问字符串
	int ask(const char* s)
	{
		int p = 0;
		while(*s)
		{
			int now = *s - 'a';
			s++;

			//如果没有对应节点，说明字典树中没有串s
			if(!tr[p][now])
				return 0;

			p = tr[p][now];
		}
		// 返回出现的次数
		return cnt[p];
	}
};
```

## 带删除01字典树

```cpp
struct BI_Trie
{
	int tr[MAX][2];		// 记录下一个比特位所在节点
	int cnt[MAX];		// cnt[p] 表示 p 节点为根的子树的节点个数
	int tot = 0;		// 新分配的存储位置

	// 初始化，全部置零
	BI_Trie(){memset(tr,0,sizeof(tr)),memset(cnt,0,sizeof(cnt));}

	// 将数的二进制位插入到字典树中
	void insert(int x)
	{
		int p = 0;
		for(int i = 30;i >= 0;--i)
		{
			int now = (x >> i) & 1;
			if(!tr[p][now])
				tr[p][now] = ++tot;
			p = tr[p][now];
			cnt[p]++;
		}
	}

	// 删除数
	void erase(int x)
	{
		int p = 0;
		for(int i = 30;i >= 0;--i)
		{
			int now = (x >> i) & 1;
			p = tr[p][now];
			cnt[p]--;
		}
	}

	// 询问最大异或和
	int max_xor(int x)
	{
		int res = 0,p = 0;
		for(int i = 30;i >= 0;--i)
		{
			int now = (x >> i) & 1;

			// 判断第i位是否能位1
			// 想要第i位为1，就要异或一个与该位不同的数，1 ^ 0 或 0 ^ 1 
			// 如果另一边存在数，就移动到另一个子树上
			// 不存在则这一位只能是0，就继续向下
			if(tr[p][now ^ 1] && cnt[tr[p][now ^ 1]])
			{
				p = tr[p][now ^ 1];
				res |= (1 << i);
			}
			else
				p = tr[p][now];
		}
		return res;
	}
};
```
# KMP

```cpp
// 求解nextval数组
void getNext(string& s) {
    nex[0] = -1;
    int i = -1, j = 0;
    while (j < s.size()) {
        if (i == -1 || s[i] == s[j]) {
            if (s[++j] == s[++i])nex[j] = nex[i];
            else nex[j] = i;
        }
        else i = nex[i];
    }
}

// KMP实现
// p为模式串，s为主串，pos为开始匹配的位置，默认从头开始
// 返回从pos位置开始模式串中出现的第一个主串的起始位置
int kmp(string& p, string& s, int pos = 0) {
    int i = pos, j = 0;
    getNext(s);
    while (i < p.size()) {
        // 如果字符匹配就将指针移动到下一格
        if (j == -1 || p[i] == s[j])
            ++j, ++i;
        else j = nex[j]; // 主串指针回溯
        // 如果主串已经完全匹配 就返回匹配的起始位置
        if (j == s.size()) 
            return j - s.size() + 1;
    }
    return -1;
}
```

# 马拉车算法

```cpp
//实现时我们用mid最右回文子串的中心，r最右回文子串的右端点，来维护最右回文子串区间
int Manacher(string& s) {
    vector<int> d(s.size() * 2 + 3);
    //初始化字符串
    string str("@");
    for (char ch : s)
        str += "#",str+=ch;
    str += "#$";
    //我们用mid,r来维护最右回文子串
    //len是最长回文子串的长度
    int r = 0, n = str.size(), len = 0, mid = 0;
    for (int i = 1; i < n - 1; ++i) {

        //判断i是否在最右回文区间内
        if (i <= r)d[i] = min(d[(mid << 1) - i], r - i + 1);
        else d[i] = 1;

        //中心扩散法求d[i]
        //这样写是为了追求代码简洁，因为其他情况并不会进入循环，不影响时间复杂度
        //就不写额外的判断来区分情况了
        while (str[i + d[i]] == str[i - d[i]])++d[i];

        //更新最右回文子串
        if (i + d[i] - 1 > r)mid = i, r = i + d[i] - 1;

        //更新最长回文子串的长度
        len = max(len, d[i] - 1);
    }
    return len;
}
```

# 最小表示法
返回字典序最小的循环串开头
```cpp
int minNotatin(vector<int>& s) {
 int k = 0, i = 0, j = 1, n = s.size();
 while (k < n && i < n && j < n) {
  if (s[(i + k) % n] == s[(j + k) % n])++k;//相同就递增k
  else (s[(i + k) % n] > s[(j + k) % n] ? ++i : ++j), k = 0;//不同就改变i或j的值
  if (i == j)++i;//当i=j时将二者错开
 }
 return min(i, j);
}
```

# 数论

## 快速幂
```cpp
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
```

## 乘法逆元



```cpp
// 扩展欧几里得 求逆元
// 适用于任何模数，但前提式求得数要和模数互质
// 时间复杂度为O(log n)
ll exgcd(ll a,ll b,ll& x,ll& y){
    if(!b){
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,x,y),x0=x,y0=y;
    x=y0;
    y=x0-a/b*y0;
    return d;
}
ll inv1(ll a){
    ll x,y;
    exgcd(a,p,x,y);
    return (x%p+p)%p;
}


// 费马小定理求逆元
// 只适用于模数是质数的情况
// 时间复杂度为O(log n)
ll qpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
ll inv2(ll a,ll p){
    return qpow(a,p-2);
}


// 递推大表求逆元
// 要求模数为质数
// 一般适用于在求解题目过程中要运算很多逆元，但数据的值域比较小的时候
// O(n)初始化，O(1)查询
ll inv[MAX];//记录逆元
void init(){
    inv[1]=1;
    for(int i=2;i<=n;++i)
        inv[i]=(ll)(p-p/i)*inv[p%i]%p;
}
```

## Lucas

```cpp
long long Lucas(long long n, long long m, long long p) {
  if (m == 0) return 1;
  return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
}
```


# 最小生成树

## Prim
```cpp
int n, m, u, v, w;

// 链式前向星模板
struct ed
{
    int v, w, next;
} edge[MAX];
int head[MAX], tot = 0;
void add(int uu, int vv, int ww)
{
    edge[tot].w = ww;
    edge[tot].v = vv;
    edge[tot].next = head[uu];
    head[uu] = tot++;
}

// V集合,true代表在V集合中
bool vis[MAX];

// Prim算法
void solve()
{
    memset(head, -1, sizeof head);
    memset(vis, 0, sizeof vis);
    cin >> n >> m;
    // 无向图，插入重边
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    // 优先队列，STL中默认是大堆，这里改成小堆
    priority_queue<pi, vector<pi>, greater<pi>> que;
    // cnt记录插入节点的数量
    // res记录最小生成树边权和
    int cnt = 0, res = 0;
    que.push({0, 1});
    while (!que.empty())
    {
        pi now = que.top();
        que.pop();
        // 不在V集合中就加入到最小生成树中
        if (!vis[now.se])
        {
            cnt++;
            res += now.fi;
            for (int j = head[now.se]; j != -1; j = edge[j].next)
                if (!vis[edge[j].v])
                    que.push({edge[j].w, edge[j].v});
        }
        // 将点插入到V集合中
        vis[now.se] = 1;
    }
    // 能将所有顶点插入最小生成树，图才是连通的
    if (cnt < n)
        printf("orz\n");
    else
        printf("%d\n", res);
}
```

## Kruskal
```cpp
int n, m;
// 并查集
int fa[MAX];
// 边定义，采用直接存边的方式储存图
struct ed
{
    int u, v, w;
    bool operator<(ed &y)
    {
        return w < y.w;
    }
} edge[MAX];
// 并查集实现
void init()
{
    for (int i = 0; i < n; ++i)
        fa[i] = i;
}
int ask(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = ask(fa[x]);
}
void merge(int x, int y)
{
    fa[ask(x)] = ask(y);
}

// Kruskal算法
void solve()
{
    cin >> n >> m;
    // 输入边
    for (int i = 0; i < m; ++i)
        cin >> edge[i].u >> edge[i].v >> edge[i].w;
    // 对边权进行排序
    sort(edge, edge + m);
    init();
    // cnt记录加入边的数量
    // ans记录最后边权和
    int ans = 0, cnt = 0;
    for (int i = 0; i < m && cnt < n - 1; ++i)
    {
        // 不连通的两点才能连边
        if (ask(edge[i].u) != ask(edge[i].v))
        {
            merge(edge[i].u, edge[i].v);
            ans += edge[i].w;
            cnt++;
        }
    }
    // 最后加入的边不足n-1说明不能形成生成树
    if (cnt < n - 1)
        cout << "orz\n";
    else
        cout << ans << '\n';
}

```

# LCA
```cpp
// dep[i]表示节点i的深度
int dep[MAX];
// dp[i][j]表示节点i第2^j的父节点
int dp[MAX][32];
// 邻接表存树
vector<int> s[MAX];

//时间复杂度O(n)
void dfs(int v, int fa) {
    dep[v] = dep[fa] + 1;
    dp[v][0] = fa;
    //dp[i][j]代表第i个节点的第2^i个祖先
    //第i个节点的第2^i个祖先是第i个节点的第2^(i-1)个节点的2^(i-1)个节点
    //递推公式:dp[i][j]=dp[dp[i][j-1]][j-1];
    for (int i = 1; (1 << i) <= dep[v]; ++i)
        dp[v][i] = dp[dp[v][i - 1]][i - 1];
    //遍历子节点
    for (int i = 0; i < s[v].size(); ++i) {
        //不能回到父节点
        if (s[v][i] == fa)continue;
        dfs(s[v][i], v);
    }
}

int lca(int x, int y) {
    //将深度较大的节点换到x上，就不用分类讨论了
    if (dep[x] < dep[y])swap(x, y);
    //计算出两个节点的高度差，将两个节点移到同一层
    int tmp = dep[x] - dep[y];
    //移动的过程和快速幂类似，将高度差按二进制位分解
    for (int i = 0; tmp; ++i) {
        //二进制位为1的，就移动相应步
        if ((tmp & (1 << i))) {
            x = dp[x][i];
            tmp ^= (1 << i);
        }
    }
    if (y == x)return x;
    //两个节点一起移动
    for (int i = 29; i >= 0; --i) {
        //移动要满足移动后两节点不重合，并且在最大步数范围内
        if ((1 << i) <= dep[x] && dp[x][i] != dp[y][i]) {
            x = dp[x][i];
            y = dp[y][i];
        }
    }
    return dp[x][0];
}
```

# 树的重心

```cpp
// 采用链式前向星的形式存树
struct
{
	int to, nxt;
} edge[MAX << 1];
int head[MAX], tot = 0;
void addEdge(int u, int v)
{
	edge[tot].to = v;
	edge[tot].nxt = head[u];
	head[u] = tot++;
}
// n是节点个数，d[u]是包括u节点及其子树的节点个数
int n, d[MAX];
// ans记录树的重心，ma是最小最大子树节点个数。
int ans[MAX], cnt = 0, ma;
void dfs(int u, int fa)
{
	d[u] = 1;
	int t = 0;
	for (int i = head[u]; ~i; i = edge[i].nxt) //链式前向星存储方式
	{
		int v = edge[i].to;
		if (v == fa)continue;    //不回到父节点
		dfs(v,u);                //计算蓝色部分节点个数
		d[u] += d[v];   
		t = max(t, d[v]);        //记录蓝色部分中最大的子树
	}
	t = max(t, n - d[u]);        //得到当前位置的最大子树
	if (t < ma)                  // 记录答案
	{
		cnt = 1;
		ans[cnt] = u;
		ma = t;
	}
	else if (t == ma)ans[++cnt] = u;//重心有多个
}
```


# 计算几何

## 点、线
```cpp
constexpr double eps = 1e-15;
struct Point;
double abs(const Point &x);

// 点
struct Point
{
    double x, y; // 二维向量，表示一个点
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    // 向量基本运算的实现+ - · *
    Point operator+(const Point &a) const { return Point{x + a.x, y + a.y}; }
    Point operator-(const Point &a) const { return Point{x - a.x, y - a.y}; }
    Point operator-() const { return Point{-x, -y}; }

    double operator|(const Point &a) const { return x * a.x + y * a.y; }  // 点乘
    double operator*(const Point &a) const { return x * a.y - y * a.x; }  // 叉乘
    Point operator*(const double a) const { return Point{x * a, y * a}; } // 向量数乘
    double pow() const { return x * x + y * y; }                          // 向量取平方

    // 求距离
    // 点到点的距离
    double disPoint(const Point &a) const
    {
        return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
    }

    // 点到直线的距离
    // a,b直线上两点
    double disline(const Point &a, const Point &b) const
    {
        Point ap = (*this) - a, ab = b - a;
        return abs(ap * ab) / abs(ab);
    }

    // 点到线段的距离
    // a,b线段两端点
    double disSeg(const Point &a, const Point &b) const
    {
        // 判断点和线段的位置关系
        if ((((*this) - a) | (b - a)) <= -eps || (((*this) - b) | (a - b)) <= -eps)
            return min(this->disPoint(a), this->disPoint(b));
        return disline(a, b);
    }

    // 重载 < 方便找线段交点
    bool operator<(const Point &b) const
    {
        if (y == b.y)
            return x < b.x;
        return y < b.y;
    }
};
double triangle(Point &a, Point &b, Point &c) { return (b - a) * (b - c) / 2.0; } // 求三角形面积
double abs(const Point &x) { return sqrt(x.pow()); }                              // 向量取模

// 线
struct line
{
    Point x1, x2;
    Point dVec;

    line(const Point &_x1 = {0, 0}, const Point &_x2 = {0, 0}) : x1(_x1),
                                                                 x2(_x2)
    {
        dVec = x2 - x1;
    }

    // 判断直线是否平行
    bool is_parallel(const line &b) const
    {
        return abs(dVec * b.dVec) <= eps;
    }

    // 求两直线交点
    Point line_intersection(const line &b) const
    {
        // 直线平行返回无穷大
        if (is_parallel(b))
            return {INT_MAX, INT_MAX};

        // 带入公式
        Point c = x2 - b.x2;
        double K = (b.dVec * c) / (dVec * b.dVec);
        Point res = x2 + dVec * K;
        return res;
    }

    // 求两线段交点
    // 交点不存在返回 INT_MAX
    Point seg_intersection(const line &b) const
    {
        // 判断平行
        if (is_parallel(b))
        {
            // 判断是否共线
            if ((b.x2 - x1) * (b.x1 - x1) == 0)
            {
                Point mi = max(min(x1, x2), min(b.x1, b.x2));
                Point ma = min(max(x1, x2), max(b.x1, b.x2));
                if (ma.x >= mi.x && ma.y >= mi.y)
                    return mi;
            }
            return {INT_MAX, INT_MAX};
        }

        // 判断是否分别在线段的两端
        if (((b.x2 - x1) * dVec) * ((b.x1 - x1) * dVec) > 0)
            return {INT_MAX, INT_MAX};
        if (((x1 - b.x1) * b.dVec) * ((x2 - b.x1) * b.dVec) > 0)
            return {INT_MAX, INT_MAX};
        
        return line_intersection(b);
    }
};
```

## 凸包

```cpp
// stk[] 是整型，存的是下标
// p[] 存储向量或点
tp = 0;                       // 初始化栈
std::sort(p + 1, p + 1 + n);  // 对点进行排序
stk[++tp] = 1;
// 栈内添加第一个元素，且不更新 used，使得 1 在最后封闭凸包时也对单调栈更新
for (int i = 2; i <= n; ++i) {
  while (tp >= 2  // 下一行 * 操作符被重载为叉积
         && (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0)
    used[stk[tp--]] = 0;
  used[i] = 1;  // used 表示在凸壳上
  stk[++tp] = i;
}
int tmp = tp;  // tmp 表示下凸壳大小
for (int i = n - 1; i > 0; --i)
  if (!used[i]) {
    // ↓求上凸壳时不影响下凸壳
    while (tp > tmp && (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0)
      used[stk[tp--]] = 0;
    used[i] = 1;
    stk[++tp] = i;
  }
for (int i = 1; i <= tp; ++i)  // 复制到新数组中去
  h[i] = p[stk[i]];
int ans = tp - 1;
```

