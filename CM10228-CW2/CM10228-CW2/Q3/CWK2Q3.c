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
int size = 0; //Total size of the hashmap.
int total_keys = 0; //Number of elements in the map right now.
char *hold_string = ""; //The holding string that's added to the map when an element is removed.

//Finds the next free index in the hashmap.
int get_next_free_index(int original_index, char **my_array) {
	//Performs the add-one probing when looking for a space to insert. The first thing it checks is the input index.
	for (int i = original_index; i < size; i++) {
		if (my_array[i] == NULL || strcmp(my_array[i], hold_string) == 0) {
			return i;
		}
	}
	return -1;
}

//The hash function as defined in the coursework specification.
int hash_function(const char *key) {
	int sum = 0;
	for (int i = 0; i < strlen(key); i++) {
		sum += key[i];
	}
	return sum % size;
}

//Calculates the loading factor. Returns 1 if a resize is needed (load factor > 0.7).
int calculate_loading_factor() {
	double load_factor = (double) total_keys / size;
	if (load_factor > 0.7) {
		return 1;
	}
	return 0;
}

//Resizes the map.
void resize_map(int new_size) {
	//malloc code from: https://www.guru99.com/malloc-in-c-example.html
	char **new_map = (char **) malloc(new_size * sizeof(*new_map)); //Allocates size for the new map.
	if (new_map == NULL) { //Checks for a null pointer.
		printf("Failed to allocate more memory");
		exit(0);
	}
	int temp = size;
	int new_hash;
	size = new_size;
	for (int i = 0; i < temp; i++) {
		if (hash_map[i] == NULL) {
			continue;
		}
		if (strcmp(hash_map[i], hold_string) != 0) {
			new_hash = hash_function(hash_map[i]); //Recalculating the hashes for the new map.
			new_map[get_next_free_index(new_hash, new_map)] = hash_map[i]; //Places them in the correct index in the new map.
		}
	}
	free(hash_map); //Frees the old hashmap.
	hash_map = new_map; //Replaces the old hashmap with the new one.
}

//Adds a string to the hashmap.
void add_to_map(const char *name) {
	int hash = hash_function(name); //Gets the hash value for the name.
	char *string_to_insert = (char *) malloc((strlen(name) + 1) * sizeof(char));
	if (string_to_insert == NULL) {
		printf("Failed to allocate more memory");
		exit(0);
	} //Allocates memory to store the name and checks for a null pointer. If all is good, copies it in.
	strcpy(string_to_insert, name);
	hash_map[get_next_free_index(hash, hash_map)] = string_to_insert; //Adds the value to the nearest free index. 
	total_keys++; //Increments total keys.
	if (calculate_loading_factor() == 1) { //If the hash map now has a loading factor of > 0.7, double the size.
		resize_map(size * 2);
	}
}

//Removes a given name from the map.
int remove_from_map(const char *name) {
	int hash = hash_function(name); //Finds the hash of this name.
	for (int i = hash; i < size; i++) { //Performs add-one probing starting at the hash index.
		if (hash_map[i] != NULL && strcmp(hash_map[i], name) == 0) {
			//If it finds the name, free the memory used by the name, decrement total_keys, replace it with a hold string and 
			//returns 1 for success.
			free(hash_map[i]);
			total_keys--;
			hash_map[i] = hold_string;
			return 1;
		}
	}
	//Return 0 for fail.
	return 0;
}


//Searches the map for a given name.
int search_map(const char *name) {
	int hash = hash_function(name); //Finds the hash of the name.
	for (int i = hash; i < size; i++) {
		if (hash_map[i] != NULL && strcmp(hash_map[i], name) == 0) {
			//If it finds a matching string return true. Performs add-one probing to do this.
			return 1;
		}
	}
	//If no string is found return false.
	return 0;
}

//Loops through the map and prints all values found.
void print_map() {
	for (int i = 0; i < size; i++) {
		if (hash_map[i] != NULL && strcmp(hash_map[i], hold_string) != 0) {
			//Only prints a value if it isn't null or a hold string.
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
	if(ret) {
		printf("Found %s!\n", stringOne);
	}

	remove_from_map(stringThree);

	ret = search_map(stringFive);
	if(ret) {
		printf("Found %s!\n", stringFive);
	}
	printf("\n");
	print_map();

	add_to_map(stringThree);
	printf("\n");
	print_map();

	return EXIT_SUCCESS;
}
