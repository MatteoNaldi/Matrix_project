//
// Created by matteo on 06/09/18.
//

#include "MatrixIntFactory.h"

MatrixIntFactory::MatrixIntFactory() {}

MatrixIntFactory::~MatrixIntFactory() {}

std::unique_ptr<Matrix<int>> MatrixIntFactory::createMatrix(int r, int c) {
    return std::unique_ptr<Matrix<int>>(new Matrix<int>(r, c));
}