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

    Matrix rowSelect(int n);

    Matrix colSelect(int n);

    Matrix trasposta();

    Matrix operator*(Matrix &B);

    Matrix Gauss(Matrix &b);

    Matrix backsubs(Matrix &b);


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

template<typename T>
Matrix<T> Matrix<T>::rowSelect(int n) {
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
Matrix<T> Matrix<T>::colSelect(int n) {
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
Matrix<T> Matrix<T>::trasposta() {
    Matrix<T> Tras(cols, rows);
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            Tras.Mat[i * rows + j] = Mat[j * cols + i];
        }
    }
    return Tras;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix &B) {
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
        std::cout << "Error Product: different dimension" << std::endl;
}

template<typename T>
Matrix<T> Matrix<T>::Gauss(Matrix &b) {  //algoritmo di gauss per la risoluzione di sistemi lineari:riduzione
    Matrix<T> x(1, rows);
    if (rows == cols) {
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
        std::cout << "Matrix not squared" << std::endl;
}

template<typename T>
Matrix<T>
Matrix<T>::backsubs(Matrix &b) { //algoritmo di gauss per la risoluzione di sistemi lineari:sostituzione all'indietro
    Matrix<T> x(1, rows);
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
}

#endif //MATRIX_PROJECT_MATRIX_H
