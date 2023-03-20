package Project1;
import java.util.Scanner;
import java.util.InputMismatchException;
import java.io.FileNotFoundException;

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


        int rowA = 0;
        int colA = 0; 
        float temp = 0;
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



        // } else if(inputMethod == 2){
        //     System.out.println("Please enter the name of the file you would like to upload:");
        //     fileName = userInput.nextLine(); //get file name from user input
        //     File file = new File(fileName);

        //     // Check file existance
        //     while(!file.exists()){
        //         System.out.println("Error: File not found. Please enter another file name.");
        //         fileName = userInput.nextLine(); //get file name from user input
        //         file = new File(fileName);
        //     }
            
        //     Scanner fileScanner = new Scanner(file);    
        //     while(fileScanner.hasNextLine()){
        //         Scanner lineScanner = new Scanner(fileScanner.nextLine());
        //         //System.out.println("\nLine "+ row);
        //         col=0;
        //         while(lineScanner.hasNextInt()){
        //             temp = lineScanner.nextInt();
        //             if(col < augmentedMatrix[row].length){
        //                 augmentedMatrix[row][col] = temp;
        //             } else{
        //                 BVector[row] = temp;
        //             }
        //             col++;
        //         }
        //         row++;
        //         lineScanner.close();
        //     }
        //     //System.out.println("Done processing text file.");

        //     fileScanner.close();
        // }

        printMatrices();
        userInput.close();
        }
    }

    private void printMatrices(){
        // Print augmented matrix
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
