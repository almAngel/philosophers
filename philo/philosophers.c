/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:26:43 by angellop          #+#    #+#             */
/*   Updated: 2025/06/15 16:18:52 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	validate_args(int ac, char **av)
{
	int	i;

	if (!av || (ac != 5 && ac != 6))
		return (0);
	i = 1;
	while (i < ac)
		if (!av[i] || ft_atoi(av[i++]) <= 0)
			return (0);
	return (1);
}

static void	philo_one_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	while (!philo->data->someone_died)
		usleep(1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->num_philos == 1)
	{
		philo_one_routine(philo);
		return (0);
	}
	while (!data->someone_died)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		philo_sleep_and_think(philo);
	}
	return (0);
}

int	start_simulation(t_data *data, t_philo *philos)
{
	int			i;
	pthread_t	monitor;

	if (!data || !philos)
		return (0);
	data->start_time = get_time_ms();
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].last_meal = data->start_time;
		if (pthread_create(&philos[i].thread,
				NULL, philo_routine, &philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
		return (0);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philos)
		pthread_join(philos[i++].thread, NULL);
	return (1);
}
