#include "../includes/philo.h"
#include "../includes/minunit.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

int tests_run = 0;

// Helper to capture output and check for early deaths
static int run_detailed_stress_test(int test_num, int num_philos, int time_to_die, 
                                   int time_to_eat, int time_to_sleep, int num_meals,
                                   int expected_min_runtime) {
    pid_t pid;
    int status;
    long start_time, end_time;
    char philo_arg[16], die_arg[16], eat_arg[16], sleep_arg[16], meals_arg[16];
    int pipefd[2];
    
    // Convert integers to strings
    sprintf(philo_arg, "%d", num_philos);
    sprintf(die_arg, "%d", time_to_die);
    sprintf(eat_arg, "%d", time_to_eat);
    sprintf(sleep_arg, "%d", time_to_sleep);
    sprintf(meals_arg, "%d", num_meals);
    
    // Create pipe to capture output
    if (pipe(pipefd) == -1) {
        printf("Test %d: Fail [x] - Pipe creation failed\n", test_num);
        return 0;
    }
    
    start_time = get_time_ms();
    
    pid = fork();
    if (pid == 0) {
        // Child process - run the simulation
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]);
        
        char *args[] = {"./philo", philo_arg, die_arg, eat_arg, sleep_arg, meals_arg, NULL};
        execv("./philo", args);
        exit(1); // Should not reach here
    } else if (pid > 0) {
        // Parent process
        close(pipefd[1]); // Close write end
        
        // Wait with timeout
        usleep(expected_min_runtime * 1000); // Wait for expected minimum runtime
        
        // Check if process is still running
        int result = waitpid(pid, &status, WNOHANG);
        end_time = get_time_ms();
        long runtime = end_time - start_time;
        
        // Read any output from pipe (to check for death messages)
        char buffer[1024];
        fcntl(pipefd[0], F_SETFL, O_NONBLOCK);
        int bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
        close(pipefd[0]);
        
        if (result == 0) {
            // Process still running - kill it and consider success
            kill(pid, SIGTERM);
            waitpid(pid, &status, 0);
            printf("Test %d: Pass [✓] - Process ran for %ldms (still running)\n", 
                   test_num, runtime);
            return 1;
        } else {
            // Process terminated - check why and how long it ran
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                // Check if there's a death message in output
                if (strstr(buffer, "died") != NULL) {
                    printf("Test %d: Fail [x] - Philosopher died after %ldms\n", 
                           test_num, runtime);
                    return 0;
                }
            }
            
            if (runtime < expected_min_runtime) {
                printf("Test %d: Fail [x] - Process terminated too early (%ldms)\n", 
                       test_num, runtime);
                return 0;
            } else {
                printf("Test %d: Pass [✓] - Process completed successfully after %ldms\n", 
                       test_num, runtime);
                return 1;
            }
        }
    } else {
        printf("Test %d: Fail [x] - Fork failed\n", test_num);
        return 0;
    }
}

// Detailed stress tests that check for early deaths
MU_TEST(test_detailed_stress_1) {
    int result = run_detailed_stress_test(1, 199, 610, 200, 200, 10, 500);
    mu_assert("Detailed stress test 1 failed", result == 1);
    return 0;
}

MU_TEST(test_detailed_stress_2) {
    int result = run_detailed_stress_test(2, 199, 610, 200, 200, 10, 500);
    mu_assert("Detailed stress test 2 failed", result == 1);
    return 0;
}

MU_TEST(test_detailed_stress_3) {
    int result = run_detailed_stress_test(3, 199, 610, 200, 200, 10, 500);
    mu_assert("Detailed stress test 3 failed", result == 1);
    return 0;
}

MU_TEST(test_detailed_stress_4) {
    int result = run_detailed_stress_test(4, 199, 610, 200, 200, 10, 500);
    mu_assert("Detailed stress test 4 failed", result == 1);
    return 0;
}

MU_TEST(test_detailed_stress_5) {
    int result = run_detailed_stress_test(5, 199, 610, 200, 200, 10, 500);
    mu_assert("Detailed stress test 5 failed", result == 1);
    return 0;
}

// Test with tighter timing constraints to stress test more
MU_TEST(test_tight_timing_1) {
    int result = run_detailed_stress_test(6, 100, 400, 200, 200, 5, 300);
    mu_assert("Tight timing test 1 failed", result == 1);
    return 0;
}

MU_TEST(test_tight_timing_2) {
    int result = run_detailed_stress_test(7, 150, 500, 150, 150, 3, 400);
    mu_assert("Tight timing test 2 failed", result == 1);
    return 0;
}

MU_TEST_SUITE(test_suite) {
    printf("Running detailed stress tests with output analysis:\n");
    MU_RUN_TEST(test_detailed_stress_1);
    MU_RUN_TEST(test_detailed_stress_2);
    MU_RUN_TEST(test_detailed_stress_3);
    MU_RUN_TEST(test_detailed_stress_4);
    MU_RUN_TEST(test_detailed_stress_5);
    printf("Running tight timing tests:\n");
    MU_RUN_TEST(test_tight_timing_1);
    MU_RUN_TEST(test_tight_timing_2);
}

int main(void) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
