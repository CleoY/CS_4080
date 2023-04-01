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
        Matrix(FILE *fp){
            // Read dimensions from first line of file
            fscanf(fp, "%d %d", &rows, &cols);
            fscanf(fp, "%*c"); // Clear file reader buffer

            // Allocate space for matrix
            matrix1 = new float*[rows];
            for(int i=0; i<rows; i++){
                matrix1[i] = new float[cols];
            }

            int rowCounter = 0;
            int colCounter = 0;
            char check; // For various file checks
            float temp; 

            while(rowCounter < rows){
                while(colCounter < cols){
                    fscanf(fp, "%f", &temp);
                    matrix1[rowCounter][colCounter] = temp;
                    colCounter++;
                    check = fgetc(fp);
                    if(check == '\n'){
                        break;
                    }
                }
                colCounter = 0;
                rowCounter++;
            }
        }
        ~Matrix(){
            for(int i=0; i<rows; i++){
                delete[] matrix1[i];
            }
            delete[] matrix1;
            rows = 0;
            cols = 0;
            exist = false;
        }


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