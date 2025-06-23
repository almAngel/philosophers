/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:26:46 by angellop          #+#    #+#             */
/*   Updated: 2025/06/23 12:13:27 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				someone_died;
	long			start_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal;
	int				meals_eaten;
	int				is_full;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

int		ft_atoi(const char *nptr);
int		validate_args(int ac, char **av);
int		init_simulation(t_data *data, t_philo **philos);
void	*philo_routine(void *arg);
int		start_simulation(t_data *data, t_philo *philos);
long	get_time_ms(void);
void	print_action(t_philo *philo, const char *msg);
void	philo_take_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep_and_think(t_philo *philo);
void	*monitor_routine(void *arg);
void	unlock_all_forks(t_data *data);
long	get_timestamp_ms(long start_time);
int		lock_fork_with_check(pthread_mutex_t *fork, t_data *data);
void	philo_take_forks_lr(t_philo *philo, int left, int right, t_data *data);
void	philo_take_forks_rl(t_philo *philo, int left, int right, t_data *data);
void	philo_loop(t_philo *philo, t_data *data);
void	philo_one_entry(t_philo *philo);

#endif
