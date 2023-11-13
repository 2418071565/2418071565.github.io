Exercise
=================
|题目|难度|AC|知识|
|:-:|:-:|:-:|:-:|
|[P4588](https://www.luogu.com.cn/problem/P4588)|普及+/提高|[AC](https://www.luogu.com.cn/record/122054122)|前缀积+线段树|
|[Just Another Game of Stones](https://codeforces.com/group/a15Z3BoCvW/contest/473006/problem/J)||[AC](https://www.luogu.com.cn/paste/vpb1l9fc)|博弈论+吉司机线段树|
|[ Iva & Pav](https://codeforces.com/contest/1878/problem/E)||[AC](https://www.luogu.com.cn/paste/6amzvq8x)|二分+线段树|
|[CF1881G](https://codeforces.com/contest/1881/problem/G)|2000|[AC](https://codeforces.com/contest/1881/submission/229705725)|回文串+线段树|
|[LC.715](https://leetcode.cn/problems/range-module/description/)|困难|√|动态开点线段树模板|

#### LC.715
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