#include <stdio.h>
#include <stdlib.h>

#include "vm_opcodes.h"

#define istore (0x036)

uint32_t vm_opcodes(uint8_t *code, uint32_t pc, vm_stack_t *STACK) {
    switch (code[pc]) {
    case istore:
        break;

    default:
        break;
    }

    return pc;
}
