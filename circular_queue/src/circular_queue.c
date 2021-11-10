/*
 -------------------------------------
 File:    circular_queue.c
 Project: circular_queue
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-14
 -------------------------------------
 */

NODE enqueue(NODE *start, NODE *np) {
	if ((start->front == NULL && start->rear = MAX - 1)
			|| (start->rear = start->front - 1)) {
		printf("OVERFLOW");
	}
	if (start->front == -1) {
		start->front = np;
		start->rear = np;
	} else if (start->rear = MAX - 1 && start->fornt != 0) {
		start->rear = np;
	}
}
