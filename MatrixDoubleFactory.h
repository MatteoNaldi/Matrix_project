//
// Created by matteo on 06/09/18.
//

#ifndef MATRIX_PROJECT_MATRIXDOUBLEFACTORY_H
#define MATRIX_PROJECT_MATRIXDOUBLEFACTORY_H

#include <memory>
#include "Matrix.h"

class MatrixDoubleFactory {
public:
    MatrixDoubleFactory();

    virtual ~MatrixDoubleFactory();

    std::unique_ptr<Matrix<double>> createMatrix(int r, int c);


};


#endif //MATRIX_PROJECT_MATRIXDOUBLEFACTORY_H
