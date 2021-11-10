/*
 -------------------------------------
 File:    queues.c
 Project: queues
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-13
 -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include "queues.h"
#include "common.h"

#ifndef NULL
#define NULL   ((void *) 0)
#endif

void enqueue(QUEUE *qp, NODE *np) {
	if (qp->front == NULL && qp->rear == NULL) {
		qp->front = np;
		qp->rear = np;
	} else {
		qp->rear->next = np;
		qp->rear = np;
	}
}

NODE* dequeue(QUEUE *qp) {
	if (qp->front == NULL && qp->front > qp->rear) {
		printf("UNDERFLOW");
	}
	NODE *np = qp->front;
	qp->front = qp->front->next;
	np->next = NULL;
	return np;
}

void clean_queue(QUEUE *qp) {
// your implementation, call clean(NODE **)
	NODE *curr = qp->front;
	NODE *prev = NULL;
	while (curr != NULL) {
		prev = curr;
		curr->next;
		free(prev);
	}
}
