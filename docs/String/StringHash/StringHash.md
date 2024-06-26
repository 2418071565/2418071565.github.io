# 进制哈希

## **简介**

字符串哈希是常见的字符串处理手段，一般的字符串哈希函数会采用进制哈希，即将一个字符串转化为一个 $P$ 进制数，将这个数当作 $key$ 值。

## **进制哈希函数**

设定一个 $P$ 进制数，和模数 $M$ ，我们把一个字符串的每一个字符看作该 $P$ 进制数上的一位，将其转化为 $P$ 进制数，得到的值就是进制哈希的 $key$ 。

举个例子，设字符串 $S=abcde$，我们将它转化成 $P$ 进制数:

$$
h_S=(a\times P^4 + b\times P^3 + c\times  P^2 + d\times P^1 + e\times P^0) \% M
$$

这里的字符可以用在字母表中的次序替换，也可也用 $ASCii$ 码来替换。

$P$ 进制一般会选取 $31,131,1313,13131$ 等，可以有效减少冲突。

### **BKDRHash**

该函数在实现时采用了一种"隐式取余法"，即自然溢出法。我们将哈希值 $h$ 设定为 $unsigned\space long\space long$ ，这样在累加过程中，超出 $ull$ 的范围就相当于对其模 $2^{64}−1$ 。这样可以避免的低效的取模运算。

```cpp
typedef unsigned long long ull;
const int p = 131;
ull BKDRHash(const char* s)
{
	ull h = 0;
	while(*s)h += h * p + (*s++);
	return h;
}
```

### **双哈希法**

使用哈希，我们最不希望看道出现冲突。对于进制哈希，为了避免冲突，我们可以使用两组不同的进制$P$和模数$M$，计算得到两个哈希值，将这两哈希值形成的二元组作为$key$，即

$$
h_S = <h_1,h_2>
$$

```cpp
const ll p[] = {29,31};
const ll M[] = {int(1e9 + 9), 998244353};
pair<ll,ll> DHash(const char* s)
{
	pair<ll,ll> h = {0,0};
	while(*s)
	{
		h.first += (h.first * p[0] + *s) % M[0];
		h.second += (h.second * p[1] + *s) % M[1];
		s++;
	}
	return h;
}
```

## **计算子串哈希值**

由于将字符串转化成了 $P$ 进制数，所以我们可以把对字符串的操作看出对 $P$ 进制数的操作，对数的操作往往比对字符串操作更加容易。

例如，我们要拼接两个字符串 $xy$ 和 $cyb$ ，转化成对数的操作，就是 $h_{xy}\times P ^{3} + h_{cyb}$ ，即将 $h_{xy}$ 左移 $3$ 位，在加上 $h_{cyb}$ ，会发现这和 $10$ 进制数拼接一模一样。

那么截取一个子串也就很容易了，例如从 $abcdef$ 中截取子串 $cde$

$$
h_{abcde} - h_{ab} \times P^{3}
$$

我们可以看出计算一个子串的哈希值，需要前缀串的哈希值，我们用一个数组 $hsh[i]$ 表示到第 $i$ 个位置的哈希值，那么一个区间为 $[l,r]$ 的子串的哈希值就是

$$
hsh[r] - hsh[l-1]\times P^{r - l + 1}
$$

为了提高效率，我们可以将 $P^i$ 提前预处理好，存到数组 $pM[]$ 中。并且将要处理的字符串的前缀串的哈希值预处理出来，存到数组 $hsh[]$ 中。

```cpp
// 初始化
SHash()
{
	tot = 0;
	for(int i = 0;i < 2;++i)
	{
		pM[i][0] = 1;
		hsh[i][0] = 0;
	}
}

// 添加维护的字符
void add(char ch)
{
	++tot;
	for(int i = 0;i < 2;++i)
	{
		pM[i][tot] = pM[i][tot - 1] * p[i] % M[i];
		hsh[i][tot] = (hsh[i][tot - 1] * p[i] + ll(ch)) % M[i];
	}
}
```

单哈希也是同理。

## **字符串哈希的应用**

### **最长回文子串**

我们设串 $S$ 是一个无限长的串，其中 $S[l,r]$ 是一个最长回文子串，那么一定满足 $S[l+1,r-1],S[l+2,r-2]\dots$ 也一定是回文串，但 $S[l-1,r+1],S[l-2,r+2]\dots$ 一定不是回文串 ，所以该问题满足单调性。

我们枚举每个中心，二分去找该位置的回文半径即可。复杂度是 $O(n\log n)$。

### **最长公共子字符串**

要求从 $m$ 个总长度不超过 $n$ 的字符串中找到最长公共子字符串。

同样是二分，因为如果长度为 $k$ 的公共子串是存在的，那么长度为 $k-1,k-2,\dots$ 也是存在的。

每次我们将所以字符串长度为 $k$ 的子串都转化成进制哈希值，存到 $set$ 或 $map$ 中，最后取交集。

时间复杂度 $O(m+n\log n)$


## **模板**

以题目 [CF1200E](https://codeforces.com/contest/1200/problem/E) 为例给出进制哈希模板，这里给出双哈希模板。

??? code "SHash"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int MAX = 1e6 + 100;

    // 字符串哈希模板
    // =================================================================================
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
    // =================================================================================


    // SHash内部空间太大，建议定义为全局变量
    SHash now, tmp;
    void solve()
    {
        int n;
        cin >> n;
        string ans;
        for (int i = 0; i < n; ++i)
        {
            string s;
            cin >> s;

            // 显示调用构造函数，初始化tmp全局变量
            // 用法详细见https://blog.csdn.net/c661280411470yb/article/details/134018212?spm=1001.2014.3001.5502
            new (&tmp) SHash();

            for (char& ch : s)
                tmp.add(ch);
            // 新串和当前串长度取小
            int mi = min(ans.size(), s.size());
            int nlen = 0;

            // 找到最长的相等前后缀子串
            for (int len = mi; len >= 1; --len)
            {
                if (now.getHash(ans.size() - len + 1, ans.size()) == tmp.getHash(1, len))
                {
                    nlen = len;
                    break;
                }
            }
            for (int j = nlen; j < s.size(); j++)
                ans.push_back(s[j]), now.add(s[j]);
        }
        cout << ans << '\n';
    }

    int main()
    {
        ios::sync_with_stdio(false);
        cin.tie(0), cout.tie(0);
        solve();
        return 0;
    }
    ```

---------------

参考文章：<br>

《算法竞赛-下册》

[Oi Wiki-字符串哈希](https://oi-wiki.org/string/hash/)

[CSDN-【算法学习】字符串哈希（Hash）](https://blog.csdn.net/Mikchy/article/details/103995537)



