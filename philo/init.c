/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:44:17 by angellop          #+#    #+#             */
/*   Updated: 2025/06/23 08:57:17 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static void	init_philos_structs(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % data->num_philos;
		philos[i].meals_eaten = 0;
		philos[i].is_full = 0;
		philos[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->num_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

int	init_simulation(t_data *data, t_philo **philos)
{
	if (!data || !philos || data->num_philos < 1)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (0);
	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
	{
		free(data->forks);
		data->forks = NULL;
		return (0);
	}
	data->someone_died = 0;
	init_philos_structs(data, *philos);
	return (1);
}
