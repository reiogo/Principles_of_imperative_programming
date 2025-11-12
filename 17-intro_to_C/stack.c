#include "stack.h"
#include "course_material/lib/contracts.h"
#include "course_material/lib/xalloc.h"
#include <stdbool.h>
#include <stdlib.h>
                         
/************************* BEGIN IMPLEMENTATION *************************/
typedef struct slist_node slist;
struct slist_node { // structure of linked lists
    stackelem data;
    slist* next;
};

typedef struct stack_header stack;
struct stack_header { // Stacks
    slist* top;
    slist* bottom;
};

bool stack_empty(stack* S)
//@requires S != NULL;
{
    REQUIRES(S != NULL);

    return S->top == S->bottom;
}

stack* stack_new()
//@ensures \result != NULL;
//@ensures stack_empty(\result);
{
    stack* S = xmalloc(sizeof(stack));
    slist* p = xmalloc(sizeof(slist));
    S->top = p;
    S->bottom = p;

    ENSURES(S != NULL);
    ENSURES(stack_empty(S));
    return S;
}

void push(stack* S, stackelem e)
//@requires S != NULL;
//@ensures !stack_empty(S);
{
    REQUIRES(S != NULL);

    slist* p = xmalloc(sizeof(slist));
    p->data = e;
    p->next = S->top;
    S->top = p;

    ENSURES(!stack_empty(S));
}

stackelem pop(stack* S)
//@requires S != NULL;
//@requires !stack_empty(S);
{
    REQUIRES(S != NULL);
    REQUIRES(!stack_empty(S));

    stackelem e = S->top->data;
    slist* copy = S->top;
    S->top = S->top->next;
    free(copy);
    return e;
}

void free_slist(slist *start, slist *end, free_elem* f){
    REQUIRES(start != NULL && end != NULL);
    slist *node = start;
    while(node != end) {
        if (f != NULL) (*f)(node->data);
        slist * copy = node;
        node = node->next;
        free(copy);
    }
}

void stack_free(stack* S, free_elem* f) {
    REQUIRES(S != NULL);
    free_slist(S->top, S->bottom, f); // free segment
    free(S->bottom); // free dummy node
    free(S); // free stack
}

stack* stack_copy(stack* S){
    REQUIRES(S != NULL);
    stack* copy = stack_new();
    stack* tmp = stack_new();

    while(!stack_empty(S)){
        push(tmp, pop(S));
    }

    while(!stack_empty(tmp)){
        stackelem p = pop(tmp);

        push(S, p);
        push(copy, p);
    }

    stack_free(tmp, NULL);
    ENSURES(S != NULL);
    ENSURES(copy != NULL);
    return copy;
}

/************************** END IMPLEMENTATION **************************/
/************************************************************************/
/************************************************************************/
