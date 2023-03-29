#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//#include "arrays.h"

float matrixA[100][100];
float matrixB[100][100];




#include <stdbool.h>
// may change input
int menu();

int printMenuOptions();

// may change
int initializeMatrices();

float addOrSubtraction();

float multiplication();

bool sizeValidation(int option);

int randomMatrices(int size);

int printMatrix(float (*given)[100]);



int main(){
    initializeMatrices();
    menu();
    return 0;
}


int menu(){
    int choice;

    do{
        printMenuOptions();
        if((scanf("%d", &choice) == 0) || 
            ((choice != 1) && (choice != 2) && (choice != 3) 
            && (choice != 4) && (choice != 5))){
            while (getchar() != '\n'); // Clear buffer
            printf("Error: Please only input an option from 1-5.\n");
        }
        
    } while((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5));
    //printf("Your choice is %d", choice);

    if(choice == 1){
        initializeMatrices();
    } else if(choice == 2){
        additionOrSubtraction(1);
    } else if(choice == 3){
        additionOrSubtraction(2);
    } else if(choice == 4){
        multiplication();
    } else{
        printf("Exiting program.");
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
    int row;
    int col;
    FILE *fp;

    //int check; // For various validation checks
    
    
    do{
        printf("Please enter the name of the file you would like to upload: ");
        fgets(fileName, sizeof(fileName), stdin);
        fileName[strcspn(fileName, "\n")] = '\0'; // remove the newline char
        //printf("The file name is %s\n", fileName);
        fp = fopen(fileName, "r");
        if(fp == NULL){
            printf("Error: File not found. Please try again.\n");
        }
    } while(fp == NULL);




    fclose(fp);
    return 0;
}

float additionOrSubtraction(){
    return 0;
}

float multiplication(){
    return 0;
}

bool sizeValidation(int option){
    int matrixARows; // # of rows in matrix A
    int matrixBRows;
    int matrixACols;
    int matrixBCols;

    if(option == 1){ // addition or subtraction
        matrixARows = sizeof(matrixA)/sizeof(matrixA[0]);
        matrixBRows = sizeof(matrixB)/sizeof(matrixB[0]);
        matrixACols = sizeof(matrixA[0])/sizeof(matrixA[0][0]);
        matrixBCols = sizeof(matrixB[0])/sizeof(matrixB[0][0]);
        if((matrixARows != matrixBRows) || (matrixACols != matrixBCols)){
            printf("Error: matrix A and matrix B must be the same size.\n");
            printf("Please select another operation or choose 2 new matrices.\n");
            return false;
        } 
    } else{ //multiplication
        if(matrixACols != matrixBRows){
            printf("Error: Cannot multiply matrix A by matrix B.\n");
            printf("The number of columns in matrix A must equal the number of columns in matrix B.\n");
            printf("Please select another operation or choose 2 new matrices.\n");
            return false;
        }
    }
    
    return true;
}

int randomMatrices(int size){
    return 0;
}

int printMatrix(float (*given)[100]){
    return 0;
}

