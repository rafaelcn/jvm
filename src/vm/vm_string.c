#include "vm_string.h"
#include "utils/vm_errors.h"

#include <stdlib.h>
#include <string.h>

int vm_strcmpl(const char *restrict s, const char *restrict s_) {
    return vm_strncmpl(s, s_, strlen(s));
}

int vm_strncmpl(const char *restrict s, const char *restrict s_, int n) {
    if (&s == &s_) {
        return 1;
    }

    int j = n;

    for (unsigned int i = strlen(s)-1; i >= strlen(s)-n; i--) {
        if (s[i] != s_[j]) {
            return 1;
        }
        j--;
    }

    return 0;
}

char *vm_strsplit(const char *restrict s, const char *restrict delim,
                   int pos) {

    char *token = NULL;
    size_t ssize = strlen(s);

    if (pos <= 0 || pos > (int)ssize) {
        vm_pferror(stderr, "Given index is out of bounds", __LINE__,
                    __FILE__, BFS_STR_ERROR);
        return "";
    }

    //Working only with delimiters that with 1 char of size.
    unsigned int index = 0;
    pos -= 1;

    if (strlen(delim) == 1) {
        while (index < strlen(s)) {
            if (s[index] == *delim) {
                pos--;
            }

            // Found string to copy
            if (pos == 0) {
                if (s[index] == *delim) {
                    index++;
                }

                int k = 0;
                unsigned int ssize = 0;

                while (s[index+1] != *delim) {
                    index++;
                    ssize++;
                }

                token = calloc(ssize, 1);

                index -= ssize;

                while (s[index] != *delim && index != index+ssize) {
                    token[k] = s[index];

                    index++;
                    k++;
                }
                break;
            }

            index++;
        }
    }

    return token;
}

int vm_strchr(const char *s, const char c) {
    unsigned int i = 0;

    while (i < strlen(s)) {
        if (s[i] == c) {
            return i;
        }
        i++;
    }

    return -1;
}