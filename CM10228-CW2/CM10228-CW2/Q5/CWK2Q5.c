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
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int length(char *input){
	int count = 0;
	while (input[count] != 0){
		count++;
	}
	return count;
}

int compare(char *str1, char *str2){
	if (length(str1) != length(str2)){
		return 0;
	}
	for (int i = 0; i < length(str2); i++){
		if ((str2[i] == str1[i]) || (str2[i] == str1[i] - 32) || (str2[i] - 32 == str1[i]) || (str2[i] == str1[i] + 32) || (str2[i] + 32 == str1[i])){
			continue;
		} else{
			return 0;
		}
	}
	return 1;
}

int toRedact (char *testString, char **redactList, int redactLength){
	for (int i = 0; i < redactLength; i++){
		if (compare(testString, redactList[i])){
			return 1;
		}
	}
	return 0;
}

char *copy(char *string){
	char *new_string = malloc(length(string) * sizeof(char));
	for (int i = 0; i <= length(string); i++){
		new_string[i] = string[i];
	}
	return new_string;
}

int isChar(char check){
	if ((check >= 65 && check <= 90) || (check >= 97 && check <= 122)){
		return 1;
	}
	return 0;
}

char **getRedactWords(const char *redact_file, int *redact_length){
	FILE *filePointer = fopen(redact_file, "r");
	if (filePointer == NULL){
		printf("Redact file not found");
		exit(0);
	}
	int size = 2;
	char **redactList = (char**) malloc(2 * sizeof(*redactList));
	char *line = NULL;
	size_t lineLen = 0;
	int count = 0;
	size_t read;
	if (redactList == NULL){
		printf("Error allocating memory to redactList");
		exit(0);
	}
	while ((read = getline(&line, &lineLen, filePointer)) != -1){
		char *string_to_add = copy(line);
		if (string_to_add[length(line) - 1] == '\n'){
			string_to_add[length(line) - 1] = '\0';
		} else{
			string_to_add[length(line) - 1] = '\0';
		}
		redactList[count] = string_to_add;
		*redact_length += 1;
		if (count == size - 1){
			char **newRedactList = (char**) realloc(redactList, ((size + 1) * sizeof(*newRedactList)));
			if (newRedactList == NULL){
				printf("Error expanding redact list");
				exit(0);
			} else{
				size++;
				redactList = newRedactList;
			}
		}
		count++;
	}
	return redactList;
}

void redact_words(const char *text_filename, const char *redact_words_filename){
	int redact_length = 0;
	char **redactList = getRedactWords(redact_words_filename, &redact_length);
	FILE *text_file = fopen(text_filename, "r");
	if (text_file == NULL){
		printf("Couldn't find text file");
		exit(0);
	}
	FILE *results_file = fopen("./result.txt", "w");
	if (results_file == NULL){
		printf("Couldn't find / make result file");
		exit(0);
	}
	char thisChar;
	char *currentString;
	int count = 0;
	while ((thisChar = fgetc(text_file)) != EOF){
		if (isChar(thisChar)){
			if (count == 0){
				currentString = malloc(sizeof(char));
				if (currentString == NULL){
					printf("Error allocating memory");
					exit(0);
				}
			} else{
				char *newString = realloc(currentString, (count + 1) * sizeof(char));
				if (newString == NULL){
					printf("Error allocating memory");
					exit(0);
				} else{
					currentString = newString;
				}
			}
			currentString[count] = thisChar;
			count++;
		} else{
			char *newString = realloc(currentString, (count + 1) * sizeof(char));
			if (newString == NULL){
				printf("Error allocating memory");
				exit(0);
			} else{
				currentString = newString;
				currentString[count] = '\0';
				count++;
				if (toRedact(currentString, redactList, redact_length)){
					for (int i = 0; i < count - 1; i++){
						fputc('*', results_file);
					}
				} else{
					fputs(currentString, results_file);
				}
				fputc(thisChar, results_file);
			}
			count = 0;
		}
	}
	free(currentString);
	fclose(results_file);
	fclose(text_file);
}

int main(int argc, char *argv[]) {
	const char *input_file = "./debate.txt";
	const char *redact_file = "./redact.txt";
	redact_words(input_file, redact_file);
	return EXIT_SUCCESS;
}
