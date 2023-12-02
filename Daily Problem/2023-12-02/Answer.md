[$01_Trie$ 模板](../../String/Trie/)。



```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e6 + 100;
typedef long long ll;
typedef unsigned long long ull;
const ll mod = 998244353;
const ll inf = 0x3f3f3f3f3f3fll;
const double pi = 3.1415926535;
void solve();

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	// clock_t c1 = clock();
#ifdef LOCAL
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
#endif
	//int T;
	//for (cin >> T; T--;)
		solve();
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

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

BI_Trie f;
struct ED
{
    int v,w;
};
void solve()
{
    int n;
    cin >> n;
    vector<vector<ED>> g(n + 1);
    for(int i = 0;i < n - 1;++i)
    {
        int u,v,w;
        cin>> u >> v >> w;
        g[u].push_back({v,w});
    }
    vector<int> a (n + 1);
    function<void(int,int,int)> dfs = [&](int u,int fa,int now)
    {
        a[u] = now;
        f.insert(a[u]);
        for(auto& [v,w]:g[u])
        {
            if(v == fa)continue;
            now ^= w;
            dfs(v,u,now);
            now ^= w;
        }
    };
    dfs(1,0,0);
    int ans = 0;
    for(int i = 1;i <= n;++i)
        ans = max(ans,f.max_xor(a[i]));
    cout << ans <<'\n';
}
```