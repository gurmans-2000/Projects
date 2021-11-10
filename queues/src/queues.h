/*
 -------------------------------------
 File:    queues.h
 Project: queues
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-13
 -------------------------------------
 */

typedef struct queue {
	int data;
	NODE *front;
	NODE *rear;
} QUEUE;
void enqueue(QUEUE *qp, NODE *np);
NODE* dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);
