### Problem Set

|           题目           |      知识点       |  AC代码   |
| :----------------------: | :---------------: | :-------: |
| P2756-飞行员配对方案问题 | 二分图匹配-网络流 | P2756.cpp |
|    P2774-方格取数问题    | 棋盘二分图-网络流 | P2774.cpp |
|  P4009-汽车加油行驶问题  |   分层图-费用流   | P4009.cpp |
|      P4014-分配问题      |  完美匹配-费用流  | P4014.cpp |
|      P4015-运输问题      |      费用流       | P4015.cpp |
|    P4016-负载平衡问题    |      费用流       | P4016.cpp |

##### P2756.cpp


```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7fffffff;

const int N = 405, M = 100005;

int n, m, s, t;
int head[N], cnt = 1;
struct node {
	int to, next, w;
} edge[M];

void add(int u, int v, int w) {
	cnt++;
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
	cnt++;
	edge[cnt].w = 0;
	edge[cnt].to = u;
	edge[cnt].next = head[v];
	head[v] = cnt;
}
int now[N], dep[N];
int bfs() {
	for (int i = 0; i <= t; i++) dep[i] = INF;
	dep[s] = 0;
	now[s] = head[s];
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (edge[i].w > 0 && dep[v] == INF) {
				q.push(v);
				now[v] = head[v];
				dep[v] = dep[u] + 1;
				if (v == t) return 1;
			}
		}
	}
	return 0;
}
int dfs(int u, ll sum) {
	if (u == t) return sum;
	ll k, flow = 0;
	for (int i = now[u]; i && sum > 0; i = edge[i].next) {
		now[u] = i;
		int v = edge[i].to;
		if (edge[i].w > 0 && (dep[v] == dep[u] + 1)) {
			k = dfs(v, min(sum, (ll)edge[i].w));
			if (k == 0) dep[v] = INF;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			flow += k;
			sum -= k;
		}
	}
	return flow;
}
ll Dinic() {
	ll ans = 0;
	while (bfs()) ans += dfs(s, INF);
	return ans;
}


int main() {
	scanf("%d%d", &m, &n);
	int u, v;
	while (~scanf("%d%d", &u, &v)) {
		if (u == -1 && v == -1) break;
		add(u, v, 1);
	}
	s = 0;
	t = n + 1;
	for (int i = 1; i <= m; i++) {
		add(s, i, 1);
	}
	for (int i = m + 1; i <= n; i++) {
		add(i, t, 1);
	}
	printf("%lld\n", Dinic());
	std::vector<pair<int, int> > ans;
	for (int i = 1; i <= m; i++) {
		for (int j = head[i]; j; j = edge[j].next) {
			if (edge[j].w == 0 && edge[j].to != s) {
				ans.push_back(make_pair(i, edge[j].to));
			}
		}
	}
	for (auto d : ans) {
		printf("%d %d\n", d.first, d.second);
	}
}
```

##### P2774.cpp

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7fffffff;

const int N = 10005, M = 1000005;

int n, m, s, t;
int head[N], cnt = 1;
struct node {
	int to, next, w;
} edge[M];

void add(int u, int v, int w) {
	cnt++;
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
	cnt++;
	edge[cnt].w = 0;
	edge[cnt].to = u;
	edge[cnt].next = head[v];
	head[v] = cnt;
}
int now[N], dep[N];
int bfs() {
	for (int i = 0; i <= t; i++) dep[i] = INF;
	dep[s] = 0;
	now[s] = head[s];
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			if (edge[i].w > 0 && dep[v] == INF) {
				q.push(v);
				now[v] = head[v];
				dep[v] = dep[u] + 1;
				if (v == t) return 1;
			}
		}
	}
	return 0;
}
int dfs(int u, ll sum) {
	if (u == t) return sum;
	ll k, flow = 0;
	for (int i = now[u]; i && sum > 0; i = edge[i].next) {
		now[u] = i;
		int v = edge[i].to;
		if (edge[i].w > 0 && (dep[v] == dep[u] + 1)) {
			k = dfs(v, min(sum, (ll)edge[i].w));
			if (k == 0) dep[v] = INF;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			flow += k;
			sum -= k;
		}
	}
	return flow;
}
ll Dinic() {
	ll ans = 0;
	while (bfs()) ans += dfs(s, INF);
	return ans;
}

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void LuanGao() {
	int r, c; scanf("%d%d", &r, &c);
	ll s1 = 0, s2 = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			ll w; scanf("%lld", &w);
			if ((i + j) & 1) s1 += w;
			else s2 += w;
		}
	}
	printf("%lld\n", max(s1, s2));
}

