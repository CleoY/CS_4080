#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <random>
#include <chrono>

float** matrixA = NULL;
float** matrixB = NULL;

int matrixARows;
int matrixACols;
int matrixBRows;
int matrixBCols;

int menu();
int printMenuOptions();
int initializeMatrices();
float** additionOrSubtraction(int option);
float** multiplication();
bool sizeValidation(int option);
int randomMatrices(int size);
int printMatrix(float** given, int rows, int cols);

// To run: g++ mallocPointer.cpp -o malloc1 -lstdc++
// Then: ./malloc1
int main(){
    int valid = 0;

    // Normal driver code
    do{
        valid = initializeMatrices();
    } while(valid != 0);
    do{
        valid = menu();
    } while(valid != 5);


    // For measuring time taken by multiplication() function for matrices of different sizes
    // randomMatrices(2);
    // std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    // multiplication();
    // std::chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    // double duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    // duration /= 1000; // Convert from microseconds to ms
    // std::cout << "Duration: " << duration << " ms" << std::endl;


    // Deallocate matrixA and matrixB
    if(matrixA != NULL){
        for(int i=0; i<matrixARows; i++){
            delete[] matrixA[i];
        }
        delete[] matrixA;
        matrixA = NULL;
    }
    if(matrixB != NULL){
        for(int i=0; i<matrixBRows; i++){
            delete[] matrixB[i];
        }
        delete[] matrixB;
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
        float** intermediate = additionOrSubtraction(1);
        if(intermediate != NULL){
            // Print resulting matrix
            printf("Resulting matrix: \n");
            printMatrix(intermediate, matrixARows, matrixACols);

            // Delete intermediate matrix
            for(int i=0; i<matrixARows; i++){
                delete[] intermediate[i];
            }
            delete[] intermediate;
        }
        intermediate = NULL;
    } else if(choice == 3){
        float** intermediate = additionOrSubtraction(2);
        
        if(intermediate != NULL){
            // Print resulting matrix
            printf("Resulting matrix: \n");
            printMatrix(intermediate, matrixARows, matrixACols);

            // Delete intermediate matrix
            for(int i=0; i<matrixARows; i++){
                delete[] intermediate[i];
            }
            delete[] intermediate;
        }
        intermediate = NULL;
    } else if(choice == 4){
        float** intermediate = multiplication();

        if(intermediate != NULL){
            // Print intermediate matrix
            printf("Resulting matrix: \n");
            printMatrix(intermediate, matrixARows, matrixBCols);

            // Delete intermediate matrix
            for(int i=0; i<matrixARows; i++){
                delete[] intermediate[i];
            }
            delete[] intermediate;
        }
        intermediate = NULL;
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

    char check; // For various file checks
    float temp; 

    // Deallocate matrixA
    // In case user already initialized matrices and wants to use different matrices
    if(matrixA != NULL){
        for(int i=0; i<matrixARows; i++){
            delete[] matrixA[i];
        }
        delete[] matrixA;
        matrixA = NULL;
    }

    // Deallocate matrixB
    if(matrixB != NULL){
        for(int i=0; i<matrixBRows; i++){
            delete[] matrixB[i];
        }
        delete[] matrixB;
        matrixB = NULL;
    }

    // Get the file from which to read the matrices
    do{
        printf("Please enter the name of the file you would like to upload: ");
        fgets(fileName, sizeof(fileName), stdin);
        fileName[strcspn(fileName, "\n")] = '\0'; // remove the newline char
        fp = fopen(fileName, "r");
        if(fp == NULL){
            printf("Error: File not found. Please try again.\n");
        }
    } while(fp == NULL);

    // Read size of matrixA from first line of file
    fscanf(fp, "%d %d", &matrixARows, &matrixACols);
    fscanf(fp, "%*c"); // Clear file reader buffer

    // Allocate space for matrixA
    matrixA = new float*[matrixARows];
    for(int i=0; i<matrixARows; i++){
        matrixA[i] = new float[matrixACols];
    }

    int rowCounter = 0;
    int colCounter = 0;

    while(rowCounter < matrixARows){
        while(colCounter < matrixACols){
            fscanf(fp, "%f", &temp);
            matrixA[rowCounter][colCounter] = temp;
            colCounter++;
            check = fgetc(fp);
            if(check == '\n'){
                break;
            }
        }
        colCounter = 0;
        rowCounter++;
    }


    // Now upload matrix B
    fscanf(fp, "%d %d", &matrixBRows, &matrixBCols);
    fscanf(fp, "%*c"); // Clear file reader buffer

    // Allocate space for matrixB
    matrixB = new float*[matrixBRows];
    for(int i=0; i<matrixBRows; i++){
        matrixB[i] = new float[matrixBCols];
    }

    rowCounter = 0;
    colCounter = 0;
    while(rowCounter < matrixBRows){
        while(colCounter < matrixBCols){ 
            fscanf(fp, "%f", &temp);
            matrixB[rowCounter][colCounter] = temp;
            colCounter++;
            check = fgetc(fp);
            if(check == '\n'){
                break;
            }
        }
        colCounter = 0;
        rowCounter++;
    }

    fclose(fp);
    return 0;
}



float** additionOrSubtraction(int option){
    if(!sizeValidation(1)){
        return NULL;
    }

    // Allocate space for intermediate matrix
    // Can use matrixB's dimensions instead of matrixA's because they are equal
    float** intermediate = new float*[matrixARows];
    for(int i=0; i<matrixARows; i++){
        intermediate[i] = new float[matrixACols];
    }

    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixACols; j++){
            if(option == 1){ // Addition
                intermediate[i][j] = matrixA[i][j] + matrixB[i][j];
            } else{ // Subtraction
                intermediate[i][j] = matrixA[i][j] - matrixB[i][j];
            }
        }
    }
    return intermediate;
}



