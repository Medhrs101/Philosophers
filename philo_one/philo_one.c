/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:07:52 by moharras          #+#    #+#             */
/*   Updated: 2021/06/06 12:50:30 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	sleeping_and_thinking_philo(t_var *var, t_philo *ph)
{
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		&var->print_lock, "\033[0;33mis sleeping\033[0m");
	usleep(var->timetosleep * 1000);
	ft_print(get_time() - var->begin_time, ph->fork + 1,
		&var->print_lock, "\033[0;34mis thinking\033[0m");
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
		sleeping_and_thinking_philo(var, ph);
		if (ph->eat_count == var->nb_ph_must_eat)
			var->counter++;
	}
	free(ph);
	return (NULL);
}

int	create_threads(t_var *var)
{
	int	i;

	i = -1;
	var->chopsticks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * var->nb_ph);
	while (++i < var->nb_ph)
		pthread_mutex_init(&(var->chopsticks[i]), NULL);
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
	pthread_mutex_init(&var->mut, NULL);
	pthread_mutex_init(&var->print_lock, NULL);
	var->begin_time = get_time();
	var->counter = 0;
	if (ac != 5 && ac != 6)
	{
		mutex_clear(var, 2);
		free(var);
		printf("\033[0;31mArguments Error\033[0m\n");
		return (1);
	}
	if (fill_args(var, ac, av))
		return (1);
	pthread_mutex_lock(&var->mut);
	create_threads(var);
	pthread_mutex_lock(&var->mut);
	mutex_clear(var, 3);
	return (0);
}
