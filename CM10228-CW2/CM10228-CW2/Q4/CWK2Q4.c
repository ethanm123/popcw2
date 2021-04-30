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

//Definses the node structure. It holds a string and a pointer to a node.
typedef struct Node {
	char *item;
	struct Node *xord_address;
}Node;

Node *head = NULL; //The head element.
int element_count = 0; //The number of elements in the linked list.

//XORs 2 Node pointers and returns the result.
Node* XORAddresses(Node *address1, Node *address2) {
	//Learnt to XOR pointers from: https://stackoverflow.com/questions/26569728/using-xor-with-pointers-in-c
	return (Node*) ((uintptr_t) (address1) ^ (uintptr_t) (address2));
}

//Makes sure the string is not greater than 64 characters (bytes) in length.
int checkStringLength(const char *newString) {
	if (strlen(newString) + 1 > 64) {
		return 0;
	}
	return 1;
}

//Allocates memory for, and creates a node. Returns a pointer to this node.
Node* makeNode(const char *newString) {
	//Allocate memory to store the node's item.
	char *string_to_insert = (char *) malloc(strlen(newString) * (sizeof(char)) + 1);
	if (string_to_insert == NULL) { //Check if malloc returns a null pointer.
		printf("Error allocating memory for string.");
		exit(0);
	} else { //If the pointer is fine then copy the string provided into this new memory slot.
		strcpy(string_to_insert, newString);
	}
	Node *thisNode = (Node *) malloc(sizeof(Node)); //Allocate memory for the node.
	if (thisNode == NULL) { //Check if malloc returns a null pointer.
		printf("Error allocating memory for node.");
		exit(0);
	} else {
		thisNode->item = string_to_insert; //Sets the node's item to the string made earlier.
		element_count++; //Increments element_counnt.
	}
	return thisNode;
}

//Deletes a node. Frees all the memory this node used.
void deleteNode(Node *nodeToDelete) {
	free(nodeToDelete->item);
	free(nodeToDelete);
	element_count--;
	//Decrements the element count.
	if (element_count == 0) { //If there are no elements left, set head to null.
		head = NULL;
	}
}

//Adds a node to the start of the linked list.
void insert_string(const char* newObj) {
	if (checkStringLength(newObj) == 0) { //Makes sure that the string isn't too long.
		return;
	}
	Node *thisNode = makeNode(newObj); //Makes a new node with this string.
	if (head != NULL) { //If this isn't the first element in the list, update the current head's pointer.
		head->xord_address = XORAddresses(thisNode, head->xord_address);
	}
	thisNode->xord_address = head; //Update new node's XOR pointer to point to the old head.
	head = thisNode; //Change head to this new node that is at the start of the list.
}

//Inserts a node before the given string.
int insert_before(const char* before, const char* newObj) {
	Node *current = head; //Allocates the pointers used to loop through the list.
	Node *prev = NULL;
	Node *next;
	while (current != NULL && checkStringLength(newObj) == 1) {
		next = XORAddresses(current->xord_address, prev);
		if (prev == NULL && strcmp(current->item, before) == 0) {
			//If we are trying to insert into the head, just call the function that already does this, return success. 
			insert_string(newObj);
			return 1;
		}
		if (next != NULL && strcmp(before, next->item) == 0) {
			//If the string to insert before is found, make a new node to insert.
			Node *thisNode = makeNode(newObj);
			thisNode->xord_address = XORAddresses(current, next); //Set the new node's XORd address to the XOR of the current node and next node.
			next->xord_address = XORAddresses(XORAddresses(current, next->xord_address), thisNode); //Updates the next node's XORd address.
			current->xord_address = XORAddresses(prev, thisNode); //Updates the current XORd address.
			return 1; //Returns success.
		}
		prev = current;
		current = next;
	}
	return 0; //Couldn't find the string to insert before, return fail.
}

