#include <stdlib.h>
#include <stdio.h>
#include "course_material/lib/xalloc.h"

// valgrind is telling me that the second loop is accessing uninitialized values 
// in arr. 30*2+1 is the last element of the array accessed by the first 
// loop, so the second loops last access is invalid

// arr is not freed
struct point {
    int x;
    int y;
};

int main () {
    int len = 63;
    struct point **arr = xmalloc(sizeof(struct point*) * (len + 1));
    for (int i = 0; i < (len+1)/2; i++) {
        arr[2*i] = xmalloc(sizeof(struct point));
        arr[2*i + 1] = xmalloc(sizeof(struct point));
        arr[2*i]->x = i+1;
        arr[2*i]->y = i+1;
        arr[2*i+1]->x = i/2;
        arr[2*i+1]->y = 5*i+3;
    }

    for (int i = 0; i < len; i++) {
        if (arr[i]->x + 100 < arr[i+1]->y) {
            printf("%s\n", "Small x value");
        }
        free(arr[i]);
    }
    free(arr[len]);
    free(arr);
}
