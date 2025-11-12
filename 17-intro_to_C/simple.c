#include "course_material/lib/contracts.h"
#include <limits.h>
#include "simple.h"

int absval(int x) {
    REQUIRES(x > INT_MIN);
    int res = x < 0 ? -x : x;
    ENSURES(res >= 0);
    return res;
}
