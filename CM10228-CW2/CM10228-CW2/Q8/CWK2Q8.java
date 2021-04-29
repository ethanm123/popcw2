/**
 *  @author Anonymous (do not change)
 *
 *  Question 8:
 *
 *  You are given the following information, but you may prefer
 *  to do some research for yourself.
 *   •	1 Jan 1900 was a Monday.
 *   •	Thirty days has September, April, June and November. All the rest
 *      have thirty-one, saving February alone, which has twenty-eight, rain
 *      or shine. And on leap years, twenty-nine.
 *   •	A leap year occurs on any year evenly divisible by 4, but not on a
 *      century unless it is divisible by 400.
 *
 *  How many Tuesdays fell on the first of the month during the twentieth
 *  century (1 Jan 1901 to 31 Dec 2000)?
 *
 *  Note, this problem is inspired by Project Euler so, as stated in the
 *  rules of Project Euler, your solution should return an answer under
 *  60 seconds.
*/
import java.lang.Math;

public class CWK2Q8 {

	//Month offsets used in Sakamoto's algorithm.
  private static final int[] leading_days = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

  /*
	 * Checks if a given date is a Tuesday.
	 * @param year the year of the date.
	 * @param month the month to look at.
	*/
	private static int isTuesday(int year, int month) {
    //https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week Sakamoto's algorithm
    if (month < 3) { //If the month is January or Febrary, treat it as a month of the previous year.
      year--;
    }
		//Performing Sakamoto's algorithm.
    int result = (year + year / 4 - year / 100 + year / 400 + leading_days[month - 1] + 1) % 7;
    if (result == 2) { //If the result is 2 it is a Tuesday.
      return 1;
    } else{
      return 0;
    }
  }

	/*
	 * Loops through all years and months to count the total Tuesdays.
	 * @return the number of Tuesdays on the 1st day in the month in the 20th century.
	*/
  public static int howManyTuesdays() {
    int totalTuesdays = 0;
		for (int i = 1901; i <= 2000; i++) { //Loop through all years in question.
      for (int j = 1; j <= 12; j++) { //Loop through all the months.
        totalTuesdays = totalTuesdays + isTuesday(i, j);
			}
    }
    return totalTuesdays;
  }

	public static void main(String[] args) {
		int result = CWK2Q8.howManyTuesdays();
		System.out.println("Number of Tuesdays = " + result);
	}
}
