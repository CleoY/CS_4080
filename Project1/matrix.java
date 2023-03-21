package Project1;
import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.io.FileNotFoundException;
import java.io.File;

public class matrix {
    private float[][] matrixA;
    private float[][] matrixB;
    
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

     public int menu() throws FileNotFoundException, InputMismatchException{
        Scanner userInput = new Scanner(System.in);
        int choice = 0;


        //userInput.nextLine();
        

        // do{
        //     printMenuOptions();
        //     try {
        //         if(!userInput.hasNextInt()) {
        //             System.out.println("Invalid input. Please enter a number.");
        //             //userInput.nextLine();
        //         }
        //         choice = userInput.nextInt();  
                
                

        //         // buffer is empty??
        //         // still nothing in buffer after invalid input -> exceptions


        //     } catch (InputMismatchException e){
        //         System.out.println("Please only select option 1 - 5.");
        //         //userInput.nextLine(); // Clear buffer
        //     } catch (NoSuchElementException e2){
        //         System.out.println("Error: nothing in buffer.");
        //         break;
        //     }
        // } while((choice != 1) && (choice != 2) && (choice != 3)
        //         && (choice != 4) && (choice != 5));
        
            //
        printMenuOptions();
        while (!userInput.hasNextInt()) {
            System.out.println("Invalid input. Please enter a number.");
            userInput.nextLine();
        }
    
        choice = userInput.nextInt();
        userInput.nextLine(); // clear buffer of newline char

        System.out.println("Choice 1: "+choice);

        if(choice == 1){
            initializeArrays();
        } else if(choice == 2){
            addition();
        } else if(choice == 3){
            subtraction();
        } else if(choice == 4){
            multiplication();
        } else{
            System.out.println("Exiting program.");
        }

        System.out.println("Choice: "+choice);
        userInput.close();
        return choice; // If user inputs 5, exit.
        
    }

    private void printMenuOptions(){
        System.out.println("");
        System.out.println("1: Upload 2 new matrices.");
        System.out.println("2: Matrix addition.");
        System.out.println("3: Matrix subtraction.");
        System.out.println("4: Matrix multiplication.");
        System.out.println("5: Exit program.");
    }



    public void initializeArrays() throws NumberFormatException, InputMismatchException, FileNotFoundException{
        Scanner userInput = new Scanner(System.in);
        int inputMethod = 0;
        String fileName = "";
        //String input = "";
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
        float temp = 0;

        // Matrix B size
        int rowB = 0;
        int colB = 0;

        validNum = false;

        // Enter the matrices' sizes and elements
        if(inputMethod == 1){
            do{
                try{
                    System.out.println("Please enter the size of matrix 1 in the form of \"row col\".");
                    //input = userInput.nextLine();
                    rowA = userInput.nextInt();
                    colA = userInput.nextInt();

                    System.out.println("Please enter the size of matrix 2 in the form of \"row col\".");
                    //input = userInput.nextLine();
                    rowB = userInput.nextInt();
                    colB = userInput.nextInt();
                    validNum = true;
                } catch(InputMismatchException e){
                    System.out.println("Error: Please only input integers.");
                    userInput.nextLine(); // Clear buffer
                    validNum = false;
                } // catch (NumberFormatException e2){
                //     System.out.println("Error: Please only input integers.");
                //     userInput.nextLine(); // Clear buffer
                //     validNum = false;
                // }
            }while(!validNum);

            System.out.println("MatA size: "+rowA+" "+colA);
            System.out.println("MatB size: "+rowB+" "+colB);

            // Set sizes of matrices
            matrixA = new float[rowA][colA];
            matrixB = new float[rowB][colB];

            // Input matrices' elements
            for (int r=0; r<rowA; r++){
                System.out.println("Please enter the elements for matrix 1 separated by spaces.");
                for (int c=0; c<colA; c++){
                    temp = userInput.nextFloat();
                    matrixA[r][c] = temp;
                }
            }

            for (int r=0; r<rowB; r++){
                System.out.println("Please enter the elements for matrix 2 separated by spaces.");
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
            
            System.out.println(file);
            
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


        //??
        //userInput.nextLine();


        userInput.close();
    }

    private void addition(){

    }

    private void subtraction(){

    }

    private void multiplication(){

    }
    

    private void printMatrices(){
        System.out.println("Matrix 1");
        for(int i=0; i<matrixA.length; i++){
            for(int j=0; j<matrixA[i].length; j++){
                System.out.print(matrixA[i][j]+" ");
            }
            System.out.println("");
        }

        System.out.println("Matrix 2");
        for(int i=0; i<matrixB.length; i++){
            for(int j=0; j<matrixB[i].length; j++){
                System.out.print(matrixB[i][j]+" ");
            }
            System.out.println("");
        }
    }
}