int main() {
	//LuanGao();
	ll r, c;
	scanf("%lld%lld", &r, &c);
	ll sum = 0;
	s = 0; t = r * c + 1;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			ll w; scanf("%lld", &w); sum += w;
			if ((i + j) % 2 == 0) {
				add(s, (i - 1)*c + j, w);
				for (int k = 0; k < 4; k++) {
					int x = i + dx[k];
					int y = j + dy[k];											
					if (x >= 1 && y >= 1 && x <= r && y <= c) {
						add((i - 1)*c + j, (x - 1)*c + y, INF);
					}
				}
			} else {
				add((i - 1)*c + j, t, w);
			}
		}
	}
	printf("%lld\n", sum - Dinic());
}
```

##### P4009.cpp

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7fffffff;

const int N = 200015, M = 1000015;
int n, m, s, t;
int head[N], cnt = 1;
struct node {
	int to, next, w, c;
} edge[M];

void add(int u, int v, int w, int c) {
	cnt++;
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	edge[cnt].c = c;
	head[u] = cnt;
	cnt++;
	edge[cnt].w = 0;
	edge[cnt].to = u;
	edge[cnt].next = head[v];
	edge[cnt].c = -c;
	head[v] = cnt;
}
int dis[N], pre[N], last[N], flow[N];
bool inq[N];

queue<int> q;
bool spfa(int s, int t) {
	for (int i = 0; i <= t + 10; i++) {
		dis[i] = flow[i] = INF;
		inq[i] = false;
	}
	q.push(s);
	inq[s] = 1; dis[s] = 0; pre[t] = -1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			int w = edge[i].w;
			int cost = edge[i].c;
			if (w > 0 && dis[v] > dis[u] + cost) {
				dis[v] = dis[u] + cost;
				pre[v] = u;
				last[v] = i;
				flow[v] = min(w, flow[u]);
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return pre[t] != -1;
}

void MinCost_MaxFlow(int& maxflow, int& mincost) {
	maxflow = mincost = 0;
	while (spfa(s, t)) {
		int now = t;
		maxflow += flow[t];
		//这里费用为单位流量的费用
		mincost += flow[t] * dis[t];
		while (now != s) {
			edge[last[now]].w -= flow[t];
			edge[last[now] ^ 1].w += flow[t];
			now = pre[now];
		}
	}
}
int f(int x, int y, int k) {
	return (x - 1) * n + y + k * n * n;
}
int K, A, B, C;
int main() {
	scanf("%d%d%d%d%d", &n, &K, &A, &B, &C);
	s = (K + 1) * n * n + 1;
	t = s + 1;
	add(s, f(1, 1, 0), 1, 0);
	for (int k = 1; k <= K; k++) {
		add(f(n, n, k), t, 1, 0);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int op; scanf("%d", &op);
			if (op == 1) {
				for (int k = 1; k <= K; k++) {
					add(f(i, j, k), f(i, j, 0), 1, A);
					if (i < n) {
						add(f(i, j, 0), f(i + 1, j, 1), 1, 0);
					}
					if (j < n) {
						add(f(i, j, 0), f(i, j + 1, 1), 1, 0);
					}
					if (i > 1) {
						add(f(i, j, 0), f(i - 1, j, 1), 1, B);
					}
					if (j > 1) {
						add(f(i, j, 0), f(i, j - 1, 1), 1, B);
					}
				}
			} else {
				for (int k = 0; k <= K - 1; k++) {
					if (i < n) {
						add(f(i, j, k), f(i + 1, j, k + 1), 1, 0);
					}
					if (j < n) {
						add(f(i, j, k), f(i, j + 1, k + 1), 1, 0);
					}
					if (i > 1) {
						add(f(i, j, k), f(i - 1, j, k + 1), 1, B);
					}
					if (j > 1) {
						add(f(i, j, k), f(i, j - 1, k + 1), 1, B);
					}
				}
				add(f(i, j, K), f(i, j, 0), 1, A + C);
			}
		}
	}
	int maxflow = 0, mincost = 0;
	MinCost_MaxFlow(maxflow, mincost);
	printf("%d\n", mincost);
}
```

