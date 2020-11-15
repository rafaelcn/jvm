#include <stdlib.h>

#include "vm_utf8.h"

vm_uint16_string_t * vm_utf8_to_uint16_t(uint16_t length, uint8_t *bytes)
{
    vm_uint16_string_t * uint16_string = calloc(1, sizeof(vm_uint16_string_t));

    uint16_string->length = 0;
    uint16_string->string = NULL;

    for (uint16_t i = 0; i < length;) {
        uint16_string->string = realloc(uint16_string->string, (sizeof(uint16_t) * (uint16_string->length + 1)));

        if (bytes[i] >> 7) {
            if ((bytes[i] >> 5) & (0x01)) {
                if (bytes[i] == 0xED) { // Characters with code points above U+FFFF
                    if (i+6 <= length) {
                        i += 6;
                    }
                } else { // '\u0800' to '\uFFFF'
                    uint16_string->string[uint16_string->length] = (
                        ((bytes[i] & 0x0F) << 12) |
                        ((bytes[i+1] & 0x3F) << 6) |
                        (bytes[i+2] & 0x3F)
                    );
                    if (i+3 <= length) {
                        i += 3;
                    }
                }
            } else { // '\u0080' up to '\u07FF' and '\u0000'
                uint16_string->string[uint16_string->length] = (((bytes[i] & 0x1F) << 6) | (bytes[i+1] & 0x3F));
                if (i+2 <= length) {
                    i += 2;
                }
            }
        } else { // '\u0001' up to '\u007F'
            uint16_string->string[uint16_string->length] = bytes[i];
            if (i+1 <= length) {
                i += 1;
            }
        }

        uint16_string->length += 1;
    }

    return uint16_string;
}
