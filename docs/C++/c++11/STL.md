

## **`any`**



## **新增 `emplace` 类函数**

`emplace` 类函数和一般的插入函数功能相同，但 `emplace` 函数的参数是参数包，只有当传入参数为对象初始化列表时二者会有不同， `emplace` 类的函数会拿参数进行原地构造，而普通的插入，要先在容器外创建好元素，再将其通过拷贝或移动的方式加入到容器中去。

这里以 `emplace_back()` 和 `push_back()` 为例：

```cpp
// 源码来自：libstdc++ 库中的 stl_vector.h 
// 编译器为：g++.exe (x86_64-win32-seh-rev0, Built by MinGW-W64 project) 8.1.0
// ============================= push_back ====================================
// push_back 的左值版本实现
      void
      push_back(const value_type& __x)
      {
        // 判断是否满
	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	  {
        
        // 在 容器末尾（this->_M_impl._M_finish） 调用拷贝构造，用 __x 进行拷贝
	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
				     __x);

	    ++this->_M_impl._M_finish;
	  }
	else    // 空间不够，重新开空间，再插入
	  _M_realloc_insert(end(), __x);
      }

/* C++11 以后右值版本的 push_back 直接复用 emplace_back */
#if __cplusplus >= 201103L
      void
      push_back(value_type&& __x)
      { emplace_back(std::move(__x)); }

// ============================= emplace_back ==================================
/* 
C++11 以后提供 emplace_back 接口
大于 C++14 的版本返回一个插入值的引用，其余版本返回 void
*/
#if __cplusplus >= 201103L
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
#if __cplusplus > 201402L
      typename vector<_Tp, _Alloc>::reference
#else
      void
#endif
      vector<_Tp, _Alloc>::
      emplace_back(_Args&&... __args)
      {
        // 判断是否满
	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	  {

        // 使用参数包，在 数组末尾（this->_M_impl._M_finish） 进行构造。
	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
				     std::forward<_Args>(__args)...);

	    ++this->_M_impl._M_finish;
	  }
	else    // 空间不够，重新开空间，再插入
	  _M_realloc_insert(end(), std::forward<_Args>(__args)...);
#if __cplusplus > 201402L
	return back();
#endif
      }
#endif
```


`emplace_back` 是用传入的参数进行构造，构造方式取决于传入的参数包，`push_back` 是用传入对象进行构造。所以在一般情况下二者完全相同，只有在传入构造参数列表时会有不同，`push_back` 会调用两次构造（构造 + 移动构造），而 `emplace_back` 只会调用一次构造。

首先我们知道两个函数在传入参数列表时，都是在下面这个语句进行构造的：

```cpp
// 使用参数包，在 数组末尾（this->_M_impl._M_finish） 进行构造。
_Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
                std::forward<_Args>(__args)...);
```

只不过 `push_back` 在第一次传参时先要将参数列表构造为对象，之后在调用这个语句时，参数包 `__args` 中是一个右值对象，所以会再进行一次移动构造。而 `emplace_back` 会一直将参数传到这里，所以只进行一次构造。