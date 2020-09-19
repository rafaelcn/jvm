#include "tests_helper.h"

#include "vm/lib/vm_string.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



char* str_slice(const char input_str[], int start, int end) {
    int i, j;
    char *slice;

    // Verifies if the start and end positions are valid
    if(start >= end || end > strlen(input_str)) {
        return NULL;
    }

    // Allocate necessary memory for the new slice string
    slice = (char *) malloc(sizeof(char) * (end - start + 1));

    // Copy values from original string to new one
    for(i = start, j = 0; i < end; i++, j++) {
        slice[j] = input_str[i];
    }

    // String terminator
    slice[j] = '\0';

    return slice;
}


char** test_strplit(const char* input_string, const char delimiter) {
    int array_index = 0; // Array index shall be the number of elements - 1.
    int last_delimiter_position = 0;
    const int string_length = strlen(input_string);
    char** array_of_substrs = NULL;

    for(int i = 0; i <= string_length; i++)
    {
        if (input_string[i] == delimiter || i == string_length)
        {   
            array_of_substrs = (char**) realloc(
                array_of_substrs,
                (sizeof(char*) * (array_index+1)));
            array_of_substrs[array_index++] = str_slice(
                input_string, last_delimiter_position, i);
            last_delimiter_position = i + 2;
        }
    }
    return array_of_substrs;
}