[问题链接](https://codeforces.com/contest/750/problem/C)


输入 n(1≤n≤2e5)，表示某人参加了 n 场 CF 比赛。
然后输入 n 行，每行两个数 c(-100~100) 和 d(1~2)，其中 c 表示比赛后这个人的 rating 变化了 c（正数表示上分，负数表示掉分，0 表示不变），d 表示这个人参加的是 div1 还是 div2。
比赛前 rating >= 1900 才能参加 div1；比赛前 rating <= 1899 才能参加 div2。

输出 n 场比赛后，rating 最大可以是多少。
如果 rating 可以无限大，输出 Infinity。

如果输入的数据自相矛盾，输出 Impossible。
