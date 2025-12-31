#include "MyMatrix.h"
#include <iostream>
using namespace std;
using namespace hw;

int main()
{
    try
    {
        MyMatrix<double> A(2, 2);
        A.set(0, 0, 4);
        A.set(0, 1, 7);
        A.set(1, 0, 2);
        A.set(1, 1, 6);

        MyMatrix<double> B(2, 2, 1.0); // 全 1 矩阵

        cout << "A:\n";
        A.print();
        cout << "B:\n";
        B.print();

        cout << "A + B:\n";
        (A + B).print();

        cout << "A * B:\n";
        (A * B).print();

        cout << "det(A): " << A.determinant() << "\n";

        cout << "A^{-1}:\n";
        A.inverse().print();
    }
    catch (const std::exception &ex)
    {
        cerr << "error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}