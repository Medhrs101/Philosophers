/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_dying.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:16:26 by moharras          #+#    #+#             */
/*   Updated: 2021/06/05 15:18:59 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

int	check_die(t_var *var, t_philo *ph)
{
	pthread_create(&(var->thread), NULL, &philo_dying, ph);
	pthread_detach(var->thread);
	usleep(100);
	return (0);
}

void	lock_forks_and_eat(t_var *var, t_philo *ph)
{
	pthread_mutex_lock(&(var->chopsticks[ph->fork]));
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		&var->print_lock, "has taken a fork");
	pthread_mutex_lock(&(var->chopsticks[(ph->fork + 1) % var->nb_ph]));
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		&var->print_lock, "has taken 2nd fork");
	ph->ph_old = get_time() + var->timetodie;
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		&var->print_lock, "\033[0;32mis eating\033[0m");
	usleep(var->timetoeat * 1000);
	pthread_mutex_unlock(&(var->chopsticks[ph->fork]));
	pthread_mutex_unlock(&(var->chopsticks[(ph->fork + 1) % var->nb_ph]));
	if (var->nb_ph_must_eat != -101)
		ph->eat_count++;
}

void	*philo_dying(void *v_ph)
{
	t_var	*var;
	t_philo	*ph;

	ph = (t_philo *)v_ph;
	var = get_struct_var(NULL);
	while (1)
	{
		if ((get_time() > ph->ph_old))
		{
			pthread_mutex_lock(&var->print_lock);
			printf("\033[0;31m%ld\t%d\tdied\033[0m\n",
				get_time() - var->begin_time, ph->fork + 1);
			pthread_mutex_unlock(&var->mut);
			return (NULL);
		}
		if (var->counter == var->nb_ph)
		{
			pthread_mutex_lock(&var->print_lock);
			printf("\033[0;35mdone\033[0m\n");
			pthread_mutex_unlock(&var->mut);
			return (NULL);
		}
		usleep(300);
	}
	return (NULL);
}