##### P4014.cpp

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7fffffff;

const int N = 200005, M = 200005;
int n, m, s, t;
int head[N], cnt = 1;
struct node {
	int to, next, w, c;
} edge[M];

void add(int u, int v, int w, int c) {
	cnt++;
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	edge[cnt].c = c;
	head[u] = cnt;
	cnt++;
	edge[cnt].w = 0;
	edge[cnt].to = u;
	edge[cnt].next = head[v];
	edge[cnt].c = -c;
	head[v] = cnt;
}
int dis[N], pre[N], last[N], flow[N];
bool inq[N];

queue<int> q;
bool spfa_min(int s, int t) {
	for (int i = 0; i <= 2 * n + 10; i++) {
		dis[i] = flow[i] = INF;
		inq[i] = false;
	}
	q.push(s);
	inq[s] = 1; dis[s] = 0; pre[t] = -1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			int w = edge[i].w;
			int cost = edge[i].c;
			if (w > 0 && dis[v] > dis[u] + cost) {
				dis[v] = dis[u] + cost;
				pre[v] = u;
				last[v] = i;
				flow[v] = min(w, flow[u]);
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return pre[t] != -1;
}

bool spfa_max(int s, int t) {
	for (int i = 0; i <= 2 * n + 10; i++) {
		dis[i] = flow[i] = -INF;
		inq[i] = false;
	}
	q.push(s);
	inq[s] = 1; dis[s] = 0; pre[t] = -1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			int w = edge[i].w;
			int cost = edge[i].c;
			if (w > 0 && dis[v] < dis[u] + cost) {
				dis[v] = dis[u] + cost;
				pre[v] = u;
				last[v] = i;
				flow[v] = min(w, flow[u]);
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return pre[t] != -1;
}

void MinCost_MaxFlow(int& maxflow, int& mincost) {
	maxflow = mincost = 0;
	while (spfa_min(s, t)) {
		int now = t;
		maxflow += flow[t];
		//这里费用为单位流量的费用
		mincost += flow[t] * dis[t];
		while (now != s) {
			edge[last[now]].w -= flow[t];
			edge[last[now] ^ 1].w += flow[t];
			now = pre[now];
		}
	}
}

int G[104][104];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &G[i][j]);
		}
	}
	s = 0, t = 2 * n + 1;

	for (int i = 1; i <= n; i++) {
		add(s, i, 1, 0);
		add(i + n, t, 1, 0);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int w = G[i][j];
			add(i, j + n, 1, w);
		}
	}

	int maxflow = 0, mincost = 0, maxcost = 0;
	MinCost_MaxFlow(maxflow, mincost);

	for (int i = 0; i <= 2 * n + 1; i++) {
		head[i] = 0;
	}
	cnt = 1;

	for (int i = 1; i <= n; i++) {
		add(s, i, 1, 0);
		add(i + n, t, 1, 0);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int w = -G[i][j];
			add(i, j + n, 1, w);
		}
	}

	MinCost_MaxFlow(maxflow, maxcost);

	printf("%d\n%d\n", mincost, -maxcost);
}
```

##### P4015.cpp

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7fffffff;

const int N = 200005, M = 200005;
int n, m, s, t;
int head[N], cnt = 1;
struct node {
	int to, next, w, c;
} edge[M];

void add(int u, int v, int w, int c) {
	cnt++;
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	edge[cnt].c = c;
	head[u] = cnt;
	cnt++;
	edge[cnt].w = 0;
	edge[cnt].to = u;
	edge[cnt].next = head[v];
	edge[cnt].c = -c;
	head[v] = cnt;
}
int dis[N], pre[N], last[N], flow[N];
bool inq[N];

queue<int> q;
bool spfa(int s, int t) {
	for (int i = 0; i <= n + 10; i++) {
		dis[i] = flow[i] = INF;
		inq[i] = false;
	}
	q.push(s);
	inq[s] = 1; dis[s] = 0; pre[t] = -1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			int w = edge[i].w;
			int cost = edge[i].c;
			if (w > 0 && dis[v] > dis[u] + cost) {
				dis[v] = dis[u] + cost;
				pre[v] = u;
				last[v] = i;
				flow[v] = min(w, flow[u]);
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return pre[t] != -1;
}

void MinCost_MaxFlow(int& maxflow, int& mincost) {
	maxflow = mincost = 0;
	while (spfa(s, t)) {
		int now = t;
		maxflow += flow[t];
		//这里费用为单位流量的费用
		mincost += flow[t] * dis[t];
		while (now != s) {
			edge[last[now]].w -= flow[t];
			edge[last[now] ^ 1].w += flow[t];
			now = pre[now];
		}
	}
}
int G[105][105];
int W[105];
int main() {
	int d;
	scanf("%d%d", &d, &n);
	n += d;
	s = 0;
	t = n + 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", W + i);
	}
	for (int i = 1; i <= d; i++) {
		for (int j = 1; j <= n - d; j++) {
			scanf("%d", &G[i][j]);
		}
	}

	for (int i = 1; i <= n; i++) {
		if (i <= d) {
			add(s, i, W[i], 0);
		} else {
			add(i, t, W[i], 0);
		}
	}
	for (int i = 1; i <= d; i++) {
		for (int j = 1; j <= n - d; j++) {
			add(i, j + d, INF, G[i][j]);
		}
	}

	int maxflow = 0, mincost = 0;
	MinCost_MaxFlow(maxflow, mincost);
	printf("%d\n", mincost);

	for (int i = 0; i <= t; i++) {
		head[i] = 0;
	}
	cnt = 1;
	for (int i = 1; i <= n; i++) {
		if (i <= d) {
			add(s, i, W[i], 0);
		} else {
			add(i, t, W[i], 0);
		}
	}
	for (int i = 1; i <= d; i++) {
		for (int j = 1; j <= n - d; j++) {
			add(i, j + d, INF, -G[i][j]);
		}
	}
	MinCost_MaxFlow(maxflow, mincost);
	printf("%d\n", -mincost);
}
```

