#ifndef VM_UTF8_H
#define VM_UTF8_H

#include <stdint.h>

typedef struct vm_utf8_t {
    uint16_t length;
    uint8_t *bytes;
} vm_utf8_t;

typedef struct vm_uint16_string {
    uint16_t length;
    uint16_t *string;
} vm_uint16_string_t;

vm_uint16_string_t * vm_utf8_to_uint16_t(uint16_t length, uint8_t *bytes);

#endif /* VM_UTF8_H */
