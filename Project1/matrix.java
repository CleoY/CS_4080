package Project1;
import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Random;
import java.io.FileNotFoundException;
import java.io.File;

public class matrix {
    private float[][] matrixA;
    private float[][] matrixB;
    //private Scanner userInput;
    /*
     * +, -, x
     * ask user to enter 2 matrices
     * present menu that loops and asks user which oper
     *      can exit menu
     *      can choose 2 new matrices
     * print result every time
     * floats
     * check matrices' sizes before oper
     * can enter by:
     *  - ask user size of each matrix, then elements
     *  - ask user to input both matrices from one or 2 text files
     *      first line = size; then elements
     */

     /**
      * Display menu to user and let them choose a menu option
      * @param userInput    Passed scanner from the main class so only 1 scanner is used throughout the lifetime of the program.
      * @return             Returns user's choice. If choice = 5, indicate to main class to terminate program.
      * @throws FileNotFoundException
      * @throws InputMismatchException
      */
     public int menu(Scanner userInput) throws FileNotFoundException, InputMismatchException{
        userInput = new Scanner(System.in);
        int choice = 0;
        
        do{
            printMenuOptions();
            try {
                // if((choice != 1) && (choice != 2) && (choice != 3)
                //         && (choice != 4) && (choice != 5)){
                //     System.out.println("Please only select option 1 - 5.");
                // }
                choice = userInput.nextInt();  
            } catch (InputMismatchException e){
                System.out.println("Please only select option 1 - 5.");
                userInput.nextLine(); // Clear buffer
            } catch (NoSuchElementException e2){
                System.out.println("Error: nothing in buffer.");
                break;
            }
        } while((choice != 1) && (choice != 2) && (choice != 3)
                && (choice != 4) && (choice != 5));
        
        //System.out.println("Choice 1: "+choice);

        if(choice == 1){
            initializeMatrices(userInput);
        } else if(choice == 2){ // Addition
            additionOrSubtraction(1);
        } else if(choice == 3){ // Subtraction
            additionOrSubtraction(2);
        } else if(choice == 4){
            multiplication();
        } else{
            System.out.println("Exiting program.");
        }

        //System.out.println("Choice: "+choice);
        return choice; // If user inputs 5, exit.
        
    }

    /**
     * Just print the possible menu options.
     */
    private void printMenuOptions(){
        System.out.println("");
        System.out.println("1: Upload 2 new matrices.");
        System.out.println("2: Matrix addition.");
        System.out.println("3: Matrix subtraction.");
        System.out.println("4: Matrix multiplication.");
        System.out.println("5: Exit program.");
    }


