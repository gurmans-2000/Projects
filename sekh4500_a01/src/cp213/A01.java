package cp213; // sekh4500

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

/**
 * @author Gurman Sekhon 181004500 sekh4500@mylaurier.ca
 *
 */
public class A01 {

    // Constants
    public static final String VOWELS = "aeiouAEIOU";
    public static final String ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    public static final int ALPHA_LENGTH = ALPHA.length();

    /**
     * Looks for a integer in an array of integers.
     *
     * @param values array of int
     * @param target value to search for
     * @return true if target in values, false otherwise
     */
    
    public static boolean contains(int[] values, int target) {
    for (int i: values) {
    	if (i == target) {
    		return true;
    	}
    }
       return false;
    	
    }
    /**
     * Determines if s is a palindrome. Ignores case, spaces, digits, and
     * punctuation in the string parameter s.
     *
     * @param s a string
     * @return true if s is a palindrome, false otherwise
     */
    public static boolean isPalindrome(final String s) {

        String clean = s.replaceAll("\\s+", "").toLowerCase(); // changes any caps into lower case
        int l = clean.length(); // gets rid of spaces anything we dont care about
        int f = 0; // going to record the string from beginning to end
        int b = l - 1; //starts at the end and finishes at the beginning 
        while (b > f) {
            char fChar = clean.charAt(f++); // records each character from beginning to end
            char bChar = clean.charAt(b--); // records each character from end to beginning 
            if (fChar != bChar) //a palindrome should be the same forward and backwards Ex. anna
                return false;
        }
        
        return true;

    }
    /**
     * Determines if name is a valid Java variable name. Variables names must start
     * with a letter or an underscore, but cannot be an underscore alone. The rest
     * of the variable name may consist of letters, numbers and underscores.
     *
     * @param name a string to test as a Java variable name
     * @return true if name is a valid Java variable name, false otherwise
     */
    public static boolean isValid(final String name) {

    	 if (name.isEmpty()) {
    	        return false;
    	    }
    	    if (!Character.isJavaIdentifierStart(name.charAt(0))) {
    	        return false;
    	    }
    	    for (int i = 1; i < name.length(); i++) {
    	        if (!Character.isJavaIdentifierPart(name.charAt(i))) {
    	            return false;
    	        }
    	    }
    	    return true;

    }
    /**
     * Determines the smallest, largest, total, and average of the values in the 2D
     * list a. You may assume there is at least one value in a and that a is a
     * square matrix - i.e. the number of columns per row is the same. a must be
     * unchanged.
     *
     * @param a - a 2D list of numbers (2D list of double)
     *
     * @return a list of four double values containing the smallest number in a,the
     *         largest number in a, the total of all numbers in a, and the average
     *         of all numbers in a, in that order.
     */
    public static double[] matrixStats(double[][] a) {
    	
    	
    	
    	int i, j;
    	int counter = 0;
    	double[] max_one = new double[1000];
    	
     	double[] final_values = new double[]{1000, 0, 0, 0};
    	// position 0 = smallest num 
    	// position 1 = largest num 
    	// position 2 = total num 
    	//position 3 = avg num
    	for (i = 0; i < a.length; i++) {
    		for (j =0; j < a[i].length; j++ ) {
    			 max_one[counter] = a[i][j];
    			 counter += 1;
    		}
    		
    	}	
    	double[] max = new double [counter];
    	for (int x = 0; x < counter; x++) {
    		max[x] = max_one[x];
    	}
    	for (int k = 0; k < max.length; k++) {
    		final_values[2] += max[k];
    		
    		if (max[k] > final_values[1]) {
    			final_values[1] = max[k];
    		}
    		if (max[k] < final_values[0])  {
    			final_values[0] = max[k];
    			
    		}
    		
    		
    	}
    	final_values[3] = final_values[2]/counter;
    	return final_values;
    

     
    }
    /**
     * Sums and returns the total of a partial harmonic series. This series is the
     * sum of all terms 1/i, where i ranges from 1 to n (inclusive).
     *
     * @param n an integer
     * @return sum of partial harmonic series from 1 to n
     */
    public static double sumPartialHarmonic(int n) {

    	double i, s = 0.0; 
    	for (i = 1; i <= n; i++) {
    		s = s+1/i;
    	
    	}
    	return s;
    }

    /**
     * Determines if a string is a good serial number. Good serial numbers are of
     * the form 'SN/nnnn-nnn', where 'n' is a digit.
     *
     * @param sn The serial number to test.
     * @return true if the serial number is valid in form, false otherwise.
     */
    public static boolean validSn(String sn) {
    	if (sn.matches("[S]{1}[N]{1}[/]{1}[0-9]{4}[-]{1}[0-9]{3}"))
    		return true;
    	else {
    		return false;
    	}
    	
    	
    	
    	
    	
    	

    }

    /**
     * Evaluates serial numbers from a file. Writes valid serial numbers to
     * good_sns, and invalid serial numbers to bad_sns.
     *
     * @param fileIn  a file already open for reading
     * @param goodSns a file already open for writing
     * @param badSns  a file already open for writing
     * @throws FileNotFoundException 
     */
    public static void validSnFile(Scanner fileIn, PrintStream goodSns, PrintStream badSns) throws FileNotFoundException {
    	
  
    	while (fileIn.hasNextLine()) {
    		String temp = fileIn.nextLine();
    		if (A01.validSn(temp)) {
    			
    			goodSns.println(temp);	
    		}
    		else {
    			badSns.println(temp);
    		}
    	}
    }
    
    
    
    
    
    
    
}

