#include <stdlib.h>

#include "vm_utf8.h"

uint16_t * vm_utf8_to_uint16_t(uint16_t length, uint8_t *bytes)
{
    uint16_t *heap = NULL;
    uint16_t j = 0;

    for (uint16_t i = 0; i < length;) {
        heap = realloc(heap, (sizeof(uint16_t) * (j+1)));

        if (bytes[i] >> 7) {
            if ((bytes[i] >> 5) & (0x01)) {
                if (bytes[i] == 0xED) { // Characters with code points above U+FFFF
                    i += 6;
                } else { // '\u0800' to '\uFFFF'
                    heap[j] = (
                        ((bytes[i] & 0x0F) << 12) |
                        ((bytes[i+1] & 0x3F) << 6) |
                        (bytes[i+2] & 0x3F)
                    );
                    i += 3;
                }
            } else { // '\u0080' up to '\u07FF' and '\u0000'
                heap[j] = (((bytes[i] & 0x1F) << 6) | (bytes[i+1] & 0x3F));
                i += 2;
            }
        } else { // '\u0001' up to '\u007F'
            heap[j] = bytes[i];
            i += 1;
        }

        j += 1;
    }

    return heap;
}
