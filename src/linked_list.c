#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	void* data;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
} LinkedList;

LinkedList* init_linkedList() {
	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
	if (list == NULL) {
		fprintf(stderr, "Memory allocation failed list\n");
		exit(EXIT_FAILURE);
	}
	list->head = NULL;
	return list;
}

void free_linkedList(LinkedList* list) {
	Node* current = list->head;
	while (current != NULL) {
		Node* tmp = current;
		current = current->next;
		free(tmp->data);
		free(tmp);
	}
	free(list);
}

void add_linkedList(LinkedList* list, void* value) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (list == NULL) {
		fprintf(stderr, "Memory allocation failed node\n");
		exit(EXIT_FAILURE);
	}
	
	node->data = value;
	node->next = list->head;
	list->head = node;
}

void remove_linkedList(LinkedList* list, int index) {
	Node* current = list->head;
	Node* prev = NULL;
	int current_index = 0;

	while (current != NULL) {
		if (current_index == index) {
			if (prev == NULL) {
				list->head = current->next;
			} else {
				prev->next = current->next;
			}

			free(current);
			return;
		}

		prev = current;
		current = current->next;
		current_index++;
	}
}

int len_linkedList(LinkedList* list) {
	const Node* current = 0;
	int index = 0;

	while (current != NULL) {
		index++;
		current = current->next;
	}

	return index;
}

void* get_linkedList(LinkedList* list, int index) {
	const Node* current = 0;
	int current_index = 0;

	while (current != NULL) {
		if (index == current_index) { break;}


		current_index++;
		current = current->next;
	}

	return current->data;
}

