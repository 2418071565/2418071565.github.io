

在 C++17 中引用入了结构化绑定（Structured binding）。

将子对象或初始化列表元素绑定到指定的名字上。

语法如下：

```cpp
cv-auto ref-qualifier ﻿(optional) [ identifier-list ] = expression ;
cv-auto ref-qualifier ﻿(optional) [ identifier-list ]{ expression };
cv-auto ref-qualifier ﻿(optional) [ identifier-list ]( expression );
```

eg：

```cpp
int main()
{
	int a[2] = { 1,2 };

	auto [x, y] = a;	// x,y 是 a[0],a[1] 的拷贝
	auto& [xr, yr] = a;	// xr,yr 是 a[0],a[1] 的引用
	std::cout << x << ' ' << y << std::endl;
	xr = 2, yr = 3;
	std::cout << a[0] << ' ' << a[1] << std::endl;
	return 0;
}
/*
输出：
1 2
2 3
*/
```