//
// Created by matteo on 06/09/18.
//

#ifndef MATRIX_PROJECT_MATRIX_H
#define MATRIX_PROJECT_MATRIX_H

#include <iostream>
#include "MatrixException.h"

template<typename T>

class Matrix {
public:
    Matrix(int r, int c);

    ~Matrix();

    int getRows() const;

    int getCols() const;

    Matrix(Matrix &that);

    Matrix &operator=(const Matrix &that);

    void setValue(T value, int pos);

    T getValue(int pos) const;

    Matrix rowSelect(int n) const;

    Matrix colSelect(int n) const;

    Matrix trasposta() const;

    Matrix operator*(const Matrix &B) const throw(MatrixException);

    Matrix Gauss(const Matrix &b) const throw(MatrixException);

    Matrix backsubs(const Matrix &b) const throw(MatrixException);

    Matrix inversa() const;

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
void Matrix<T>::setValue(T value, int pos) {
    Mat[pos] = value;
}

template<typename T>
T Matrix<T>::getValue(int pos) const {
    return Mat[pos];
}

template<typename T>
Matrix<T> Matrix<T>::rowSelect(int n) const {
    Matrix x(1, cols);
    if (n > 0 && n <= rows) {
        int j = 0;
        for (int i = (n - 1) * cols; i < n * cols; ++i) {
            x.Mat[j] = Mat[i];
            j++;
        }
        return x;
    }
}

template<typename T>
Matrix<T> Matrix<T>::colSelect(int n) const {
    Matrix x(1, rows);
    if (n > 0 && n <= cols) {
        int j = 0;
        for (int i = (n - 1); i < rows * cols; i += cols) {
            x.Mat[j] = Mat[i];
            j++;
        }
        return x;
    }
}

template<typename T>
Matrix<T> Matrix<T>::trasposta() const {
    Matrix<T> Tras(cols, rows);
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            Tras.Mat[i * rows + j] = Mat[j * cols + i];
        }
    }
    return Tras;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &B) const throw(MatrixException) {
    Matrix<T> P(rows, B.cols);
    if (cols == B.rows) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < B.cols; ++j) {
                P.Mat[i * rows + j] = 0;
                for (int k = 0; k < cols; ++k) {
                    P.Mat[i * rows + j] += Mat[i * cols + k] * B.Mat[k * B.cols + j];
                }
            }
        }
        return P;
    } else
        throw MatrixException("Different Matrix Dimension");
}

template<typename T>
Matrix<T>
Matrix<T>::Gauss(
        const Matrix &b) const throw(MatrixException) {  //algoritmo di gauss per la risoluzione di sistemi lineari:riduzione
    if (rows == cols) {
        Matrix<T> x(1, rows);
        int c = 1;
        for (int k = 0; k < rows * cols; k += rows + 1) {
            if (Mat[k] != 0) {
                int d = 0;
                for (int i = k + rows; i < rows * cols; i += rows) {
                    int m = Mat[i] / Mat[k];
                    Mat[i] = 0;
                    b.Mat[c + d] -= m * b.Mat[c - 1];
                    d++;
                    for (int j = 0; j < rows - c; ++j) {
                        Mat[j + i + 1] -= m * Mat[k + j + 1];
                    }
                }
            }
            c++;
        }
        x = backsubs(b);
        return x;
    } else
        throw MatrixException("Matrix not squared");
}

template<typename T>
Matrix<T>
Matrix<T>::backsubs(
        const Matrix &b) const throw(MatrixException) { //algoritmo di gauss per la risoluzione di sistemi lineari:sostituzione all'indietro
    int tri = 0;  //controllo matrice triangolare superiore
    for (int k = 1; k < cols; ++k) {
        int l = 0;
        while (l < k) {
            if (Mat[k * cols + l] == 0) {
                tri++;
            }
            l++;
        }
    }
    int sum = 0;  //num zeri previsto
    for (int a = 1; a <= cols - 1; ++a) {
        sum += a;
    }
    Matrix<T> x(1, rows);
    if (tri == sum) {
        x.Mat[rows - 1] = b.Mat[rows - 1] / Mat[rows * rows - 1];
        int c = rows - 1;
        int d = 1;
        for (int i = rows * rows - 1; i >= rows; i -= rows) {
            T s = 0;
            for (int j = 0; j < rows - c; ++j) {
                s += Mat[i - rows - j] * x.Mat[rows - j - 1];
            }
            x.Mat[c - 1] = (b.Mat[c - 1] - s) / Mat[i - rows - d];
            c--;
            d++;
        }
        return x;
    } else
        throw MatrixException("Not triangular matrix");
}

template<typename T>
Matrix<T> Matrix<T>::inversa() const {  //chiama gauss e come vettore dei termini noti usa una colonna di I
    Matrix M(rows, cols);
    Matrix I(rows, cols); //matrice identità
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == j)
                I.Mat[i * rows + j] = 1;
            else
                I.Mat[i * rows + j] = 0;
        }
    }
    Matrix b(1, cols);
    for (int k = 0; k < cols; ++k) {
        b = I.rowSelect(k + 1);
        Matrix x(1, cols);
        x = Gauss(b);
        for (int l = 0; l < rows; ++l) {
            M.Mat[l * cols + k] = x.Mat[l];
        }
    }
    return M;
}

#endif //MATRIX_PROJECT_MATRIX_H
