/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:15:00 by angellop          #+#    #+#             */
/*   Updated: 2025/06/23 12:07:52 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	print_action(t_philo *philo, const char *msg)
{
	long	timestamp;

	if (philo->data->someone_died)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_timestamp_ms(philo->data->start_time);
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_take_forks(t_philo *philo)
{
	t_data	*data;
	int		left;
	int		right;

	data = philo->data;
	left = philo->left_fork;
	right = philo->right_fork;
	if (data->someone_died)
		return ;
	if (left < right)
		philo_take_forks_lr(philo, left, right, data);
	else
		philo_take_forks_rl(philo, left, right, data);
}

void	philo_eat(t_philo *philo)
{
	if (philo->data->someone_died)
		return ;
	philo->last_meal = get_time_ms();
	print_action(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	philo->meals_eaten++;
	if (philo->data->num_meals > 0
		&& philo->meals_eaten >= philo->data->num_meals)
		philo->is_full = 1;
}

void	philo_sleep_and_think(t_philo *philo)
{
	if (philo->data->someone_died)
		return ;
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	if (philo->data->someone_died)
		return ;
	print_action(philo, "is thinking");
}
