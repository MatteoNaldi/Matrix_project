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

    Matrix(Matrix &that);

    Matrix &operator=(const Matrix &that);

    void setValue();

    void setValue(T value, int pos);

    T getValue(int pos);

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

template<typename T>
Matrix<T>::Matrix(Matrix &that) {
    rows = that.rows;
    cols = that.cols;
    Mat = new T;
    if (that.Mat != nullptr)
        *Mat = *that.Mat;
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &that) {
    rows = that.rows;
    cols = that.cols;
    for (int i = 0; i < rows * cols; ++i) {
        Mat[i] = that.Mat[i];
    }
    return *this;
}


template<typename T>
void Matrix<T>::setValue() {
    for (int i = 0; i < rows * cols; ++i) {
        std::cout << "Insert value: ";
        std::cin >> Mat[i];
    }
}

template<typename T>
void Matrix<T>::setValue(T value, int pos) {
    Mat[pos] = value;
}

template<typename T>
T Matrix<T>::getValue(int pos) {
    return Mat[pos];
}
#endif //MATRIX_PROJECT_MATRIX_H
