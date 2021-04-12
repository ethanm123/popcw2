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

  private static int isTuesday(int year, int month, int century){
    //Algorithm taken from: https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html
    int result = (int) Math.round((1 + Math.floor((2.6 * month) - 0.2) - (2 * 19) + year + Math.floor(year / 4) + Math.floor(19 / 4)) % 7);
    if (result == 6){
      return 1;
    } else{
      return 0;
    }
  }
	
  public static int howManyTuesdays(){
    int totalTuesdays = 0;
		for (int i = 1901; i <= 2000; i++){
      for (int j = 1; j <= 12; j++){
        if (j == 11 || j == 12){
          totalTuesdays = totalTuesdays + isTuesday(i - 1, j, 19);
        } else{
          totalTuesdays = totalTuesdays + isTuesday(i, j, 19);
        }
      }
    }
    return totalTuesdays;
  }
	
	public static void main(String[] args){
		int result = CWK2Q8.howManyTuesdays();
		System.out.println("Number of Tuesdays = " + result);
	}
}
