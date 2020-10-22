#include "vm_double.h"

double vm_itod(uint32_t low, uint32_t high) {
    return (double)vm_itolf(low, high);
}