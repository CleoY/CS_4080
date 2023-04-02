package Project1;
import java.io.IOException;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.time.Duration;

public class Main {
    public static void main(String args[]) throws IOException, FileNotFoundException{       
        int menuResult = 0;
        Scanner userInput = new Scanner(System.in);
        matrix start = new matrix();
        
        //Normal driver code
        start.initializeMatrices(userInput);
        do{
            menuResult = start.menu(userInput);
        } while(menuResult != 5);
        
        // Code just for measuring time taken to complete multiplication function for nxn matrices
        // start.randomMatrices(1024);
        // double beginning = System.nanoTime();
        // start.multiplication();
        // double end = System.nanoTime();
        // double duration = end - beginning;
        // duration /= 1000000;
        // System.out.println("Duration: "+duration+" ms");

        userInput.close();
    }
}
