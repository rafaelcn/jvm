#ifndef VM_CHECKS_H
#define VM_CHECKS_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Check if the pointer passed is different than null.
 * @param p A pointer to any object.
 * @returns  An integer representing whether or not the pointer passed is
 * different than NULL, that is true if different than NULL and false otherwise.
 */
int vm_valid_pointer(void *p);


#endif /* VM_CHECK */