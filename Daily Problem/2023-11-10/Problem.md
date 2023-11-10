"[题目链接](https://codeforces.com/problemset/problem/1879/D)" 
给你一个长度为 $n$ 的数组 $a$ ，由非负整数组成。

您必须计算 $\sum_{l=1}^{n} \sum_{r=l}^{n} f(l, r) \cdot (r - l + 1)$ 的值，其中 $f(l, r)$ 是 $a_l \oplus a_{l+1} \oplus \dots \oplus a_{r-1} \oplus a_r$ （字符 $\oplus$ 表示位向 XOR）。

由于答案可能非常大，因此请打印它的模数 $998244353$ 。