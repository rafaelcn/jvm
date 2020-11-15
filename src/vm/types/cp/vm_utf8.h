#ifndef VM_UTF8_H
#define VM_UTF8_H

#include <stdint.h>

/**
 * @brief Describes the structure of a string inside the constant pool code.
 */
typedef struct vm_utf8_t {
    uint16_t length;
    uint8_t *bytes;
} vm_utf8_t;

/**
 * @brief Describes a UTF8 string after the decode process.
 */
typedef struct vm_uint32_string {
    uint16_t length;
    uint32_t *string;
} vm_uint32_string_t;

/**
 * @brief Decodes an UTF8 string into an array of uint32_t.
 * @param length The size of the encoded string.
 * @param bytes An array of all bytes retrieved from the constant pool.
 * @returns An array of uint16_t.
 */
vm_uint32_string_t * vm_utf8_to_uint32_t(uint16_t length, uint8_t *bytes);

#endif /* VM_UTF8_H */
