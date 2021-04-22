import java.util.ArrayList;
import java.util.Collections;

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
import java.text.DecimalFormat;
import java.util.Arrays;

public class CWK2Q1 {

	private static final ArrayList<Integer> gaps = new ArrayList<Integer>(Arrays.asList(511, 255, 127, 63, 31, 15, 7, 3, 1));

	private static void printArray(ArrayList<Double> array){
		//https://stackoverflow.com/q/2538787
		DecimalFormat formatDecimals = new DecimalFormat();	
		formatDecimals.setMaximumFractionDigits(2);
		formatDecimals.setMinimumFractionDigits(2);
		int n = array.size();
		String output = "[";
		for (int printer = 0; printer < n; printer++){
			if (printer != n - 1){
				output = output + formatDecimals.format(array.get(printer)) + ", ";
			} else{
				output = output + formatDecimals.format(array.get(printer)) + "]";
			}
		}
		System.out.println(output);
	}

	public static void shell_sort(ArrayList<Double> array) {
		//Pseudocode from https://en.wikipedia.org/wiki/Shellsort
		int n = array.size();
		if (n > 1000){
			return;
		}
		int j;
		for (Integer gap : gaps){
			for (int i = gap; i < n; i++){
				double temp = array.get(i);
				for (j = i; j >= gap && array.get(j - gap) > temp; j -= gap){
					array.set(j, array.get(j - gap));
				}
				array.set(j, temp);
			}
			printArray(array);
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
