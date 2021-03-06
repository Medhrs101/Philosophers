/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 15:26:47 by ymarji            #+#    #+#             */
/*   Updated: 2021/06/06 12:25:56 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <semaphore.h>
# include <sys/time.h>
# define CHOPST "chopst"
# define MUT "mut"
# define PRINT "print"

typedef struct s_philo
{	
	int		fork;
	long	ph_old;
	int		eat_count;
}				t_philo;

typedef struct s_var
{
	int			counter;
	int			nb_ph;
	int			timetodie;
	int			timetoeat;
	int			timetosleep;
	int			nb_ph_must_eat;
	long		begin_time;
	pthread_t	thread;
	sem_t		*chopsticks;
	sem_t		*mut;
	sem_t		*print_lock;
}				t_var;

int		ft_atoi(const char *str);
int		check_args(t_var *var, int ac);
int		fill_args(t_var *var, int ac, char **av);
void	creat_sem(t_var *var);
void	*philo_dying(void *v_ph);
void	lock_forks_and_eat(t_var *var, t_philo *ph);
int		check_die(t_var *var, t_philo *ph);
t_philo	*get_philo(int *i);
void	clear_sem(t_var *var);
void	ft_print(int timestamp, int nb_ph, sem_t *p_l, char const *s);
t_var	*get_struct_var(t_var *var);
long	get_time(void);

#endif
