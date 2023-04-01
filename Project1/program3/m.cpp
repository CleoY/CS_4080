#include <stdio.h>
#include <random>
#include <chrono>

Matrix matrixA;
Matrix matrixB;

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







/// matrix obj will not be null
    // Deallocate matrixA
    // In case user already initialized matrices and wants to use different matrices
    if(matrixA.existenceCheck()){ // If matrixA already exists, delete it
        matrixA.deleteMatrix();
        matrixA = NULL;
    }

    // Deallocate matrixB
    if(matrixB != NULL){
        matrixB.deleteMatrix();
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

    
    
    fclose(fp);
    return 0;
}