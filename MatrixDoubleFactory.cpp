//
// Created by matteo on 06/09/18.
//

#include "MatrixDoubleFactory.h"

MatrixDoubleFactory::MatrixDoubleFactory() {}

MatrixDoubleFactory::~MatrixDoubleFactory() {}

std::unique_ptr<Matrix<double>> MatrixDoubleFactory::createMatrix(int r, int c) {
    return std::unique_ptr<Matrix<double>>(new Matrix<double>(r, c));
}