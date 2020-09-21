#define MUNIT_ENABLE_ASSERT_ALIASES

#include "args_parser.h"
#include "tests_helper.h"
#include "vm/lib/vm_string.h"

#include "munit/munit.h"

#include <stdio.h>


static char* args_parse_params[] = {
    /* Flag Name! Flag Value(ARGC/2 TIMES)/
        Input Argv/ Input Argc */
    (char*) "filename! programa_legal/ filename! programa_legal/ 3/",
    (char*) "help! / help/ 2",
    (char*) "version! / version/ 2",
    (char*) "execute! programa_legal/ execute! programa_legal/ 3",
    (char*) "inform! programa_legal/ inform! programa_legal/ 3",
    NULL
};

static MunitParameterEnum test_args_parse_params[] = {
    { (char*) "args_parse_params", args_parse_params },
    { NULL, NULL },
};

static MunitResult
test_args_parse(const MunitParameter params[], void* user_data) {
    const char* args_parse_params;
    char* delimiter;
    char** input_argv;
    args_t expected_result;
    args_t predicted_result;
    int parameters_length, input_argc;
    char** parsed_args, **parsed_args_t;
    int position;
    (void) user_data;

    args_parse_params = munit_parameters_get(params, "args_parse_params");

    // Let's first parse the params
    parameters_length = strlen(args_parse_params);
    parsed_args = test_strplit(args_parse_params, '/');
    input_argv = test_strplit(parsed_args[1], '!');
    input_argc = atoi(parsed_args[2]);
    parsed_args_t = test_strplit(parsed_args[0], '!');
    expected_result.flags->flag_name = parsed_args_t[0];
    expected_result.flags->flag_value = parsed_args_t[1];
    // Now we have parsed the arguments, let's test our function

    predicted_result = args_parse(
        input_argc, input_argv);

    assert_string_equal(
        expected_result.flags->flag_name,
        predicted_result.flags->flag_name);
    if(vm_strcmpl(predicted_result.flags->flag_name, ""))
    assert_string_equal(
        expected_result.flags->flag_value,
        predicted_result.flags->flag_value);



    free(input_argv);
    free(parsed_args[2]);
    free(parsed_args[1]);
    free(parsed_args[0]);
    free(parsed_args);
    free(parsed_args_t[1]);
    free(parsed_args_t[0]);
    free(parsed_args_t);

    return MUNIT_OK;
}

// Test Suite, aggregate test cases and params
static MunitTest test_suite_tests[] = {
  { (char*) "Testing args_parse", test_args_parse,
        NULL, NULL, MUNIT_TEST_OPTION_NONE, test_args_parse_params },

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