    /**
     * Initialize the size and elements of matrixA and matrixB.
     * @param userInput    Passed scanner from the main class so only 1 scanner is used throughout the lifetime of the program.
     * @throws NumberFormatException
     * @throws InputMismatchException
     * @throws FileNotFoundException
     */
    public void initializeMatrices(Scanner userInput) throws NumberFormatException, InputMismatchException, FileNotFoundException{
        int inputMethod = 0;
        String fileName = "";
        boolean validNum = false;

        // Get user's matrix input method
        System.out.println("Please select a method to input the matrices.");
        do{
            System.out.println("1: Manually input every element for each matrix.");
            System.out.println("2: Upload the matrices from a text file.");
            try {
                inputMethod = userInput.nextInt();    
            } catch (InputMismatchException e){
                System.out.println("Please only select option 1 or 2.");
                userInput.nextLine(); // Clear buffer
            }
        } while((inputMethod != 1) && (inputMethod != 2));
        userInput.nextLine(); //Clear buffer

        // Matrix A size
        int rowA = 0;
        int colA = 0; 

        // Matrix B size
        int rowB = 0;
        int colB = 0;

        float temp = 0;
        validNum = false;

        // Enter the matrices' sizes and elements
        if(inputMethod == 1){
            do{
                try{
                    System.out.println("Please enter the size of matrix A in the form of \"row col\".");
                    //input = userInput.nextLine();
                    rowA = userInput.nextInt();
                    colA = userInput.nextInt();

                    System.out.println("Please enter the size of matrix B in the form of \"row col\".");
                    //input = userInput.nextLine();
                    rowB = userInput.nextInt();
                    colB = userInput.nextInt();
                    validNum = true;
                } catch(InputMismatchException e){
                    System.out.println("Error: Please only input integers.");
                    userInput.nextLine(); // Clear buffer
                    validNum = false;
                }
            }while(!validNum);

            System.out.println("MatA size: "+rowA+" "+colA);
            System.out.println("MatB size: "+rowB+" "+colB);

            // Set sizes of matrices
            matrixA = new float[rowA][colA];
            matrixB = new float[rowB][colB];

            // Input matrices' elements
            for (int r=0; r<rowA; r++){
                System.out.println("Please enter the elements for matrix A separated by spaces.");
                for (int c=0; c<colA; c++){
                    temp = userInput.nextFloat();
                    matrixA[r][c] = temp;
                }
            }

            for (int r=0; r<rowB; r++){
                System.out.println("Please enter the elements for matrix B separated by spaces.");
                for (int c=0; c<colB; c++){
                    temp = userInput.nextFloat();
                    matrixA[r][c] = temp;
                }
            }
        } else if(inputMethod == 2){
            File file;
        
            System.out.println("Please enter the name of the file you would like to upload:");    
            do{
                fileName = userInput.nextLine(); //get file name from user input
                file = new File(fileName);
                if (!file.exists()){
                    System.out.println("Error: File not found. Please enter another file name.");
                }
            } while(!file.exists());
            
            //System.out.println(file);
            


            // Can try to make more efficient starting here
            Scanner fileScanner = new Scanner(file); 
            Scanner lineScanner;
            rowA = fileScanner.nextInt();
            colA = fileScanner.nextInt();
            matrixA = new float [rowA][colA];
            fileScanner.nextLine();

            //System.out.println("MatA size: "+rowA+" "+colA);

            int rowCounter = 0;
            int colCounter = 0;

            // Scan for matrix A
            while(rowCounter < rowA){
                //System.out.println("Row counter: "+rowCounter);
                lineScanner = new Scanner(fileScanner.nextLine());
                while(lineScanner.hasNextFloat()){
                    //System.out.println("Col counter: "+colCounter);
                    temp = lineScanner.nextFloat();
                    //System.out.println("Temp: "+ temp);
                    matrixA[rowCounter][colCounter] = temp;
                    colCounter++;
                    if(colCounter >= colA){
                        colCounter = 0;
                        //System.out.println("break?");
                        break;
                    }
                }
                lineScanner.close();
                rowCounter++;
                //System.out.println("Row counter again: "+rowCounter);
            }

            // Reset temp counters
            rowCounter = 0;
            colCounter = 0;

            // Initialize matrix B size
            rowB = fileScanner.nextInt();
            colB = fileScanner.nextInt();
            matrixB = new float [rowB][colB];
            fileScanner.nextLine();

            //System.out.println("MatB size: "+rowB+" "+colB);

            // Scan for matrix B
            while(rowCounter < rowB){
                lineScanner = new Scanner(fileScanner.nextLine());
                while(lineScanner.hasNextFloat()){
                    temp = lineScanner.nextFloat();
                    matrixB[rowCounter][colCounter] = temp;
                    colCounter++;
                    if(colCounter >= colB){
                        colCounter = 0;
                        break;
                    }
                }
                lineScanner.close();
                rowCounter++;
            }
            fileScanner.close();
        }

        printMatrices();
    }


