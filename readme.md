# 作业项目说明文档  
---
该repo为个人期末作业。
- [作业项目说明文档](#--------)
  * [简介](#--)
  * [项目结构](#----)
  * [构建与运行](#-----)

(github竟然不支持[TOC])

## 简介
本项目实现了MyMatrix类(My_matrix lib)，其支持操作：
(1)给定矩阵⼤⼩，初始化对应⼤⼩、元素全为0的矩阵。
(2)将矩阵所有元素置零或置⼀。
(3)将矩阵所有元素取负值。
(4)对矩阵实现数乘。
(5)实现两个矩阵之间的加减乘除。
(6)通过指定指令实现矩阵的初等⾏/列变换
(7)获得矩阵的转置。
(8)获得矩阵中任何元素的余⼦式（注意是余⼦式⽽不是代数余⼦式）。
(9)获得矩阵的伴随矩阵和逆矩阵。
(10)求得矩阵的⾏列式。
(11)判别可能出现的奇异矩阵和不合法运算，并输出对应错误信息。
(12)输出当前矩阵内容。  

## 项目结构

- CMakeLists.txt：顶层build配置。
- app/
	- CMakeLists.txt：可执行程序(main)配置。
	- main.cpp：示例入口，简单演示矩阵创建、加法、乘法、行列式与逆矩阵打印。
- libs/
	- my_matrix/
		- CMakeLists.txt：lib配置。
		- include/MyMatrix.h：矩阵模板类声明。
		- src/MyMatrix.cpp：矩阵模板类实现。
- tests/
	- CMakeLists.txt：配置。
	- doctest.h：测试框架。
	- tests.cpp：单元测试，用 doctest 验证行列式、逆矩阵、加法与乘法。

## 构建与运行
1. 安装 CMake 和支持的编译器（如 g++ 或 MSVC）。
2. 在项目根目录下创建构建目录并进入：
   ```bash
   mkdir build
   cd build
   ```
3. 运行 CMake 生成构建文件：
    ```bash
    cmake ..
    ```
4. 编译项目：
    ```bash
    cmake --build .
    ```
5. 运行可执行文件（在 build/app 目录下的 main）：
    ```bash
    ./build/app/main
    ```
- windows 下为`main.exe`