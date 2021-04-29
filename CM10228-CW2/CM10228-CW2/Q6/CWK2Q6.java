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

  private static final ArrayList<String> punctuationToEndSentence = new ArrayList<String>(Arrays.asList("!", ".", "?"));
	private static ArrayList<String> wordsToRedact;
	private static ArrayList<String> previouslyRedacted = new ArrayList<String>();

  private static String asteriskStringGenerator(String toAsterisk){
		boolean dot = false;
    if (wordsToRedact.contains(toAsterisk.replaceAll("\"|'|“", ""))){
			if (wordsToRedact.get(wordsToRedact.indexOf(toAsterisk.replaceAll("\"|'|“", ""))).contains(".")){
				dot = true;
			}
		}
		String asteriskString = "";
    for (int i = 0; i < toAsterisk.length(); i++){
      if (Character.isLetter(toAsterisk.charAt(i)) || (dot && toAsterisk.charAt(i) == ".".charAt(0))){
        asteriskString = asteriskString + "*";
      } else{
        asteriskString = asteriskString + toAsterisk.charAt(i);
      }
    }
    return asteriskString;
  }

  private static ArrayList<String> getRedactList(String redactFileName) throws IOException{
		BufferedReader redactReader = new BufferedReader(new FileReader(redactFileName));
    ArrayList<String> redactList = new ArrayList<String>();
		String line;
    String previousLine = "";
		while ((line = redactReader.readLine()) != null){
			for (String s : line.split(" ")){
        redactList.add(s);
      }
		}
    redactReader.close();
    return redactList;
	}

  private static boolean firstLetterCapital(String toTest){
    for (int i = 0; i < toTest.length(); i++){
      if (Character.isLetter(toTest.charAt(i))){
        if (Character.isUpperCase(toTest.charAt(i))){
          return true;
        } else{
          return false;
        }
      }
    }
    return false;
  }

  private static boolean testProperNoun(String toTest, String toTestNoPunc, String prevWord, String previousLine, ArrayList<String> wordsToRedact){
		if (previouslyRedacted.contains(toTestNoPunc.replaceAll("\"|'|“", "").toUpperCase())){
			return true;
		} else if (((previousLine.equals("") && prevWord.length() == 0) || (prevWord.length() > 0 && punctuationToEndSentence.contains(Character.toString(prevWord.charAt(prevWord.length() - 1))) && !previouslyRedacted.contains(toTestNoPunc.replaceAll("\"|'|“", "").toUpperCase())))){
      return wordsToRedact.contains(toTestNoPunc.replaceAll("\"|'|“", ""));
    } else if (toTestNoPunc.equals("I")){
      return false;
    } else{
			previouslyRedacted.add(toTestNoPunc.replaceAll("\"|'|“", "").toUpperCase());
      return true;
    }
  }

  private static void makeResultsFile() throws IOException{
    File resutltFile = new File("./result.txt");
    if (!resutltFile.exists()) {
      resutltFile.createNewFile();
    }
  }

  private static void writeToResultsFile(StringBuffer fileRewrite) throws IOException{
    FileOutputStream fileOut = new FileOutputStream("./result.txt");
    fileOut.write(fileRewrite.toString().getBytes());
    fileOut.close();
  }

	public static void redactWords(String textFilename, String redactWordsFilename){
    try{
			int count = 0;
      makeResultsFile();
      wordsToRedact = getRedactList(redactWordsFilename);
      BufferedReader textFileReader = new BufferedReader(new FileReader(textFilename));
      StringBuffer fileRewrite = new StringBuffer();
      String line, lineNoPunc, currentWordNoPunc;
      String previousLine = "";
      String prevWord = "";
      String newLineString;
      List<String> currentLineWords, currentLineWordsNoPunc;
      while ((line = textFileReader.readLine()) != null){
        newLineString = "";
        //Regex from https://www.studytonight.com/java-examples/how-to-remove-punctuation-from-string-in-java
        currentLineWords = Arrays.asList(line.split(" "));
				if (line.equals("")){
					prevWord = "";
				}
        for (int i = 0; i < currentLineWords.size(); i++){
					currentWordNoPunc = currentLineWords.get(i).replaceAll("\\p{Punct}", "");
          if (firstLetterCapital(currentWordNoPunc)){
						if (testProperNoun(currentLineWords.get(i), currentWordNoPunc, prevWord, previousLine, wordsToRedact)){
							newLineString = newLineString + " " + asteriskStringGenerator(currentLineWords.get(i));
						} else{
							newLineString = newLineString + " " + currentLineWords.get(i);
						}
          } else{
            newLineString = newLineString + " " + currentLineWords.get(i);
          }
					prevWord = currentLineWords.get(i);
        }
        fileRewrite.append(newLineString + "\n");
        previousLine = line;
        prevWord = currentLineWords.get(currentLineWords.size() - 1);
      }
      writeToResultsFile(fileRewrite);
      textFileReader.close();
    } catch (IOException e){
      System.out.println("Error reading/writing file");
    }
	}

	public static void main(String[] args) {
		String inputFile = "./warandpeace.txt";
		String redactFile = "./redact.txt";
		redactWords(inputFile, redactFile);
	}

}
