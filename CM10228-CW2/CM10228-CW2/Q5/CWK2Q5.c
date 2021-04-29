/*
 ============================================================================
 Name        : CWK2Q5.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement an algorithm in C which given a file containing a block of text as
 input, redacts all words from a given set of “redactable” words (also from a
 file), and outputs the result to a file called “result.txt”. For example,
 given the block of text:
    The quick brown fox jumps over the lazy dog

 and the redactable set of words:
    the, jumps, lazy

 the output text in “result.txt” should be
    *** quick brown fox ***** over *** **** dog

 Note that the number of stars in the redacted text is the same as the number
 of letters in the word that has been redacted, and that capitalization is
 ignored. You should not use any of the string libraries to answer this
 question. You should also test your program using the example files
 provided.
 ============================================================================
*/
#include <stdio.h>
#include <stdlib.h>

//My implementation of strlen()
int length(char *input) {
	int count = 0;
	while (input[count] != '\0') {
		count++;
	}
	return count;
}

//My implementation or strcmp that compares 2 strings of letters.
int compare(char *str1, char *str2) {
	if (length(str1) != length(str2)) { //If their length doesn't match they aren't the same.
		return 0;
	}
	for (int i = 0; i < length(str2); i++) {
		//Checks equality regardless of capitalisation.
		if ((str2[i] == str1[i]) || (str2[i] == str1[i] - 32) || (str2[i] - 32 == str1[i]) || (str2[i] == str1[i] + 32) || (str2[i] + 32 == str1[i])) {
			continue;
		} else {
			return 0;
		}
	}
	return 1; //If it makes it here then the strings are equal.
}

//Compares a given string with the list of words to redact.
int toRedact (char *testString, char **redactList, int redactLength) {
	for (int i = 0; i < redactLength; i++) {
		if (compare(testString, redactList[i])) { 
			return 1; //If it finds a match return true.
		}
	}
	return 0;
}

//My implementation of strcpy.
char *copy(char *string) {
	char *new_string = malloc(length(string) * sizeof(char));
	for (int i = 0; i <= length(string); i++) {
		new_string[i] = string[i];
	}
	return new_string;
}

//Checks if a given char is a letter by using ascii values.
int isChar(char check) {
	if ((check >= 65 && check <= 90) || (check >= 97 && check <= 122)) {
		//If the char is in the ascii range of letters, return true.
		return 1;
	}
	return 0;
}

//Get the list of words to redact.
char **getRedactWords(const char *redact_file, int *redact_length) {
	FILE *filePointer = fopen(redact_file, "r");
	if (filePointer == NULL) { //Open the redact file and make sure it exists.
		printf("Redact file not found");
		exit(0);
	}
	int size = 2;
	char **redactList = (char**) malloc(2 * sizeof(*redactList)); //Allocate memory for the array of redact words.
	char thisChar;
	char *currentString;
	int count = 0;
	int char_count = 0;
	if (redactList == NULL) { //Make sure the pointer assigned to redactList is valid.
		printf("Error allocating memory to redactList");
		exit(0);
	}
	while ((thisChar = fgetc(filePointer)) != EOF) { //Loop through the file char by char.
		if (isChar(thisChar)) { //If the char is a letter add it to the current word being processed.
			if (char_count == 0) { //If the length is currently 0 allocate memory for the string.
				currentString = malloc(sizeof(char));
				if (currentString == NULL) {
					printf("Error allocating memory");
					exit(0);
				}
			} else { //If the string length > 0 then reallocate the string to add more space.
				char *newString = realloc(currentString, (char_count + 1) * sizeof(char));
				if (newString == NULL) {
					printf("Error allocating memory");
					exit(0);
				} else { //Check for null pointer and reassign the currentString.
					currentString = newString;
				}
			}
			currentString[char_count] = thisChar; //Add the char to the current string.
			char_count++; //Increment the string length.
		} else { //If it is not a char then we are at the end of the word.
			char *newString = realloc(currentString, (char_count + 1) * sizeof(char));
			if (newString == NULL) { //Realloc and check for null pointer.
				printf("Error allocating memory");
				exit(0);
			} else { 
				currentString = newString;
				currentString[char_count] = '\0'; //Add string terminator.
				char_count++; 
				redactList[count] = currentString; //Add string to redact list.
				*redact_length += 1; 
				char_count = 0;
				count++;
			}
		if (count == size - 1) {
			char **newRedactList = (char**) realloc(redactList, ((size + 1) * sizeof(*newRedactList)));
			if (newRedactList == NULL) { //If redact list is full then allocate it more memory.
				printf("Error expanding redact list");
				exit(0);
			} else {
				size++;
				redactList = newRedactList;
			}
		}
		}	
	}
	return redactList; //Return the list of words to redact.
}

//Goes through the text file and redacts the words.
void redact_words(const char *text_filename, const char *redact_words_filename) {
	int redact_length = 0;
	char **redactList = getRedactWords(redact_words_filename, &redact_length); //Get the redact list.
	FILE *text_file = fopen(text_filename, "r");
	if (text_file == NULL) {
		printf("Couldn't find text file");
		exit(0);
	}
	FILE *results_file = fopen("./result.txt", "w");
	if (results_file == NULL) { //Open the needed files, make them if needed. Check the pointers are not null.
		printf("Couldn't find / make result file");
		exit(0);
	}
	char thisChar;
	char *currentString;
	int count = 0;
	while ((thisChar = fgetc(text_file)) != EOF) { //Loop through the file char by char.
		if (isChar(thisChar)) { //If it is a char add it to the current string.
			if (count == 0) { //If current string is empty allocate memory for it.
				currentString = malloc(sizeof(char));
				if (currentString == NULL) {
					printf("Error allocating memory");
					exit(0);
				}
			} else {
				char *newString = realloc(currentString, (count + 1) * sizeof(char)); //If the string already exists add extra room to it.
				if (newString == NULL) { //Check for null pointer.
					printf("Error allocating memory");
					exit(0);
				} else {
					currentString = newString;
				}
			}
			currentString[count] = thisChar; //Add the char to the string.
			count++;
		} else {
			char *newString = realloc(currentString, (count + 1) * sizeof(char));
			if (newString == NULL) {
				printf("Error allocating memory");
				exit(0);
			} else {
				currentString = newString;
				currentString[count] = '\0'; //If at the end of the string add null terminator.
				count++;
				if (toRedact(currentString, redactList, redact_length)) {
					//If it is in redact list then add asterisks to the results file.
					for (int i = 0; i < count - 1; i++) {
						fputc('*', results_file);
					}
				} else { //If it isn't in the file add the string to the results file.
					fputs(currentString, results_file);
				}
				fputc(thisChar, results_file); //If the char wasn't a letter just add it to the results file.
			}
			count = 0;
		}
	}
	free(currentString); //Free memory and close files.
	for (int i = 0; i < redact_length; i++){
		free(redactList[i]);
	}
	free(redactList);
	fclose(results_file);
	fclose(text_file);
}

int main(int argc, char *argv[]) {
	const char *input_file = "./debate.txt";
	const char *redact_file = "./redact.txt";
	redact_words(input_file, redact_file); 
	return EXIT_SUCCESS;
}
