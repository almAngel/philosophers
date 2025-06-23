#include "../includes/philo.h"
#include "../includes/minunit.h"
#include <pthread.h>

int tests_run = 0;

// Test: inicialización de t_data desde argumentos
MU_TEST(test_data_init_from_args) {
    t_data data;
    char *av[] = {"./philo", "5", "800", "200", "200", "7"};
    int ac = 6;

    data.num_philos = ft_atoi(av[1]);
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    data.num_meals = (ac == 6) ? ft_atoi(av[5]) : 0;

    mu_assert("num_philos != 5", data.num_philos == 5);
    mu_assert("time_to_die != 800", data.time_to_die == 800);
    mu_assert("time_to_eat != 200", data.time_to_eat == 200);
    mu_assert("time_to_sleep != 200", data.time_to_sleep == 200);
    mu_assert("num_meals != 7", data.num_meals == 7);
    return 0;
}

// Test: inicialización de t_data sin argumento opcional
MU_TEST(test_data_init_no_optional) {
    t_data data;
    char *av[] = {"./philo", "4", "800", "200", "200"};
    int ac = 5;

    data.num_philos = ft_atoi(av[1]);
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    data.num_meals = (ac == 6) ? ft_atoi(av[5]) : 0;

    mu_assert("num_philos != 4", data.num_philos == 4);
    mu_assert("num_meals != 0", data.num_meals == 0);
    return 0;
}

// Test: init_simulation inicializa correctamente
MU_TEST(test_init_simulation_success) {
    t_data data;
    t_philo *philos = NULL;
    char *av[] = {"./philo", "3", "800", "200", "200"};
    int ac = 5;

    data.num_philos = ft_atoi(av[1]);
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    data.num_meals = (ac == 6) ? ft_atoi(av[5]) : 0;

    int result = init_simulation(&data, &philos);
    mu_assert("init_simulation should succeed", result == 1);
    mu_assert("forks should not be NULL", data.forks != NULL);
    mu_assert("philos should not be NULL", philos != NULL);

    // Limpieza
    int i;
    for (i = 0; i < data.num_philos; i++)
        pthread_mutex_destroy(&data.forks[i]);
    pthread_mutex_destroy(&data.print_mutex);
    free(data.forks);
    free(philos);
    return 0;
}

// Test: init_simulation falla con 0 filósofos
MU_TEST(test_init_simulation_fail_zero_philos) {
    t_data data;
    t_philo *philos = NULL;
    data.num_philos = 0;
    data.time_to_die = 800;
    data.time_to_eat = 200;
    data.time_to_sleep = 200;
    data.num_meals = 0;
    int result = init_simulation(&data, &philos);
    mu_assert("init_simulation should fail with 0 philosophers", result == 0);
    mu_assert("forks should be NULL", data.forks == NULL);
    mu_assert("philos should be NULL", philos == NULL);
    return 0;
}

// Test: init_simulation con 1 filósofo (caso límite)
MU_TEST(test_init_simulation_one_philo) {
    t_data data;
    t_philo *philos = NULL;
    data.num_philos = 1;
    data.time_to_die = 800;
    data.time_to_eat = 200;
    data.time_to_sleep = 200;
    data.num_meals = 0;
    int result = init_simulation(&data, &philos);
    mu_assert("init_simulation should succeed with 1 philosopher", result == 1);
    mu_assert("forks should not be NULL", data.forks != NULL);
    mu_assert("philos should not be NULL", philos != NULL);
    pthread_mutex_destroy(&data.forks[0]);
    pthread_mutex_destroy(&data.print_mutex);
    free(data.forks);
    free(philos);
    return 0;
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_data_init_from_args);
    MU_RUN_TEST(test_data_init_no_optional);
    MU_RUN_TEST(test_init_simulation_success);
    MU_RUN_TEST(test_init_simulation_fail_zero_philos);
    MU_RUN_TEST(test_init_simulation_one_philo);
}

int main(void) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