    //// MAY NOT NEED TO RETURN MATRIX
    /**
     * Returns matrix after addition or subtraction between matrix A and B. 
     * Option flag allows me to reuse code since addition and subtraction operations are similar.
     * @param option    A flag for addition or subtraction
     * @return          The resulting matrix after adding/subtracting matrixA and matrixB.
     *                  Return null if size validation fails.
     */
    private float[][] additionOrSubtraction(int option){
        if(!sizeValidation(1)){
            return null;
        }
        float[][] intermediate = new float[matrixA.length][matrixA[0].length];
        int rows = matrixA.length; // could use matrixB. After size validation, they should be equal
        int cols = matrixA[0].length;
        
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                if(option == 1){ // addition
                    intermediate[i][j] = matrixA[i][j] + matrixB[i][j];
                } else{ // subtraction
                    intermediate[i][j] = matrixA[i][j] - matrixB[i][j];
                }
            }
        }
        printMatrix(intermediate, "\nResulting matrix: ");
        return intermediate;
    }



    /**
     * Multiply matrix A and B
     * @return  Return the product matrix.
     *          Return null and exit function if sizes of matrices are invalid.
     */
    public float[][] multiplication(){
        if(!sizeValidation(2)){
            return null; // Exit function if sizes are invalid for multiplication.
        }
        // Intermediate matrix should have the same number of rows as matrixA and columns as matrixB
        float[][] intermediate = new float[matrixA.length][matrixB[0].length];
        for(int i=0; i<matrixA.length; i++){
            for(int j=0; j<matrixB[0].length; j++){
                for(int k=0; k<matrixA[i].length; k++){
                    intermediate[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
        //printMatrix(intermediate, "\nResulting matrix: ");
        return intermediate;
    }
    


    /**
     * Validates the size of matrixA and matrixB for addition, subtraction, or multiplication
     * @param option    Choice between addition/subtraction or multiplication validation    
     * @return          Returns a boolean indicating whether the matrices are of acceptable sizes.
     */
    private boolean sizeValidation(int option){
        if(option == 1){ // addition or subtraction
            if((matrixA.length != matrixB.length) || (matrixA[0].length != matrixB[0].length)){
                System.out.println("Error: matrix A and matrix B must be the same size.");
                System.out.println("Please select another operation or choose 2 new matrices.");
                return false;
            }
        } else{ // multiplication
            if(matrixA[0].length != matrixB.length){
                System.out.println("Error: Cannot multiply matrix A by matrix B.");
                System.out.println("The number of columns in matrix A must equal the number of columns in matrix B.");
                System.out.println("Please select another operation or choose 2 new matrices.");
                return false;
            }
        }
        return true;
    }



    /**
     * Initialize matrixA and matrixB with random numbers given a desired size.
     * @param size Length and height of each matrix. 
     *      Square matrices so the lengths and heights will all be equivalent.
     */
    public void randomMatrices(int size){
        matrixA = new float[size][size];
        matrixB = new float[size][size];
        Random rand = new Random();

        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                matrixA[i][j] = rand.nextFloat() * (10.0f);
                matrixB[i][j] = rand.nextFloat() * (10.0f);
            }
        }

        
        //printMatrices();
    }

    // public matrix(int size){
    //     nSizeMatrix = new int[size][size];
    //     for(int i=0; i<size; i++){
    //         for(int j=0; j<size; j++){
    //             nSizeMatrix[i][j] =(int) (Math.random()*(10-1)); // can change to dif range later, after testing
    //         }
    //     }
    //     //saveMatrix();
    // }

    // delete later
    private void printMatrices(){
        printMatrix(matrixA, "Matrix A");
        printMatrix(matrixB, "Matrix B");
    }

    /**
     * Prints a matrix and a passed message, if any.
     * @param given A given matrix to print
     * @param msg   An associated message to print alongside the matrix
     */
    private void printMatrix(float[][] given, String msg){
        System.out.println(msg);
        for(int i=0; i<given.length; i++){
            for(int j=0; j<given[i].length; j++){
                System.out.print(given[i][j]+" ");
            }
            System.out.println("");
        }
        System.out.println("");
    }
}
