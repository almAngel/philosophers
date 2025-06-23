#ifndef MINUNIT_H
# define MINUNIT_H

# include <stdio.h>

# define MU_COLOR_GREEN "\033[0;32m"
# define MU_COLOR_RED   "\033[0;31m"
# define MU_COLOR_RESET "\033[0m"

# define MU_TEST(name) static char *name(void)
# define MU_TEST_SUITE(name) static void name(void)
# define MU_RUN_TEST(test) do { \
    char *message = test(); \
    tests_run++; \
    if (message) { \
        printf(MU_COLOR_RED "[KO] %s\n" MU_COLOR_RESET, message); \
    } else { \
        printf(MU_COLOR_GREEN "[OK] %s\n" MU_COLOR_RESET, #test); \
    } \
} while (0)
# define MU_RUN_SUITE(suite) suite()
# define MU_REPORT() printf("%d tests run\n", tests_run)

# define mu_assert(message, test) do { if (!(test)) return message; } while (0)

extern int	tests_run;

char*		all_tests();

#endif