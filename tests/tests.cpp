#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "MyMatrix.h"

using hw::MyMatrix;

TEST_CASE("2x2 行列式、逆矩阵计算")
{
    MyMatrix<double> A(2, 2);
    A.set(0, 0, 4);
    A.set(0, 1, 7);
    A.set(1, 0, 2);
    A.set(1, 1, 6);

    CHECK(A.determinant() == doctest::Approx(14.0));

    auto inv = A.inverse();
    // A * A^{-1} ≈ I
    auto I = A * inv;
    CHECK(I.get(0, 0) == doctest::Approx(1.0));
    CHECK(I.get(0, 1) == doctest::Approx(0.0));
    CHECK(I.get(1, 0) == doctest::Approx(0.0));
    CHECK(I.get(1, 1) == doctest::Approx(1.0));
}

TEST_CASE("加法、乘法运算")
{
    MyMatrix<int> A(2, 2);
    A.set(0, 0, 1);
    A.set(0, 1, 2);
    A.set(1, 0, 3);
    A.set(1, 1, 4);

    MyMatrix<int> B(2, 2, 1);

    auto C = A + B;
    CHECK(C.get(0, 0) == 2);
    CHECK(C.get(0, 1) == 3);
    CHECK(C.get(1, 0) == 4);
    CHECK(C.get(1, 1) == 5);

    auto M = A * B;
    CHECK(M.get(0, 0) == 3);
    CHECK(M.get(0, 1) == 3);
    CHECK(M.get(1, 0) == 7);
    CHECK(M.get(1, 1) == 7);
}
