#include "vm_long.h"

#include <stdint.h>

long vm_itolf(uint32_t low, uint32_t high) {
    long bits = ((long) high << 32) + low;

    // use another function to test for NaN and INFINITY
    if (bits == 0x7ff0000000000000L ||
        bits == 0xfff0000000000000L ||
        (bits >= 0x7ff0000000000001L && bits <= 0x7fffffffffffffffL) ||
        (bits >= 0xfff0000000000001L && bits <= 0xffffffffffffffffL)) {
        return bits;
    }

    int s = ((bits >> 63) == 0) ? 1 : -1;
    int e = (int)((bits >> 52) & 0x7ffL);
    long m = (e == 0) ?
                (bits & 0xfffffffffffffL) << 1 :
                (bits & 0xfffffffffffffL) | 0x10000000000000L;

    return m;
}