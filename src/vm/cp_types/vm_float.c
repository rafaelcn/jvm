#include "vm_float.h"

#include <math.h>

float vm_itof(uint32_t bytes) {
    const int bits = (int)bytes;

    int s = ((bits >> 31) == 0) ? 1 : -1;
    int e = ((bits >> 23) & 0xff);
    int m = (e == 0) ?
        (bits & 0x7fffff) << 1 :
        (bits & 0x7fffff) | 0x800000;

    //printf("  | s = %d, e = %d, m = %d | ", s, e, m);

    float r = s * m * pow(2, (e-150));

    return r;
}