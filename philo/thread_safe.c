/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:33 by angellop          #+#    #+#             */
/*   Updated: 2025/07/03 12:21:18 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}

void	set_death_flag(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

long	get_last_meal_time(t_philo *philo)
{
	long	result;

	pthread_mutex_lock(&philo->data->meal_mutex);
	result = philo->last_meal;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (result);
}
