[题目链接](https://codeforces.com/contest/1894/problem/D)


给你一个由 $n$ 个整数组成的数组 $a$ ，以及一个由 $m$ 个整数组成的数组 $b$ 。

让 $\text{LIS}(c)$ 表示数组 $c$ 的 [最长递增子序列](https://en.wikipedia.org/wiki/Longest_increasing_subsequence) 的长度。例如， $\text{LIS}([2, \underline{1}, 1, \underline{3}])$ = $2$ ， $\text{LIS}([\underline{1}, \underline{7}, \underline{9}])$ = $3$ ， $\text{LIS}([3, \underline{1}, \underline{2}, \underline{4}])$ = $3$ 。

您需要在数组 $a$ 中的任意位置以任意顺序插入数字 $b_1, b_2, \ldots, b_m$ 。得到的数组为 $c_1, c_2, \ldots, c_{n+m}$ 。你需要选择插入的位置以**最小** $\text{LIS}(c)$ 。

形式上，你需要找到一个数组 $c_1, c_2, \ldots, c_{n+m}$ 同时满足以下条件：

- 数组 $a_1, a_2, \ldots, a_n$ 是数组 $c_1, c_2, \ldots, c_{n+m}$ 的子序列。
- 数组 $c_1, c_2, \ldots, c_{n+m}$ 由可能重新排列的数字 $a_1, a_2, \ldots, a_n, b_1, b_2, \ldots, b_m$ 组成。
- 数组 $\text{LIS}(c)$ 的值是所有合适的数组 $c$ 中可能的**最小值。