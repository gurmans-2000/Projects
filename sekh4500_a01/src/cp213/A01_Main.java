package cp213; // sekh4500

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.Scanner;

/**
 * @author Gurman Sekhon 181004500 sekh4500@mylaurier.ca
 *
 */
public class A01_Main {
    // Constants
    public static final String SEP = "-".repeat(40);
	public static final String CIPHERTEXT = "AVIBROWNZCEFGHJKLMPQSTUXYD"; // for testing substitute method

    public static void main(String[] args) throws FileNotFoundException{
    int target = 5;
    int[] values = new int[] {1,2,3,4};
    
    System.out.println(A01.contains(values, target) + " : Contains" );
    System.out.println(SEP);
    palindrome();
    System.out.println(SEP);
    isValid();
    System.out.println(SEP);
    matrixStats();
    System.out.println(SEP);
    sumPartialHarmonic();
    System.out.println(SEP);
    validSn();
    System.out.println(SEP);
    validSnFile();
   }
    public static void palindrome() {
    	String s = ("an na");
    	A01.isPalindrome(s);
    	System.out.println(A01.isPalindrome(s) + " : IsPalindrome");
    }
    public static void isValid() {
    	String name = "32hello";
    	A01.isValid(name);
    	System.out.println(A01.isValid(name) + " : IsValid");
    }
    public static void matrixStats() {
    	double [][] a = new double[][]  {{1,0,10,4},
    	{5,6,7,8}};
    	
    	for (int x= 0; x < A01.matrixStats(a).length; x++) {
    		System.out.println(A01.matrixStats(a)[x]);
    	}
    }
    public static void sumPartialHarmonic() {
    	int n = 12;
    	System.out.printf("Sum is %f: sumPartialHarmonic\n",A01.sumPartialHarmonic(n));
    }
    public static void validSn() {
    	String sn = "SN/1234-567";
    	System.out.printf("%b: ValidSn\n",A01.validSn(sn));
    	
    }
    public static void validSnFile() throws FileNotFoundException{
    	File file = new File("C:\\Users\\Tardis\\CP213\\sekh4500_a01\\src\\cp213\\fileIn");
    	Scanner scan = new Scanner(file);
    	PrintStream good = new PrintStream("C:\\Users\\Tardis\\CP213\\sekh4500_a01\\src\\cp213\\goodSns");
    	PrintStream bad = new PrintStream("C:\\Users\\Tardis\\CP213\\sekh4500_a01\\src\\cp213\\badSns");
    	A01.validSnFile(scan, good, bad);
    	
        
    }
}







