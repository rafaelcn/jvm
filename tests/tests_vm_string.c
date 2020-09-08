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
    /*
    Expected result/ number of interegers to count/ left string/ right string
    */
    (char*) "1/ 03/ one/ one",
    (char*) "1/ 02/ one/ one",
    (char*) "1/ 01/ one/ one",
    (char*) "1/ 04/ pato/ pato",
    (char*) "1/ 03/ pato/ pato",
    (char*) "1/ 02/ pato/ pato",
    (char*) "1/ 01/ pato/ pato",
    (char*) "0/ 03/ one/ nne",
    (char*) "1/ 02/ one/ nne",
    (char*) "1/ 01/ one/ nne",
    (char*) "1/ 07/ liberal/ patocracia liberal",
    (char*) "1/ 07/ democracia liberal/ liberal",
    (char*) "1/ 14/ democracia liberal/ patocracia liberal",
    (char*) "0/ 16/ democracia liberal/ patocracia liberal",
    (char*) "0/ 20/ democracia liberal/ patocracia liberal",
    NULL
};

static MunitParameterEnum test_vm_strncmpl_params[] = {
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
    for(int i = last_comma_position; i < strlen(vm_strncmpl_params); i++)
    {
        if (vm_strncmpl_params[i] == '/')
        {
            left_string = string_substring(
                vm_strncmpl_params, last_comma_position+1, i);
            last_comma_position = i;
            i = strlen(vm_strncmpl_params);
        }
    }

    right_string = string_substring(
        vm_strncmpl_params, last_comma_position+2,
        strlen(vm_strncmpl_params));

    // Now we have parsed the arguments, let's test our function
    predicted_result = vm_strncmpl(
        left_string, right_string, num_characters_to_count);

    assert_int(expected_result, ==, predicted_result);

    free(left_string);
    free(right_string);
    free(num_characters_to_count_string);
    return MUNIT_OK;
}

static char* vm_strcmpl_params[] = {
    /* Expected result/ left string/ right string */
    (char*) "1/ one/ one",
    (char*) "1/ pato/ pato",
    (char*) "0/ one/ nne",
    (char*) "0/ democracia liberal/ patocracia liberal",
    NULL
};

static MunitParameterEnum test_vm_strcmpl_params[] = {
    { (char*) "vm_strcmpl_params", vm_strcmpl_params },
    { NULL, NULL },
};

/**
 * @author Vinicius Gomes de Souza - 150047941
 * @brief Receives an argument string and parses it into an array of substrings.
 * @param input_string The string to be split in substrings.
 * @param separator The character that is going to be used as a delimiter in the
 * splitting process.
 * @returns An array containing the substrings, without the separator character,
 * of the input string.
 */
char** arg_str_to_array_of_str(const char* input_string, const char separator) {
    int array_index = 0;
    int separator_position = 0;
    char* substr_before_separator;
    char** array_of_substrs = NULL;

    for(int i = 0; i <= strlen(input_string); i++)
    {
        if (input_string[i] == '/')
        {
            substr_before_separator = string_substring(
                input_string, separator_position, i);

            array_of_substrs = (char**) realloc(
                array_of_substrs,
                sizeof(array_of_substrs) +
                (sizeof(char) * (i - separator_position + 1)));

            array_of_substrs[array_index] = substr_before_separator;

            array_index = array_index + 1;
            separator_position = i + 2;
        }

        else if (i == strlen(input_string))
        {
            substr_before_separator = string_substring(
                input_string, separator_position, i);

            array_of_substrs = (char**) realloc(
                array_of_substrs,
                sizeof(array_of_substrs) +
                (sizeof(char) * (i - separator_position + 1)));

            array_of_substrs[array_index] = substr_before_separator;
        }
    }

    return array_of_substrs;
}

