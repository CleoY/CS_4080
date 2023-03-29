#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//#include "arrays.h"

int menu();
int printMenuOptions();
int initializeMatrices();
int additionOrSubtraction(int option);
int multiplication();
bool sizeValidation(int option);
int randomMatrices(int size);
//int printMatrix(int rows, int cols, float given[rows][cols], char msg[]);
//int printMatrix(int cols, float given[][cols]);
//int printMatrix(float** given, int rows, int cols, char msg[]);
int printMatrix(int rows, int cols, float given[rows][cols], char msg[]);

float matrixA[100][100];
float matrixB[100][100];

int matrixARows;
int matrixACols;
int matrixBRows;
int matrixBCols;

int main(){
    int menuResult = 0;

    initializeMatrices();
    do{
        menuResult = menu();
    } while(menuResult != 5);
    
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
        additionOrSubtraction(1);
    } else if(choice == 3){
        additionOrSubtraction(2);
    } else if(choice == 4){
        multiplication();
    } else{
        printf("Exiting program.");
        return 5;
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
    // for(int i=0; i<5; i++){
    //     for(int j=0; j<5; j++){
    //         matrixA[i][j] = 1.0;
    //     }
    // }


    // Read size of matrixA from first line of file
    fscanf(fp, "%d %d", &matrixARows, &matrixACols);
    fscanf(fp, "%*c"); // Clear file reader buffer
    printf("MatA size: %d %d\n", matrixARows, matrixACols);

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


    printf("MatrixA: \n");
    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixACols; j++){
            printf("%f ", matrixA[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    // now upload matrix B
    fscanf(fp, "%d %d", &matrixBRows, &matrixBCols);
    fscanf(fp, "%*c"); // Clear file reader buffer
    printf("MatB size: %d %d\n", matrixBRows, matrixBCols);

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

    printf("MatrixB: \n");
    for(int i=0; i<matrixBRows; i++){
        for(int j=0; j<matrixBCols; j++){
            printf("%f ", matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    fclose(fp);
    return 0;
}

int additionOrSubtraction(int option){
    if(!sizeValidation(1)){
        return 1;
    }

    // Can use matrixB's dimensions instead of matrixA's because they are equal
    float intermediate[matrixARows][matrixACols];
    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixACols; j++){
            if(option == 1){ // Addition
                intermediate[i][j] = matrixA[i][j] + matrixB[i][j];
            } else{ // Subtraction
                intermediate[i][j] = matrixA[i][j] - matrixB[i][j];
            }
        }
    }

    // Print resulting matrix
    printf("Resulting matrix: \n");
    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixACols; j++){
            printf("%f ", intermediate[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int multiplication(){
    if(!sizeValidation(2)){
        return 1; // Function failure
    }

    // Initialize intermediate matrix
    float intermediate[matrixARows][matrixBCols];
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
    
    // Print intermediate matrix
    printf("Resulting matrix: \n");
    for(int i=0; i<matrixARows; i++){
        for(int j=0; j<matrixBCols; j++){
            printf("%f ", intermediate[i][j]);
        }
        printf("\n");
    }

    return 0;
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
// int printMatrix(int rows, int cols, float given[rows][cols], char msg[]) {
//     int i = 0;
//     int j = 0;

//     //Location(a[i][j]) = address(a[1][1]) + (i-1)*n*element_size + (j-1)*element_size
//     // a[1][1] = a[0][0] + 99 cols + 1 row
//     // last in row: a[0][3] (96 more cols unused + 1 row to get to a[1][1])


//     printf("%s\n", msg);
//     for(int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             printf("%f ", given[i][j]);
//         }
//         // if(j < 100){
//         //     i+=
//         // }
//         printf("\n");
//     }
//     return 0;

//     // printf("%s\n", msg);
//     // while(i<100){
//     //     while(j<100){
//     //         printf("%f ", given[i][j]);
//     //         
//     //         j++;
//     //         if(j == cols){
//     //             j=0;
//     //             break;
//     //         }
//     //     }
//     //     printf("\n"); 
//     //     i+=(100-cols);
//     //     if(i == rows){
//     //         break;
//     //     }
//     // }
//     // printf("\n");

//     // return 0;
// }