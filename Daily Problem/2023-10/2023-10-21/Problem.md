[问题链接](https://atcoder.jp/contests/arc127/tasks/arc127_d)

输入 n(1≤n≤250000) 和两个长为 n 的数组 a b，元素范围 [0,2^18)。
定义 f(i,j) = min(a[i] ⊕ a[j], b[i] ⊕ b[j])，其中 ⊕ 表示异或。
输出所有 f(i,j) 的和，其中 i<j。



