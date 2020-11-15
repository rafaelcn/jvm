#include "vm_long.h"

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "../../vm_settings.h"

long vm_itol(uint32_t low, uint32_t high) {
    long bits = ((long) high << 32) + low;

    return bits;
}
