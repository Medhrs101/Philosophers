/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:26:47 by ymarji            #+#    #+#             */
/*   Updated: 2021/06/05 15:14:47 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{	
	int		fork;
	long	ph_old;
	int		eat_count;
}				t_philo;

typedef struct s_var
{
	int				counter;
	int				nb_ph;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				nb_ph_must_eat;
	long			begin_time;
	pthread_t		thread;
	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	mut;
	pthread_mutex_t	print_lock;
}				t_var;

int		ft_atoi(const char *str);
int		check_args(t_var *var, int ac);
int		fill_args(t_var *var, int ac, char **av);
int		check_die(t_var *var, t_philo *ph);
void	lock_forks_and_eat(t_var *var, t_philo *ph);
void	*philo_dying(void *v_ph);
t_philo	*get_philo(int *i);
void	mutex_clear(t_var *var, int n);
void	ft_print(int timestamp, int n_p, pthread_mutex_t *p, char const *s);
t_var	*get_struct_var(t_var *var);
long	get_time(void);

#endif
