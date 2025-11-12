// Exercise 1 ====================================================================
//in stack.c
// Exercise 2 ====================================================================
// in use_stack.c
// Exercise 3 ====================================================================
// in use_stack.c
// Exercise 4 ====================================================================
// in use_stack.c
// Exercise 5 ====================================================================
// in use_stack.c
// Exercise 6 ====================================================================
// in use_stack.c
// Exercise 7 ====================================================================
// debug this function

#include "course_material/lib/xalloc.h"
#include "stack.h"
int main() {
    int* elem1 = xmalloc(sizeof(int)); // Create some elements
    *elem1 = 1;
    int* elem2 = xmalloc(sizeof(int));
    *elem2 = 2;
    int* elem3 = xmalloc(sizeof(int));
    *elem3 = 3;

    stack_t S = stack_new(); // Create a stack
    push(S, (void*)elem1);
    push(S, (void*)elem2);

    stack_t S_copy = stack_copy(S); // Make a copy
                                    
                          
    int* x = pop(S_copy);
    printf("%d\n", *x);
    free(x);

    push(S_copy, (void*)elem3);

    stack_free(S_copy, &free); // free the copy
    stack_free(S, NULL); // free the stack
                               
    printf("All tests passed!\n");
    return 0;
}


