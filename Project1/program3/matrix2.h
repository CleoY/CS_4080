#ifndef MATRIX_H
#define MATRIX_H
extern Matrix();
Matrix(int nRows, int nCols);
Matrix(int nRows, int nCols, FILE *fp);
Matrix operator+(const Matrix& matrix2);
Matrix operator-(const Matrix& matrix2);
int deleteMatrix();
#endif