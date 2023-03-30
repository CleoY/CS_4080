#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int menu();
int printMenuOptions();
int initializeMatrices();
int additionOrSubtraction(int option);
int multiplication();
bool sizeValidation(int option);

float matrixA[100][100];
float matrixB[100][100];

int matrixARows;
int matrixACols;
int matrixBRows;
int matrixBCols;

int main(){
    int valid = 0;

    do{
        valid = initializeMatrices();
    } while(valid != 0);

    do{
        valid = menu();
    } while(valid != 5);
    
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
        fp = fopen(fileName, "r");
        if(fp == NULL){
            printf("Error: File not found. Please try again.\n");
        }
    } while(fp == NULL);

    // Read size of matrixA from first line of file
    fscanf(fp, "%d %d", &matrixARows, &matrixACols);
    fscanf(fp, "%*c"); // Clear file reader buffer
    if(matrixARows > 100 || matrixACols > 100){
        printf("Error: Matrices must fit within 100 rows x 100 columns.\n");
        printf("Please upload new matrices.\n");
        return 1; // Function failure
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
    if(matrixBRows > 100 || matrixBCols > 100){
        printf("Error: Matrices must fit within 100 rows x 100 columns.\n");
        printf("Please upload new matrices.\n");
        return 1; // Function failure
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