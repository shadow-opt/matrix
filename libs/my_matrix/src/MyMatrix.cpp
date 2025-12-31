#include "MyMatrix.h"
#include <vector>
using std::vector;
using namespace hw;

template <typename T>
MyMatrix<T>::MyMatrix() : colNum(0), rowNum(0), data() {}

template <typename T>
MyMatrix<T>::MyMatrix(int col, int row) : colNum(col), rowNum(row), data(col, vector<T>(row, 0))
{
    if (col <= 0 || row <= 0)
    {
        throw std::invalid_argument("矩阵的行数和列数必须为正整数");
    }
}

template <typename T>
MyMatrix<T>::MyMatrix(int col, int row, T initValue) : colNum(col), rowNum(row), data(col, vector<T>(row, initValue))
{
    if (col <= 0 || row <= 0)
    {
        throw std::invalid_argument("矩阵的行数和列数必须为正整数");
    }
}

template <typename T>
MyMatrix<T>::MyMatrix(const MyMatrix &other) : colNum(other.colNum), rowNum(other.rowNum), data(other.data) {}

template <typename T>
int MyMatrix<T>::getColNum() const { return colNum; }

template <typename T>
int MyMatrix<T>::getRowNum() const { return rowNum; }

template <typename T>
T MyMatrix<T>::get(int col, int row) const { return data[col][row]; }

template <typename T>
void MyMatrix<T>::set(int col, int row, T value) { data[col][row] = value; }

template <typename T>
void MyMatrix<T>::checkSizeSame(const MyMatrix<T> &other) const
{
    if (colNum != other.colNum || rowNum != other.rowNum)
    {
        throw std::invalid_argument("矩阵尺寸不匹配");
    }
}

template <typename T>
void MyMatrix<T>::checkSquare() const
{
    if (colNum != rowNum)
    {
        throw std::invalid_argument("矩阵不是方阵");
    }
}
template <typename T>
void MyMatrix<T>::checkSizeMultiplicable(const MyMatrix<T> &other) const
{
    if (rowNum != other.colNum)
    {
        throw std::invalid_argument("矩阵尺寸不匹配，无法相乘");
    }
}

