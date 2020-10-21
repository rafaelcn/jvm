#include "vm_double.h"

#include <math.h>

double vm_itod(uint32_t low, uint32_t high) {
    return vm_itolf(low, high);
}