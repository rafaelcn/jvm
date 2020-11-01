#include <stdlib.h>

#include "vm_utf8.h"

uint16_t * vm_utf8_to_uint16_t(uint16_t length, uint8_t *bytes)
{
    uint16_t *heap = NULL;

    for (uint16_t i = 0; i < length; i++) {
        heap = realloc(heap, (sizeof(uint16_t) * (i+1)));

        if (bytes[i] >> 7) {
            if ((bytes[i] >> 5) & (0x01)) {
                if (bytes[i] == 0xED) { // Characters with code points above U+FFFF
                    heap[i] = 0x0000;
                } else { // '\u0800' to '\uFFFF'
                    heap[i] = (((bytes[i] & 0x0F) << 12) |
                              ((bytes[i+1] & 0x3F) << 6) |
                              (bytes[i+2] & 0x3F));
                }
            } else { // '\u0080' up to '\u07FF' and '\u0000'
                heap[i] = (((bytes[i] & 0x1F) << 6) | (bytes[i+1] & 0x3F));
            }
        } else { // '\u0001' up to '\u007F'
            heap[i] = bytes[i];
        }
    }

    return heap;
}
