#include <math.h>

#include "vm_double.h"

double vm_itod(uint32_t low, uint32_t high) {
    long bits = ((long) high << 32) + low;

    double result;

    // use another function to test for NaN and INFINITY
    if (bits == 0x7ff0000000000000L) {
        result = INFINITY;
    } else if (bits == 0xfff0000000000000L) {
        result = -INFINITY;
    } else if ((bits >= 0x7ff0000000000001L && bits <= 0x7fffffffffffffffL) || (bits >= 0xfff0000000000001L && bits <= 0xffffffffffffffffL)) {
        result = NAN;
    } else {
        int s = ((bits >> 63) == 0) ? 1 : -1;
        int e = (int) ((bits >> 52) & 0x7ffL);
        long m = (e == 0) ? (bits & 0xfffffffffffffL) << 1 : (bits & 0xfffffffffffffL) | 0x10000000000000L;

        result = s * m * pow(2, (e-1075));
    }

    return result;
}
