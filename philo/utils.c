/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:39:54 by angellop          #+#    #+#             */
/*   Updated: 2025/06/23 08:00:46 by angellop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	skip_spaces(const char *s, int i)
{
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	return (i);
}

static int	is_valid_int(unsigned long long n, int sign)
{
	if ((sign == 1 && n > 2147483647ULL) || (sign == -1 && n > 2147483648ULL))
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int					i;
	int					sign;
	unsigned long long	n;

	i = 0;
	sign = 1;
	n = 0;
	if (!nptr)
		return (0);
	i = skip_spaces(nptr, i);
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
		n = n * 10 + (nptr[i++] - '0');
	i = skip_spaces(nptr, i);
	if (nptr[i] != '\0' || !is_valid_int(n, sign))
		return (0);
	return ((int)(n * sign));
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_timestamp_ms(long start_time)
{
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (now - start_time);
}
