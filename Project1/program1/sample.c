#include <stdio.h>
#include <stdbool.h>
#include <string.h>

float matrixA[100][100];
int matrixARows;
int matrixACols;


int printMatrix(int rows, int cols, float given[rows][cols], char msg[]){
    printf("\n%s", msg);
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            printf("%f ", given[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    return 0;
}

int printMatrix(int rows, int cols, float given[rows][cols], char msg[]){
    printf("\n%s", msg);
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            printf("%f ", given[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
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

    // Read size of matrixA from first line of file
    fscanf(fp, "%d %d", &matrixARows, &matrixACols);
    fscanf(fp, "%*c"); // Clear file reader buffer
    printf("MatA size: %d %d", matrixARows, matrixACols);

    int rowCounter = 0;
    int colCounter = 0;

    while(rowCounter < matrixARows){
        while((colCounter < matrixACols)){ 
            fscanf(fp, "%f", &temp);
            printf("Temp: %f ", temp);
            printf("r: %d, c: %d\n", rowCounter, colCounter);
            matrixA[rowCounter][colCounter] = temp;
            printf(" MatrixA[r][c] = %f\n", matrixA[rowCounter][colCounter]);
            colCounter++;
            check = fgetc(fp);
            printf("check: %c\n", check);
            if(strcmp(&check, "\n") == 0){
                break;
            }
        }
        colCounter = 0;
        rowCounter++;
        printf("row counter: %d\n", rowCounter);
    }
    printMatrix(matrixARows, matrixACols, matrixA, "Matrix A:\n");
    return 0;
}

int main(){
    initializeMatrices();
    menu();
    return 0;
}