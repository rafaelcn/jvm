#include <stdlib.h>

#include "vm_utf8.h"

vm_uint32_string_t * vm_utf8_to_uint32_t(uint16_t length, uint8_t *bytes)
{
    vm_uint32_string_t * string_t = calloc(1, sizeof(vm_uint32_string_t));

    string_t->length = 0;
    string_t->string = NULL;

    for (uint16_t i = 0; i < length;) {
        string_t->string = realloc(string_t->string, (sizeof(uint32_t) * (string_t->length + 1)));

        if (bytes[i] >> 7) {
            if ((bytes[i] >> 5) & (0x01)) {
                if (bytes[i] == 0xED) {
                    // Characters with code points above U+FFFF
                    string_t->string[string_t->length] = (
                        0x00010000 | ((bytes[i+1] & 0x0f) << 16) |
                        ((bytes[i+2] & 0x3f) << 10) |
                        ((bytes[i+4] & 0x0f) << 6) |
                        (bytes[i+5] & 0x3f)
                    );
                    if (i+6 <= length) {
                        i += 6;
                    }
                } else {
                    // '\u0800' to '\uFFFF'
                    string_t->string[string_t->length] = (
                        ((bytes[i] & 0x0F) << 12) |
                        ((bytes[i+1] & 0x3F) << 6) |
                        (bytes[i+2] & 0x3F)
                    );
                    if (i+3 <= length) {
                        i += 3;
                    }
                }
            } else {
                // '\u0080' up to '\u07FF' and '\u0000'
                string_t->string[string_t->length] = (((bytes[i] & 0x1F) << 6) | (bytes[i+1] & 0x3F));
                if (i+2 <= length) {
                    i += 2;
                }
            }
        } else {
            // '\u0001' up to '\u007F'
            string_t->string[string_t->length] = bytes[i];
            if (i+1 <= length) {
                i += 1;
            }
        }

        string_t->length += 1;
    }

    return string_t;
}
