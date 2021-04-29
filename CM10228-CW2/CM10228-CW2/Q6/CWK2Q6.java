/**
 *  @author Anonymous (do not change)
 *
 *  Question 6:
 *
 *  Implement in Java a similar algorithm to that in Q5, i.e. given a
 *  block of text your algorithm should be able to redact words from
 *  a given set and outputs the result to a file called â€œresult.txtâ€�.
 *  However, in this implementation of the algorithm all
 *  redactable words will be proper nouns (i.e. a name used for an
 *  individual person, place, or organisation, spelled with an initial
 *  capital letter) and your algorithm should take into account that
 *  the list of redactable words might not be complete. For example,
 *  given the block of text:
 *      It was in July, 1805, and the speaker was the well-known Anna
 *      Pavlovna Scherer, maid of honor and favorite of the Empress
 *      Marya Fedorovna. With these words she greeted Prince Vasili
 *      Kuragin, a man of high rank and importance, who was the first
 *      to arrive at her reception. Anna Pavlovna had had a cough for
 *      some days. She was, as she said, suffering from la grippe;
 *      grippe being then a new word in St. Petersburg, used only by
 *      the elite.
 *
 *  and the redactable set of words
 *      Anna Pavlovna Scherer, St. Petersburg, Marya Fedorovna
 *
 *  the output text should be
 *      It was in ****, 1805, and the speaker was the well-known ****
 *      ******** *******, maid of honor and favorite of the *******
 *      ***** *********. With these words she greeted ****** ******
 *      *******, a man of high rank and importance, who was the first
 *      to arrive at her reception. **** ******** had had a cough for
 *      some days. She was, as she said, suffering from la grippe;
 *      grippe being then a new word in *** **********, used only by
 *      the elite.
 *
 *  You should test your program using the example files provided.
*/
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CWK2Q6 {

  private static final ArrayList<String> punctuationToEndSentence = new ArrayList<String>(Arrays.asList("!", ".", "?")); //List of sentence ending punctuation.
	private static ArrayList<String> wordsToRedact;
	private static ArrayList<String> previouslyRedacted = new ArrayList<String>();

  /*
	 * Returns a string of asterisks that is the same length as the word being redacted. Keeps punctuation consistent.
	 * @param toAsterisk the string that needs to be redacted.
	 * @return a string of asterisks and punctuation with appropriate length.
	*/
	private static String asteriskStringGenerator(String toAsterisk) {
		boolean dot = false;
    if (wordsToRedact.contains(toAsterisk.replaceAll("\"|'|“", "").toUpperCase())) {
			if (wordsToRedact.get(wordsToRedact.indexOf(toAsterisk.replaceAll("\"|'|“", "").toUpperCase())).contains(".")) {
				dot = true; //Checks if the dot needs to be redacted.
			}
		}
		String asteriskString = "";
    for (int i = 0; i < toAsterisk.length(); i++) {
      if (Character.isLetter(toAsterisk.charAt(i)) || (dot && toAsterisk.charAt(i) == ".".charAt(0))) {
        asteriskString = asteriskString + "*"; //Redact all letters or dots that need redacting.
      } else {
        asteriskString = asteriskString + toAsterisk.charAt(i); //If not just add the punctuation.
      }
    }
    return asteriskString; 
  }

	/*
	 * Gets the list of words that need redacting from the redact.txt file.
	 * @param redactFileName the file name of words to redact.
	 * @return ArrayList of words that need to be redacted.
	*/
  private static ArrayList<String> getRedactList(String redactFileName) throws IOException {	
		if (!((new File(redactFileName)).exists())) { //Check if redact file exists.
			System.out.println("Redact file does not exist");
			System.exit(0);
		}
		BufferedReader redactReader = new BufferedReader(new FileReader(redactFileName)); //Open buffered reader.
    ArrayList<String> redactList = new ArrayList<String>();
		String line;
    String previousLine = "";
		while ((line = redactReader.readLine()) != null) {
			for (String s : line.split(" ")) { //Split each line by spaces and add it to the array list.
        redactList.add(s.toUpperCase());
      }
		}
    redactReader.close(); //Close buffered reader.
    return redactList;
	}

  /*
	 * Checks if the first letter of a given string is a capital letter.
	 * @param toTest the string to check.
	 * @return true if the first letter is a capital, false if it is not.
	*/
	private static boolean firstLetterCapital(String toTest) { 
    for (int i = 0; i < toTest.length(); i++) { //Finds first letter in string.
      if (Character.isLetter(toTest.charAt(i))) {
        if (Character.isUpperCase(toTest.charAt(i))) { //Checks if it is upper case.
          return true;
        } else {
          return false;
        }
      }
    }
    return false;
  }

	/*
	 * Runs a series of checks to see if a word is a proper noun or just some random word with a capital.
	 * @param toTest the string that needs to be checked to see if it is a proper noun or not
	 * @param toTestNoPunc toTest with punctuation removed.
	 * @param prevWord the previous word from the line. Used to see if punctuation was at the end.
	 * @param previousLine see if the word is at the start of a paragraph.
	 * @return true if the word is a proper noun, false if not.
	*/
  private static boolean testProperNoun(String toTest, String toTestNoPunc, String prevWord, String previousLine) {
		if (previouslyRedacted.contains(toTestNoPunc.replaceAll("\"|'|“", "").toUpperCase())) {
			//Check if the word has been redacted previously. If it has, redact it again.
			return true;
		} else if (((previousLine.equals("") && prevWord.length() == 0) || (prevWord.length() > 0 && punctuationToEndSentence.contains(Character.toString(prevWord.charAt(prevWord.length() - 1))) && !previouslyRedacted.contains(toTestNoPunc.replaceAll("\"|'|“", "").toUpperCase())))) {
			//Check if the word is at the start of a sentence or paragraph. If so, check the redact list.
      return wordsToRedact.contains(toTestNoPunc.replaceAll("\"|'|“", "").toUpperCase());
    } else if (toTestNoPunc.equals("I")) {
			//I is not a proper noun, account for this.
      return false;
    } else {
			//If it falls to here it must be a proper noun so add it to the list of previously redacted words and return true.
			previouslyRedacted.add(toTestNoPunc.replaceAll("\"|'|“", "").toUpperCase());
      return true;
    }
  }

	/*
	 * Creates the results file that will be written in.
	*/
  private static void makeResultsFile() throws IOException {
    File resutltFile = new File("./result.txt");
    if (!resutltFile.exists()) {
      resutltFile.createNewFile();
    }
  }

	/*
	 * Writes all of the results that have been compiled to the results file.
	 * @param fileRewrite a string buffer containing all of the words to add to the file.
	*/
  private static void writeToResultsFile(StringBuffer fileRewrite) throws IOException {
    FileOutputStream fileOut = new FileOutputStream("./result.txt");
    fileOut.write(fileRewrite.toString().getBytes());
    fileOut.close();
  }

	/*
	 * The main function for redacting the words.
	 * @param textFilename the name of the text file to be redacted.
	 * @param redactWordsFilename the name of the filename that contains words to be redacted.
	*/
	public static void redactWords(String textFilename, String redactWordsFilename) {
    try {
			int count = 0;
      makeResultsFile();
			if (!((new File(textFileName)).exists())) { //Check if text file exists.
				System.out.println("Text file does not exist");
				System.exit(0);
			}	
      wordsToRedact = getRedactList(redactWordsFilename);
      BufferedReader textFileReader = new BufferedReader(new FileReader(textFilename)); //Open buffered reader.
      StringBuffer fileRewrite = new StringBuffer();
      String line, lineNoPunc, currentWordNoPunc;
      String previousLine = "";
      String prevWord = "";
      String newLineString;
      List<String> currentLineWords, currentLineWordsNoPunc;
      while ((line = textFileReader.readLine()) != null) { //Read each line of the file.
        newLineString = "";
        currentLineWords = Arrays.asList(line.split(" ")); //Split the words based on spaces.
				if (line.equals("")) { //If line is empty, reflect this in prevWord.
					prevWord = "";
				}
        for (int i = 0; i < currentLineWords.size(); i++) { //LOop through each word in the line.
					//Regex from https://www.studytonight.com/java-examples/how-to-remove-punctuation-from-string-in-java
					currentWordNoPunc = currentLineWords.get(i).replaceAll("\\p{Punct}", ""); //Strip each word of its punctuation.
          if (firstLetterCapital(currentWordNoPunc)) { //If the first letter is a capital:
						if (testProperNoun(currentLineWords.get(i), currentWordNoPunc, prevWord, previousLine)) { //Check if its a proper noun.
							newLineString = newLineString + " " + asteriskStringGenerator(currentLineWords.get(i)); //If it is, run it through the string generator.
						} else {
							newLineString = newLineString + " " + currentLineWords.get(i); //If it isn't just add it to the line that will be written to the results file.
						}
          } else {
            newLineString = newLineString + " " + currentLineWords.get(i); //If the first letter is not a capital just add it straight to the string buffer.
          }
					prevWord = currentLineWords.get(i);
        }
        fileRewrite.append(newLineString + "\n"); //Add the line to the string buffer.
        previousLine = line;
        prevWord = currentLineWords.get(currentLineWords.size() - 1);
      }
      writeToResultsFile(fileRewrite); //Write the results to the file and close the buffered reader.
      textFileReader.close();
    } catch (IOException e) { //Catch the IO Exception and exit if it happens.
      System.out.println("Error reading/writing file");
			System.exit(0);
    }
	}

	public static void main(String[] args) {
		String inputFile = "./warandpeace.txt";
		String redactFile = "./redact.txt";
		redactWords(inputFile, redactFile);
	}

}
