#include "vm_utf8.h"

uint16_t * utf8_to_uint16_t(vm_class_file_t *cf, uint16_t table_index)
{
    uint16_t length = cf->constant_pool[table_index].info.utf8_info.length;
    uint8_t *b = cf->constant_pool[table_index].info.utf8_info.bytes;
    uint16_t *heap = NULL;

    for (int i = 0; i < length; i++) {
        heap = realloc(heap, (sizeof(uint16_t) * (i+1)));

        if (b[i] >> 7) {
            if ((b[i] >> 5) & (0x01)) {
                if (b[i] == 0xED) { // Characters with code points above U+FFFF
                    heap[i] = 0x0000;
                } else { // '\u0800' to '\uFFFF'
                    heap[i] = (((b[i] & 0x0F) << 12) | ((b[i+1] & 0x3F) << 6) | (b[i+2] & 0x3F));
                }
            } else { // '\u0080' up to '\u07FF' and '\u0000'
                heap[i] = (((b[i] & 0x1F) << 6) | (b[i+1] & 0x3F));
            }
        } else { // '\u0001' up to '\u007F'
            heap[i] = b[i];
        }
    }

    return heap;
}