/*
 -------------------------------------
 File:    stacks.c
 Project: stacks
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-14
 -------------------------------------
 */
#ifndef NULL
#define NULL   ((void *) 0)
#endif

void push(STACK *sp, NODE *np) {
	if (sp->top == NULL) {
		sp->top = np;
	} else {
		np->next = sp->top;
		sp->top = np;
	}
}

NODE* pop(STACK *sp) {
	if (sp->top == NULL)
		return NULL;
	NODE *np = sp->top;
	sp->top = sp->top->next;
	np->next = NULL;
	return np;
}

void clean(STACK *sp) {
	NODE *curr = sp->top;
	NODE *prev = NULL;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	sp = NULL;

}
