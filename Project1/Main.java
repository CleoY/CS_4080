package Project1;
import java.io.IOException;
import java.io.FileNotFoundException;

public class Main {
    public static void main(String args[]) throws IOException, FileNotFoundException{       
        int menuResult = 0;
        matrix start = new matrix();
        //start.menu();
        for(int i=0; i<2; i++){
            start.menu();
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
        // System.out.println("End of program.");
    }
}
