package Project1;
import java.io.IOException;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class Main {
    public static void main(String args[]) throws IOException, FileNotFoundException{       
        int menuResult = 0;
        Scanner userInput = new Scanner(System.in);
        matrix start = new matrix();
        
        
        
        //start.menu(userInput);
        for(int i=0; i<2; i++){
            start.menu(userInput);
        }
        //start.initializeArrays();
        //start.menu();
        // while(true){
        //     start.menu();
        //     if (menuResult == 5){
        //         break;
        //     }
        // }
        // do{
        //     menuResult = start.menu();
        // } while(menuResult != 5);
        
        userInput.close();
        System.out.println("End of program. Scanner closed.");
    }
}
