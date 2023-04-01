#include <stdio.h>
#include <random>
#include <chrono>

// Function signatures
int menu();
int printMenuOptions();
int initializeMatrices();
int addition();
int subtraction();
int multiplication();
bool sizeValidation(int option);
int randomMatrices(int size);

// Matrix class signature
class Matrix{
    private:
        float** matrix1;
        int rows;
        int cols;
        bool exist;

    public:
        Matrix();
        Matrix(int nRows, int nCols, bool init0);
        Matrix(int size);
        Matrix(FILE *fp);
        ~Matrix();
        int getRows();
        int getCols();
        Matrix operator+(const Matrix& addend);
        Matrix operator-(const Matrix& subtrahend);
        Matrix operator*(const Matrix& multiplicand);
        int print();
};


Matrix* matrixA;
Matrix* matrixB;


// To run: g++ m.cpp -o mat -lstdc++
int main(){
    int valid = 0;

    // Normal driver code
    do{
        valid = initializeMatrices();
    } while(valid != 0);
    do{
        valid = menu();
    } while(valid != 5);



    // Deallocate matrixA and matrixB
    if(matrixA != NULL){
        delete matrixA;
        matrixA = NULL;
    }

    // Deallocate matrixB
    if(matrixB != NULL){
        delete matrixB;
        matrixB = NULL;
    }
    return 0;
}



int menu(){
    int choice;

    do{
        printMenuOptions();
        if((scanf("%d", &choice) == 0) || 
            ((choice != 1) && (choice != 2) && (choice != 3) 
            && (choice != 4) && (choice != 5))){
            printf("Error: Please only input an option from 1-5.\n");
        }
        while (getchar() != '\n'); // Clear buffer
        
    } while((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5));

    if(choice == 1){
        initializeMatrices();
    } else if(choice == 2){
        addition();
    } else if(choice == 3){
        subtraction();
    } else if(choice == 4){
        multiplication();
    } else{
        printf("Exiting program.");
        return 5;
    }
    return 0;
}


int printMenuOptions(){
    printf("\n");
    printf("1: Upload 2 new matrices.\n");
    printf("2: Matrix addition.\n");
    printf("3: Matrix subtraction.\n");
    printf("4: Matrix multiplication.\n");
    printf("5: Exit program.\n");
    return 0;
}



int initializeMatrices(){
    char fileName[100];
    FILE *fp;

    // Deallocate matrixA
    // In case user already initialized matrices and wants to use different matrices
    if(matrixA != NULL){ // If matrixA already exists, delete it
        delete matrixA;
        matrixA = NULL;
    }

    // Deallocate matrixB
    if(matrixB != NULL){
        delete matrixB;
        matrixB = NULL;
    }

    // Get the file from which to read the matrices
    do{
        printf("Please enter the name of the file you would like to upload for matrix A: ");
        fgets(fileName, sizeof(fileName), stdin);
        fileName[strcspn(fileName, "\n")] = '\0'; // remove the newline char
        fp = fopen(fileName, "r");
        if(fp == NULL){
            printf("Error: File not found. Please try again.\n");
        }
    } while(fp == NULL);

    matrixA = new Matrix(fp);
    

    do{
        printf("Please enter the name of the file you would like to upload for matrix B: ");
        fgets(fileName, sizeof(fileName), stdin);
        fileName[strcspn(fileName, "\n")] = '\0'; // remove the newline char
        fp = fopen(fileName, "r");
        if(fp == NULL){
            printf("Error: File not found. Please try again.\n");
        }
    } while(fp == NULL);

    matrixB = new Matrix(fp);
    
    fclose(fp);
    return 0;
}



int addition(){
    if(!sizeValidation(1)){
        return 1;
    }
    Matrix sum = (*matrixA) + (*matrixB); // Overloaded + operation
    printf("Sum matrix: \n");
    sum.print();

    // Deallocate resulting matrix
    sum.~Matrix();
    //sum = NULL; //////// Memory leak?

    return 0;
}


