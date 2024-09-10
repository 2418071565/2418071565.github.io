
## **引入**

很多题目中，需要我们计算出小于等于 $n$ 的所有素数。

如果每个数字进行一次质数检验，是 $O(n\sqrt{n})$，当 $n$ 到 $1e6$ 时，这样效率就很差了。

这就要用到筛法了。


## **埃氏筛**

筛法的核心思想就是：**质数的倍数不是质数。**

顺着这个思路，我们首先假设所有数都标记位质数，我们用一个数组 `is_p` 来记录是否为素数，$1$ 表示是，$0$ 表示否。

从 $2$ 开始，将将遇到的所有素数的倍数的 `is_p` 都改成 $0$。

```cpp
// N 在 1e5 ~ 1e7 都可以使用这个方法，更大范围可能就需要其他方法来判断素数了 
vector<bool> is_p(MAX,true);
void init() {
    is_p[0] = is_p[1] = 0;
    for(int i = 2;i < N;++i) {
        if(!is_p[i]) continue; // 不是素数直接跳过
        // 从 2 ~ i - 1 的倍数都已经遍历过了
        for(int j = i * i;j < N;j += i) 
            is_p[j] = 0;    // 筛调素数的倍数
    }
}
```

埃氏筛的复杂度是 $O(n\log{n}\log{n})$。大多数情况都够用了，题目也不会故意卡筛法的复杂度。

但也有一些优化可以做，我们可以发现，其实不必要将 $[1,n]$ 范围内的所有数字都遍历一遍，我们只要遍历 $[1,\sqrt{n}]$ ，就可以将 $[1,n]$ 范围内的质数都筛出来了。

```cpp
vector<bool> is_p(MAX,true);
void init() {
    is_p[0] = is_p[1] = 0;
    for(int i = 2;i * i < N;++i) {
        if(!is_p[i]) continue; // 不是素数直接跳过
        // 从 2 ~ i - 1 的倍数都已经遍历过了
        for(int j = i * i;j < N;j += i) 
            is_p[j] = 0;    // 筛调素数的倍数
    }
}
```

## **欧拉筛（线性筛）**

在埃氏筛中，同一个合数可能会被筛好多次，如：$30 = 2 \times 3\times 5$，$30$ 就会被 $2,3,5$ 都筛一遍。

那我们就要消除这样的重复，这里的想法就是：**让每个合数都被其最小的质因数筛出去。**比如：设 $p_1$ 是 $n$ 的最小质因数，$n'=\frac{n}{p_1}$，那么在欧拉筛中，$n$ 通过 $n'\times p_1$ 筛去。 

这里我们用一个数组 `pri` 来记录已经筛出的素数。先给出代码：

```cpp
vector<bool> is_p(MAX,true);
vector<int> pri;
void init() {
    is_p[0] = is_p[1] = 0;
    for(int i = 2;i < MAX;++i) {
        if(is_p[i]) {
            pri.push_back(i);
        }
        for(auto& j : pri) {
            if(i * j > MAX) break;
            // j 是 i * j 的最小质因数
            is_p[i * j] = 0;
            if(i % j == 0) {
                break;
            }
        }
    }
}
```

因为 `pri` 的数组里，质数一定是从小到达排列的，所以如果 $i$ 的因数里有 $j$ 了，`pri` 后面的质数枚举的质数 $j'$ 就不再是 $i \times j'$ 的最小质因数了，所以我们选择直接 `break`。后面比 $i * j$ 大的，$j$ 的倍数，会由后面枚举的其他数字去筛掉。


通过一次欧拉晒，我们会发现，我们同时也求得了 $[1,n]$ 所有数字的最小质因数。

### **求因数个数**

我们记 $d_i$ 为数字 $i$ 因数个数，记 $cnt_i$ 为数字 $i$ 最小质因数的幂次。$d_i$ 可以由一下公式算得：

$$
d_i = \prod_{i=1}^{m}(c_i + 1) 
$$

其中 $c_i$ 表示数字 $i$ 的质因数 $p_i$ 的幂次。

!!! note "证明"
    由唯一分解定理可知，$i$ 可以分解为：

    $$
    a=p^{c_1}_1 p^{c_2}_2\cdots p^{c_r}_r
    $$

    对于每个质因数 $p_i$ ，我们可以选 $[0,c_i]$ 个，来组成我们的因数，根据乘法原理，能得到因数个数为：

    $$
    d_i = \prod_{i=1}^{m}(c_i + 1) 
    $$

筛法求因数个数的思路如下：

- 当 $i$ 为质数时，$cnt_i = 1，d_i = 2$

- 当 $j$ 是 $i$ 的因数时（$i,j$ 的含义同上文线性筛）：
 
$$
\begin{matrix}
cnt_{i\times j} = cnt_i + 1\\
d_{i \times j} = \frac{d_i}{cnt_i}\times (cnt_{i \times j} + 1)
\end{matrix}
$$

- 当 $j$ 不是 $i$ 的因数时，$j$ 是质数，说明 $i,j$ 互质，$d_i$ 又是积性函数：

$$
\begin{matrix}
cnt_{i\times j} = 1\\
d_{i \times j} = d_i \times d_j
\end{matrix}
$$

实现如下：

```cpp
vector<bool> is_p(MAX,true);
vector<int> pri;
vector<int> d(MAX),cnt(MAX);
void init() {
    is_p[0] = is_p[1] = 0;
    for(int i = 2;i < MAX;++i) {
        if(is_p[i]) {
            pri.push_back(i);
            d[i] = 2;
            cnt[i] = 1;
        }
        for(auto& j : pri) {
            if(i * j > MAX) break;
            is_p[i * j] = 0;
            if(i % j == 0) {
                cnt[i * j] = cnt[i] + 1;
                d[i * j] = d[i] / cnt[i] * (cnt[i * j] + 1);
                break;
            }
            // 最小质因数为 j，且幂次为 1
            cnt[i * j] = 1;
            // 积性函数定义
            d[i * j] = d[i] * d[j]; 
        }
    }
}
```

对于一些积性函数，筛法都能做到线性时间内递推求解，如：因数和，欧拉函数，莫比乌斯函数等，这些可以参考: [OI Wiki 筛法](https://oi-wiki.org/math/number-theory/sieve/#%E7%B4%A0%E6%95%B0%E7%AD%9B%E6%B3%95){target=_blank}

<hr>

参考文章：

[OI Wiki 筛法](https://oi-wiki.org/math/number-theory/sieve/#%E7%B4%A0%E6%95%B0%E7%AD%9B%E6%B3%95){target=_blank}

[积性函数 CSDN](https://blog.csdn.net/qcwlmqy/article/details/95937390){target=_blank}
