#include "uba.h"
#include <stdio.h>
int main(){
    uba_t test = uba_new(3);
    uba_set(test, 0, "a");
    uba_set(test, 1, "b");
    uba_set(test, 2, "c");
    uba_add(test, "h");
    uba_add(test, "i");
    uba_add(test, "m");
    uba_rem(test);
    
    printf("%c is the first char, size: %ld\n",
            *uba_get(test, 0),
            uba_len(test));

    uba_print(test);

    uba_free(test);
    return 0;
}
