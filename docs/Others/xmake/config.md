
## **常用接口**

这里列出一些常用的接口，更详细的描述可以参考官方文档

下面是一些全局接口：

```lua
-- 设置 xmake 最小版本
set_xmakever()
-- 添加规则，一般是 "mode.debug", "mode.release"，两个内置规则：调试和发行规则
add_rules()  
-- 添加头文件搜索路径
add_includedirs()  
-- 添加包，要写对应的包版本、如：jsoncpp 1.9.5
add_requires() 
-- 添加子项目
includes() 
```

下面是一些用于工程目标的接口

```lua
-- 声明构建目标
target() 
-- 设置构建目标的类型
set_kind() 
-- 为构建目标添加源文件
add_files() 
-- 为构建目标添加依赖包
add_packages() 
-- 设置允许时工作目录
set_rundir() 
-- 设置代码语言标准，如：c11，cxx11等
set_languages()
-- 可用于设置 xmake run 的默认运行参数，通过它，我们可以避免每次命令行输入运行参数，2.6.9 新增接口
set_runargs()
```

还有一些内置的全局变量：

```lua
$(projectdir) -- 项目目录
```