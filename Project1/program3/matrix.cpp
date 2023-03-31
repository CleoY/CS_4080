#include <stdio.h>

class Matrix{
    private:
        float** matrix1;
        int rows;
        int cols;
    
    public:
        Matrix(){
            rows = 0;
            cols = 0;
            matrix1 = NULL;
        }
        Matrix(int nRows, int nCols){
            rows = nRows;
            cols = nCols;
            
            matrix1 = new float*[rows];
            for(int i=0; i<rows; i++){
                matrix1[i] = new float[cols];
            }
        }

        Matrix(int nRows, int nCols, FILE *fp) : Matrix(nRows, nCols, {}) {
            

        }

        Matrix operator+(const Matrix& matrix2){
            Matrix result(this->rows, this->cols);
            
        }

};