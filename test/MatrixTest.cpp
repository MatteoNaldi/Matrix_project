//
// Created by matteo on 03/09/18.
//

#include "gtest/gtest.h"

#include "../Matrix.h"

TEST(Matrix, Constructor) {
    Matrix<int> M(2, 2);
    ASSERT_EQ(2, M.getRows());
    ASSERT_EQ(2, M.getCols());
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(0, M.getValue(i));
    }
}

TEST(Matrix, RowSelect) {
    Matrix<int> M(2, 2);
    for (int i = 0; i < 4; ++i) {
        M.setValue(i + 1, i);
    }
    Matrix<int> r1(1, 2);
    r1 = M.rowSelect(1);
    EXPECT_EQ(1, r1.getValue(0));
    EXPECT_EQ(2, r1.getValue(1));
    Matrix<int> r2(1, 2);
    r2 = M.rowSelect(2);
    EXPECT_EQ(3, r2.getValue(0));
    EXPECT_EQ(4, r2.getValue(1));
}

TEST(Matrix, ColSelect) {
    Matrix<int> M(2, 2);
    for (int i = 0; i < 4; ++i) {
        M.setValue(i + 1, i);
    }
    Matrix<int> c1(1, 2);
    c1 = M.colSelect(1);
    EXPECT_EQ(1, c1.getValue(0));
    EXPECT_EQ(3, c1.getValue(1));
    Matrix<int> c2(1, 2);
    c2 = M.colSelect(2);
    EXPECT_EQ(2, c2.getValue(0));
    EXPECT_EQ(4, c2.getValue(1));
}

TEST(Matrix, trasposta) {
    Matrix<int> M(2, 2);
    for (int i = 0; i < 4; ++i) {
        M.setValue(i + 1, i);
    }
    Matrix<int> T(2, 2);
    T = M.trasposta();
    EXPECT_EQ(1, T.getValue(0));
    EXPECT_EQ(3, T.getValue(1));
    EXPECT_EQ(2, T.getValue(2));
    EXPECT_EQ(4, T.getValue(3));
}

TEST(Matrix, op_x) {
    Matrix<double> A(2, 2);
    for (int i = 0; i < 4; ++i) {
        A.setValue(i + 1, i);
    }
    Matrix<double> B(2, 2);
    for (int i = 0; i < 4; ++i) {
        B.setValue(i + 1, i);
    }
    Matrix<double> C(2, 2);
    C = A * B;
    EXPECT_EQ(7, C.getValue(0));
    EXPECT_EQ(10, C.getValue(1));
    EXPECT_EQ(15, C.getValue(2));
    EXPECT_EQ(22, C.getValue(3));
}

TEST(Matrix, Gauss) {
    Matrix<double> A(2, 2);
    for (int i = 0; i < 4; ++i) {
        A.setValue(i + 1, i);
    }
    Matrix<double> b(1, 2);
    b.setValue(1, 0);
    b.setValue(1, 1);
    Matrix<double> x(1, 2);
    x = A.Gauss(b);
    EXPECT_EQ(-1, x.getValue(0));
    EXPECT_EQ(1, x.getValue(1));
}

TEST(Matrix, Inversa) {
    Matrix<double> A(2, 2);
    for (int i = 0; i < 4; ++i) {
        A.setValue(i + 1, i);
    }
    Matrix<double> B(2, 2);
    B = A.inversa();
    EXPECT_EQ(-2, B.getValue(0));
    EXPECT_EQ(1, B.getValue(1));
    EXPECT_EQ(1.5, B.getValue(2));
    EXPECT_EQ(-0.5, B.getValue(3));
}