template <typename T>
void MyMatrix<T>::fill(T value)
{
    for (int c = 0; c < colNum; ++c)
    {
        for (int r = 0; r < rowNum; ++r)
        {
            data[c][r] = value;
        }
    }
}
template <typename T>
void MyMatrix<T>::negate()
{
    for (int c = 0; c < colNum; ++c)
    {
        for (int r = 0; r < rowNum; ++r)
        {
            data[c][r] = -data[c][r];
        }
    }
}
template <typename T>
MyMatrix<T> MyMatrix<T>::operator+(const MyMatrix<T> &other) const
{
    checkSizeSame(other);
    MyMatrix<T> result(colNum, rowNum);
    for (int c = 0; c < colNum; ++c)
    {
        for (int r = 0; r < rowNum; ++r)
        {
            result.data[c][r] = data[c][r] + other.data[c][r];
        }
    }
    return result;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::operator-(const MyMatrix<T> &other) const
{
    checkSizeSame(other);
    MyMatrix<T> result(colNum, rowNum);
    for (int c = 0; c < colNum; ++c)
    {
        for (int r = 0; r < rowNum; ++r)
        {
            result.data[c][r] = data[c][r] - other.data[c][r];
        }
    }
    return result;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::operator*(const MyMatrix<T> &other) const
{
    checkSizeMultiplicable(other);
    MyMatrix<T> result(other.colNum, rowNum);
    for (int c = 0; c < other.colNum; ++c)
    {
        for (int r = 0; r < rowNum; ++r)
        {
            T sum = 0;
            for (int k = 0; k < colNum; ++k)
            {
                sum += data[k][r] * other.data[c][k];
            }
            result.data[c][r] = sum;
        }
    }
    return result;
}

template <typename T>
MyMatrix<T> MyMatrix<T>::operator*(T scalar) const
{
    MyMatrix<T> result(colNum, rowNum);
    for (int c = 0; c < colNum; ++c)
    {
        for (int r = 0; r < rowNum; ++r)
        {
            result.data[c][r] = data[c][r] * scalar;
        }
    }
    return result;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::operator/(const MyMatrix<T> &other) const
{
    return (*this) * other.inverse();
}

template <typename T>
void MyMatrix<T>::operator+=(const MyMatrix<T> &other)
{
    *this = *this + other;
}
template <typename T>
void MyMatrix<T>::operator-=(const MyMatrix<T> &other)
{
    *this = *this - other;
}
template <typename T>
void MyMatrix<T>::operator*=(const MyMatrix<T> &other)
{
    *this = *this * other;
}
template <typename T>
void MyMatrix<T>::operator*=(T scalar)
{
    *this = *this * scalar;
}
template <typename T>
void MyMatrix<T>::operator/=(const MyMatrix<T> &other)
{
    *this = *this / other;
}
template <typename T>
void MyMatrix<T>::swapRows(int r1, int r2)
{
    if (r1 < 0 || r1 >= rowNum || r2 < 0 || r2 >= rowNum)
    {
        throw std::out_of_range("行索引越界");
    }
    for (int c = 0; c < colNum; ++c)
    {
        std::swap(data[c][r1], data[c][r2]);
    }
}

template <typename T>
void MyMatrix<T>::scaleRow(int r, T k)
{
    if (r < 0 || r >= rowNum)
    {
        throw std::out_of_range("行索引越界");
    }
    for (int c = 0; c < colNum; ++c)
    {
        data[c][r] *= k;
    }
}
template <typename T>
void MyMatrix<T>::addRowMultiple(int target, int source, T k)
{
    if (target < 0 || target >= rowNum || source < 0 || source >= rowNum)
    {
        throw std::out_of_range("行索引越界");
    }
    for (int c = 0; c < colNum; ++c)
    {
        data[c][target] += k * data[c][source];
    }
}
template <typename T>
void MyMatrix<T>::swapCols(int c1, int c2)
{
    if (c1 < 0 || c1 >= colNum || c2 < 0 || c2 >= colNum)
    {
        throw std::out_of_range("列索引越界");
    }
    std::swap(data[c1], data[c2]);
}
template <typename T>
void MyMatrix<T>::scaleCol(int c, T k)
{
    if (c < 0 || c >= colNum)
    {
        throw std::out_of_range("列索引越界");
    }
    for (int r = 0; r < rowNum; ++r)
    {
        data[c][r] *= k;
    }
}
template <typename T>
void MyMatrix<T>::addColMultiple(int target, int source, T k)
{
    if (target < 0 || target >= colNum || source < 0 || source >= colNum)
    {
        throw std::out_of_range("列索引越界");
    }
    for (int r = 0; r < rowNum; ++r)
    {
        data[target][r] += k * data[source][r];
    }
}
template <typename T>
MyMatrix<T> MyMatrix<T>::getTranspose() const
{
    MyMatrix<T> result(rowNum, colNum);
    for (int c = 0; c < colNum; ++c)
    {
        for (int r = 0; r < rowNum; ++r)
        {
            result.data[r][c] = data[c][r];
        }
    }
    return result;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::minorMatrix() const
{
    checkSquare();
    MyMatrix<T> result(colNum, rowNum);
    for (int c = 0; c < colNum; ++c)
    {
        for (int r = 0; r < rowNum; ++r)
        {
            // 计算余子式
            MyMatrix<T> subMatrix(colNum - 1, rowNum - 1);
            for (int sc = 0; sc < colNum; ++sc)
            {
                if (sc == c)
                    continue;
                for (int sr = 0; sr < rowNum; ++sr)
                {
                    if (sr == r)
                        continue;
                    int destC = sc < c ? sc : sc - 1;
                    int destR = sr < r ? sr : sr - 1;
                    subMatrix.data[destC][destR] = data[sc][sr];
                }
            }
            T det = subMatrix.determinant();
            result.data[c][r] = ((c + r) % 2 == 0) ? det : -det;
        }
    }
    return result;
}

template <typename T>
T MyMatrix<T>::determinant() const
{
    checkSquare();
    int n = colNum;
    MyMatrix<T> temp(*this);
    T det = 1;
    for (int i = 0; i < n; ++i)
    {
        // 寻找主元
        int pivotRow = i;
        for (int r = i + 1; r < n; ++r)
        {
            if (std::abs(temp.data[i][r]) > std::abs(temp.data[i][pivotRow]))
            {
                pivotRow = r;
            }
        }
        if (std::abs(temp.data[i][pivotRow]) < 1e-10)
        {
            return 0; // 矩阵奇异，行列式为零
        }
        if (pivotRow != i)
        {
            temp.swapRows(i, pivotRow);
            det = -det; // 交换行改变行列式符号
        }
        det *= temp.data[i][i];
        // 消元
        for (int r = i + 1; r < n; ++r)
        {
            T factor = temp.data[i][r] / temp.data[i][i];
            for (int c = i; c < n; ++c)
            {
                temp.data[c][r] -= factor * temp.data[c][i];
            }
        }
    }
    return det;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::inverse() const
{
    checkSquare();
    int n = colNum;
    MyMatrix<T> augmented(n, n * 2);
    // 构造增广矩阵
    for (int c = 0; c < n; ++c)
    {
        for (int r = 0; r < n; ++r)
        {
            augmented.data[c][r] = data[c][r];
            augmented.data[c][r + n] = (c == r) ? 1 : 0;
        }
    }
    // 高斯-约旦消元法
    for (int i = 0; i < n; ++i)
    {
        // 寻找主元
        int pivotRow = i;
        for (int r = i + 1; r < n; ++r)
        {
            if (std::abs(augmented.data[i][r]) > std::abs(augmented.data[i][pivotRow]))
            {
                pivotRow = r;
            }
        }
        if (std::abs(augmented.data[i][pivotRow]) < 1e-10)
        {
            throw std::runtime_error("矩阵不可逆");
        }
        if (pivotRow != i)
        {
            augmented.swapRows(i, pivotRow);
        }
        // 归一化主元行
        T pivotValue = augmented.data[i][i];
        for (int c = 0; c < n * 2; ++c)
        {
            augmented.data[c][i] /= pivotValue;
        }
        // 消去其他行
        for (int r = 0; r < n; ++r)
        {
            if (r != i)
            {
                T factor = augmented.data[i][r];
                for (int c = 0; c < n * 2; ++c)
                {
                    augmented.data[c][r] -= factor * augmented.data[c][i];
                }
            }
        }
    }
    // 提取逆矩阵
    MyMatrix<T> ans(n, n);
    for (int c = 0; c < n; ++c)
    {
        for (int r = 0; r < n; ++r)
        {
            ans.data[c][r] = augmented.data[c][r + n];
        }
    }
    return ans;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::adjugate() const
{
    return this->minorMatrix().getTranspose();
}
template <typename T>
void MyMatrix<T>::print(std::ostream &os) const
{
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < colNum; ++c)
        {
            os << std::setw(10) << data[c][r] << " ";
        }
        os << std::endl;
    }
}
