//
// Created by matteo on 06/09/18.
//

#ifndef MATRIX_PROJECT_MATRIX_H
#define MATRIX_PROJECT_MATRIX_H

#include <iostream>

template<typename T>

class Matrix {
public:
    Matrix(int r, int c);

    ~Matrix();

    int getRows() const;

    int getCols() const;

private:
    int rows;
    int cols;
    T *Mat;
};

template<typename T>
Matrix<T>::Matrix(int r, int c) {  //matrice pensata come array lineare
    rows = r;
    cols = c;
    Mat = new T[rows * cols];
    for (int i = 0; i < rows * cols; ++i)
        Mat[i] = 0;
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] Mat;
}

template<typename T>
int Matrix<T>::getRows() const {
    return rows;
}

template<typename T>
int Matrix<T>::getCols() const {
    return cols;
}
#endif //MATRIX_PROJECT_MATRIX_H
