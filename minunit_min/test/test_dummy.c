#include "../includes/minunit.h"

int tests_run = 0;

MU_TEST(test_dummy) {
    mu_assert("1 should be equal to 1", 1 == 1);
    return 0;
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_dummy);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
