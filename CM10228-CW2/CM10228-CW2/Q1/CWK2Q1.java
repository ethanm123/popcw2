import java.util.ArrayList;
import java.util.Collections;
import java.text.DecimalFormat;
import java.util.Arrays;


/**
 *  @author Anonymous (do not change)
 *
 *  Question 1:
 *
 *  Implement the Shellsort algorithm (https://en.wikipedia.org/wiki/Shellsort) 
 *  for an array of up to 1000 signed doubles in Java. Your solution must use 
 *  concrete gaps of [1, 3, 7, 15, 31, 63, 127, 255, 511]. Your solution must 
 *  print the (partially) sorted array after each gap on a new line in the form:
 *      [a0, a1, a2, a3, ..., an]
 *  Where an is the nth element in the (partially) sorted array (please note 
 *  the space after the commas), and each element should be formatted to 2 
 *  decimal places (e.g. 1.00).
 *
*/

public class CWK2Q1 {

	//Defining gaps as required in spec.
	private static final ArrayList<Integer> gaps = new ArrayList<Integer>(Arrays.asList(511, 255, 127, 63, 31, 15, 7, 3, 1));

	/**
	 * Function for printing out the array in the format required (2dp).
   * @param array The array that needs printing.
	*/
	private static void printArray(ArrayList<Double> array) {
		//https://stackoverflow.com/q/2538787 learning how to format to 2dp.
		DecimalFormat formatDecimals = new DecimalFormat();	
		formatDecimals.setMaximumFractionDigits(2); //Defining the decimal format required (must be 2dp.)
		formatDecimals.setMinimumFractionDigits(2);
		int n = array.size();
		String output = "[";
		for (int printer = 0; printer < n; printer++) { //Looping through the array.
			if (printer != n - 1) {
				output = output + formatDecimals.format(array.get(printer)) + ", "; //Adding the string of each decimal to the output.
			} else {
				output = output + formatDecimals.format(array.get(printer)) + "]"; //Ending the output with the square bracket.
			}
		}
		System.out.println(output); //Printing the finished output.
	}

	/*
	 * The main shell sort function that performs the sorting.
	 * @param array The array to be sorted.
	*/
	public static void shell_sort(ArrayList<Double> array) {
		//Using the pseudocode from the provided wikipedia article (https://en.wikipedia.org/wiki/Shellsort).
		int n = array.size();
		if (n > 1000) { //If the array is bigger than 1000 doubles it returns (up to 1000 signed doubles as required in the spec.)
			return;
		}
		int j;
		for (Integer gap : gaps) { //Looping through each gap.
			for (int i = gap; i < n; i++) { //Only enters into this loop if the gap is less than the length of the array.
				double temp = array.get(i); //Stores the variable that is currently in this position of the array.
				for (j = i; j >= gap && array.get(j - gap) > temp; j -= gap) { //Moves earlier sorted elements until the correct position for temp is found.
					array.set(j, array.get(j - gap));
				}
				array.set(j, temp); //Sets this position's value to temp.
			}
			printArray(array); //Printing the array after each gap.
		}
	}

	public static void main(String[] args) {
		ArrayList<Double> testList = new ArrayList<Double>();
		testList.add(3.4);
		testList.add(6.55);
		testList.add(-12.2);
		testList.add(1.73);
		testList.add(140.98);
		testList.add(-4.18);
		testList.add(52.87);
		testList.add(99.14);
		testList.add(73.202);
		testList.add(-23.6);
		
		shell_sort(testList);
	}
}
