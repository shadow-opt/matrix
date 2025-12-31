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

    CHECK(A.determinant() == doctest::Approx(10.0));

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

TEST_CASE("转置与取负")
{
    MyMatrix<int> A(2, 3);
    int v = 1;
    for (int r = 0; r < 2; ++r)
        for (int c = 0; c < 3; ++c)
            A.set(r, c, v++);

    auto T = A.getTranspose();
    CHECK(T.getRowNum() == 3);
    CHECK(T.getColNum() == 2);
    CHECK(T.get(0, 1) == 4); // A(1,0) -> T(0,1)
    CHECK(T.get(2, 1) == 6); // A(1,2) -> T(2,1)

    A.negate();
    CHECK(A.get(0, 0) == -1);
    CHECK(A.get(1, 2) == -6);
}

TEST_CASE("奇异矩阵求逆抛异常")
{
    MyMatrix<double> S(2, 2);
    S.set(0, 0, 1);
    S.set(0, 1, 2);
    S.set(1, 0, 2);
    S.set(1, 1, 4); // 行线性相关，det=0
    CHECK_THROWS_AS(S.inverse(), std::runtime_error);
}

TEST_CASE("尺寸不匹配的乘法抛异常")
{
    MyMatrix<int> A(2, 3, 1);
    MyMatrix<int> B(2, 2, 1);
    CHECK_THROWS_AS(A * B, std::invalid_argument);
}
