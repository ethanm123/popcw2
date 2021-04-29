import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.io.*;

/**
 *  @author Anonymous (do not change)
 *
 *  Question 2:
 *
 *  Implement interpolation search for a list of Strings in Java
 *  using the skeleton class provided. The method should return
 *  the position in the array if the string is present, or -1 if
 *  it is not present.
*/

public class CWK2Q2 {

	/*
	 * Checks for the eventuality that there are more than 1 item in the list with the same sum of ascii values.
	 * Finds all of these instances, and compares the item with each of them in the original array to find the 
	 * correct index in the original array.
	 * @param searchArray the 2D array of ascii values and indexes in the original array.
	 * @param index the index found by interpolation search.
	 * @pram value the sum of the ascii values of all of the chars in the item.
	 * @param item the string being searched for.
	 * @param array the original array of strings.
	 * @return the index of the string in the original array if it exists, -1 if it does not.
	*/
	private static int findCorrectValue(int[][] searchArray, int index, int value, String item, ArrayList<String> array) {
		if (array.get(searchArray[index][1]).equals(item)) { 
			//Check if the index found by the search is actually the item, if so returns this index.
			return searchArray[index][1];
		}
		if (index != 0 && searchArray[index - 1][0] == value) { //Loops through the array backwards until it finds a value that doesn't match the item value.
			for (int i = index - 1; i > -1; i--) {
				if (searchArray[i][0] == value) {
					//If the value at this index matches the value for the item, check this index against the one in the original array.
					if (array.get(searchArray[i][1]).equals(item)) {
						return searchArray[i][1]; //If it matches, return it.
					}
				} else { //If the value is not the same as the item value, break out of the loop.
					break;
				}
			}
		} 
		if (index != searchArray.length - 1 && searchArray[index + 1][0] == value) { 
			//Loops through the array forwards until it finds a value that doesn't match the item value.
			for (int i = index + 1; i < searchArray.length - 1; i++) {
				if (searchArray[i][0] == value) {
					if (array.get(searchArray[i][1]).equals(item)) {
						return searchArray[i][1]; //If it finds the index of the item return it.
					}
				} else { //If the value doesn't match the item value break.
					break;
				}
			}
		}
		return -1; //If the item still isn't found then it wasn't in the original array so return -1.
	}

	/*
	 * Generates the 2D array that will be used for sorting and searching.
	 * @param array The original array of strings inputted to the program.
	 * @return A 2D array where the first index is the sum of all the ascii values in the string, and the second
	 * is the position that string took in the original array.
	*/
	private static int[][] getSearchArray(ArrayList<String> array) {
		int[][] arrayToSearch = new int[array.size()][2]; //Defines the array.
		int sum;
		for (int i = 0; i < array.size(); i++) {
			sum = 0;
			for (int j = 0; j < array.get(i).length(); j++) {
				sum += (int) (array.get(i).charAt(j)); //Calculates the sum of all the ascii values in the current string.
			}
			arrayToSearch[i][0] = sum; //Sets the array values to match the sum and the index in the original array.
			arrayToSearch[i][1] = i;
		}
		return arrayToSearch;
	}

	/*
	 * The main interpolation search method using the pseudocode provided in the lectures. Carries out 
	 * the sorting of the array and the searching of it.
	 * @param array The array of strings to be searched.
	 * @param item The item to find in the array.
	 * @return the index in the array of the item. -1 if it doesn't exist.
	*/
	public static int interpolation_search(ArrayList<String> array, String item) {
		int[][] arrayToSearch = getSearchArray(array);
		int itemValue = 0;
		for (int i = 0; i < item.length(); i++) { //Getting the total ascii value of the item.
			itemValue += (int) (item.charAt(i));
		}
		//Sorting method taken from https://stackoverflow.com/questions/15452429/java-arrays-sort-2d-array
		Arrays.sort(arrayToSearch, (a, b) -> Integer.compare(a[0], b[0])); //Sorting the array based on the total ascii values.
		int low = 0;
		int high = arrayToSearch.length - 1;
		int mid; 
		while ((arrayToSearch[high][0] != arrayToSearch[low][0]) && (itemValue >= arrayToSearch[low][0]) && (itemValue <= arrayToSearch[high][0])) {//Starting the interpolation search loop.
			mid = low + ((itemValue - arrayToSearch[low][0]) * (high - low) / (arrayToSearch[high][0] - arrayToSearch[low][0])); //Linearlly interpolating the midpoint.
			if (arrayToSearch[mid][0] < itemValue) { //Deciding which part of the list to cut based on the values found
				low = mid + 1;
			} else if (itemValue < arrayToSearch[mid][0]) {
				high = mid - 1;
			} else {
				return findCorrectValue(arrayToSearch, mid, itemValue, item, array); //Finding the correct index.
			}
		}
		if (itemValue == arrayToSearch[low][0]) {
			return findCorrectValue(arrayToSearch, low, itemValue, item, array); //Finding the correct index if itemValue is found.
		} else {
			return -1; //Item isn't in list.
		}
	}

	public static void main(String[] args) {
		ArrayList<String> testList = new ArrayList<String>();
		testList.add("Hello");
		testList.add("World");
		testList.add("How");
		testList.add("Are");
		testList.add("You");

		int result = interpolation_search(testList, "How");
		System.out.println("Result = " + result);
	}
}
