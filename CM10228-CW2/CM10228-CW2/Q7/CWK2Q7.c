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

int *sortKey(const char *key){
	//Using buuble sort pseudocode from lecture
	char *edit_key = (char *) malloc((strlen(key) + 1) * sizeof(char));
	strcpy(edit_key, key);
	int *sorted_key = (int *) malloc((strlen(key) + 1) * sizeof(int));
	for (int i = 0; i < strlen(key); i++){
		sorted_key[i] = i;
	}
	int swapped = 1;
	char char_temp;
	int int_temp;
	while (swapped){
		swapped = 0;
		for (int i = 1; i < strlen(key); i++){
			if (edit_key[i - 1] > edit_key[i]){
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
	return sorted_key;
}

void encrypt_columnar(const char *message_filename, const char *key, char **result){
	char **sorting_array = (char **) malloc(2 * sizeof(*sorting_array));
	sorting_array[0] = (char*) malloc((strlen(key) + 1) * sizeof(char));
	sorting_array[1] = (char*) malloc((strlen(key) + 1) * sizeof(char));
	if (sorting_array == NULL){
		printf("Error allocating memory for array");
		exit(0);
	}
	int *sorted_key = sortKey(key);
	int size = 2;
	int first_index = 0;
	int second_index = 0;
	char thisChar;
	int increment;
	FILE *file = fopen(message_filename, "r");
	if (file == NULL){
		printf("File does not exist");
		return;
	}
	//https://www.codevscolor.com/c-program-read-file-contents-character
	while ((thisChar = fgetc(file)) != EOF){
		increment = 1;
		if (thisChar == '\n'){
			continue;
		}
		sorting_array[first_index][second_index] = thisChar;
		if (second_index == strlen(key) - 1){
			second_index = 0;
			increment = 0;
			sorting_array[first_index][strlen(key)] = '\0';
			first_index++;
			sorting_array[first_index] = (char*) malloc((strlen(key) + 1) * sizeof(char));
		}
		if (first_index == size - 1){
			char **new_array = (char **) realloc(sorting_array, sizeof(*sorting_array)  * (size + 1));
			if (new_array == NULL){
				printf("error allocating more memory");
				exit(0);
			} else{
				increment = 0;
				size++;
				sorting_array = new_array;
				second_index = 0;
			}
		}
		if (increment){
			second_index++;
		}
	}
	if (second_index < strlen(key)){
		for (int i = second_index; i < strlen(key); i++){
			sorting_array[first_index][i] = 'x';
		}
		sorting_array[first_index][strlen(key)] = '\0';
	}
	*result = (char *) malloc(((strlen(key) + 1) * (size - 1)) * sizeof(char));
	if (*result == NULL){
		printf("Error allocating memory for result");
		exit(0);
	}
	int count = 0;
	for (int i = 0; i < size - 1; i++){
		for (int j = 0; j < strlen(key); j++){
			strncat(*result, &sorting_array[i][sorted_key[j]], 1);
			count++;
		}
		free(sorting_array[i]);
	}
	free(sorting_array);
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
