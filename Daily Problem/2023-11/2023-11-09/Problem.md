[题目链接](https://codeforces.com/gym/104160/problem/C)

给定一个整数序列 $a_1, a_2, \ldots, a_n$ 和一个正整数 $d$ ，你需要将序列箝位在满足 $0 \le r-l \le d$ 的范围 $[l,r]$ 内，使 $\sum_{i=1}^{n-1}|a_i - a_{i+1}|$ 最大化，其中 $|x|$ 是 $x$ 的绝对值。

更具体地说，将序列箝位到范围 $[l,r]$ 使得每个元素

$$
a_i := \left\{ \begin{array}{rcl} l, & a_i &lt; l; \\ a_i, & l \le a_i \le r; \\ r, & a_i &gt; r. \\ \end{array} \right.
$$ $l$ 和 $r$ 都是在给定的约束条件下由你决定的任意实数。可以证明最大和总是整数。