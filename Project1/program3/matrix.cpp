#include <stdio.h>

class Matrix{
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
        Matrix(int nRows, int nCols, FILE *fp){
            Matrix(nRows, nCols); // I hope this works

        }

        

        Matrix operator+(const Matrix& matrix2){
            Matrix result(this->rows, this->cols);
            
        }

        Matrix operator-(const Matrix& matrix2){

        }

        int print(){
            if(matrix1 == NULL){
                printf("Matrix has not been defined.\n");
                return 1;
            }
            for(int i=0; i<rows; i++){
                for(int j=0; j<cols; j++){
                    printf("%f ", matrix1[i][j]);
                }
                printf("\n");
            }
            return 0;
        }

    private:
        float** matrix1;
        int rows;
        int cols;

};