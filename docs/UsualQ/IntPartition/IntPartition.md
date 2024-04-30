
**前置知识：最大公因数($gcd$)**

## **问题**

给你一个含有 $n$ 个正整数的数组 $a$，你可以进行以下操作：

- 选择一个其中任意一个整数 $a_i$
- 用两个正整数 $x,y$ 替换掉 $a_i$ ，并且满足 $x+y=a_i$

现在要求你用最小的操作数，将 $a$ 中元素全部变为相同值。


## **思路**

确定最终数组最后相等的数很重要，我们设这个数是 $x$ 。那么数组中每个数都一定是 $x$ 的倍数，不然最后一定拆不出 $x$。并且要操作数最小，那就是要 $x$ 尽可能大，所以取整个数组的 $gcd$ 即可。

### **变形**

[题目连接](https://codeforces.com/contest/1909/problem/D){target="_blank"}

我们将替换操作改为 $x+y=a_i+k$，求最小操作数，其中 $k$ 是一个给定的值。


### **思路**

有一个额外的数 $k$ ，就很不好处理，想要利用上面的结论就要想办法将 $k$ 消掉。

我们把每个数都变化一下，令 $a_i'+k=a_i$，拆的两个数也变化一下，$x'+k=x，y'+k=y$。这样左右都有两个 $k$ ，就可以消掉了，得到下式：

$$
x'+y'=a_i'
$$

这样操作不就变成和上面相同了，我们将整个数组的所有 $a_i$ 变为 $a_i'$ ，再所有 $a_i'$ 的 $gcd$ 即可。

**判断不可能的情况**：

如果 $a_i'$ 有正有负，那么它一定是拆不成相同的，比如一个整数无论如何都不可能拆成两个负数相加，负数同理。

或者 $a_i'$ 中有 $0$ 但不是全为 $0$ 也是不行的。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve();

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	for (cin >> T; T--;)
	    solve();
	return 0;
}

void solve()
{
	ll n,k;
	cin >> n >> k;
	vector<ll> a(n + 1);
	bool isp = 0,isn = 0,isz = 0;
	for(int i = 1;i <= n;++i)
	{
		cin >> a[i],a[i] = a[i] - k;
		if(a[i] < 0)isn = 1;
		if(a[i] > 0)isp = 1;
		if(a[i] == 0)isz = 1;
	}
	if((!isp) && (!isn)) cout << "0\n";
	else if(isz || (isp && isn)) cout << "-1\n";
	else
	{
		ll x = 0;
		ll ans = 0;
		for(int i = 1;i <= n;++i)
			x = __gcd(x,abs(a[i]));
		for(int i = 1;i <= n;++i)
			ans += abs(a[i]) / x - 1;
		cout << ans << '\n';
	}
}
```