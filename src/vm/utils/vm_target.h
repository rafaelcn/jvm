#ifndef VM_TARGET_H
#define VM_TARGET_H

#include <stdint.h>

/**
 * @brief Returns the JVM execution target given a major class number.
 */
const char* vm_target(uint16_t compile_version);

#endif /* VM_TARGET_H */