static MunitResult
test_vm_strcmpl(const MunitParameter params[], void* user_data) {
    const char* vm_strcmpl_params;
    char* left_string;
    char* right_string;
    int parameters_length, last_comma_position;
    int expected_result, predicted_result;
    (void) user_data;
    char** parsed_args;

    vm_strcmpl_params = munit_parameters_get(params, "vm_strcmpl_params");
    // Let's first parse the params
    parameters_length = strlen(vm_strcmpl_params);

    parsed_args = arg_str_to_array_of_str(vm_strcmpl_params, '/');

    expected_result = atoi(parsed_args[0]);
    left_string = parsed_args[1];
    right_string = parsed_args[2];

    // Now we have parsed the arguments, let's test our function
    predicted_result = vm_strcmpl(
        left_string, right_string);

    assert_int(expected_result, ==, predicted_result);

    free(left_string);
    free(right_string);
    return MUNIT_OK;
}

static char* vm_strsplit_params[] = {
    /*Expected Result/ Input String/ Delimiter/ 1-Started Index */
    (char*) "Gosto de pão/ Gosto de pão, queijo e margarina./ ,/ 1",
    (char*) "Gosto de pão/ Gosto de pão, presunto, queijo e margarina./ ,/ 1",
    (char*) " presunto/ Gosto de pão, presunto, queijo e margarina./ ,/ 2",
    (char*) " queijo e margarina./ Gosto de pão, presunto, queijo e margarina./ ,/ 3",


    NULL
};

static MunitParameterEnum test_vm_strsplit_params[] = {
    { (char*) "vm_strsplit_params", vm_strsplit_params },
    { NULL, NULL },
};

static MunitResult
test_vm_strsplit(const MunitParameter params[], void* user_data) {
    const char* vm_strsplit_params;
    char* delimiter;
    char* input_string;
    char* expected_result, *predicted_result;
    int parameters_length, last_slash_position;
    char* position_string;
    int position;
    (void) user_data;

    vm_strsplit_params = munit_parameters_get(params, "vm_strsplit_params");
    // Let's first parse the params
    parameters_length = strlen(vm_strsplit_params);
    last_slash_position = 0;
    for(int i = last_slash_position; i < strlen(vm_strsplit_params); i++)
    {
        if (vm_strsplit_params[i] == '/')
        {
            expected_result = string_substring(
                vm_strsplit_params, last_slash_position, i);
            last_slash_position = i;
            i = strlen(vm_strsplit_params);
        }
    }

    for(int i = last_slash_position + 1; i < strlen(vm_strsplit_params); i++)
    {
        if (vm_strsplit_params[i] == '/')
        {
            input_string = string_substring(
                vm_strsplit_params, last_slash_position + 2, i);
            last_slash_position = i;
            i = strlen(vm_strsplit_params);
        }
    }

    for(int i = last_slash_position + 1; i < strlen(vm_strsplit_params); i++)
    {
        if (vm_strsplit_params[i] == '/')
        {
            delimiter = string_substring(
                vm_strsplit_params, last_slash_position+2, i);
            last_slash_position = i;
            i = strlen(vm_strsplit_params);
        }
    }

    position_string = string_substring(
        vm_strsplit_params, last_slash_position+2, strlen(vm_strsplit_params));
    position = atoi(position_string);
    // Now we have parsed the arguments, let's test our function

    predicted_result = vm_strsplit(
        input_string, delimiter, position);

    assert_string_equal(expected_result, predicted_result);


    free(input_string);
    free(expected_result);
    free(predicted_result);
    free(delimiter);
    free(position_string);
    return MUNIT_OK;
}

// Test Suite, aggregate test cases and params
static MunitTest test_suite_tests[] = {
  { (char*) "Testing vm_strncmpl", test_vm_strncmpl,
        NULL, NULL, MUNIT_TEST_OPTION_NONE, test_vm_strncmpl_params },
  { (char*) "Testing vm_strcmpl", test_vm_strcmpl,
        NULL, NULL, MUNIT_TEST_OPTION_NONE, test_vm_strcmpl_params },
  { (char*) "Testing vm_strsplit", test_vm_strsplit,
        NULL, NULL, MUNIT_TEST_OPTION_NONE, test_vm_strsplit_params },

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
