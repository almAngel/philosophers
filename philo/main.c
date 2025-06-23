/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:25:58 by angellop          #+#    #+#             */
/*   Updated: 2025/06/23 09:05:55 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	free_all(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(philos);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	philos = NULL;
	if (!validate_args(ac, av))
		return (EXIT_FAILURE);
	data.num_philos = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.num_meals = ft_atoi(av[5]);
	else
		data.num_meals = 0;
	if (!init_simulation(&data, &philos))
		return (EXIT_FAILURE);
	if (!start_simulation(&data, philos))
		return (EXIT_FAILURE);
	free_all(&data, philos);
	return (0);
}
