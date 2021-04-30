/*
 ============================================================================
 Name        : CWK2Q7.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement a Columnar Transposition Cipher in C to encrypt a message of any
 length. A Columnar Transposition Cipher is transposition cipher that follows
 a simple rule for mixing up the characters in the plaintext to form the
 ciphertext.

 As an example, to encrypt the message ATTACKATDAWN with the keyword KEYS,
 we first write out our message as shown below,
    K	E	Y	S
    A	T	T	A
    C	K	A	T
    D	A	W	N

 Note: if the message to encode does not fit into the grid, you should pad
 the message with x's or random characters for example, ATTACKNOW with the
 keyword KEYS might look like below,
    K	E	Y	S
    A	T	T	A
    C	K	N	O
    W	X	X	X

 Once you have constructed your table, the columns are now reordered such
 that the letters in the keyword are ordered alphabetically,
    E	K	S	Y
    T	A	A	T
    K	C	T	A
    A	D	N	W

 The ciphertext is now read off along the columns, so in our example above,
 the ciphertext is TAATKCTAADNW.

 You should demonstrate your implementation by encrypting the file in the
 folder Q7 using the keyword - LOVELACE.

 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Alphabetically sorting the key using bubble sort.
int *sortKey(const char *key) {
	//Using buuble sort pseudocode from lecture
	char *edit_key = (char *) malloc((strlen(key) + 1) * sizeof(char));
	if (edit_key == NULL) { //Allocate memory for key and check for null pointer.
		printf("Error allocating memory for edit key");
		exit(0);
	}
	strcpy(edit_key, key); 
	int *sorted_key = (int *) malloc((strlen(key) + 1) * sizeof(int));
	if (sorted_key == NULL) { //Allocate memory for the sorted indexes, check for null pointer.
		printf("Error allocating memory for sorted_key");
		exit(0);
	}
	for (int i = 0; i < strlen(key); i++) { //Add values to the sorted_key representing all the chars in the key.
		sorted_key[i] = i;
	}
	int swapped = 1;
	char char_temp;
	int int_temp;
	while (swapped) { //Performing bubble sort on the key, and moving the appropriate elements in the sorted_key.
		swapped = 0;
		for (int i = 1; i < strlen(key); i++) {
			if (edit_key[i - 1] > edit_key[i]) { 
				char_temp = edit_key[i - 1];
				edit_key[i - 1] = edit_key[i];
				edit_key[i] = char_temp;
				int_temp = sorted_key[i - 1];
				sorted_key[i - 1] = sorted_key[i];
				sorted_key[i] = int_temp;
				swapped = 1;
			}
		}
	}
	free(edit_key); 
	return sorted_key; //Returns the array of positions of chars after they have been ordered alphabetically.
}

//The main function for the columnar encryption.
void encrypt_columnar(const char *message_filename, const char *key, char **result) {
	char **sorting_array = (char **) malloc(2 * sizeof(*sorting_array)); //Allocating memory for the sorting_array and its first 2 elements.
	sorting_array[0] = (char*) malloc((strlen(key) + 1) * sizeof(char));
	sorting_array[1] = (char*) malloc((strlen(key) + 1) * sizeof(char));
	if (sorting_array == NULL || sorting_array[0] == NULL || sorting_array[1] == NULL) { //Checking for null pointers.
		printf("Error allocating memory for array");
		exit(0);
	}
	int *sorted_key = sortKey(key); //Get the sorted key from function above.
	int size = 2;
	int first_index = 0;
	int second_index = 0;
	char thisChar;
	int increment;
	FILE *file = fopen(message_filename, "r"); 
	if (file == NULL) { //Open the message file and make sure it exists.
		printf("File does not exist");
		return;
	}
	//Looping through characters in the file one by one: https://www.codevscolor.com/c-program-read-file-contents-character
	while ((thisChar = fgetc(file)) != EOF) {
		increment = 1;
		if (thisChar == '\n') { //Skip newline characters.
			continue;
		}
		sorting_array[first_index][second_index] = thisChar; //Add this char to the right position in the string.
		if (second_index == strlen(key) - 1) { //If the string is as long as the key make a new string.
			second_index = 0;
			increment = 0;
			sorting_array[first_index][strlen(key)] = '\0'; //Add null terminator to the end of the string.
			first_index++;
			sorting_array[first_index] = (char*) malloc((strlen(key) + 1) * sizeof(char)); //Allocate memory for the next string.
		}
		if (first_index == size - 1) {
			//Allocate extra memory for the table.
			char **new_array = (char **) realloc(sorting_array, sizeof(*sorting_array)  * (size + 1));
			if (new_array == NULL) { //Check for null pointer.
				printf("error allocating more memory");
				exit(0);
			} else {
				increment = 0;
				size++;
				sorting_array = new_array;
				second_index = 0;
			}
		}
		if (increment) {
			second_index++;
		}
	}
	if (second_index == 0) { //Make sure extra string is not appended to end of result if it isn't needed.
		free(sorting_array[first_index]);
		size--;
	}
	if (second_index != 0 && second_index < strlen(key)) { //Pad with x's if needed.
		for (int i = second_index; i < strlen(key); i++) {
			sorting_array[first_index][i] = 'x';
		}
		sorting_array[first_index][strlen(key)] = '\0';
	}
	*result = (char *) malloc(((strlen(key) + 1) * (size - 1)) * sizeof(char)); //Allocate memory to result.
	if (*result == NULL) { //Check for null pointer.
		printf("Error allocating memory for result");
		exit(0);
	}
	int count = 0;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < strlen(key); j++) {
			//Loop through all of the strings and add the characters to the result in the order defined by the bubble sort.
			strncat(*result, &sorting_array[i][sorted_key[j]], 1);
			count++;
		}
		free(sorting_array[i]); //Free the memory used in sorting array.
	}
	free(sorting_array); //Free all of the other memory used.
	free(sorted_key);
	fclose(file);
}

int main(int argc, char *argv[]) {
	const char *example_message = "./text.txt";
	const char *example_key = "LOVELACE";
	char *encrypted_message = NULL;
	encrypt_columnar(example_message, example_key, &encrypted_message);
	printf("Encrypted message = %s\n", encrypted_message);
	free(encrypted_message);
	return EXIT_SUCCESS;
}
