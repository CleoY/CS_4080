#include <stdio.h>
#include <random>
#include <chrono>
#include "matrix.h"

// Function signatures
int menu();
int printMenuOptions();
int initializeMatrices();
int addition();
int subtraction();
int multiplication();
bool sizeValidation(int option);
int randomMatrices(int size);


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
    
    
    // Print matrices
    printf("Matrix A: \n");
    matrixA->print();
    printf("Matrix B: \n");
    matrixB->print();


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
    printf("Matrix A: \n");
    matrixA->print();
    printf("Matrix B: \n");
    matrixB->print();
    return 0;
}