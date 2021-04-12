/*
 ============================================================================
 Name        : CWK2Q4.c
 Author      : Anonymous (DO NOT CHANGE)
 Description :
 Implement your own XOR Linked List (https://en.wikipedia.org/wiki/XOR_linked_list)
 in C capable of storing names. Your implementation should have the following
 functions:
    void insert_string(const char* newObj)
	int insert_before(const char* before, const char* newObj)
	int insert_after(const char* after, const char* newObj)
	void remove_string(char* result)
	int remove_after(const char *after, char *result)
	int remove_before(const char *before, char *result)
    void print_list()

 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_string(const char* newObj){
	
}


int insert_before(const char* before, const char* newObj){
	
}


int insert_after(const char* after, const char* newObj) {
	
}


int remove_string(char* result){
	
}


int remove_after(const char *after, char *result){
	
}


int remove_before(const char *before, char *result) {
	
}

void print_list(){
	
}

int main(int argc, char *argv[]) {

	insert_string("Alpha");
	insert_string("Bravo");
	insert_string("Charlie");
	insert_after("Bravo", "Delta");
	insert_before("Alpha", "Echo");
	print_list(); // Charlie -> Bravo -> Delta -> Echo -> Alpha

	char result[10];
	int ret;

	ret = remove_after("Delta",result);
	if(ret)
		printf("Removed: %s\n", result);

	ret = remove_before("Bravo", result);
	if(ret)
		printf("Removed: %s\n", result);

	ret = remove_string(result);
	if(ret)
		printf("Removed: %s\n", result);
		
	print_list();
}
