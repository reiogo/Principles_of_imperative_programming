#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef void* stackelem; // Element type
typedef void free_elem(stackelem s);  // Free function
                         
typedef struct stack_header* stack_t;

bool stack_empty(stack_t S) /* O(1) */
/*@requires S != NULL; @*/ ;

stack_t stack_new() /* O(1) */
/*@ensures \result != NULL; @*/
/*@ensures stack_empty(\result); @*/ ;

void push(stack_t S, stackelem x) /* O(1) */
/*@requires S != NULL; @*/
/*@ensures !stack_empty(S); @*/ ;

stackelem pop(stack_t S) /* O(1) */
/*@requires S != NULL; @*/
/*@requires !stack_empty(S); @*/ ;

void stack_free(stack_t S, free_elem* f); // O(n)
//@requires S != NULL;

stack_t stack_copy(stack_t S)
//@requires S != NULL;
;

#endif
