#define MUNIT_ENABLE_ASSERT_ALIASES

#include <stdlib.h>
#include <stdio.h>

#include "munit/munit.h"

#include "utils/tests_helper.h"

#include "vm/lib/vm_string.h"

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
    NULL
};

static MunitParameterEnum test_vm_strncmpl_params[] = {
    { (char*) "vm_strncmpl_params", vm_strncmpl_params },
    { NULL, NULL },
};


static MunitResult
test_vm_strncmpl(const MunitParameter params[], void* user_data) {
    const char* vm_strncmpl_params;
    char* left_string;
    char* right_string;
    char** parsed_args;
    int num_characters_to_count, parameters_length, last_comma_position;
    int expected_result, predicted_result;
    (void) user_data;

    vm_strncmpl_params = munit_parameters_get(params, "vm_strncmpl_params");
    // Let's first parse the params
    parameters_length = strlen(vm_strncmpl_params);

    parsed_args = test_strplit(vm_strncmpl_params, '/');

    expected_result = atoi(parsed_args[0]);
    num_characters_to_count = atoi(parsed_args[1]);
    left_string = parsed_args[2];
    right_string = parsed_args[3];

    // Now we have parsed the arguments, let's test our function
    predicted_result = vm_strncmpl(left_string, right_string,
        num_characters_to_count);

    assert_int(expected_result, ==, predicted_result);

    free(left_string);
    free(right_string);
    free(parsed_args[1]);
    free(parsed_args[0]);
    free(parsed_args);

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

    parsed_args = test_strplit(vm_strcmpl_params, '/');

    expected_result = atoi(parsed_args[0]);
    left_string = parsed_args[1];
    right_string = parsed_args[2];

    // Now we have parsed the arguments, let's test our function
    predicted_result = vm_strcmpl(left_string, right_string);

    assert_int(expected_result, ==, predicted_result);

    free(parsed_args[0]);
    free(parsed_args);
    free(left_string);
    free(right_string);

    return MUNIT_OK;
}

static char* vm_strspliti_params[] = {
    /*Expected Result/ Input String/ Delimiter/ 1-Started Index */
    (char*) "Gosto de pão/ Gosto de pão, queijo e margarina./ ,/ 1",
    (char*) "Gosto de pão/ Gosto de pão, presunto, queijo e margarina./ ,/ 1",
    (char*) " presunto/ Gosto de pão, presunto, queijo e margarina./ ,/ 2",
    (char*) " queijo e margarina./ Gosto de pão, presunto, queijo e margarina./ ,/ 3",
    NULL
};

static MunitParameterEnum test_vm_strspliti_params[] = {
    { (char*) "vm_strspliti_params", vm_strspliti_params },
    { NULL, NULL },
};

static MunitResult
test_vm_strspliti(const MunitParameter params[], void* user_data) {
    const char* vm_strspliti_params;
    char* delimiter;
    char* input_string;
    char* expected_result, *predicted_result;
    int parameters_length, last_slash_position;
    char** parsed_args;
    int position;
    (void) user_data;

    vm_strspliti_params = munit_parameters_get(params, "vm_strspliti_params");
    // Let's first parse the params
    parameters_length = strlen(vm_strspliti_params);
    parsed_args = test_strplit(vm_strspliti_params, '/');

    expected_result = parsed_args[0];
    input_string = parsed_args[1];
    delimiter = parsed_args[2];
    position = atoi(parsed_args[3]);

    // Now we have parsed the arguments, let's test our function

    predicted_result = vm_strspliti(input_string, delimiter, position);

    assert_string_equal(expected_result, predicted_result);

    free(input_string);
    free(expected_result);
    free(predicted_result);
    free(delimiter);
    free(parsed_args);

    return MUNIT_OK;
}

static char* vm_strsplit_params[] = {
    /*Expected Number of Strings/ Input String/ Delimiter*/
    (char*) "2/ Gosto de pão, queijo e margarina./ ,",
    (char*) "3/ Gosto de pão, presunto, queijo e margarina./ ,",
    (char*) "4/ Gosto de pão! Presunto! Abacate! E margarina./ !",
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
    char**predicted_result;
    int expected_result, parameters_length, last_slash_position;
    char** parsed_args;
    int position;
    (void) user_data;

    vm_strsplit_params = munit_parameters_get(params, "vm_strsplit_params");
    // Let's first parse the params
    parameters_length = strlen(vm_strsplit_params);
    parsed_args = test_strplit(vm_strsplit_params, '/');

    expected_result = atoi(parsed_args[0]);
    input_string = parsed_args[1];
    delimiter = parsed_args[2];

    // Now we have parsed the arguments, let's test our function

    predicted_result = vm_strsplit(input_string, delimiter);

    for (int i = 0; i < expected_result; i++) {
        assert_ptr_not_null(predicted_result[i]);
    }

    free(input_string);
    free(parsed_args[0]);
    free(predicted_result);
    free(delimiter);
    free(parsed_args);

    return MUNIT_OK;
}

// Test Suite, aggregate test cases and params
static MunitTest test_suite_tests[] = {
    { (char*) "Testing vm_strncmpl", test_vm_strncmpl,
        NULL, NULL, MUNIT_TEST_OPTION_NONE, test_vm_strncmpl_params },
    { (char*) "Testing vm_strcmpl", test_vm_strcmpl,
        NULL, NULL, MUNIT_TEST_OPTION_NONE, test_vm_strcmpl_params },
    { (char*) "Testing vm_strspliti", test_vm_strspliti,
        NULL, NULL, MUNIT_TEST_OPTION_NONE, test_vm_strspliti_params },
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
