#### 定义
线段树和树状数组都是解决区间问题的数据结构，但与树状数组相比更易理解，但是实现代码比较长。

线段树融合了**分治算法**、**二叉树结构**和$Lazy-Tag$**技术**思想。
#### 基本结构
线段树是一棵二叉树，树上的节点是“线段”，即区间，如下图是一棵线段树
![](https://pic1.zhimg.com/80/v2-5e9124a6147143e51cea46755e9a0398_1440w.webp)
我们用分治法自定向下，每次分治，将区间分成左右两半，每一个节点维护一个这样的区间，节点所维护的线段所表示的值可以是区间和、区间最值等等，根据题目灵活定义。这样求解一个大区间的解可以有左右两个小区间合并而来。

#### 线段树的构造
在竞赛中，一般用静态数组来实现满二叉树表示线段树，虽然比较浪费空间，但是易于编码。

定义静态数组实现满二叉树时，有两种实现方法，我们即可以定义结构体表示二叉树的节点，也可也直接用数组来实现。本文的实现都采用定义结构体的方式。

需要注意的是线段树空间要开到$4N$才能保证不越界访问。
```cpp
//定义结构体
struct{
    int l,r;//节点维护的区间
    int data;//节点维护的区间数据
}f[MAX << 2];
//定义数组
int f[MAX << 2];
```

在满二叉树中父节点与子节点之间的访问非常简单，父节点$k$的左右子节点为$2\times k$和$2\times k+1$
```cpp
inline int ls(int k){return k<<1;}
inline int rs(int k){return k<<1|1;}
```
我们采用递归分治的方式构建线段树，每次将区间分为左右两部分，下面是现实：
```cpp
inline void push_up(int k){
    f[k].data=f[ls(k)].data+f[rs(k)].data;//从下向上传递区间值
}
void build(int k,int l,int r){
    f[k].l=l,f[k].r=r;
    if(l==r){
        f[k].data=a[l];//叶子节点存原数组的值
        return;
    }
    int m=(l+r)>>1;//折半
    build(ls(k),l,m);//递归左儿子
    build(rs(k),m+1,r);//递归右儿子
    push_up(k);
}
```
#### 线段树的基本功能
##### 区间查询
线段树的区间查询非常简单，只要递归搜索线段树，将被搜索区间覆盖的区间节点累加到结果上即可。可以实现对区间最值，区间和的查询，下面以区间和为例，给出示例代码
```cpp
void ask(int k,int l,int r){
    if(l<=f[k].l&&r>=f[k].r)return f[k].data;
    int m=(f[k].l+f[k].r)>>1;
    int res=0;
    if(l<=m)res+=ask(ls(k),l,r);//与左节点有重叠
    if(r>m)res+=ask(rs(k),l,r);//与右节点右重叠
    return res;
}
```
时间复杂度为$O(\log n)$
##### 修改
线段树的基本应用是单点修改。单点修改只要修改叶子节点的值，再从下至上的修改更新线段树即可，时间复杂度为$O(\log n)$。比较简单不详细介绍了。

[P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
> 题意：已知一个数列，你需要进行下面两种操作：
1 x y k :将[x,y]区间每一个数加上 k。
2 x y:输出区间[x,y]每一个数的和。

对于区间修改，我们就要用到$Lazy-Tag$**技术**。$Lazy-Tag$的核心思想就是通过延迟对节点信息的更改，从而减少可能不必要的操作次数。

在用$Lazy-Tag$方法时，若修改一个线段区间，就只对这个线段区间进行整体上的修改，其内部每个元素的内容先不做修改，只有当这个线段区间的一致性被破坏时（即查询或要修改其子区间时），才把变化值传递给下一层的子区间，我们称这个过程为下传标记，一般我们会单独写一个$push\_down$函数来完成这一操作。

我们可以额外定义一个$tag$数组或者在结构体中多加一个变量来记录每个线段区间的标记。

我们以上面这道题为例给出完整的线段树代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(2e5+7)
typedef long long ll;
const int mod = 1e9+7;
typedef vector<int> vi;
//定义线段树
struct{
    int l,r;
    ll sum,tag;
}f[MAX<<2];
//求左右子节点的函数和区间折半的函数
inline int ls(int k){return k<<1;}
inline int rs(int k){return k<<1|1;}
inline int md(int l,int r){return (l+r)>>1;}
int n,m;
//从下向上传递区间值
void push_up(int k){f[k].sum=f[ls(k)].sum+f[rs(k)].sum;}

//递归的构建线段树
void build(int k,int l,int r){
    f[k].l=l,f[k].r=r,f[k].tag=0;//初始化每个节点维护的区间和tag标记
    if(l==r){
        cin>>f[k].sum;
        return;
    }
    int m=md(l,r);//分治：折半
    build(ls(k),l,m);
    build(rs(k),m+1,r);
    push_up(k);
}

//给区间打标记，并更新该区间值
inline void add_tag(int k,ll x){
    f[k].sum+=(f[k].r-f[k].l+1)*x;
    f[k].tag+=x;
}
//下传标记
inline void push_down(int k){
    add_tag(ls(k),f[k].tag);
    add_tag(rs(k),f[k].tag);
    f[k].tag=0;
}

//区间修改
void update(int k,int l,int r,ll x){
    //修改区间完全覆盖当前区间时，就对区间进行修改，不深入其子节点
    if(l<=f[k].l&&r>=f[k].r){
        add_tag(k,x);
        return;
    }
    push_down(k);//下传标记
    int m=md(f[k].l,f[k].r);
    if(l<=m)update(ls(k),l,r,x);//与左节点有重叠,递归左子树
    if(r>m)update(rs(k),l,r,x);//与右节点右重叠,递归右子树
    push_up(k);//更新
}

ll ask(int k,int l,int r){
    //查询区间完全覆盖当前区间时，直接返回区间值，不深入其子节点
    if(l<=f[k].l&&r>=f[k].r)return f[k].sum;
    push_down(k);//下传标记
    int m=md(f[k].l,f[k].r);
    ll res=0;
    if(l<=m)res+=ask(ls(k),l,r);//与左节点有重叠,递归左子树
    if(r>m)res+=ask(rs(k),l,r);//与右节点右重叠,递归右子树
    return res;
}

void solve(){
    cin>>n>>m;
    build(1,1,n);//建树
    while(m--){
        ll op,l,r,x;
        cin>>op>>l>>r;
        if(op==1){
            cin>>x;
            update(1,l,r,x);//区间修改
        }
        else cout<<ask(1,l,r)<<'\n';//区间查询
    }
}

int main() {
    ios::sync_with_stdio(false);
        solve();

    return 0;
}
```
整个代码时间复杂为$O(m\log n)$，$m$次操作，每次修改和查询都是$O(\log n)$

#### 线段树的基础应用

##### 特殊的区间修改
[Can you answer these queries?](https://acm.hdu.edu.cn/showproblem.php?pid=4027)
> 题意：对区间求每个数的开方，输出区间查询
元素个数$N\le 10^5$，元素之和不超过$2^{63}$，操作次数$M\le 10^5$`

对于该题很容易我们能发现一个不超过$2^{63}$的数开方的次数不会超过$7$次，所以我们对于不等于$1$的数单独修改它，再递归的修改其父节点；当一个区间的数都为`$1$`时，就不对该区间进行修改。

复杂度：每个数开发$7$次，共$7N$次，在做$M$次修改复杂度为$M\log N$

##### 同时做多种区间修改
[P3373 【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)
> 如题，已知一个数列，你需要进行下面三种操作：
>- 1.将某区间每一个数乘上 x；
>- 2.将某区间每一个数加上 x；
>- 3.求出某区间每一个数的和。

我们设维护的区间和为$sum$，当我们可以将其看成$1\times sum+0$，当我对其进行一次操做$2$和操做$1$时，区间和变为$k_1sum+b_1$，我们再重复一边操做得到:
```math
k_2(k_1sum+b_1)+b_2=k_2k_1sum+k_2b_1+b_2
```
我们要维护两种标记$add 、multi$
可见我们对区间标记修改时，先要做$multi$的修改，并且将$add$修改为$add\times multi$，再进行$add$修改。

###### 进阶：[Transformation](https://acm.hdu.edu.cn/showproblem.php?pid=4578)

##### 线段树的二分操做
[Vases and Flowers](https://acm.hdu.edu.cn/showproblem.php?pid=4614)
线段树的结构就是二分，在线段树上进二分答案非常方便，这题就是非常典型的二分答案，思路非常简单，用线段树进行区间更新的操做，在线段树上用二分法去找到放第一个花的位置，和最后一个花放的位置即可。


#### 吉司机线段树
##### 区间最值操作
[Gorgeous Sequence](https://acm.hdu.edu.cn/showproblem.php?pid=5306)
> 有一个长度为$n$ 的序列$ a$ 。我们使用 $a_i $来表示此序列中的$i -th$ 元素。应对此序列执行以下三种类型的操作。
0 x y t ： 对于每个 $x≤i≤y$ ，我们使用 $min(a_i,t)$ 来替换原来的 $a_i$的值。
1 x y ： 打印$ a_i $的最大值 那$x≤i≤y$ .
2 x y ： 打印$ a_i$ 的总和 那 $x≤i≤y$ .

线段树解题，解题要用到$Lazy-Tag$标记来实现高效的修改。如何设计标记就是解题的关键。吉如一在其论文中提到的解决方法定义的四个标记，巧妙的将区间最值和区间和结合起来。

对于线段树的每个节点，我们定义四个标记；区间和$sum$、区间最大值$ma$，区间严格次大值$se$，最大值个数$cnt$。

当我们要用$min(a_i,x)$对区间$[l,r]$进行修改时，在线段树上定位到对应区间后，有以下三种情况：
- 当$ma\le x$时，这次修改不影响节点，不进行修改
- 当$se< x<ma$时，这次修改值影响最大值，更新$sum=sum-cnt\times(ma -x)$，并且修改最大值$ma=x$。
- 当$se\ge x$时，无法直接修改这个节点，递归它的左右儿子

上述算法的关键是严格次大值$se$，他起到剪枝的作用。时间复杂度是 $O(m\log n)$ 。

下面是基础吉司机线段树的模板代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAX int(1e6+7)
typedef long long ll;
const int mod = 1e9 + 7;
typedef vector<int> vi;
//交hduoj加上注释代码才能过
//const int L = 1 << 20 | 1;
//char buffer[L], * S, * TT;
//#define getchar() ((S==TT&&(TT=(S=buffer)+fread(buffer,1,L,stdin),S==TT))?EOF:*S++)
inline ll input() {
    bool sym = false; ll res = 0; char ch = getchar();
    while (!isdigit(ch))sym |= (ch == '-'), ch = getchar();
    while (isdigit(ch))res = (res << 3) + (res << 1) + (ch ^ 48), ch = getchar();
    return sym ? -res : res;
}
//定义线段树
struct {
    ll l, r, sum, cnt, ma, se;
}f[MAX << 2];
//求左右子节点的函数
inline int ls(int k) { return k << 1; }
inline int rs(int k) { return k << 1 | 1; }
inline int md(int l, int r) { return (l + r) >> 1; }
int n, m;
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

void solve() {
    n = input(), m = input();
    build(1, 1, n);
    for (int i = 0; i < m; ++i) {
        ll op = input(), l = input(), r = input();
        if (op == 0)change(1, l, r, input());
        if (op == 1)printf("%lld\n", ask2(1, l, r));
        if (op == 2)printf("%lld\n", ask1(1, l, r));
    }
}

int main() {
    ios::sync_with_stdio(false); ll T;
    for (T = input(); T--;)solve();

    return 0;
}
```
练习：[Just Another Game of Stones](https://codeforces.com/group/a15Z3BoCvW/contest/473006/problem/J)这是一道吉司机线段树+博弈论的题目。
[AC代码](https://www.luogu.com.cn/paste/vpb1l9fc)












