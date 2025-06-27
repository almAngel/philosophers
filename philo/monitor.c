/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:15:00 by angellop          #+#    #+#             */
/*   Updated: 2025/06/27 14:18:12 by angellop         ###   ########.fr       */
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

static int	check_philosopher_death(t_data *data, t_philo *philo, long now)
{
	long	last_meal_time;

	pthread_mutex_lock(&philo->data_mutex);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->data_mutex);
	if (now - last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", now - data->start_time, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		data->someone_died = 1;
		unlock_all_forks(data);
		return (1);
	}
	return (0);
}

static int	check_death_and_full(t_data *data, t_philo *philos, int *full_count)
{
	int		i;
	long	now;
	int		is_full;

	i = 0;
	*full_count = 0;
	now = get_time_ms();
	while (i < data->num_philos)
	{
		if (check_philosopher_death(data, &philos[i], now))
			return (1);
		pthread_mutex_lock(&philos[i].data_mutex);
		is_full = philos[i].is_full;
		pthread_mutex_unlock(&philos[i].data_mutex);
		if (data->num_meals > 0 && is_full)
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
