#include "course_material/lib/xalloc.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "simple.h"



int main(){

    struct point2d* P = xmalloc(sizeof(struct point2d));

    P->x = -15;
    P->y = 0;
    P->y = P->y + absval(P->x * 2);
    assert(P->y > P->x && true);
    free(P);
    printf("x coord: %d\n", P->x);

    return 0;
}
