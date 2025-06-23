/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:15:00 by angellop          #+#    #+#             */
/*   Updated: 2025/06/23 09:15:09 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	unlock_all_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_mutex_unlock(&data->forks[i++]);
}

static int	check_death_and_full(t_data *data, t_philo *philos, int *full_count)
{
	int		i;
	long	now;
	long	timestamp;

	i = 0;
	*full_count = 0;
	while (i < data->num_philos)
	{
		now = get_time_ms();
		if (now - philos[i].last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			timestamp = get_timestamp_ms(data->start_time);
			printf("%ld %d died\n", timestamp, philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			data->someone_died = 1;
			unlock_all_forks(data);
			return (1);
		}
		if (data->num_meals > 0 && philos[i].is_full)
			(*full_count)++;
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	t_philo	*philos;
	int		full_count;

	data = ((t_philo *)arg)->data;
	philos = (t_philo *)arg;
	while (!data->someone_died)
	{
		if (check_death_and_full(data, philos, &full_count))
			return (0);
		if (data->num_meals > 0 && full_count == data->num_philos)
			return (0);
		usleep(1000);
	}
	return (0);
}
