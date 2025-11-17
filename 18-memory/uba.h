#ifndef UBA_H
#define UBA_H

#include <stddef.h>
typedef struct uba_header* uba_t;


// typedef ______* uba_t;
size_t uba_len(uba_t A)
/*@requires A != NULL; @*/
/*@ensures \result >= 0; @*/ ;

uba_t uba_new(size_t size)
/*@requires 0 <= size; @*/
/*@ensures \result != NULL; @*/
/*@ensures uba_len(\result) == size; @*/ ;

char* uba_get(uba_t A, size_t i)
/*@requires A != NULL; @*/
/*@requires 0 <= i && i < uba_len(A); @*/ ;

void uba_set(uba_t A, size_t i, char* x)
/*@requires A != NULL; @*/
/*@requires 0 <= i && i < uba_len(A); @*/ ;

void uba_add(uba_t A, char* x)
/*@requires A != NULL; @*/ ;

char* uba_rem(uba_t A)
/*@requires A != NULL; @*/
/*@requires 0 < uba_len(A); @*/ ;

// bonus function
void uba_print(uba_t A)
/*@requires A != NULL; @*/ ;

void uba_free(uba_t A)
//@requires A != NULL;
;
#endif
