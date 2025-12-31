#include "MyMatrix.h"

using std::vector;
using namespace hw;

template <typename T>
MyMatrix<T>::MyMatrix() : colNum(0), rowNum(0), data() {}

template <typename T>
MyMatrix<T>::MyMatrix(int row, int col) : colNum(col), rowNum(row), data(row, vector<T>(col, 0))
{
    if (col <= 0 || row <= 0)
    {
        throw std::invalid_argument("矩阵的行数和列数必须为正整数");
    }
}

template <typename T>
MyMatrix<T>::MyMatrix(int row, int col, T initValue) : colNum(col), rowNum(row), data(row, vector<T>(col, initValue))
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
T MyMatrix<T>::get(int row, int col) const { return data[row][col]; }

template <typename T>
void MyMatrix<T>::set(int row, int col, T value) { data[row][col] = value; }

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
    if (colNum != other.rowNum)
    {
        throw std::invalid_argument("矩阵尺寸不匹配，无法相乘");
    }
}

template <typename T>
void MyMatrix<T>::fill(T value)
{
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < colNum; ++c)
        {
            data[r][c] = value;
        }
    }
}
template <typename T>
void MyMatrix<T>::negate()
{
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < colNum; ++c)
        {
            data[r][c] = -data[r][c];
        }
    }
}
template <typename T>
MyMatrix<T> MyMatrix<T>::operator+(const MyMatrix<T> &other) const
{
    checkSizeSame(other);
    MyMatrix<T> result(rowNum, colNum);
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < colNum; ++c)
        {
            result.data[r][c] = data[r][c] + other.data[r][c];
        }
    }
    return result;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::operator-(const MyMatrix<T> &other) const
{
    checkSizeSame(other);
    MyMatrix<T> result(rowNum, colNum);
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < colNum; ++c)
        {
            result.data[r][c] = data[r][c] - other.data[r][c];
        }
    }
    return result;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::operator*(const MyMatrix<T> &other) const
{
    checkSizeMultiplicable(other);
    MyMatrix<T> result(rowNum, other.colNum);
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < other.colNum; ++c)
        {
            T sum = 0;
            for (int k = 0; k < colNum; ++k)
            {
                sum += data[r][k] * other.data[k][c];
            }
            result.data[r][c] = sum;
        }
    }
    return result;
}

template <typename T>
MyMatrix<T> MyMatrix<T>::operator*(T scalar) const
{
    MyMatrix<T> result(rowNum, colNum);
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < colNum; ++c)
        {
            result.data[r][c] = data[r][c] * scalar;
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
    swap(data[r1], data[r2]);
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
        data[r][c] *= k;
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
        data[target][c] += k * data[source][c];
    }
}
template <typename T>
void MyMatrix<T>::swapCols(int c1, int c2)
{
    if (c1 < 0 || c1 >= colNum || c2 < 0 || c2 >= colNum)
    {
        throw std::out_of_range("列索引越界");
    }
    for (int r = 0; r < rowNum; ++r)
    {
        std::swap(data[r][c1], data[r][c2]);
    }
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
        data[r][c] *= k;
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
        data[r][target] += k * data[r][source];
    }
}
template <typename T>
MyMatrix<T> MyMatrix<T>::getTranspose() const
{
    MyMatrix<T> result(colNum, rowNum);
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < colNum; ++c)
        {
            result.data[c][r] = data[r][c];
        }
    }
    return result;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::minorMatrix() const
{
    checkSquare();
    MyMatrix<T> result(rowNum, colNum);
    for (int r = 0; r < rowNum; ++r)
    {
        for (int c = 0; c < colNum; ++c)
        {
            // 计算余子式
            MyMatrix<T> subMatrix(rowNum - 1, colNum - 1);
            for (int sr = 0; sr < rowNum; ++sr)
            {
                if (sr == r)
                    continue;
                for (int sc = 0; sc < colNum; ++sc)
                {
                    if (sc == c)
                        continue;
                    int destR = sr < r ? sr : sr - 1;
                    int destC = sc < c ? sc : sc - 1;
                    subMatrix.data[destR][destC] = data[sr][sc];
                }
            }
            T det = subMatrix.determinant();
            result.data[r][c] = ((c + r) % 2 == 0) ? det : -det;
        }
    }
    return result;
}

template <typename T>
T MyMatrix<T>::determinant() const
{
    checkSquare();
    int n = rowNum;
    MyMatrix<T> temp(*this);
    T det = 1;
    for (int i = 0; i < n; ++i)
    {
        // 寻找主元
        int pivotRow = i;
        for (int r = i + 1; r < n; ++r)
        {
            if (std::abs(temp.data[r][i]) > std::abs(temp.data[pivotRow][i]))
            {
                pivotRow = r;
            }
        }
        if (std::abs(temp.data[pivotRow][i]) < 1e-10)
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
            T factor = temp.data[r][i] / temp.data[i][i];
            for (int c = i; c < n; ++c)
            {
                temp.data[r][c] -= factor * temp.data[i][c];
            }
        }
    }
    return det;
}
template <typename T>
MyMatrix<T> MyMatrix<T>::inverse() const
{
    checkSquare();
    int n = rowNum;
    MyMatrix<T> augmented(n, n * 2);
    // 构造增广矩阵 [A | I]
    for (int r = 0; r < n; ++r)
    {
        for (int c = 0; c < n; ++c)
        {
            augmented.data[r][c] = data[r][c];
            augmented.data[r][c + n] = (c == r) ? 1 : 0;
        }
    }
    // 高斯-约旦消元法
    for (int i = 0; i < n; ++i)
    {
        // 寻找主元
        int pivotRow = i;
        for (int r = i + 1; r < n; ++r)
        {
            if (std::abs(augmented.data[r][i]) > std::abs(augmented.data[pivotRow][i]))
            {
                pivotRow = r;
            }
        }
        if (std::abs(augmented.data[pivotRow][i]) < 1e-10)
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
            augmented.data[i][c] /= pivotValue;
        }
        // 消去其他行
        for (int r = 0; r < n; ++r)
        {
            if (r != i)
            {
                T factor = augmented.data[r][i];
                for (int c = 0; c < n * 2; ++c)
                {
                    augmented.data[r][c] -= factor * augmented.data[i][c];
                }
            }
        }
    }
    // 提取逆矩阵
    MyMatrix<T> ans(n, n);
    for (int r = 0; r < n; ++r)
    {
        for (int c = 0; c < n; ++c)
        {
            ans.data[r][c] = augmented.data[r][c + n];
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
            os << std::setw(10) << data[r][c] << " ";
        }
        os << std::endl;
    }
}
