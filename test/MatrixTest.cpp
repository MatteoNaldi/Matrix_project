//
// Created by matteo on 03/09/18.
//

#include "gtest/gtest.h"

#include "../Matrix.h"

#include "../MatrixDoubleFactory.h"

std::unique_ptr<MatrixDoubleFactory> MatFact;

TEST(Matrix, Constructor) {
    auto M = MatFact->createMatrix(2, 2);
    ASSERT_EQ(2, M->getRows());
    ASSERT_EQ(2, M->getCols());
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(0, M->getValue(i));
    }
    EXPECT_THROW(M->setValue(1, -2), MatrixException);
    EXPECT_THROW(M->setValue(1, 5), MatrixException);
    EXPECT_THROW(M->getValue(-7), MatrixException);
    EXPECT_THROW(M->getValue(10), MatrixException);
}

TEST(Matrix, RowSelect) {
    auto M = MatFact->createMatrix(2, 2);
    for (int i = 0; i < 4; ++i) {
        M->setValue(i + 1, i);
    }
    auto r1 = MatFact->createMatrix(1, 2);
    *r1 = M->rowSelect(1);
    EXPECT_EQ(1, r1->getValue(0));
    EXPECT_EQ(2, r1->getValue(1));
    auto r2 = MatFact->createMatrix(1, 2);
    *r2 = M->rowSelect(2);
    EXPECT_EQ(3, r2->getValue(0));
    EXPECT_EQ(4, r2->getValue(1));
    EXPECT_THROW(M->rowSelect(3), MatrixException);
}

TEST(Matrix, ColSelect) {
    auto M = MatFact->createMatrix(2, 2);
    for (int i = 0; i < 4; ++i) {
        M->setValue(i + 1, i);
    }
    auto c1 = MatFact->createMatrix(1, 2);
    *c1 = M->colSelect(1);
    EXPECT_EQ(1, c1->getValue(0));
    EXPECT_EQ(3, c1->getValue(1));
    auto c2 = MatFact->createMatrix(1, 2);
    *c2 = M->colSelect(2);
    EXPECT_EQ(2, c2->getValue(0));
    EXPECT_EQ(4, c2->getValue(1));
    EXPECT_THROW(M->colSelect(3), MatrixException);
}

TEST(Matrix, trasposta) {
    auto M = MatFact->createMatrix(2, 2);
    for (int i = 0; i < 4; ++i) {
        M->setValue(i + 1, i);
    }
    auto T = MatFact->createMatrix(2, 2);
    *T = M->trasposta();
    EXPECT_EQ(1, T->getValue(0));
    EXPECT_EQ(3, T->getValue(1));
    EXPECT_EQ(2, T->getValue(2));
    EXPECT_EQ(4, T->getValue(3));
}

TEST(Matrix, op_x) {
    auto A = MatFact->createMatrix(2, 2);
    for (int i = 0; i < 4; ++i) {
        A->setValue(i + 1, i);
    }
    auto B = MatFact->createMatrix(2, 2);
    for (int i = 0; i < 4; ++i) {
        B->setValue(i + 1, i);
    }
    auto C = MatFact->createMatrix(2, 2);
    *C = *A * *B;
    EXPECT_EQ(7, C->getValue(0));
    EXPECT_EQ(10, C->getValue(1));
    EXPECT_EQ(15, C->getValue(2));
    EXPECT_EQ(22, C->getValue(3));

    auto D = MatFact->createMatrix(3, 3);
    for (int i = 0; i < 4; ++i) {
        D->setValue(i + 1, i);
    }
    auto E = MatFact->createMatrix(2, 2);
    EXPECT_THROW(*E = *D * *B, MatrixException);
}

TEST(Matrix, Gauss) {
    auto A = MatFact->createMatrix(2, 2);
    for (int i = 0; i < 4; ++i) {
        A->setValue(i + 1, i);
    }
    auto b = MatFact->createMatrix(1, 2);
    b->setValue(1, 0);
    b->setValue(1, 1);
    auto x = MatFact->createMatrix(1, 2);
    *x = A->Gauss(*b);
    EXPECT_EQ(-1, x->getValue(0));
    EXPECT_EQ(1, x->getValue(1));
    auto B = MatFact->createMatrix(3, 2);
    for (int i = 0; i < 6; ++i) {
        B->setValue(i + 1, i);
    }
    auto y = MatFact->createMatrix(1, 2);
    EXPECT_THROW(*y = B->Gauss(*b), MatrixException);
}

TEST(Matrix, backsub) {
    auto A = MatFact->createMatrix(2, 2);
    A->setValue(1, 0);
    A->setValue(2, 1);
    A->setValue(0, 2);
    A->setValue(1, 3);
    auto b = MatFact->createMatrix(1, 2);
    b->setValue(1, 0);
    b->setValue(1, 1);
    auto x = MatFact->createMatrix(1, 2);
    *x = A->backsubs(*b);
    EXPECT_EQ(-1, x->getValue(0));
    EXPECT_EQ(1, x->getValue(1));
    auto D = MatFact->createMatrix(2, 2);
    for (int i = 0; i < 4; ++i) {
        D->setValue(i + 1, i);
    }
    auto y = MatFact->createMatrix(1, 2);
    EXPECT_THROW(*y = D->backsubs(*b), MatrixException);
}

TEST(Matrix, Inversa) {
    auto A = MatFact->createMatrix(2, 2);
    for (int i = 0; i < 4; ++i) {
        A->setValue(i + 1, i);
    }
    auto B = MatFact->createMatrix(2, 2);
    *B = A->inversa();
    EXPECT_EQ(-2, B->getValue(0));
    EXPECT_EQ(1, B->getValue(1));
    EXPECT_EQ(1.5, B->getValue(2));
    EXPECT_EQ(-0.5, B->getValue(3));
}