//Insert a new node after a given string.
int insert_after(const char* after, const char* newObj) {
	Node *current = head; //Defining the pointers needed to loop through the list.
	Node *prev = NULL;
	Node *next;
	while (current != NULL && checkStringLength(newObj) == 1) {
		next = XORAddresses(current->xord_address, prev);
		if (prev != NULL && strcmp(after, prev->item) == 0) {
			//If the previous node contains the string to insert after make a new node.
			Node *thisNode = makeNode(newObj);
			thisNode->xord_address = XORAddresses(current, prev); //Update the new node's XORd address.
			prev->xord_address = XORAddresses(XORAddresses(current, prev->xord_address), thisNode); //Updates the previous node's XORd address.
			current->xord_address = XORAddresses(next, thisNode); //Updates the current node's XORd address.
			return 1; //Return success.
		} else if (next == NULL && strcmp(after, current->item) == 0) {
			//Adds an item to the end of the list if the after string is the current last item.
			Node *thisNode = makeNode(newObj);
			thisNode->xord_address = current;
			current->xord_address = XORAddresses(current->xord_address, thisNode);
			return 1;
		}
		prev = current;
		current = next;
	}
	return 0; //Couldn't find the after string so insert failed.
}

//Removes the string at the beginning of the list.
int remove_string(char* result) { //If there is nothing in the list return fail.
	if (head == NULL) {
		return 0;
	}
	if (head->xord_address != NULL) {
		//If the head isn't the only item in the lisr, update the next node's pointers.
		head->xord_address->xord_address = XORAddresses(head->xord_address->xord_address, head);
		Node *temp = head->xord_address;
		strcpy(result, head->item); //Updates the result to store the item from the removed node.
		deleteNode(head);
		head = temp;
		return 1; //Success.
	} else {
		strcpy(result, head->item);
		deleteNode(head); //Just deletes the head as its the last node in the list.
		return 1;
	}
	return 0;
}

//Removes the node that follows a given string.
int remove_after(const char *after, char *result) {
	Node *current = head; //Defines the pointers needed to loop through the list.
	Node *prev = NULL;
	Node *next;
	while (current != NULL) {
		next = XORAddresses(current->xord_address, prev);
		if (prev != NULL && strcmp(prev->item, after) == 0) {
			strcpy(result, current->item); //If the item to remove is found, copy it into result.
			if (prev != NULL) {
				prev->xord_address = XORAddresses(XORAddresses(prev->xord_address, current), next); //Update the pointers.
				if (next != NULL) {
					next->xord_address = XORAddresses(XORAddresses(next->xord_address, current), prev);
				}
				deleteNode(current); //Delete the node.
				return 1; //Return success.
			}
		}
		prev = current;
		current = next;
	}
	return 0; //If it reaches here it has failed so return 0.
}

//Removes the item before the given string.
int remove_before(const char *before, char *result) {
	Node *current = head; //Defines the pointers needed to loop through the list.
	Node *prev = NULL;
	Node *next;
	while (current != NULL) {
		next = XORAddresses(current->xord_address, prev);
		if (next == NULL) { //If the end of the list is reached, return fail.
			return 0;
		}
		if (next != NULL && strcmp(next->item, before) == 0) {
			strcpy(result, current->item); //Result found, copy it into result.
			if (prev != NULL) { //Update the pointers as required.
				prev->xord_address = XORAddresses(XORAddresses(prev->xord_address, current), next);
			} else {
				head = next;
			}
			next->xord_address = XORAddresses(XORAddresses(next->xord_address, current), prev);
			deleteNode(current); //Delete the node.
			return 1; //Return success.
		}
		prev = current;
		current = next;
	}
	return 0;
}

//Loop through the list and print each element.
void print_list() {
	//https://stackoverflow.com/questions/4372976/c-print-linked-list-of-strings
	//All functions that loop through the list are based on the pseudocode from the link above.
	Node *current = head;
	Node *next;
	Node *prev = NULL;
	while (current != NULL) {
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
	insert_after("Alpha", "Golf");
	insert_before("Charlie", "Hotel");
	insert_before("Alpha", "Echo");
	print_list(); // Charlie -> Bravo -> Delta -> Echo -> Alpha

	char result[10];
	int ret;

	ret = remove_after("hi",result);
	if(ret) {
		printf("Removed 1: %s\n", result);
	}

	ret = remove_before("Bravo", result);
	if(ret) {
		printf("Removed 2: %s\n", result);
	}

	ret = remove_string(result);
	if(ret) {
		printf("Removed 3: %s\n", result);
	}
	remove_string(result);
	remove_string(result);
	remove_string(result);
	remove_string(result);
	remove_string(result);
	remove_string(result);
	remove_string(result);
	remove_string(result);
	remove_string(result);
	
	print_list();
}
