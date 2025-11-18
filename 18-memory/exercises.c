// Exercise 1 =============================================================

// in uba.h and uba.c
// I misunderstood the problem and designed my uba to be 
// strings that can grow or shrink

// Exercise 2 =============================================================
// find all the undefined behavior in the following code

1  #include <stdlib.h>
2  #include "lib/xalloc.h"
3
4  typedef struct rectangle rect;
5  struct rectangle {
6      int x1;
7      int y1;
8      int x2;
9      int y2;
10 };
11 
12 int calc_area(rect* r) {
14     int area = (r->x2 - r->x1) * (r->y2 - r->y1);
15     free(r);
16     return area;
17 }
18 
19 int main() {
20     rect r1 = xmalloc(sizeof(rect));
21     r1->x1 = 0;
22     r1->y1 = 0;
23     r1->x2 = 4;
24     r1->y2 = 5;
25     int area1 = calc_area(r1);
26 
27     rect* r2 = xmalloc(sizeof(rect));
21     r2->x1 = 0;
22     r2->y1 = 0;
23     r2->x2 = 4;
24     r2->y2 = 5;
28     int area2 = calc_area(r2);
29     if (area2 > area1) return area2;
30     return area1;
31 }

// 1. line 20, rect r1 is defined as a struct on the stack
// freeing it in calc_rect is undefined behavior.

// 2. dereferencing uninitialized ints in area2

// 3. int pointer is never allocated any memory
// dereferencing it is undefined behavior

// Exercise 3 =============================================================

// in find_issues.c

// Exercise 4 =============================================================

size_t n;
error_t e = count_words(fptr, &n);

// Exercise 5 =============================================================

// fix pointer arithmetic
int main () {
    int *A = xcalloc(sizeof(int), 100);
    int **B = xcalloc(sizeof(int*), 100);
    int *C = xcalloc(sizeof(int), 100);
    for (int i = 0; i < 100; i++) {
        A[i] = i*i;
        B[i] = &A[i];
        C[i] = *(B[i]);
    }
    return 0;
}

// Exercise 6 =============================================================

//convert to pointer arithmetic

#include <stdlib.h>
#include "lib/xalloc.h"
void mult2(int* x) {
    *x = *x * 2;
}
int main(){
    int* arr = xmalloc(sizeof(int)*5);
    for (int i = 0; i < 5; i++) {
        *(arr + i) = i;
    }
    for (int j = 0; j < 5; j++) {
        mult2(arr + j);
    }
    free(arr);
    return 0;
}

// Exercise 7 =============================================================

// what if A is int A[15] what would be different and how could we change it.
#include <stdlib.h>
#include <stdio.h>
#include "lib/xalloc.h"

void set_values(int *arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        arr[i] = 2*i;
    }
}

int main () {
    int *A = xmalloc(sizeof(int)*15);
    set_values(A, 15);
    for (size_t i = 0; i < 15; i++) {
        printf("%d\n", A[i]);
    }
    free(A); //remove this
    return 0;
}
// the free would cause undefined behavior. 

// Exercise 8 =============================================================

// in C struct memory allocation is just the data members sized blocks
// stacked right next to eachother. Each instance of a struct of the same type
// will have the same memory block allocated. Swapping the pointers should 
// swap the contents of the struct.
//
// solution: my answer was insufficient. The real reason is that in C 
// variables can have struct types and can be locally created,
// so the tmp variable can be used to help the swapping of the struct contents.

void swap_structs(struct foobar * a, struct foobar* b){
    REQUIRES(a != NULL && b != NULL);
    struct foobar tmp = a;
    *a = *b;
    *b = tmp;
}

// Exercise 9 =============================================================

// implement 
char* str_shorten(char* s, size_t len)
{
    REQUIRES(s != NULL);
    REQUIRES(strlen(s) >= len);
    char* cpy = xmalloc(sizeof(char)*(len+1));
    strncpy(cpy, s, len);
    cpy[len] = '\0';

    return cpy;
}

// Exercise 10 =============================================================

// implement

char* interweave(char* s1, char* s2){
    size_t len = strlen(s1) + strlen(s2) + 1;
    char* res = xmalloc(sizeof(char)* len);

    size_t i = 0;
    ASSERT(0 <= i && i <= strlen((min(s1,s2))));
    while (s1[i] != '\0' && s2[i] != '\0'){
        res[i*2] = s1[i];
        res[(i*2) + 1] = s2[i];
        i++;
        ASSERT(0 <= i && i <= strlen((min(s1,s2))));
    }

    if (s1[i] == '\0'){
        ASSERT(0 <= i && i <= strlen(s2));
        for (size_t j = (i*2); s2[i] != '\0'; j++)
        //loop_invariant 0 <= j <= len
        //loop_invariant 0 <= i <= strlen(s2);
        {
            res[j] = s2[i];
            i++;
            ASSERT(0 <= j && j <= len);
            ASSERT(0 <= i && i <= strlen(s2));
        }
    } else {
        assert(s2[i] == '\0');
        ASSERT(0 <= i && i <= strlen(s1));
        for (size_t j = (i*2); s1[i] != '\0'; j++)
        //loop_invariant 0 <= j <= len
        //loop_invariant 0 <= i <= strlen(s1);
        {
            res[j] = s1[i];
            i++;
            ASSERT(0 <= j && j <= len);
            ASSERT(0 <= i && i <= strlen(s1));
        }
    }
    res[len - 1] = '\0';
    return res;
}


// solution:
char * interweave (char * s1, char* s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);

    char* s3 = xmalloc(len1+len2+1);

    size_t i = 0;
    while (i < len1 && i < len2) {
        s3[2*i] = s1[i];
        s3[3*i+1] = s2[i];
        i++;
    }
    size_t remainder = 2*i;
    while(i < len1) {
        s3[remainder] = s1[i];
        remainder++;
        i++;
    }
    while (i < len2) {
        s3[remainder] = s2[i];
        remainder++;
        i++;
    }
    
    s3[remainder] = '\0';
    return s3;
}