int subtraction(){
    if(!sizeValidation(1)){
        return 1;
    }
    Matrix difference = (*matrixA) - (*matrixB); // Overloaded + operation
    printf("Difference matrix: \n");
    difference.print();
    
    // Deallocate resulting matrix
    difference.~Matrix();
    //difference = NULL; //////// Memory leak?

    return 0;
}


int multiplication(){
    if(!sizeValidation(2)){
        return 1;
    }
    Matrix product = (*matrixA) * (*matrixB);
    printf("Product matrix: \n");
    product.print();
    
    // Deallocate resulting matrix
    product.~Matrix();
    //product = NULL; //////// Memory leak?

    return 0;
}




bool sizeValidation(int option){
    if(option == 1){ // addition or subtraction
       if((matrixA->getRows() != matrixB->getRows()) || (matrixA->getCols() != matrixB->getCols())){
            printf("Error: matrix A and matrix B must be the same size.\n");
            printf("Please select another operation or choose 2 new matrices.\n");
            return false;
        } 
    } else{ //multiplication
        if(matrixA->getCols() != matrixB->getRows()){
            printf("Error: Cannot multiply matrix A by matrix B.\n");
            printf("The number of columns in matrix A must equal the number of rows in matrix B.\n");
            printf("Please select another operation or choose 2 new matrices.\n");
            return false;
        }
    }
    return true;
}



int randomMatrices(int size){
    matrixA = new Matrix(size);
    matrixB = new Matrix(size);
    
    // Print matrices
    matrixA->print();
    matrixB->print();
    return 0;
}








// Matrix class
class Matrix{
    public:
        Matrix(){
            rows = 0;
            cols = 0;
            matrix1 = NULL;
            exist = true;
        }
        Matrix(int nRows, int nCols, bool init0){
            rows = nRows;
            cols = nCols;
            exist = true;
            
            // Allocate memory
            matrix1 = new float*[rows];
            for(int i=0; i<rows; i++){
                matrix1[i] = new float[cols];
            }

            // Initialize cells as 0's but only if user does not want to populate the matrix with random values
            if(init0){
                for(int i=0; i<rows; i++){
                    for(int j=0; j<cols; j++){
                        matrix1[i][j] = 0.0; 
                    }
                }
            }
            
        }
        Matrix(int size){ // For initializing with random values
            Matrix(size, size, false);
            std::random_device rando;
            std::mt19937 gen(rando());
            std::uniform_real_distribution<float> dist(1.0f, 10.0f);

            // Initialize matrix with random floats
            for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    matrix1[i][j] = dist(gen);
                }
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
            matrix1 = NULL;
            rows = 0;
            cols = 0;
            exist = false;
        }

        // Get functions
        int getRows(){
            return this->rows;
        }
        
        int getCols(){
            return this->cols;
        }

        Matrix operator+(const Matrix& addend){
            Matrix result(this->rows, this->cols, false); // may need to initialize with 0's (true) 

            for(int i=0; i<rows; i++){
                for(int j=0; j<rows; j++){
                    result.matrix1[i][j] = this->matrix1[i][j] + addend.matrix1[i][j];
                }
            }

            return result;
        }

        Matrix operator-(const Matrix& subtrahend){
            Matrix result(this->rows, this->cols, false); // may need to initialize with 0's (true) 

            for(int i=0; i<rows; i++){
                for(int j=0; j<rows; j++){
                    result.matrix1[i][j] = this->matrix1[i][j] - subtrahend.matrix1[i][j];
                }
            }

            return result;
        }

        Matrix operator*(const Matrix& multiplicand){
            int nRows = this->rows; // matrixA rows
            int nCols = multiplicand.cols; // matrixB cols
            Matrix result(nRows, nCols, true);
            
            for(int i=0; i<nRows; i++){
                for(int j=0; j<nCols; j++){
                    for(int k=0; k<(this->cols); k++){ // matrixA cols
                        result.matrix1[i][j] += this->matrix1[i][k] * multiplicand.matrix1[k][j];
                    }
                }
            }

            return result;
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
        bool exist; // = false; // initial value should not cause issues?

};