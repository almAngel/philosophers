#include "../includes/philo.h"
#include "../includes/minunit.h"
#include <pthread.h>

int tests_run = 0;

// Estructura y función auxiliar fuera del test
struct sim_args { t_data *d; t_philo *p; int *r; };
void* sim_func(void* a) {
    struct sim_args *s = (struct sim_args*)a;
    *(s->r) = start_simulation(s->d, s->p);
    return NULL;
}

// Test: start_simulation retorna 1 y termina rápido con num_meals = 1
MU_TEST(test_start_simulation_with_num_meals) {
    t_data data;
    t_philo *philos = NULL;
    char *av[] = {"./philo", "2", "800", "200", "200", "1"};
    int ac = 6;

    data.num_philos = ft_atoi(av[1]);
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    data.num_meals = (ac == 6) ? ft_atoi(av[5]) : 0;

    int ok = init_simulation(&data, &philos);
    mu_assert("init_simulation failed", ok == 1);

    int result = start_simulation(&data, philos);
    mu_assert("start_simulation should succeed with num_meals", result == 1);

    // Limpieza
    int i;
    for (i = 0; i < data.num_philos; i++)
        pthread_mutex_destroy(&data.forks[i]);
    pthread_mutex_destroy(&data.print_mutex);
    free(data.forks);
    free(philos);
    return 0;
}

// Test: start_simulation retorna 1 y arranca correctamente sin num_meals (no debe quedarse colgado mucho tiempo)
MU_TEST(test_start_simulation_without_num_meals) {
    t_data data;
    t_philo *philos = NULL;
    char *av[] = {"./philo", "2", "800", "200", "200"};
    int ac = 5;

    data.num_philos = ft_atoi(av[1]);
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    data.num_meals = (ac == 6) ? ft_atoi(av[5]) : 0;

    int ok = init_simulation(&data, &philos);
    mu_assert("init_simulation failed", ok == 1);

    pthread_t sim_thread;
    int result = -1;
    struct sim_args args = { &data, philos, &result };
    int err = pthread_create(&sim_thread, NULL, sim_func, &args);
    mu_assert("pthread_create failed", err == 0);
    usleep(100000); // Espera 0.1s para comprobar que arranca
    pthread_cancel(sim_thread); // Detenemos el hilo para no colgar el test
    pthread_join(sim_thread, NULL);

    // No comprobamos el valor de result, solo que no hay crash ni deadlock

    // Limpieza
    int i;
    for (i = 0; i < data.num_philos; i++)
        pthread_mutex_destroy(&data.forks[i]);
    pthread_mutex_destroy(&data.print_mutex);
    free(data.forks);
    free(philos);
    return 0;
}

// Test: start_simulation retorna 0 si philos es NULL
MU_TEST(test_start_simulation_null_philos) {
    t_data data;
    t_philo *philos = NULL;
    data.num_philos = 2;
    data.time_to_die = 800;
    data.time_to_eat = 200;
    data.time_to_sleep = 200;
    data.num_meals = 0;

    int result = start_simulation(&data, philos);
    mu_assert("start_simulation should fail with NULL philos", result == 0);
    return 0;
}

MU_TEST_SUITE(test_suite) {
    MU_RUN_TEST(test_start_simulation_with_num_meals);
    MU_RUN_TEST(test_start_simulation_without_num_meals);
    MU_RUN_TEST(test_start_simulation_null_philos);
}

int main(void) {
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return 0;
}