float** multiplication(){
    if(!sizeValidation(2)){
        return NULL; // Function failure
    }

    // Initialize intermediate matrix
    float** intermediate = new float*[matrixARows];
    for(int i=0; i<matrixARows; i++){
        intermediate[i] = new float[matrixBCols];
    }
    
    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixBCols; j++){
           intermediate[i][j] = 0.0; 
        }
    }

    // Conduct matrix multiplication
    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixBCols; j++){
            for(int k=0; k<matrixACols; k++){
                intermediate[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return intermediate;
}



bool sizeValidation(int option){
    if(option == 1){ // addition or subtraction
       if((matrixARows != matrixBRows) || (matrixACols != matrixBCols)){
            printf("Error: matrix A and matrix B must be the same size.\n");
            printf("Please select another operation or choose 2 new matrices.\n");
            return false;
        } 
    } else{ //multiplication
        if(matrixACols != matrixBRows){
            printf("Error: Cannot multiply matrix A by matrix B.\n");
            printf("The number of columns in matrix A must equal the number of rows in matrix B.\n");
            printf("Please select another operation or choose 2 new matrices.\n");
            return false;
        }
    }
    return true;
}



int randomMatrices(int size){
    std::random_device rando;
    std::mt19937 gen(rando());
    std::uniform_real_distribution<float> dist(1.0f, 10.0f);
    
    // Allocate matrixA and matrixB
    matrixA = new float*[size];
    matrixB = new float*[size];
    for(int i=0; i<size; i++){
        matrixA[i] = new float[size];
        matrixB[i] = new float[size];
    }

    // Initialize matrixA and matrixB with random floats
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            matrixA[i][j] = dist(gen);
            matrixB[i][j] = dist(gen);
        }
    }
    matrixARows = size;
    matrixACols = size;
    matrixBRows = size;
    matrixBCols = size;

    // Print matrices A and B
    // printf("Matrix A: \n");
    // printMatrix(matrixA, size, size);
    // printf("Matrix B: \n");
    // printMatrix(matrixB, size, size);
    
    return 0;
}



int printMatrix(float** given, int rows, int cols){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            printf("%f ", given[i][j]);
        }
        printf("\n");
    }

    return 0;
}