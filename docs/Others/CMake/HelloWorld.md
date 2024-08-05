

## **简介**

CMake是个一个开源的跨平台自动化建构系统，用来管理软件建置的程序，并不依赖于某特定编译器，并可支持多层目录、多个应用程序与多个函数库。 

软件构建就是全自动完成代码编译、链接、打包的过程，以及管理不同组件、甚至第三方库的关联。

## **HolleWorld**

CMake 对项目的构建依赖于文件 CMakeLists.txt（大小写要完全一样），CMake 会通过该文件为我们生成对应平台下的原生工程文件（如：Linux 下的 Makefile，Visual Studio 工程的 .sln等）。

我们来看一个简单的 CMakeLists.txt 文件：

```cmake
cmake_minimum_required(VERSION 3.9) # 标识 CMake 最低版本

project(HelloWorld)     # 项目名称
set(CMAKE_CXX_STANDARD 11)  # C++ 标准版本
# 添加要生成的可执行文件，前一个是生成的可执行文件的名字，后面是依赖的 cpp 文件
add_executable(HelloWorld main.cpp) 
```