##### P4016.cpp

```C++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x7fffffff;

const int N = 200005, M = 200005;
int n, m, s, t;
int head[N], cnt = 1;
struct node {
	int to, next, w, c;
} edge[M];

void add(int u, int v, int w, int c) {
	cnt++;
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	edge[cnt].c = c;
	head[u] = cnt;
	cnt++;
	edge[cnt].w = 0;
	edge[cnt].to = u;
	edge[cnt].next = head[v];
	edge[cnt].c = -c;
	head[v] = cnt;
}
int dis[N], pre[N], last[N], flow[N];
bool inq[N];

queue<int> q;
bool spfa(int s, int t) {
	for (int i = 0; i <= n + 10; i++) {
		dis[i] = flow[i] = INF;
		inq[i] = false;
	}
	q.push(s);
	inq[s] = 1; dis[s] = 0; pre[t] = -1;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for (int i = head[u]; i; i = edge[i].next) {
			int v = edge[i].to;
			int w = edge[i].w;
			int cost = edge[i].c;
			if (w > 0 && dis[v] > dis[u] + cost) {
				dis[v] = dis[u] + cost;
				pre[v] = u;
				last[v] = i;
				flow[v] = min(w, flow[u]);
				if (!inq[v]) {
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return pre[t] != -1;
}

void MinCost_MaxFlow(int& maxflow, int& mincost) {
	while (spfa(s, t)) {
		int now = t;
		maxflow += flow[t];
		//这里费用为单位流量的费用
		mincost += flow[t] * dis[t];
		while (now != s) {
			edge[last[now]].w -= flow[t];
			edge[last[now] ^ 1].w += flow[t];
			now = pre[now];
		}
	}
}

int main() {
	scanf("%d", &n);
	vector<int> vec(n + 1);
	int ave = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &vec[i]);
		ave += vec[i];
	}
	ave /= n;
	s = 0; t = n + 1;
	for (int i = 1; i <= n; i++) {
		vec[i] -= ave;
	}
	for (int i = 1; i <= n; i++) {
		if (vec[i] > 0) {
			add(s, i, vec[i], 0);
		} else if (vec[i] < 0) {
			add(i, t, -vec[i], 0);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (i != 1) {
			add(i, (i - 1), INF, 1);
		}
		if (i != n) {
			add(i, (i + 1), INF, 1);
		}
	}
	add(1, n, INF, 1);
	add(n, 1, INF, 1);
	int maxflow = 0, mincost = 0;
	MinCost_MaxFlow(maxflow, mincost);
	printf("%d\n", mincost);
}
```

