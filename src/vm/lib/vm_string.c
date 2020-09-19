#include "vm_string.h"

#include "../utils/vm_errors.h"
#include "../utils/vm_logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int vm_strcmpl(const char *restrict s, const char *restrict s_) {
    if (strlen(s) != strlen(s_)) {
        return 0;
    }
    return vm_strncmpl(s, s_, strlen(s));
}

int vm_strncmpl(const char *restrict s, const char *restrict s_, int n) {
    int length_s = strlen(s);
    int length_s_ = strlen(s_);
    int i = strlen(s)-1;
    int j = length_s_-1;
    bool are_valid_indexes = i >= strlen(s)-n+1 && j >= length_s_-n+1
            && i >= 0 && j >= 0;

    if (&s == &s_) {
        return 1;
    
    }

    for (; are_valid_indexes; i--, j--) {
        if (s[i] != s_[j]) {
            return 0;
        }
        are_valid_indexes = i >= strlen(s)-n+1 && j >= length_s_-n+1
                && i >= 0 && j >= 0;
    }

    return 1;
}

char *vm_strspliti(const char *restrict s, const char *restrict delim,
                   int pos) {

    char *token = NULL;
    size_t ssize = strlen(s);

    if (pos <= 0 || pos > (int)ssize) {
        vm_log(stderr, "given index is out of bounds", __LINE__,
                    __FILE__, VM_LOG_ERROR);
        return "";
    }

    //Working only with delimiters that have 1 char in size.
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
    } else {
        vm_log(stderr, "vm_strspliti doesn't work with len(delimiter) > 1",
            __LINE__, __FILE__, VM_LOG_ERROR);
    }

    return token;
}

char** vm_strsplit(const char* s, const char *restrict delim) {
    int array_index = 0; // Array index shall be the number of elements - 1.
    int last_delim_position = 0;
    int splitted_str_count = 1; // If there's no delim, there'll be at 
                                // least 1 string.
    const int string_length = strlen(s);
    char** array_of_substrs = NULL;

    for(int i = 0; i < string_length; i++)
    {
        if(s[i] == delim[0]) splitted_str_count++;
    }

    array_of_substrs = (char**) calloc(splitted_str_count, (sizeof(char*)));
    for(int i = 0; i < splitted_str_count; i++)
    {
        array_of_substrs[i] = vm_strspliti(s, delim, i+1);
    }

    return array_of_substrs;
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

