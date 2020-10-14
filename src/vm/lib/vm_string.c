#include "vm_string.h"

#include "../utils/vm_errors.h"
#include "../utils/vm_logger.h"
#include "../utils/vm_checks.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int vm_strcmpl(const char *restrict s, const char *restrict s_) {
    if (strlen(s) != strlen(s_)) {
        return 0;
    }
    return vm_strncmpl(s, s_, strlen(s));
}

int vm_strncmpl(const char *restrict s, const char *restrict s_, int n) {

    int i = strlen(s)-1;
    int j = strlen(s_)-1;

    bool is_valid = i >= i-n+1 && j >= j-n+1 && i >= 0 && j >= 0;

    if (&s == &s_) {
        return 1;
    }

    for (; is_valid; i--, j--) {
        if (s[i] != s_[j]) {
            return 0;
        }
        is_valid = i >= i >= i-n+1 && j >= j-n+1 && i >= 0 && j >= 0;
    }

    return 1;
}

char *vm_strspliti(const char *restrict s, const char *restrict delim,
                   int pos) {

    char *token = NULL;
    size_t s_size = strlen(s);

    if (pos < 0 || pos > (int)s_size) {
        vm_log(stderr, "given index is out of bounds", __LINE__,
                    __FILE__, VM_LOG_ERROR);
        return "";
    }

    // Working only with delimiters that have 1 char in size.
    if (strlen(delim) == 1) {
        size_t delimiters_count = vm_strfreq(s, *delim);

        if (pos > delimiters_count) {
            token = "";
        } else {
            char *copy = calloc(sizeof(char), s_size);
            strcpy(copy, s);

            char *word = strtok(copy, delim);

            size_t i = 0;

            // iterate over the token
            while (vm_valid_pointer(word) && *word) {
                if (i == pos) {
                    token = word;
                    break;
                }

                word = strtok(NULL, delim);

                ++i;
            }
        }
    } else {
        vm_log(stderr, "vm_strspliti doesn't work with len(delimiter) > 1",
            __LINE__, __FILE__, VM_LOG_ERROR);
    }

    return token;
}

char** vm_strsplit(const char* s, const char *restrict delim) {
    char **words;

    // calculte how many words
    size_t words_quantity = vm_strfreq(s, ' ');
    // it's always the number of delimiters + 1 except on 0.
    size_t words_alloc = 0;

    if (words_quantity > 0) {
        words_alloc = words_quantity + 1;
    }

    words = calloc(sizeof (char*), words_alloc);

    for (size_t i = 0; i < words_alloc; i++) {
        char *word = vm_strspliti(s, " ", i);

        if (vm_valid_pointer(word)) {
            words[i] = calloc(sizeof(char*), strlen(word));
            strcpy(words[i], word);
        }
    }

    return words;
}

int vm_strchr(const char *s, const char c) {
    uint32_t i = 0;

    while (i < strlen(s)) {
        if (s[i] == c) {
            return i;
        }
        i++;
    }

    return -1;
}

size_t vm_strfreq(const char *s, const char c) {
    size_t i = 0;
    size_t r = 0;

    while (i < strlen(s)) {
        if (s[i] == c) {
            r++;
        }
        i++;
    }

    return r;
}