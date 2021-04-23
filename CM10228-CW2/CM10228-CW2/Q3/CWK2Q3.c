/*
 ============================================================================
 Name        : CWK2Q3.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement your own Hash Table in C for storing and searching names, i.e. char
 arrays. In the event of collisions, you should use linear probing with an
 interval of 1. The hash function should be the sum of the ASCII values of the
 string modulo the size of the underlying data structure. Your Hash Table
 implementation should have the following interface:
	int hash_function(const char *key)
	void resize_map(int new_size)
	void add_to_map(const char *name)
	int remove_from_map(const char *name)
	int search_map(const char *name)
	void print_map()

 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **hash_map;  // this is where you should store your names
int size = 0;
int total_keys = 0;
char *hold_string = "";

int get_next_free_index(int original_index, char **my_array){
	for (int i = original_index; i < size; i++){
		if (my_array[i] == NULL || strcmp(my_array[i], hold_string) == 0){
			return i;
		}
	}
	return -1;
}

int hash_function(const char *key) {
	int sum = 0;
	for (int i = 0; i < strlen(key); i++){
		sum += key[i];
	}
	return sum % size;
}

int calculate_loading_factor(){
	double load_factor = (double) total_keys / size;
	if (load_factor > 0.7){
		return 1;
	}
	return 0;
}

void resize_map(int new_size) {
	//Learnt to malloc for pointers: https://www.guru99.com/malloc-in-c-example.html
	char **new_map = malloc(new_size * sizeof(*new_map));
	if (new_map == NULL){
		return;
	}
	int temp = size;
	int new_hash;
	size = new_size;
	for (int i = 0; i < temp; i++){
		if (hash_map[i] == NULL){
			continue;
		}
		if (strcmp(hash_map[i], hold_string) != 0){
			new_hash = hash_function(hash_map[i]);
			new_map[get_next_free_index(new_hash, new_map)] = hash_map[i];
		}
	}
	free(hash_map);
	hash_map = new_map;
}

void add_to_map(const char *name) {
	int hash = hash_function(name);
	char *string_to_insert = malloc((strlen(name) + 1) * sizeof(char));
	if (string_to_insert == NULL){
		return;
	}
	strcpy(string_to_insert, name);
	hash_map[get_next_free_index(hash, hash_map)] = string_to_insert;
	total_keys++;
	if (calculate_loading_factor() == 1){
		resize_map(size * 2);
	}
}

int remove_from_map(const char *name) {
	int hash = hash_function(name);
	for (int i = hash; i < size; i++){
		if (hash_map[i] != NULL && strcmp(hash_map[i], name) == 0){
			free(hash_map[i]);
			total_keys--;
			hash_map[i] = hold_string;
			return 1;
		}
	}
	return 0;
}

int search_map(const char *name) {
	int hash = hash_function(name);
	for (int i = hash; i < size; i++){
		if (hash_map[i] != NULL && strcmp(hash_map[i], name) == 0){
			return 1;
		}
	}
	return 0;
}

void print_map() {
	for (int i = 0; i < size; i++){
		if (hash_map[i] != NULL && strcmp(hash_map[i], hold_string) != 0){
			printf("%s At index: %d\n", hash_map[i], i);
		}
	}
}

int main(int argc, char *argv[]) {
	char *stringOne = "#Hello world!";
	char *stringTwo = "How are you?";
	char *stringThree = "Be the best you...!!";
	char *stringFour = "Be kind to yourself";
	char *stringFive = "Principles of Programming 2";

	resize_map(6);
	add_to_map(stringOne);
	add_to_map(stringTwo);
	add_to_map(stringOne);
	add_to_map(stringThree);
	add_to_map(stringFour);
	add_to_map(stringFive);
	
	print_map();
	printf("\n");

	int ret = search_map(stringOne);
	if(ret){
		printf("Found %s!\n", stringOne);
	}

	remove_from_map(stringThree);

	ret = search_map(stringFive);
	if(ret){
		printf("Found %s!\n", stringFive);
	}
	printf("\n");
	print_map();

	add_to_map(stringThree);
	printf("\n");
	print_map();

	return EXIT_SUCCESS;
}
