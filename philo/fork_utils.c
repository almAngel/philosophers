/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:08:10 by angellop          #+#    #+#             */
/*   Updated: 2025/06/23 12:08:26 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	lock_fork_with_check(pthread_mutex_t *fork, t_data *data)
{
	pthread_mutex_lock(fork);
	if (data->someone_died)
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	return (1);
}

void	philo_take_forks_lr(t_philo *philo, int left, int right, t_data *data)
{
	if (!lock_fork_with_check(&data->forks[left], data))
		return ;
	if (data->num_philos == 2)
	{
		print_action(philo, "has taken a fork");
		usleep(1000);
		if (!lock_fork_with_check(&data->forks[right], data))
		{
			pthread_mutex_unlock(&data->forks[left]);
			return ;
		}
		print_action(philo, "has taken a fork");
		return ;
	}
	print_action(philo, "has taken a fork");
	if (!lock_fork_with_check(&data->forks[right], data))
	{
		pthread_mutex_unlock(&data->forks[left]);
		return ;
	}
	print_action(philo, "has taken a fork");
}

void	philo_take_forks_rl(t_philo *philo, int left, int right, t_data *data)
{
	if (!lock_fork_with_check(&data->forks[right], data))
		return ;
	if (data->num_philos == 2)
	{
		print_action(philo, "has taken a fork");
		usleep(1000);
		if (!lock_fork_with_check(&data->forks[left], data))
		{
			pthread_mutex_unlock(&data->forks[right]);
			return ;
		}
		print_action(philo, "has taken a fork");
		return ;
	}
	print_action(philo, "has taken a fork");
	if (!lock_fork_with_check(&data->forks[left], data))
	{
		pthread_mutex_unlock(&data->forks[right]);
		return ;
	}
	print_action(philo, "has taken a fork");
}
