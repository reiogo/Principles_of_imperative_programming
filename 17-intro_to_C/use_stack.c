#include <stdio.h>
#include "stack.h"
#include "course_material/lib/xalloc.h"
#include "course_material/lib/contracts.h"

int main() {
    // Create a stack of ints
    stack_t S = stack_new();
    int* elem1 = xmalloc(sizeof(int));
    *elem1 = 1;
    push(S, (void*)elem1);
    int* elem2 = xmalloc(sizeof(int));
    *elem2 = 2;
    push(S, (void*)elem2);
    int* elem3 = xmalloc(sizeof(int));
    *elem3 = 3;
    push(S, (void*)elem3);
    int i = 3;
    ASSERT(1 <= i && i <= 3);
    while (i > 1)
        //@loop_invariant 1 <= i && i <= 3;
    {
        int* elem = (int*)pop(S);
        assert(*elem == i);
        i--;
        ASSERT(1 <= i && i <= 3);
        free(elem);
    }
    stack_t copy = stack_copy(S);

    int* copy_popped = (int*)pop(copy);

    assert(*copy_popped == 5);

    printf("%d\n", *(int*)pop(S));
    free(copy_popped);

    stack_free(S, &free);
    stack_free(copy, &free);

    printf("All tests passed!\n");
    return 0;
}
