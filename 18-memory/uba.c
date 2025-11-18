/************************************************************************/
/************************* BEGIN IMPLEMENTATION *************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "course_material/lib/xalloc.h"
#include "course_material/lib/contracts.h"
#include "uba.h"

typedef struct uba_header uba;
struct uba_header {
    size_t size; // 0 <= size && size < limit
    size_t limit; // 0 < limit, NUL not included
    char** data; // \length(data) == limit
};

// Internal debugging function that prints an UBA without checking contracts
// (useful to debug representation invariant issues)
void uba_print_unsafe(uba* A)
{
    printf("UBA limit=%d; length=%d; data=[", A->limit, A->size);
    for (size_t i = 0; i < A->limit; i++)
    //@loop_invariant 0 <= i && i <= A->limit;
    {
        ASSERT(0 <= i && i <= A->limit);
        if (i < A->size)
            printf("%s", A->data[i]);
        else
            printf("X");
        if (i < A->limit-1) {
            if (i == A->size-1) printf(" | ");
            else printf(", ");
        }
        ASSERT(0 <= i && i <= A->limit);
    }
    printf("]");
}

bool is_uba(uba* A) {
    return A != NULL
        && 0 <= A->size && A->size < A->limit;
}
// Internal debugging function that prints an SSA
// (useful to spot bugs that do not invalidate the representation invariant)
void uba_print_internal(uba* A){
    REQUIRES(is_uba(A));
    uba_print_unsafe(A);
}

// Implementation of exported functions
size_t uba_len(uba* A){
    REQUIRES(is_uba(A));
    return A->size;
    }
    
char* uba_get(uba* A, size_t i){
    REQUIRES(is_uba(A));
    REQUIRES(0 <= i && i < uba_len(A));
    return A->data[i];
}

void uba_set(uba* A, size_t i, char* x)
{
    REQUIRES(is_uba(A));
    REQUIRES(0 <= i && i < uba_len(A));
    ENSURES(is_uba(A));
    A->data[i] = x;
    uba_print_unsafe(A);
}

uba* uba_new(size_t size){
    REQUIRES(0 <= size);
    uba* A = xmalloc(sizeof(uba));
    size_t limit = size == 0 ? 1 : size*2;
    A->data = xmalloc(sizeof(char)*limit);
    A->size = size;
    A->limit = limit;

    ENSURES(is_uba(A));
    ENSURES(uba_len(A) == size);
    return A;
}

void uba_resize(uba* A, size_t new_limit)
    /* A may not be a valid array since A->size == A->limit is possible! */
{
    REQUIRES(A != NULL);
    REQUIRES(0 <= A->size && A->size < new_limit);
    char** B =(char**)xmalloc(sizeof(char*)*new_limit);
    B[new_limit] = '\0';
    for (size_t i = 0; i < A->size; i++)
        //@loop_invariant 0 <= i;
    {
        B[i] = A->data[i];
        ASSERT(0 <= i);
    }
    A->limit = new_limit;
    free(A->data);
    A->data = B;
    ENSURES(is_uba(A));
}

void uba_add(uba* A, char* x){
    REQUIRES(is_uba(A));
    A->data[A->size] = x;
    (A->size)++;
    if (A->size < A->limit) return;
    assert(A->limit <= SIZE_MAX / 2); // Fail if array would get too big
    uba_resize(A, A->limit * 2);
    ENSURES(is_uba(A));
}

char* uba_rem(uba* A){
    REQUIRES(is_uba(A));
    REQUIRES(0 < uba_len(A));
    (A->size)--;
    char *x = A->data[A->size];
    if (A->limit >= 4 && A->size <= A->limit / 4)
        uba_resize(A, A->limit / 2);

    ENSURES(is_uba(A));
    return x;
}

void uba_print(uba* A)
{
    REQUIRES(is_uba(A));
    printf("[");
    for (size_t i = 0; i < A->size; i++)
    {
        printf("%s", A->data[i]);
        if (i+1 != A->size) printf(", ");
    }
    printf("]");
}

void uba_free(uba* A) {
    free(A->data);
    free(A);
}
/************************** END IMPLEMENTATION **************************/
/************************************************************************/
