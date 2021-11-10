/*
 -------------------------------------
 File:    linked_list_stack.c
 Project: linked_list_stacks
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-14
 -------------------------------------
 */

void push(STACK *sp, int value) {
	NODE *np = np(value);
	if (sp->top == NULL) {
		sp->top = np;
	}
	np->next = top;
	sp->top = np;
}

NODE* pop(STACK *sp) {
	if (sp->top == NULL)
		return NULL;
	NODE *ptr = sp->top;
	sp->top = sp->top->next;
	free(ptr);

	return NULL;
}

NODE* peek(STACK *sp) {
	if (sp->top == NULL)
		return NULL;

	return sp->top->data;
}
