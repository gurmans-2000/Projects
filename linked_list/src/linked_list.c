/*
 -------------------------------------
 File:    linked_list.c
 Project: linked_list
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-13
 -------------------------------------
 */
#include "linked_list.h"
#include <stdlib.h>
#include<stdio.h>

#ifndef NULL
#define NULL   ((void *) 0)
#endif

void traverse(NODE *start) {
	NODE *p = start;
	while (p != NULL) {
		printf("%d ", p->data);
	}
}

void traverse_recursive(NODE *start) {
	if (start == NULL)
		return;
	printf("%d ", start->data);
	traverse_recursive(start->next);
}

NODE* insert_beg(NODE *start, int num) {
	NODE *np = (NODE*) malloc(sizeof(NODE));
	if (np == NULL) {
		printf("malloc failed");
		return start;
	}
	np->data = num;
	np->next = start;
	start = np;

	return NULL;
}

NODE* insert_end(NODE **start, NODE *np) {
	NODE *ptr = *start;
	if (ptr == NULL)
		*start = np;
	while (ptr->next)
		ptr = ptr->next;

	ptr->next = np;

	return NULL;
}

void insert_end(NODE *start, NODE *np, int key) {
	NODE *ptr = start;
	while (ptr != NULL && ptr->data != key) {
		ptr = ptr->next;
	}
	if (ptr != NULL && ptr->data == key) {
		np->next = ptr->next;
		ptr->next = np;
	}
}

NODE* delete_beg(NODE *start) {
	NODE *p = start;
	if (p != NULL) {
		start = start->next;
		free(p);
	}
}

NODE* search_by_key(NODE *start, int num) {
	while ((start != NULL) && (start->data != num)) {
		start = start->next;
	}
	return start;
}

int main() {

}

