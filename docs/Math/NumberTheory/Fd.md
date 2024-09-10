# 数论基础

## **整除性与约数**
整除的定义：设 $a,b\in\mathbf{Z}，a\ne 0$。如果$ \exists q\in\mathbf{Z}$，使得 $b=aq$，那么就说$ b$可被$a$ 整除，记作$a\mid b$，$b$不被$a$整除记作$a\nmid b$

如果$d\mid a$，且$d\ge0$，则$d$是$a$的约数。任何正整数$a$均可被**平凡约数**$1$和其自身$a$所整除，整数$a$的**非平凡约束**称为$a$的因子。$eg：20$的因子为2、4、5、10$

## **素数与合数**
如果一个整数$a>0$且只能被平凡约数和其自身所整除，，则这个数是**素数**。一个整数$a>1$且不是素数，那么它就是合数。称整数为**基本单位**，并且它既不是素数也不是合数。

## **除法定理、余数和等模**
**除法定理：**对于任意整数$a$和任意正整数$n$，存在唯一整数$q$和$r$，满足$0\le r<n$且$a=qn+r$。
称$q=\left \lfloor a/n \right \rfloor$为除法的商，值$r=a\space mod \space b$为除法的余数。
我们根据整数模$n$的余数，我们可以将所有整数划分成$n$个等价类。包含整数$a$模$n$等价类为

$$
[a]_n=\{ a+kn:k\in Z\}
$$

例如，$[3]_7=\{\dots ,-11,-4,3,10,17,\dots\}$，这个集合同时可以表示为$[-4]_7$和$[10]_7$,$a \in [b]_n$和$a\equiv b(mod\space n)$，是等价的。所有这类等价类的集合是：

$$
Z_n=\{[a]_n ：0\le a\le n-1\}
$$

## **公约数和最大公约数**
如果$d$是$a$的约数并且也是$b$的约数，则$d$是$a、b$的公约数。
公约数的一条重要性质是：

$$
d\mid a且d\mid b，则d\mid (a+b)且d\mid (a-b)
$$

更一般的对任意整数$x$和$y$，有：

$$
d\mid a且d\mid b，则d\mid (ax+by)
$$

并且如果$a\mid b$，那么$\left | a \right |\le \left | b \right |$，或者$b=0$,而这说明：

$$
a\mid b且b\mid a，则a=\pm b
$$

公约数中最大的称为**最大公约数**，记作$gcd(a,b)$.定义$gcd(0,0)=0$，那么$gcd$函数有以下性质：
- $gcd(a,b)=gcd(b,a)$
- $gcd(a,b)=gcd(-a,b)$
- $gcd(a,b)=gcd(|a|,|b|)$
- $gcd(a,0)=|a|$
- $gcd(a,ka)=|a|$

### **定理1**
如果任意整数$a$和$b$步都为$0$，则$gcd(a,b)$是$a$与$b$的线性组合集$\{ax+by：x,y\in Z\}$中的最小正元素。

### **定理2**
对任意整数$a$和$b$，如果$d\mid a且d\mid b，则d\mid gcd(a,b)$

### **定理3**

对所有整数$a$和$b$以及任意非负整数$n$，有

$$
gcd(an,bn)=n\space gcd(a,b)
$$

### **互质数**
如果两个整数$a$和$b$只有公约数$1$，即$gcd(a,b)=1$，则$a、b$称为互质数.

### **定理4**

对任意整数 $a、b$ 和$p$，如果$gcd(a,p)=1$且$gcd(b,p)=1$，则$gcd(ab,p)=1$

由此可得，对于任意整数$n_1,n_2,n_3\dots n_k$ ，如果对任意$i\ne j$，都有$gcd(n_i,n_j)=1$，则称整数 $n_1,n_2,n_3\dots n_k$**两两互质**。

## **唯一因子分解定理**

合数 $a$ 仅能以一种方式写成如下乘积形式：

$$
a=P^{e_1}_1 P^{e_2}_2\cdots P^{e_r}_r
$$

其中 $P_i$ 为素数，$P_1<P_2<P_3\cdots <P_r$，且 $e_i$ 为正整数。

## **模运算**
定义：设 $a,b\in Z$ 且 $b>0$,如果 $q,r\in Z$ 满足 $a=qb+r$ 且 $0\le r<b$ ，$a$ 模 $b$ 等于 $r$ 记作

$$
a\space mod \space b=r
$$

- 负数取模：将 $a$ 不断的加上 $b$ 直到结果大于 $0$ ，这个结果就是模运算的结果
  
### **模运算的性质**

- $b\mid a\Leftrightarrow a\space mod\space b=0$
-  $(a+b)mod\space n=(a\space mod \space n+b\space mod\space n)mod\space n$ 
-  $(a-b)mod\space n=(a\space mod \space n-b\space mod\space n)mod\space n$
-  $(a\times  b)mod\space n=(a\space mod \space n\times b\space mod\space n)mod\space n$
- 除法不具有这样的性质


## **积性函数**

### **定义**

**数论函数：**指定义域为正整数的函数。数论函数也可以视作一个数列。

若函数 $f(n)$ 满足 $f(1) = 1$ 且对于任意两个互质的整数 $a,b$，有 $f(ab) = f(a)f(b)$，则 $f(n)$ 为**积性函数**。


若函数 $f(n)$ 满足 $f(1) = 1$ 且对于任意两个整数 $a,b$，有 $f(ab) = f(a)f(b)$，则 $f(n)$ 为**完全积性函数**。

### **性质**

若 $f(x)$ 和 $g(x)$ 都是积性函数，则一下函数 $h(x)$ 也是积性函数：

$$
\begin{matrix}
h(x) =&f(x^p)\\
h(x) =&f^p(x)\\
h(x) =&f(x)g(x)\\
h(x) =&\sum_{d\mid x}f(d)g(\frac{x}{d})
\end{matrix}
$$
