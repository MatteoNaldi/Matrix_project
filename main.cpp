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
    Mtx->setValue();
    std::cout << "Matrix Mtx: " << std::endl;
    Mtx->print();
    std::cout << "----------" << std::endl;
    auto r1 = MatFact->createMatrix(1, 3);
    *r1 = Mtx->rowSelect(1);
    auto r2 = MatFact->createMatrix(1, 3);
    *r2 = Mtx->rowSelect(2);
    auto r3 = MatFact->createMatrix(1, 3);
    *r3 = Mtx->rowSelect(3);
    std::cout << "Row 1: ";
    r1->print();
    std::cout << "Row 2: ";
    r2->print();
    std::cout << "Row 3: ";
    r3->print();
    std::cout << "----------" << std::endl;
    auto c1 = MatFact->createMatrix(1, 3);
    *c1 = Mtx->colSelect(1);
    auto c2 = MatFact->createMatrix(1, 3);
    *c2 = Mtx->colSelect(2);
    auto c3 = MatFact->createMatrix(1, 3);
    *c3 = Mtx->colSelect(3);
    std::cout << "Col 1: ";
    c1->print();
    std::cout << "Col 2: ";
    c2->print();
    std::cout << "Col 3: ";
    c3->print();
    std::cout << "----------" << std::endl;
    auto T = MatFact->createMatrix(3, 3);
    *T = Mtx->trasposta();
    std::cout << "Matrix trasposta: " << std::endl;
    T->print();
    std::cout << "----------" << std::endl;
    auto P = MatFact->createMatrix(3, 3);
    *P = (*Mtx) * (*T);
    std::cout << "Matrix prodotto: " << std::endl;
    P->print();
    std::cout << "----------" << std::endl;
    auto b = MatFact->createMatrix(1, 3);
    b->setValue();
    auto x = MatFact->createMatrix(1, 3);
    *x = Mtx->Gauss(*b);
    std::cout << "Vettore soluzione x: " << std::endl;
    x->print();
    std::cout << "----------" << std::endl;
    auto I = MatFact->createMatrix(1, 3);
    *I = Mtx->inversa();
    std::cout << "Matrix inversa: " << std::endl;
    I->print();
    return 0;
}