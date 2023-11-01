[问题链接](https://leetcode.cn/problems/minimum-number-of-groups-to-create-a-valid-assignment/description/)

给你一个长度为 n 下标从 0 开始的整数数组 nums 。

我们想将下标进行分组，使得 [0, n - 1] 内所有下标 i 都 恰好 被分到其中一组。

如果以下条件成立，我们说这个分组方案是合法的：

对于每个组 g ，同一组内所有下标在 nums 中对应的数值都相等。
对于任意两个组 g1 和 g2 ，两个组中 下标数量 的 差值不超过 1 。
请你返回一个整数，表示得到一个合法分组方案的 最少 组数。


