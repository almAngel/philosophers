/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:26:43 by angellop          #+#    #+#             */
/*   Updated: 2025/07/03 13:05:25 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	validate_args(int ac, char **av)
{
	int	i;
	int	val;

	if (!av || (ac != 5 && ac != 6))
		return (0);
	i = 1;
	while (i < ac)
	{
		val = ft_atoi(av[i]);
		if (!av[i] || val <= 0)
			return (0);
		i++;
	}
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->num_philos == 1)
	{
		philo_one_entry(philo);
		return (0);
	}
	update_last_meal(philo);
	if (philo->id % 2 == 0)
		usleep(100);
	philo_loop(philo, data);
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
