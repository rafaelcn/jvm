#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "vm/lib/vm_string.h"
#include "vm/lib/tests_helper.h"


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
    char** parsed_args;
    int position;
    (void) user_data;

    vm_strsplit_params = munit_parameters_get(params, "vm_strsplit_params");
    // Let's first parse the params
    parameters_length = strlen(vm_strsplit_params);
    parsed_args = arg_str_to_array_of_str(vm_strsplit_params, '/');

    expected_result = parsed_args[0];
    input_string = parsed_args[1];
    delimiter = parsed_args[2];
    position = atoi(parsed_args[3]);

    // Now we have parsed the arguments, let's test our function

    predicted_result = vm_strsplit(
        input_string, delimiter, position);

    assert_string_equal(expected_result, predicted_result);


    free(input_string);
    free(expected_result);
    free(predicted_result);
    free(delimiter);
    free(parsed_args);
    return MUNIT_OK;
}

// Test Suite, aggregate test cases and params
static MunitTest test_suite_tests[] = {
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
