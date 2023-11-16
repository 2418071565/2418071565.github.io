

我们可以看到，数组的第一个元素 $b$ 决定了所有其他值 $b_{i + 1} = b_1 \oplus a_1 \cdots \oplus a_i$ 。

因此，让我们遍历 $b_1$ 的值。对于 $b_1$ 的每一个值，我们都需要检查它是否产生了正确的排列（即所有的 $b_i < n$ ）。为了快速完成检查，我们可以生成一个数组 $c$ ，其中 $c_i$ 是数组 $a$ 中第一个 $i$ 元素的 XOR（即 $c_i = a_1 \oplus a_2 \oplus \cdots \oplus a_i$ 和 $c_0 = 0$ ）。我们可以看到 $b_{i + 1} = b_1 \oplus c_i$ 。

需要注意的是，我们实际上并不需要检查最小值是否恰好是 $0$ ，而且所有元素都是不同的：我们可以保证答案是存在的，因此所有值 $[0, c_1, c_2, c_3, \dots, c_{n-1}]$ 都是成对不同的，而且无论我们选择哪个 $b_1$ ，所有 $b_i$ 也都是成对不同的。

我们用$01$字典树来求$b_1$和$c_i$最大异或和，找到一个可以使最大异或和不超过$n-1$的$b_1$即可。

[字典树详解](../../String/Trie/)

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 4e6 + 100;
typedef long long ll;
typedef unsigned long long ull;
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
	// int T;
	// for (cin >> T; T--;)
		solve();
	// f()
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

BI_Trie t;
void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 1;i <= n- 1;++i)
	{
		cin >> a[i];
		a[i] = a[i] ^ a[i - 1];
		t.insert(a[i]);
	}
	for(int i = 0;i <= n - 1;++i)
	{
		if(t.max_xor(i) <= n - 1)
		{
			for(int j = 1;j <= n;++j)
				cout << (a[j - 1] ^ i)  << " \n"[i == n];
			return;
		}
	}

}
```