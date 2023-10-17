[【灵神的题解】](https://www.luogu.com.cn/blog/endlesscheng/solution-cf1765n)<br>
本题属于【字典序最小子序列问题】，可以用单调栈解决，时间复杂度严格 O(n)。

先看看允许有前导零要怎么做：直接遍历字符串，用单调栈维护，只要当前字符小于栈顶，就弹出栈顶，同时把 kk 减一。最后栈底到栈顶是单调非降的，把栈顶的 kk 个元素弹出。

回到原题，不允许有前导零，我们可以在前 k+1 个字符中找到第一个最小的非 0 字符，设其为下标为 j，那么肯定要把下标小于 j 的字符都删掉。然后从 j+1 开始按照上面的做法跑单调栈即可。

```cpp
#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;
const int MAX = 1e6 + 100;
typedef long long ll;

string s;
int p[MAX];
int k, n;
void solve()
{
	cin >> s >> k;
	n = s.size();
	int cnt = n - k;
	int id = -1;
	for (int i = 0; i <= k; ++i)
		if (id==-1||(s[i] > '0' && s[i] < s[id]))
			id = i;

	int tt = 1, hh = 1;
	cout<<s[id];
	for (int i = id + 1; i < n - cnt + 1; ++i)
	{
		while (hh < tt && s[i] < s[p[tt - 1]])
			tt--;
		p[tt++] = i;
	}
	for (int i = n - cnt + 1; i < n; ++i)
	{
		while (hh < tt && s[i] < s[p[tt - 1]])
			tt--;
		p[tt++] = i;
		cout << s[p[hh++]];
	}
	cout << '\n';
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	for (cin >> T; T--;)
		solve();
	return 0;
}
```
