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
#include <inttypes.h>

typedef struct Node{
	char *item;
	struct Node *xord_address;
}Node;

Node *head = NULL;
int element_count = 0;

Node* XORAddresses(Node *address1, Node *address2){
	// https://stackoverflow.com/questions/26569728/using-xor-with-pointers-in-c
	return (Node*) ((uintptr_t) (address1) ^ (uintptr_t) (address2));
}

Node* makeNode(const char *newString){
	char *string_to_insert = malloc(strlen(newString) * (sizeof(char)) + 1);
	if (string_to_insert == NULL){
		printf("Error allocating memory for string.");
	} else{
		strcpy(string_to_insert, newString);
	}
	Node *thisNode = malloc(sizeof(Node));
	if (thisNode == NULL){
		printf("Error allocating memory for node.");
	} else{
		thisNode->item = string_to_insert;
		element_count++;
	}
	return thisNode;
}

void deleteNode(Node *nodeToDelete){
	free(nodeToDelete->item);
	free(nodeToDelete);
	element_count--;
	if (element_count == 0){
		head = NULL;
	}
}

void insert_string(const char* newObj){
	Node *thisNode = makeNode(newObj);
	if (head != NULL){
		head->xord_address = XORAddresses(thisNode, head->xord_address);
	}
	thisNode->xord_address = head; 
	head = thisNode;
}

int insert_before(const char* before, const char* newObj){
	Node *current = head;
	Node *prev = NULL;
	Node *next;
	while (current != NULL){
		next = XORAddresses(current->xord_address, prev);
		if (prev == NULL && strcmp(current->item, before) == 0){
			insert_string(newObj);
			return 1;
		}
		if (next != NULL && strcmp(before, next->item) == 0){
			Node *thisNode = makeNode(newObj);
			thisNode->xord_address = XORAddresses(current, next);
			next->xord_address = XORAddresses(XORAddresses(current, next->xord_address), thisNode);
			current->xord_address = XORAddresses(prev, thisNode);
			return 1;
		}
		prev = current;
		current = next;
	}
	return 0;
}

int insert_after(const char* after, const char* newObj) {
	Node *current = head;
	Node *prev = NULL;
	Node *next;
	while (current != NULL){
		next = XORAddresses(current->xord_address, prev);
		if (prev != NULL && strcmp(after, prev->item) == 0){
			Node *thisNode = makeNode(newObj);
			thisNode->xord_address = XORAddresses(current, prev);
			prev->xord_address = XORAddresses(XORAddresses(current, prev->xord_address), thisNode);
			current->xord_address = XORAddresses(next, thisNode);
			return 1;
		} else if (next == NULL && strcmp(after, current->item) == 0){
			Node *thisNode = makeNode(newObj);
			thisNode->xord_address = current;
			current->xord_address = XORAddresses(current->xord_address, thisNode);
			return 1;
		}
		prev = current;
		current = next;
	}
	return 0;
}

int remove_string(char* result){
	if (head == NULL){
		return 0;
	}
	if (head->xord_address != NULL){
		head->xord_address->xord_address = XORAddresses(head->xord_address->xord_address, head);
		Node *temp = head->xord_address;
		strcpy(result, head->item);
		deleteNode(head);
		head = temp;
		return 1;
	} else{
		strcpy(result, head->item);
		deleteNode(head);
	}
	return 0;
}

int remove_after(const char *after, char *result){
	Node *current = head;
	Node *prev = NULL;
	Node *next;
	while (current != NULL){
		next = XORAddresses(current->xord_address, prev);
		if (next == NULL){
			return 0;
		}
		if (prev != NULL && strcmp(prev->item, after) == 0){
			strcpy(result, current->item);
			if (prev != NULL){
				prev->xord_address = XORAddresses(XORAddresses(prev->xord_address, current), next);
				next->xord_address = XORAddresses(XORAddresses(next->xord_address, current), prev);
				deleteNode(current);
				return 1;
			}
		}
		prev = current;
		current = next;
	}
	return 0;
}

int remove_before(const char *before, char *result) {
	Node *current = head;
	Node *prev = NULL;
	Node *next;
	while (current != NULL){
		next = XORAddresses(current->xord_address, prev);
		if (next == NULL){
			return 0;
		}
		if (next != NULL && strcmp(next->item, before) == 0){
			strcpy(result, current->item);
			if (prev != NULL){
				prev->xord_address = XORAddresses(XORAddresses(prev->xord_address, current), next);
			} else{
				head = next;
			}
			next->xord_address = XORAddresses(XORAddresses(next->xord_address, current), prev);
			deleteNode(current);
			return 1;
		}
		prev = current;
		current = next;
	}
	return 0;
}

void print_list(){
	//https://stackoverflow.com/questions/4372976/c-print-linked-list-of-strings
	//All functions that loop through the list are based on the pseudocode from the link above.
	Node *current = head;
	Node *next;
	Node *prev = NULL;
	while (current != NULL){
		next = XORAddresses(current->xord_address, prev);
		printf("%s\n", current->item);
		prev = current;
		current = next;
	}
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

	ret = remove_after("Charlie",result);
	if(ret){
		printf("Removed 1: %s\n", result);
	}

	ret = remove_before("Echo", result);
	if(ret){
		printf("Removed 2: %s\n", result);
	}

	ret = remove_string(result);
	if(ret){
		printf("Removed 3: %s\n", result);
	}
	print_list();
}
