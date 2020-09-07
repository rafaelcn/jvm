#define MUNIT_ENABLE_ASSERT_ALIASES
#include <stdlib.h>
#include <stdio.h>
#include "munit/munit.h"
#include "vm/lib/vm_string.h"

char* string_substring(const char str[], int start, int end) {
    int i, j;
    char *sub; 
     
    // Verifies if the start and end positions are valid
    if(start >= end || end > strlen(str)) {
        return NULL;
    }
     
    // Allocate necessary memory for substring
    sub = (char *) malloc(sizeof(char) * (end - start + 1));
     
    // Copy values from original string to new one
    for(i = start, j = 0; i < end; i++, j++) {
        sub[j] = str[i];
    }
     
    // String terminator
    sub[j] = '\0';
     
    return sub;
}

static char* vm_strncmpl_params[] = {
    /* Expected result, number of interegers to count, left string, right string */
    (char*) "1, 03, one, one",
    (char*) "1, 02, one, one",
    (char*) "1, 01, one, one",
    (char*) "1, 04, pato, pato",
    (char*) "1, 03, pato, pato",
    (char*) "1, 02, pato, pato",
    (char*) "1, 01, pato, pato",
    (char*) "0, 03, one, nne",
    (char*) "1, 02, one, nne",
    (char*) "1, 01, one, nne",
    (char*) "1, 08, democracia liberal, patocracia liberal",
    (char*) "1, 14, democracia liberal, patocracia liberal",
    (char*) "0, 16, democracia liberal, patocracia liberal",
    (char*) "0, 20, democracia liberal, patocracia liberal",
    NULL
};


static MunitParameterEnum test_params[] = {
    { (char*) "vm_strncmpl_params", vm_strncmpl_params },
    { NULL, NULL },
};

static MunitResult
test_vm_strncmpl(const MunitParameter params[], void* user_data) {
    const char* vm_strncmpl_params;
    char* num_characters_to_count_string;
    char* left_string;
    char* right_string;
    int num_characters_to_count, parameters_length, last_comma_position;
    int expected_result, predicted_result;
    (void) user_data;

    vm_strncmpl_params = munit_parameters_get(params, "vm_strncmpl_params");
    // Let's first parse the params
    parameters_length = strlen(vm_strncmpl_params);

    expected_result = atoi(&vm_strncmpl_params[0]);

    num_characters_to_count_string = string_substring(vm_strncmpl_params, 2, 5);
    num_characters_to_count = atoi(num_characters_to_count_string);

    last_comma_position = 6;
    for(int i = 6; i < strlen(vm_strncmpl_params); i++)
    {
        if (vm_strncmpl_params[i] == ',')
        {
            left_string = string_substring(
                vm_strncmpl_params, last_comma_position+1, i);
            last_comma_position = i;
            i = strlen(vm_strncmpl_params);
        }
    }

    right_string = string_substring(
        vm_strncmpl_params, last_comma_position+2, strlen(vm_strncmpl_params));

    // Now we have parsed the arguments, let's test our function
    predicted_result = vm_strncmpl(
        left_string, right_string, num_characters_to_count);

    assert_int(expected_result, ==, predicted_result);

    free(left_string);
    free(right_string);
    free(num_characters_to_count_string);
    return MUNIT_OK;
}


static MunitTest test_suite_tests[] = {
  { (char*) "Testing vm_strncmpl", test_vm_strncmpl, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
  (char*) "",
  /* The first parameter is the array of test suites. */
  test_suite_tests,
  NULL,
  1,
  MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  return munit_suite_main(&test_suite, (void*) "µnit", argc, argv);
}