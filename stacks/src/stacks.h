/*
 -------------------------------------
 File:    stacks.h
 Project: stacks
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-04-14
 -------------------------------------
 */

#ifndef STACK_H
#define STACK_H

#include "common.h"
#include <stdlib.h>

typedef struct stack {
	NODE *top;
} STACK;
void push(STACK *sp, NODE *np);
NODE* pop(STACK *sp);
void clean_stack(STACK *sp);

#endif
