/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:17:47 by angellop          #+#    #+#             */
/*   Updated: 2025/06/27 14:09:13 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static void	philo_one_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	while (!philo->data->someone_died)
		usleep(1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

static int	philo_check_and_unlock(t_philo *philo, t_data *data,
		int has_left, int has_right)
{
	int	is_full;

	pthread_mutex_lock(&philo->data_mutex);
	is_full = philo->is_full;
	pthread_mutex_unlock(&philo->data_mutex);
	if (is_full || data->someone_died)
	{
		if (has_left)
			pthread_mutex_unlock(&data->forks[philo->left_fork]);
		if (has_right)
			pthread_mutex_unlock(&data->forks[philo->right_fork]);
		return (1);
	}
	return (0);
}

static void	philo_iteration(t_philo *philo, t_data *data)
{
	int	has_left;
	int	has_right;

	has_left = 0;
	has_right = 0;
	usleep(philo->id * 10);
	if (philo->id % 2 == 0)
		usleep(200);
	philo_take_forks(philo);
	has_left = 1;
	has_right = 1;
	if (philo_check_and_unlock(philo, data, has_left, has_right))
		return ;
	philo_eat(philo);
	if (has_left)
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
	if (has_right)
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
	usleep(100);
	philo_sleep_and_think(philo);
}

void	philo_loop(t_philo *philo, t_data *data)
{
	int	is_full;

	pthread_mutex_lock(&philo->data_mutex);
	is_full = philo->is_full;
	pthread_mutex_unlock(&philo->data_mutex);
	while (!data->someone_died && !is_full)
	{
		philo_iteration(philo, data);
		pthread_mutex_lock(&philo->data_mutex);
		is_full = philo->is_full;
		pthread_mutex_unlock(&philo->data_mutex);
	}
}

void	philo_one_entry(t_philo *philo)
{
	philo_one_routine(philo);
}
