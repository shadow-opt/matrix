#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <type_traits>

namespace hw
{
    template <typename T>
    class MyMatrix
    {
        // 类型检查
        static_assert(std::is_arithmetic<T>::value,
                      "MyMatrix 只支持数字类型 (int, double等)");

    private:
        int colNum;
        int rowNum;
        std::vector<std::vector<T>> data;
        void checkSizeSame(const MyMatrix<T> &other) const;
        void checkSquare() const;
        void checkSizeMultiplicable(const MyMatrix<T> &other) const;

    public:
        MyMatrix();
        MyMatrix(int row, int col);
        MyMatrix(int row, int col, T initValue);
        MyMatrix(const MyMatrix &other);

        int getColNum() const;
        int getRowNum() const;
        // 元素存取
        T get(int row, int col) const;
        void set(int row, int col, T value);

        // 批量修改
        void fill(T value); // 支持全部置零或一
        void negate();      // 矩阵取负

        MyMatrix<T> operator+(const MyMatrix<T> &other) const;
        MyMatrix<T> operator-(const MyMatrix<T> &other) const;
        MyMatrix<T> operator*(const MyMatrix<T> &other) const;
        MyMatrix<T> operator*(T scalar) const; // 数乘
        // 我倒，线代白学了，不知道矩阵除法
        MyMatrix<T> operator/(const MyMatrix<T> &other) const;

        void operator+=(const MyMatrix<T> &other);
        void operator-=(const MyMatrix<T> &other);
        void operator*=(const MyMatrix<T> &other);
        void operator*=(T scalar);
        void operator/=(const MyMatrix<T> &other);

        // 初等行列变换
        void swapRows(int r1, int r2);
        void scaleRow(int r, T k);
        void addRowMultiple(int target, int source, T k); // target 行 += k * source 行
        void swapCols(int c1, int c2);
        void scaleCol(int c, T k);
        void addColMultiple(int target, int source, T k); // target 列 += k * source 列

        // 转置
        MyMatrix<T> getTranspose() const;
        // 代数余子式
        MyMatrix<T> minorMatrix() const;

        // 行列式
        T determinant() const;
        // 逆矩阵
        MyMatrix<T> inverse() const;
        // 伴随矩阵
        MyMatrix<T> adjugate() const;

        // 输出 （利用 ostream）
        void print(std::ostream &os = std::cout) const;
    };

}