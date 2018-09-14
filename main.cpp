#include <iostream>
#include <memory>
#include "Matrix.h"
#include "MatrixIntFactory.h"
#include "MatrixDoubleFactory.h"

#define DOUBLE

int main() {
#ifdef DOUBLE
    std::unique_ptr<MatrixDoubleFactory> MatFact;
#else
    std::unique_ptr<MatrixIntFactory> MatFact;
#endif
    auto Mtx = MatFact->createMatrix(3, 3);
    Mtx->setValue(1, 0);
    Mtx->setValue(1, 1);
    Mtx->setValue(-2, 2);
    Mtx->setValue(1, 3);
    Mtx->setValue(0, 4);
    Mtx->setValue(1, 5);
    Mtx->setValue(-2, 6);
    Mtx->setValue(1, 7);
    Mtx->setValue(1, 8);

    auto r1 = MatFact->createMatrix(1, 3);
    *r1 = Mtx->rowSelect(1);
    auto r2 = MatFact->createMatrix(1, 3);
    *r2 = Mtx->rowSelect(2);
    auto r3 = MatFact->createMatrix(1, 3);
    *r3 = Mtx->rowSelect(3);

    auto c1 = MatFact->createMatrix(1, 3);
    *c1 = Mtx->colSelect(1);
    auto c2 = MatFact->createMatrix(1, 3);
    *c2 = Mtx->colSelect(2);
    auto c3 = MatFact->createMatrix(1, 3);
    *c3 = Mtx->colSelect(3);

    auto T = MatFact->createMatrix(3, 3);
    *T = Mtx->trasposta();


    try {
    auto P = MatFact->createMatrix(3, 3);
    *P = (*Mtx) * (*T);
    } catch (MatrixException &e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        auto b = MatFact->createMatrix(1, 3);
        b->setValue(1, 0);
        b->setValue(0, 1);
        b->setValue(-3, 2);
        auto x = MatFact->createMatrix(1, 3);
        *x = Mtx->Gauss(*b);

    } catch (MatrixException &e) {
        std::cerr << e.what() << std::endl;
    }
    try {
        auto s = MatFact->createMatrix(2, 2);
        s->setValue(1, 0);
        s->setValue(1, 1);
        s->setValue(0, 2);
        s->setValue(1, 0);
        auto c = MatFact->createMatrix(1, 2);
        c->setValue(1, 0);
        c->setValue(0, 1);
        auto y = MatFact->createMatrix(1, 2);
        *y = s->backsubs(*c);
    } catch (MatrixException &e) {
        std::cerr << e.what() << std::endl;
    }

    auto I = MatFact->createMatrix(3, 3);
    *I = Mtx->inversa();
    return 0;
}