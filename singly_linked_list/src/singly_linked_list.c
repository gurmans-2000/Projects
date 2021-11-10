/*
 -------------------------------------
 File:    singly_linked_list.c
 Project: final_questions
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-12
 -------------------------------------
 */

#include "singly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#ifndef NULL
#define NULL   ((void *) 0)
#endif

NODE* new_node(int val) {
	NODE *np = (NODE*) malloc(sizeof(NODE));
	if (np == NULL) {
		printf("malloc fails");
		return NULL;
	}
	np->data = val;
	np->next = NULL;
	return np;
}
int length(NODE *start) {
	int counter = 0;
	NODE *ptr = start;
	while (ptr != NULL) {
		counter++;
		ptr = ptr->next;
	}
	return counter;
}
NODE* get_node_at(NODE *start, int i) {
	if (start == NULL || i < 0)
		return NULL;
	int counter = 0;
	NODE *ptr = start;
	while (ptr != NULL) {
		if (counter == i)
			return ptr;
		counter++;
		ptr = ptr->next;
	}
	return NULL;
}

void display(NODE *start) {
	if (start == NULL)
		return;
	NODE *ptr = start;
	while (ptr != NULL) {
		printf("%d ", ptr->data);
		ptr = ptr->next;
	}
}

int node_count(NODE *start) {
	int counter = 0;

	NODE *ptr = start;
	while (ptr != NULL) {
		counter++;
		ptr = ptr->next;
	}
	return counter;
}

void display_recursive(NODE *start) {
	if (start == NULL)
		return;
	printf("%d ", start->data);
	display_recursive(start->next);
}

void display_backward_recursive(NODE *start) {
	if (start == NULL)
		return;
	display_backward_recurisve(start->next);
	printf("%d ", start->data);
}
void display_backward(NODE *end) {
	if (end == NULL)
		return;
	NODE *ptr = end;
	while (ptr != NULL) {
		printf("%d ", ptr->data);
		ptr = ptr->prev;
	}
	void display_forward(NODE *start) {
		if (start == NULL)
			return;
		NODE *ptr = start;
		while (ptr != NULL) {
			printf("%d ", ptr->data);
			ptr = ptr->next;
		}
	}
	NODE* search(NODE *start, int num) {
		while (start != NULL) {
			if (start->data == num)
				return start;
			start = start->next;
		}
		return NULL;
	}

	NODE* insert_beg(NODE *start, int num) {
		NODE *np = (NODE*) malloc(sizeof(NODE));
		if (np == NULL) {
			printf("malloc fails");
			return start;
		}
		np->data = num;
		np->next = start;
		start = np;
		return start;
	}
	void insert_beg(NODE **startp, NODE *new_node) {
		new_node->next = *startp;
		*startp = new_node;
	}
	NODE* insert_beg(NODE *start, int num) {
		NODE *np = (NODE*) malloc(sizeof(NODE));
		if (np == NULL) {
			printf("malloc fails");
			return start;
		}
		np->data = num;
		np->next = start;
		start = np;
		return start;
	}
	NODE* insert_beg(NODE *start, NODE *new_node) {
		new_node->next = start;
		start = new_node;
		return start;
	}
	void insert_beg(NODE **startp, int num) {
		NODE *np = (NODE*) malloc(NODE);
		if (np == NULL) {
			printf("malloc fails");
			return;
		}
		np->data = num;
		np->next = *startp;
		*startp = np;
	}

	void insert_end(NODE **startp, NODE *new_node) {
		NODE *ptr = *startp;
		if (ptr == NULL)
			*startp = new_node;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_node;
	}

	void insert_after(NODE **startp, NODE *np, int key) {
		NODE *ptr = *startp;
		while (ptr != NULL && ptr->data != key) {
			ptr = ptr->next;
		}
		if (ptr != NULL && ptr->data == key) {
			new_node = ptr->next;
			ptr->next = new_node;
		}
	}

	void delete_after(NODE **startp, int value) {
		NODE *ptr = *startp;
		NODE *pre_ptr = NULL;
		while (ptr != NULL && ptr->data != value) {
			pre_ptr = ptr;
			ptr = ptr->next;
		}
		if (ptr->data == value && pre_ptr == NULL) {
			*startp = NULL;
			free(ptr);
		} else if (ptr->data == value && pre_ptr != NULL) {
			pre_ptr->next = ptr->next;
			free(ptr);
		}
	}

	void delete_beg(NODE **startp) {
		NODE *ptr = *startp;
		if (ptr != NULL) {
			*startp = ptr->next;  // this set start point to the second node
			free(ptr); // this frees the memory block of the deleted node
		}
	}

	void display_backward(NODE *end) {
		if (end == NULL)
			return;
		NODE *ptr = end;
		while (ptr != NULL) {
			printf("%d ", ptr->data);
			ptr = ptr->prev;
		}
	}

//FUNCTIONS FOR REVERSE LINKED LIST
	void reverse(NODE **head_ref) {
		NODE *prev = NULL;
		NODE *current = *head_ref;
		NODE *next = NULL;
		while (current != NULL) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		*head_ref = prev;
	}

	void push(NODE **head_ref, int new_data) {
		NODE *new_node = (NODE*) malloc(sizeof(NODE));
		new_node->data = new_data;
		new_node->next = (*head_ref);
		(*head_ref) = new_node;
	}

	void printList(NODE *head) {
		NODE *temp = head;
		while (temp != NULL) {
			printf("%d  ", temp->data);
			temp = temp->next;
		}
	}

	int main() {
		NODE *head = NULL;

		push(&head, 20);
		push(&head, 4);
		push(&head, 15);
		push(&head, 85);

		printf("Given linked list\n");
		printList(head);
		reverse(&head);
		printf("\nReversed Linked list \n");
		printList(head);

		return 0;
	}

