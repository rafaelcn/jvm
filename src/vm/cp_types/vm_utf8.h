#ifndef VM_UTF8_H
#define VM_UTF8_H

#include <stdint.h>

#include "../vm_constant_pool.h"

typedef struct vm_utf8_t {
    uint16_t length;
    uint8_t *bytes;
} vm_utf8_t;

uint16_t * utf8_to_uint16_t(vm_class_file_t *cf, uint16_t table_index);

#endif /* VM_UTF8_H */