
```cpp
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int MAX = 6e5 + 100;
typedef long long ll;
const ll mod = 998244353;
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
	int T;
	for (cin >> T; T--;)
	solve();
	// f()
	// cerr << "Time Used: " << clock() - c1 << " ms\n";
	return 0;
}

struct ED
{
	int to,nxt,w;
}ed[MAX];
int head[MAX],tot;
void addEdge(int u,int v,int w)
{
	ed[++tot].to = v;
	ed[tot].nxt = head[u];
	ed[tot].w = w;
	head[u] = tot;
}

void solve()
{
	int n,a,b;
	cin >> n >> a >> b;
	memset(head,-1,sizeof(int)*(n + 1));
	tot = 0;
	for(int i = 0;i < n - 1;++i)
	{
		int u,v,w;
		cin >> u >> v >> w;
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	set<int> st;
	function<void(int,int,int)> dfs1 = [&](int u,int fa,int now)
	{
		st.insert(now);
		for(int i = head[u];~i;i = ed[i].nxt)
		{
			int v = ed[i].to, w = ed[i].w;
			if(v == fa || v == b)continue;
			dfs1(v,u,now ^ w);
		}
	};
	dfs1(a,0,0);
	function<bool(int,int,int)> dfs2 = [&](int u,int fa,int now)
	{
		for(int i = head[u];~i;i = ed[i].nxt)
		{
			int v = ed[i].to, w = ed[i].w;
			if(v == fa)continue;
			if(st.find(now ^ w) != st.end())
				return cout << "Yes\n",true;
			if(dfs2(v,u,now ^ w))return true;
		}
		return false;
	};
	if(!dfs2(b,0,0))cout << "No\n";
}
```