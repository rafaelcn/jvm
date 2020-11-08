#include <stdio.h>
#include <stdlib.h>

#include "vm_opcodes.h"

#define istore (0x36)
#define wide (0xC4)

uint32_t vm_opcodes(uint8_t *code, uint32_t pc, vm_stack_t *STACK) {
    uint8_t _WIDE = 0;

    for (uint8_t i = 0; i <= _WIDE; i++) {
        switch (code[pc]) {
        case istore:
            break;

        case wide:
            _WIDE = 1;
            break;

        default:
            break;
        }
    }


    return pc;
}
