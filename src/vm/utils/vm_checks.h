#ifndef VM_CHECKS_H
#define VM_CHECKS_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Check if the pointer passed is different than null.
 * @param p A pointer to any object.
 * @returns  A bool constant representing whether or not the pointer passed is
 * different than NULL, that is true if different than NULL and false otherwise.
 */
bool vm_valid_pointer(void *p) {
    return (p != NULL);
}


#endif /* VM_CHECK */