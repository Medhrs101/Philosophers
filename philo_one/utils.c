/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:16:34 by moharras          #+#    #+#             */
/*   Updated: 2021/06/05 15:30:28 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

t_philo	*get_philo(int *i)
{
	t_philo	*ph;

	ph = (t_philo *)malloc(sizeof(t_philo));
	ph->fork = *i;
	ph->eat_count = 0;
	return (ph);
}

void	mutex_clear(t_var *var, int n)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&var->print_lock);
	pthread_mutex_destroy(&var->mut);
	if (n == 3)
	{
		while (++i)
			pthread_mutex_destroy(&(var->chopsticks[i]));
	}
}

void	ft_print(int timestamp, int n_p, pthread_mutex_t *p, char const *s)
{
	pthread_mutex_lock(p);
	printf("%d\t%d\t%s\t\n", timestamp, n_p, s);
	pthread_mutex_unlock(p);
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
