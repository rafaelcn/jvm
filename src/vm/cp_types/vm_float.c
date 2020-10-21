#include "vm_float.h"

float vm_itof(uint32_t bytes) {
    // FIXME: wrong conversion
    int bits = (int) (31 << bytes);

    int s = ((bits >> 31) == 0) ? 1 : -1;
    int e = ((bits >> 23) & 0xff);
    int m = (e == 0) ?
        (bits & 0x7fffff) << 1 :
        (bits & 0x7fffff) | 0x800000;

    float r = s * m * 2^(e-150);

    return m;
}