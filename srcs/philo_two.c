#include "../philosopher.h"
#include <sys/time.h>
#include <semaphore.h>

void	ft_print(int timestamp, int num_philo, pthread_mutex_t *print_lock, char const *s)
{
	pthread_mutex_lock(print_lock);
	printf("%d\t%d\t%s\t\n", timestamp, num_philo, s);
	pthread_mutex_unlock(print_lock);
}

int		check_args(t_var *var, int ac)
{
	if (var->nb_ph <= 0 || var->timetodie <= 0 || var->timetosleep <= 0 || (ac == 6 && var->nb_ph_must_eat <= 0 ))
		return (1);
	return (0);
}

int	fill_args(t_var *var, int ac, char **av)
{
	var->nb_ph = ft_atoi(av[1]);
	var->timetodie = ft_atoi(av[2]);
	var->timetoeat = ft_atoi(av[3]);
	var->timetosleep = ft_atoi(av[4]);
	if (ac == 6)
		var->nb_ph_must_eat = ft_atoi(av[5]);
	else
		var->nb_ph_must_eat = -101;
	if(check_args(var, ac))
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}

t_var	*get_struct_var(t_var *var)
{
	static t_var	*tmp;

	if (var)
		tmp = var;
	return (tmp);
}

long		get_time()
{
	long old;
	struct timeval time;
	old = gettimeofday(&time, NULL);
	if (old == -1)
		printf("%s", "Eror : gettimeofday Failed\n");
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleeping_philo(t_var *var, t_philo *ph)
{
	ft_print(get_time() - var->begin_time, ph->fork + 1, &var->print_lock, "\033[0;33mis sleeping\033[0m");
	usleep(var->timetosleep * 1000);
	ft_print(get_time() - var->begin_time, ph->fork + 1, &var->print_lock, "\033[0;34mis thinking\033[0m");
}

void	*philo_dying(void *v_ph)
{
	t_var *var = get_struct_var(NULL);
	t_philo *ph = (t_philo *)v_ph;
	while(1)
	{
		if ((get_time() > ph->ph_old))
		{
			pthread_mutex_lock(&var->print_lock);
			printf("\033[0;31m%ld\t%d\tdied\033[0m\n", get_time() - var->begin_time, ph->fork + 1);
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

int	check_die(t_var *var, t_philo *ph)
{
	pthread_create(&(var->thread), NULL, &philo_dying, ph);
	pthread_detach(var->thread);
	usleep(100);
	return(0);
}

void lock_forks(t_var *var, t_philo *ph)
{
	pthread_mutex_lock(&(var->chopsticks[ph->fork]));
	ft_print(get_time() - var->begin_time, ph->fork + 1, &var->print_lock, "has taken a fork");
	pthread_mutex_lock(&(var->chopsticks[(ph->fork + 1) % var->nb_ph]));
	ft_print(get_time() - var->begin_time, ph->fork + 1, &var->print_lock, "has taken 2nd fork");
}

void	*philosophize(void *v_ph)
{
	t_var *var = get_struct_var(NULL);
	t_philo *ph;
	ph = (t_philo *)v_ph;

	ph->ph_old = get_time() + var->timetodie;
	check_die(var, ph);
	while(1)
	{
		lock_forks(var, ph);
		ph->ph_old = get_time() + var->timetodie;
		ft_print(get_time() - var->begin_time, ph->fork + 1, &var->print_lock,  "\033[0;32mis eating\033[0m");		
		usleep(var->timetoeat * 1000);
		pthread_mutex_lock(&var->print_lock);
		pthread_mutex_unlock(&var->print_lock);
		pthread_mutex_unlock(&(var->chopsticks[ph->fork]));
		pthread_mutex_unlock(&(var->chopsticks[(ph->fork + 1) % var->nb_ph]));
		if (var->nb_ph_must_eat > 0)
		{
			pthread_mutex_lock(&var->print_lock);
			ph->eat_count++;
			pthread_mutex_unlock(&var->print_lock);
		}
		if (var->nb_ph_must_eat > 0 && (ph->eat_count == var->nb_ph_must_eat))
		{
			pthread_mutex_lock(&var->print_lock);
			printf("%ld\t%d\t\t\t\033[0;31mfinished number of eating times\033[0m\n", get_time() - var->begin_time, ph->fork + 1);
			var->counter++;
			pthread_mutex_unlock(&var->print_lock);
			break;
		}
		sleeping_philo(var, ph);
	}
	return (NULL);
}

t_philo *get_philo(int *i)
{
	t_philo *ph;
	ph = (t_philo *)malloc(sizeof(t_philo));
	ph->fork = *i;
	ph->eat_count = 0;
	return(ph);
}

int	create_threads(t_var *var)
{
	int i;

	i = 0;
	var->chopsticks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->nb_ph);
	while (i < var->nb_ph)
	{
		pthread_mutex_init(&(var->chopsticks[i]), NULL);
		i++;
	}
	i = 0;
	while(i < var->nb_ph)
	{
		if (pthread_create(&(var->thread), NULL, &philosophize, get_philo(&i)) != 0)
		{
			printf ("Error : Failed to create thread\n");
			return (1);
		}
		if (pthread_detach(var->thread) != 0)
		{
			printf("Error in pthread_detach\n");
			return (2);
		}
		usleep(100);
		i++;
	}
	/* i = 0;
	while (i < ph->nb_ph)
	{
		if (pthread_join(ph->tb_thread[i], NULL) != 0)
		{
			printf("Error in pthread_join\n");
			return (2);
		}
		printf("Thread %d has finished execution\n", i);
		i++;
	} */
	// pthread_mutex_destroy(ph->mutex);
	return (0);
}

int	main(int ac, char **av)
{
	(void)av;
	t_var *var;
	
	var = (t_var *)malloc(sizeof(t_var));
	var = get_struct_var(var);
	pthread_mutex_init(&var->mut, NULL);
	pthread_mutex_init(&var->print_lock, NULL);
	var->begin_time = get_time();
	var->counter = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Arguments Error\n");
		return (1);
	}
	if(fill_args(var, ac, av))
		return (1);
	pthread_mutex_lock(&var->mut);
	if(create_threads(var))
		return(1);
	pthread_mutex_lock(&var->mut);
	return (0);
}