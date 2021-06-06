/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_dying.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:47:15 by moharras          #+#    #+#             */
/*   Updated: 2021/06/06 12:48:54 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

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
			sem_wait(var->print_lock);
			printf("\033[0;31m%ld\t%d\tdied\033[0m\n",
				get_time() - var->begin_time, ph->fork + 1);
			sem_post(var->mut);
			return (NULL);
		}
		usleep(300);
	}
	return (NULL);
}

int	check_die(t_var *var, t_philo *ph)
{
	pthread_create(&(var->thread), NULL, &philo_dying, ph);
	pthread_detach(var->thread);
	usleep(100);
	return (0);
}

void	lock_forks_and_eat(t_var *var, t_philo *ph)
{
	sem_wait(var->chopsticks);
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		var->print_lock, "has taken a fork");
	sem_wait(var->chopsticks);
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		var->print_lock, "has taken 2nd fork");
	ph->ph_old = get_time() + var->timetodie;
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		var->print_lock, "\033[0;32mis eating\033[0m");
	usleep(var->timetoeat * 1000);
	sem_post(var->chopsticks);
	sem_post(var->chopsticks);
	if (var->nb_ph_must_eat != -101)
		ph->eat_count++;
}

void	*check_eating(void *arg)
{
	t_var	*var;

	var = (t_var *)arg;
	if (var->nb_ph_must_eat != -101)
	{
		while (1)
		{
			sem_wait(var->sem_eat);
			var->counter++;
			if (var->counter == var->nb_ph)
			{
				sem_wait(var->print_lock);
				printf("\033[0;35mdone\033[0m\n");
				sem_post(var->mut);
				break ;
			}
			usleep(100);
		}
	}
	return (NULL);
}
