//
// Created by matteo on 06/09/18.
//

#ifndef MATRIX_PROJECT_MATRIXINTFACTORY_H
#define MATRIX_PROJECT_MATRIXINTFACTORY_H

#include <memory>
#include "Matrix.h"

class MatrixIntFactory {
public:
    MatrixIntFactory();

    virtual ~MatrixIntFactory();

    std::unique_ptr<Matrix<int>> createMatrix(int r, int c);

};


#endif //MATRIX_PROJECT_MATRIXINTFACTORY_H
