import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

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

	private static int findCorrectValue(int[][] searchArray, int index, int value, String item, ArrayList<String> array){
		if (array.get(searchArray[index][1]).equals(item)){
			return searchArray[index][1];
		}
		if (index != 0 && searchArray[index - 1][0] == value){
			for (int i = index - 1; i > -1; i--){
				if (searchArray[i][0] == value){
					if (array.get(searchArray[i][1]).equals(item)){
						return searchArray[i][1];
					}
				} else{
					break;
				}
			}
		} else if (index != searchArray.length - 1 && searchArray[index + 1][0] == value){
			for (int i = index + 1; i < searchArray.length - 1; i++){
				if (searchArray[i][0] == value){
					if (array.get(searchArray[i][1]).equals(item)){
						return searchArray[i][1];
					}
				} else{
					break;
				}
			}
		}
		return -1;
	}

	private static int[][] getSearchArray(ArrayList<String> array){
		int[][] arrayToSearch = new int[array.size()][2];
		int sum;
		for (int i = 0; i < array.size(); i++){
			sum = 0;
			for (int j = 0; j < array.get(i).length(); j++){
				sum += (int) (array.get(i).charAt(j));
			}
			arrayToSearch[i][0] = sum;
			arrayToSearch[i][1] = i;
		}
		return arrayToSearch;
	}

	public static int interpolation_search(ArrayList<String> array, String item) {
		int[][] arrayToSearch = getSearchArray(array);
		int itemValue = 0;
		for (int i = 0; i < item.length(); i++){
			itemValue += (int) (item.charAt(i));
		}
		//Sorting taken from https://stackoverflow.com/questions/15452429/java-arrays-sort-2d-array
		Arrays.sort(arrayToSearch, (a, b) -> Integer.compare(a[0], b[0]));
		int low = 0;
		int high = arrayToSearch.length - 1;
		int mid; 
		while ((arrayToSearch[high][0] != arrayToSearch[low][0]) && (itemValue >= arrayToSearch[low][0]) && (itemValue <= arrayToSearch[high][0])){
			mid = low + ((itemValue - arrayToSearch[low][0]) * (high - low) / (arrayToSearch[high][0] - arrayToSearch[low][0]));
			if (arrayToSearch[mid][0] < itemValue){
				low = mid + 1;
			} else if (itemValue < arrayToSearch[mid][0]){
				high = mid - 1;
			} else{
				return findCorrectValue(arrayToSearch, mid, itemValue, item, array);
			}
		}
		if (itemValue == arrayToSearch[low][0]){
			return findCorrectValue(arrayToSearch, low, itemValue, item, array);
		} else{
			return -1;
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
