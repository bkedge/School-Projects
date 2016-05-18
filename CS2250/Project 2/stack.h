
#ifndef STACK_H
#define STACK_H

struct node
{
	int data;

	node *next;
};



void showstack(node *stack);

void push(int val, node *&stack);

int pop(node *&stack);


#endif