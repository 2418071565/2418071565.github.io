## **C++ 程序编译**


C++程序编译过程分为四个阶段：预处理，编译，汇编，链接。

- **预处理**
  
预处理部分，对代码进行文本操作，即头文件展开、宏替换、去注释、条件编译。这个阶段进行完成后会生成后缀为 `.i` 的文件。

- **编译**
  
这个部分进行语法检查，并且生成汇编代码（指令级代码） 。这个阶段进行完成后会生成后缀为 `.s `的文件。

- **汇编**
  
这个过程将汇编代码生成二进制机器码，并且形成符号表，符号表中存储的是函数名（这个里的函数名是经过编译器修饰后的函数名）和其地址的映射。这个阶段完成会生成后缀为 `.o` 的目标文件，也叫可重定位二进制文件。

- **链接**
  
这个过程中，连接器将会把所有二进制形式的目标文件和系统库（动态库或静态库）合成一个可执行文件，并且进行符号表的合并和重定位。这个过程结束后就生成可以运行的可执行文件了。


## **缺省参数函数**

1. 半缺省参数必须从右往左依次来给出，不能间隔着给
   
2. 缺省参数不能在函数声明和定义中同时出现，只能在声明中给定缺省参数，定义中不给。
   
3. 缺省值必须是常量或者全局变量
   
4. C语言不支持（编译器不支持）


## **拷贝构造函数调用时机**

- 使用已存在对象创建对象时
- 函数参数类型为类类型对象
- 函数返回值类型为类类型对象

## **运算符重载**
注意：

- 不能通过链接其他符号来创建新的运算符，比如operator@
- 重载操作符必须有一个类类型参数
- 用于内置类型的运算符，其含义不能改变，例如：内置的整形+，不能改变其含义
- 作为类成员函数重载时。其形参看起来比操作数目少1，因为成员函数的第一个参数位隐藏的this
- 类成员指针访问运算符（.* ） 、域作用限定符（::） 、（sizeof） 、  三目运算符（?:）  成员访问运算符 （.） 这五个 运算符不能进行重载。


## **初始化列表**

非静态成员变量是在初始化列表进行定义，即使不在初始化列表显式的定义，c++也会按照类中声明次序依次初始化成员变量。所以一些在定义时必须赋值的类型就只能在初始化列表中给值。如：**引用，$const$，没有默认构造函数的自定义类型**。

我们在类中声明成员变量时可以给缺省值参数，这些参数会给到初始化列表进行初始化。


初始化列表的存在导致我们不能在类中给静态成员变量进行赋值，因为c++会认为这是给初始化列表用于初始化的值，但是静态成员变量的初始化是在程序的编译阶段，我们就不能在类中对齐赋值，而是要在类外进行声明，并且要加类限定符。


## **`new/delete` 和 `malloc/free` 的区别**
`malloc/free` 和 `new/delete` 的共同点是：

- 都是从堆上申请空间，并且需要用户手动释放。

不同点：

- malloc和free是函数，new和delete是操作符
- malloc函数申请的空间不会进行初始化，new可以进行初始化
- malloc申请空间时，需要手动计算空间大小并传递，new只需在其后跟上空间的类型即可，如果是多个对象，[]中指定对象个数即可
- malloc的返回值为void*, 在使用时必须强转，new不需要，因为new后跟的是空间的类型
- malloc申请空间失败时，返回的是NULL，因此使用时必须判空，new不需要，但是new需要捕获异常
- 申请自定义类型对象时，malloc/free只会开辟空间，不会调用构造函数与析构函数，而new在申请空间后会调用构造函数完成对象的初始化，delete在释放空间前会调用析构函数完成空间中资源的清理。






