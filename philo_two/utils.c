/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:29:19 by moharras          #+#    #+#             */
/*   Updated: 2021/06/05 15:30:19 by moharras         ###   ########.fr       */
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

void	clear_sem(t_var *var)
{
	sem_unlink(CHOPST);
	sem_unlink(MUT);
	sem_unlink(PRINT);
	free(var);
}

void	ft_print(int timestamp, int nb_ph, sem_t *p_l, char const *s)
{
	sem_wait(p_l);
	printf("%d\t%d\t%s\t\n", timestamp, nb_ph, s);
	sem_post(p_l);
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
