#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//#include "arrays.h"

int menu();
int printMenuOptions();
int initializeMatrices();
float additionOrSubtraction(int option);
float multiplication();
bool sizeValidation(int option);
int randomMatrices(int size);
//int printMatrix(int rows, int cols, float given[rows][cols], char msg[]);
//int printMatrix(int cols, float given[][cols]);
//int printMatrix(float** given, int rows, int cols, char msg[]);
int printMatrix(int rows, int cols, float given[rows][cols]);

float matrixA[100][100];
float matrixB[100][100];

int matrixARows;
int matrixACols;
int matrixBRows;
int matrixBCols;

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
            printf("Error: Please only input an option from 1-5.\n");
        }
        while (getchar() != '\n'); // Clear buffer
        
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
    //while ((getchar()) != '\n'); // Clear buffer
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


    // init matrix A
    for(int i=0; i<100; i++){
        for(int j=0; j<100; j++){
            matrixA[i][j] = 1.0;
        }
    }







    // Read size of matrixA from first line of file
    fscanf(fp, "%d %d", &matrixARows, &matrixACols);
    fscanf(fp, "%*c"); // Clear file reader buffer
    printf("MatA size: %d %d\n", matrixARows, matrixACols);

    // NEED to press enter after it prints, for some reason
    //while (getchar() != '\n'); // Clear buffer

    int rowCounter = 0;
    int colCounter = 0;

    while(rowCounter < matrixARows){
        while(colCounter < matrixACols){        // check != "\n"
            fscanf(fp, "%f", &temp);
            //printf("Temp: %f ", temp);
            //printf("r: %d, c: %d\n", rowCounter, colCounter);
            matrixA[rowCounter][colCounter] = temp;
            //printf(" MatrixA[r][c] = %f\n", matrixA[rowCounter][colCounter]);
            colCounter++;
            check = fgetc(fp);
            //printf("check: %d\n", check); //print ascii code of whitespace
            if(check == '\n'){
                //printf("Check is a newline char \n");
                break;
            }
        }
        colCounter = 0;
        rowCounter++;
        //printf("row counter: %d\n", rowCounter);
    }

    //printMatrix((float**)matrixA, matrixARows, matrixACols, "MatrixA: ");

    // print matrixA
    // printMatrix(matrixARows, matrixACols, matrixA, "Matrix A:\n");
    // printMatrix(matrixACols, matrixA);
    
    printf("MatrixA: \n");
    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixACols; j++){
            printf("%f ", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printMatrix(matrixARows, matrixACols, matrixA);

    // now upload matrix B
    fscanf(fp, "%d %d", &matrixBRows, &matrixBCols);
    fscanf(fp, "%*c"); // Clear file reader buffer
    printf("MatB size: %d %d\n", matrixBRows, matrixBCols);

    rowCounter = 0;
    colCounter = 0;

    while(rowCounter < matrixBRows){
        while(colCounter < matrixBCols){        // check != "\n"
            fscanf(fp, "%f", &temp);
            //printf("Temp: %f ", temp);
            //printf("r: %d, c: %d\n", rowCounter, colCounter);
            matrixB[rowCounter][colCounter] = temp;
            //printf(" MatrixB[r][c] = %f\n", matrixB[rowCounter][colCounter]);
            colCounter++;
            check = fgetc(fp);
            //printf("check: %d\n", check); //print ascii code of whitespace
            if(check == '\n'){
                //printf("Check is a newline char \n");
                break;
            }
        }
        colCounter = 0;
        rowCounter++;
        //printf("row counter: %d\n", rowCounter);
    }

    printf("MatrixB: \n");
    for(int i=0; i<matrixBRows; i++){
        for(int j=0; j<matrixBCols; j++){
            printf("%f ", matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printMatrix(matrixBRows, matrixBCols, matrixB);

    float matrix[3][4] = {{1.0, 2.0, 3.0, 4.0},
                          {5.0, 6.0, 7.0, 8.0},
                          {9.0, 10.0, 11.0, 12.0}};
    printMatrix(3, 4, matrix);


    fclose(fp);
    return 0;
}

float additionOrSubtraction(int option){
    printf("MatrixA in add: \n");
    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixACols; j++){
            printf("%f ", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

float multiplication(){
    return 0;
}

// bool sizeValidation(int option){
//     int matrixARows; // # of rows in matrix A
//     int matrixBRows;
//     int matrixACols;
//     int matrixBCols;

//     if(option == 1){ // addition or subtraction
//         matrixARows = sizeof(matrixA)/sizeof(matrixA[0]);
//         matrixBRows = sizeof(matrixB)/sizeof(matrixB[0]);
//         matrixACols = sizeof(matrixA[0])/sizeof(matrixA[0][0]);
//         matrixBCols = sizeof(matrixB[0])/sizeof(matrixB[0][0]);
//         if((matrixARows != matrixBRows) || (matrixACols != matrixBCols)){
//             printf("Error: matrix A and matrix B must be the same size.\n");
//             printf("Please select another operation or choose 2 new matrices.\n");
//             return false;
//         } 
//     } else{ //multiplication
//         if(matrixACols != matrixBRows){
//             printf("Error: Cannot multiply matrix A by matrix B.\n");
//             printf("The number of columns in matrix A must equal the number of columns in matrix B.\n");
//             printf("Please select another operation or choose 2 new matrices.\n");
//             return false;
//         }
//     }

//     return true;
// }

int randomMatrices(int size){
    return 0;
}

// current printMatrix function does not print as expected due to the way that arrays are stored in memory.
// for the following matrix:
/**
 * 1 2 3 0 0 0
 * 4 5 6 0 0 0 
 * 7 8 9 0 0 0
 * it will be stored as 1 2 3 0 0 0 4 5 6 0 0 0 7 8 9 0 0 0
 * which means you need to increment the row and col counters more to access the next row
*/
int printMatrix(int rows, int cols, float given[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", given[i][j]);
        }
        printf("\n");
    }
    return 0;
}

// int printMatrix(float** given, int rows, int cols, char msg[]){

//     printf("%s\n", msg);
//     for(int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             printf("%f ", given[i][j]);
//         }
//         printf("\n");
//     }
//     return 0;
// }


// int printMatrix(int cols, float given[][cols]){
//     for(int i=0; i<3; i++){
//         for(int j=0; j<cols; j++){
//             printf("%f ", given[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
//     return 0;
// }

// int printMatrix(int rows, int cols, float given[rows][cols], char msg[]){
//     printf("\n%s", msg);
//     for(int i=0; i<rows; i++){
//         for(int j=0; j<cols; j++){
//             printf("%f ", given[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
    
//     return 0;
// }

// int printMatrix(float (*given)[100]){
//     if(&given == &matrixA){
//         printf("Given is matrix A.\n");
//     }
//     return 0;
// }

