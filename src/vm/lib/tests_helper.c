#include "tests_helper.h"

#include <string.h>
#include <stdlib.h>


char* string_substring(const char input_string[], int start, int end) {
    int i, j;
    char *slice_string;

    // Verifies if the start and end positions are valid
    if(start >= end || end > strlen(input_string)) {
        return NULL;
    }

    // Allocate necessary memory for the new slice string
    slice_string = (char *) malloc(sizeof(char) * (end - start + 1));

    // Copy values from original string to new one
    for(i = start, j = 0; i < end; i++, j++) {
        slice_string[j] = input_string[i];
    }

    // String terminator
    slice_string[j] = '\0';

    return slice_string;
}


char** arg_str_to_array_of_str(const char* input_string, const char delimiter) {
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
            array_of_substrs[array_index++] = string_substring(
                input_string, last_delimiter_position, i);
            last_delimiter_position = i + 2;
        }
    }
    return array_of_substrs;
}