#include <stdio.h>
#include <random>
#include <chrono>

Matrix matrixA = NULL;
Matrix matrixB = NULL;


int menu();
int printMenuOptions();
int initializeMatrices();
bool sizeValidation(int option);
int randomMatrices(int size);
//int printMatrix(float** given, int rows, int cols);

int main(){


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
        //
    } else if(choice == 3){
        //
    } else if(choice == 4){
        //
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