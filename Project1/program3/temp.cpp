#include <stdio.h>
#include <random>
#include <chrono>

class Matrix{
    public:
        Matrix(){
            rows = 0;
            cols = 0;
            matrix1 = NULL;
            exist = true;
        }
        Matrix(int nRows, int nCols){
            rows = nRows;
            cols = nCols;
            exist = true;
            
            matrix1 = new float*[rows];
            for(int i=0; i<rows; i++){
                matrix1[i] = new float[cols];
            }
        }
        Matrix(int nRows, int nCols, FILE *fp){
            Matrix(nRows, nCols); // I hope this works

        }

        // int setMatrix(int nRows, int nCols, FILE *fp){
        //     rows = nRows;
        //     cols = nCols;
        //     exist = true;
            
        //     matrix1 = new float*[rows];
        //     for(int i=0; i<rows; i++){
        //         matrix1[i] = new float[cols];
        //     }
        // }



        Matrix operator+(const Matrix& matrix2){
            Matrix result(this->rows, this->cols);
            

            result.print();
            return result;
        }

        Matrix operator-(const Matrix& matrix2){
            Matrix result(this->rows, this->cols);


            result.print();
            return result;
        }

        Matrix operator*(const Matrix& matrix2){
            Matrix result(this->rows, this->cols);


            result.print();
            return result;
        }

        bool existenceCheck(){
            return exist;
        }

        int deleteMatrix(){
            if(matrix1 == NULL){
                printf("The matrix cannot be deleted because it does not exist.\n");
                return 1; // Deletion failure
            }
            for(int i=0; i<rows; i++){
                    delete[] matrix1[i];
            }
            delete[] matrix1;
            matrix1 = NULL;
            rows = 0;
            cols = 0;
            exist = false;

            return 0;
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
        bool exist = false; // initial value should not cause issues?

};