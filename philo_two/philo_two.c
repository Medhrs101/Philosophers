/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:32:48 by moharras          #+#    #+#             */
/*   Updated: 2021/06/05 16:04:24 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	sleeping_and_thinking_philo(t_var *var, t_philo *ph)
{
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		var->print_lock, "\033[0;33mis sleeping\033[0m");
	usleep(var->timetosleep * 1000);
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		var->print_lock, "\033[0;34mis thinking\033[0m");
}

void	*philosophize(void *v_ph)
{
	t_var	*var;
	t_philo	*ph;

	ph = (t_philo *)v_ph;
	var = get_struct_var(NULL);
	ph->ph_old = get_time() + var->timetodie;
	check_die(var, ph);
	while (1)
	{
		lock_forks_and_eat(var, ph);
		if (ph->eat_count == var->nb_ph_must_eat)
		{
			var->counter++;
			break ;
		}
		sleeping_and_thinking_philo(var, ph);
	}
	free(ph);
	return (NULL);
}

int	create_threads(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->nb_ph)
	{
		pthread_create(&(var->thread), NULL, &philosophize, get_philo(&i));
		pthread_detach(var->thread);
		usleep(100);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	var = get_struct_var(var);
	var->begin_time = get_time();
	var->counter = 0;
	if (ac != 5 && ac != 6)
	{
		free(var);
		printf("\033[0;31mArguments Error\033[0m\n");
		return (1);
	}
	if (fill_args(var, ac, av))
		return (1);
	creat_sem(var);
	sem_wait (var->mut);
	create_threads(var);
	sem_wait (var->mut);
	clear_sem(var);
	return (0);
}
