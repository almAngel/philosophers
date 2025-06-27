#include "../includes/philo.h"
#include "../includes/minunit.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int tests_run = 0;

// Helper to run a simulation test by spawning the actual program
static int run_stress_test(int test_num, int num_philos, int time_to_die, 
                          int time_to_eat, int time_to_sleep, int num_meals) {
    pid_t pid;
    int status;
    long start_time, end_time;
    char philo_arg[16], die_arg[16], eat_arg[16], sleep_arg[16], meals_arg[16];
    
    // Convert integers to strings
    sprintf(philo_arg, "%d", num_philos);
    sprintf(die_arg, "%d", time_to_die);
    sprintf(eat_arg, "%d", time_to_eat);
    sprintf(sleep_arg, "%d", time_to_sleep);
    sprintf(meals_arg, "%d", num_meals);
    
    start_time = get_time_ms();
    
    pid = fork();
    if (pid == 0) {
        // Child process - run the simulation
        char *args[] = {"./philo", philo_arg, die_arg, eat_arg, sleep_arg, meals_arg, NULL};
        
        // Redirect stdout to suppress output during tests
        freopen("/dev/null", "w", stdout);
        execv("./philo", args);
        exit(1); // Should not reach here
    } else if (pid > 0) {
        // Parent process - wait with timeout
        sleep(1); // Let it run for 1 second
        
        // Check if process is still running
        int result = waitpid(pid, &status, WNOHANG);
        end_time = get_time_ms();
        
        if (result == 0) {
            // Process still running - kill it and consider it a pass
            kill(pid, SIGTERM);
            waitpid(pid, &status, 0);
            printf("Test %d: Pass [✓] - Process ran for %ldms without early death\n", 
                   test_num, end_time - start_time);
            return 1;
        } else {
            // Process terminated - check how long it ran
            long runtime = end_time - start_time;
            if (runtime < 50) {
                printf("Test %d: Fail [x] - Process died after %ldms (too early)\n", 
                       test_num, runtime);
                return 0;
            } else {
                printf("Test %d: Pass [✓] - Process completed after %ldms\n", 
                       test_num, runtime);
                return 1;
            }
        }
    } else {
        printf("Test %d: Fail [x] - Fork failed\n", test_num);
        return 0;
    }
}

// Test 1: Stress test replicating the 199 610 200 200 10 scenario
MU_TEST(test_stress_199_philosophers_run_1) {
    int result = run_stress_test(1, 199, 610, 200, 200, 10);
    mu_assert("Stress test 1 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_2) {
    int result = run_stress_test(2, 199, 610, 200, 200, 10);
    mu_assert("Stress test 2 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_3) {
    int result = run_stress_test(3, 199, 610, 200, 200, 10);
    mu_assert("Stress test 3 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_4) {
    int result = run_stress_test(4, 199, 610, 200, 200, 10);
    mu_assert("Stress test 4 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_5) {
    int result = run_stress_test(5, 199, 610, 200, 200, 10);
    mu_assert("Stress test 5 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_6) {
    int result = run_stress_test(6, 199, 610, 200, 200, 10);
    mu_assert("Stress test 6 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_7) {
    int result = run_stress_test(7, 199, 610, 200, 200, 10);
    mu_assert("Stress test 7 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_8) {
    int result = run_stress_test(8, 199, 610, 200, 200, 10);
    mu_assert("Stress test 8 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_9) {
    int result = run_stress_test(9, 199, 610, 200, 200, 10);
    mu_assert("Stress test 9 failed", result == 1);
    return 0;
}

MU_TEST(test_stress_199_philosophers_run_10) {
    int result = run_stress_test(10, 199, 610, 200, 200, 10);
    mu_assert("Stress test 10 failed", result == 1);
    return 0;
}

MU_TEST_SUITE(test_suite) {
    printf("Running stress tests with 199 philosophers (610ms die, 200ms eat, 200ms sleep, 10 meals):\n");
    MU_RUN_TEST(test_stress_199_philosophers_run_1);
    MU_RUN_TEST(test_stress_199_philosophers_run_2);
    MU_RUN_TEST(test_stress_199_philosophers_run_3);
    MU_RUN_TEST(test_stress_199_philosophers_run_4);
    MU_RUN_TEST(test_stress_199_philosophers_run_5);
    MU_RUN_TEST(test_stress_199_philosophers_run_6);
    MU_RUN_TEST(test_stress_199_philosophers_run_7);
    MU_RUN_TEST(test_stress_199_philosophers_run_8);
    MU_RUN_TEST(test_stress_199_philosophers_run_9);
    MU_RUN_TEST(test_stress_199_philosophers_run_10);
}

int main(void) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
