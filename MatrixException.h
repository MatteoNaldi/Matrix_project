//
// Created by matteo on 14/09/18.
//

#ifndef MATRIX_PROJECT_MATRIXEXCEPTION_H
#define MATRIX_PROJECT_MATRIXEXCEPTION_H


#include <stdexcept>

class MatrixException : public std::runtime_error {
public:
    MatrixException(std::string whatMsg);
};


#endif //MATRIX_PROJECT_MATRIXEXCEPTION_H
