#include <iostream>
#include "stack.h"

using namespace std;

void showstack (node *stack)
{
        cout << "Top: ";
        for ( ; stack != NULL; stack = stack->next) {
                cout << stack->data << ' ';
                }
        cout << endl;
}

void push (int val, node *&stack)
{
        node *p = new node;
        p->data = val;
        p->next = stack;
        stack = p;
}

int pop (node *&stack)
{
        node *t = stack;
        int val = stack->data;
        stack = stack->next;
        delete t;
        return val;
}


