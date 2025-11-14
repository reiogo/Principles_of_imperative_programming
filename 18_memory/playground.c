#include "course_material/lib/xalloc.h"
#include <stdio.h>
int main(){
    int *A = xmalloc(sizeof(int) * 5);
    for(size_t i = 0; i < 5; i++){
        A[i] = i*i*i*i;
    }

    for(int i = 5; i < 10; i++){
        printf("%d\n", A[i]);
    }
    int B[] = {0,1,2,3,4};
    int C[5] = {0,1,2,3,4};

    printf("%d\n", B[4]);
    printf("%d\n", C[3]);
    free(A);

    return 0;
}
