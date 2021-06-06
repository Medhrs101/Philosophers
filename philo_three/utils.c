/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:46:51 by moharras          #+#    #+#             */
/*   Updated: 2021/06/06 12:28:20 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	ft_print(int timestamp, int num_philo, sem_t *print_lock, char const *s)
{
	sem_wait(print_lock);
	printf("%d\t%d\t%s\t\n", timestamp, num_philo, s);
	sem_post(print_lock);
}

t_var	*get_struct_var(t_var *var)
{
	static t_var	*tmp;

	if (var)
		tmp = var;
	return (tmp);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_philo	*get_philo(int *i)
{
	t_philo	*ph;

	ph = (t_philo *)malloc(sizeof(t_philo));
	ph->fork = *i;
	ph->eat_count = 0;
	return (ph);
}
