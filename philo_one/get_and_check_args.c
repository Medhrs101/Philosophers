#include "./philosopher.h"

int	ft_atoi(const char *str)
{
	int	rslt;
	int	i;
	int	n;

	i = 0;
	n = 1;
	rslt = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (rslt == 2147483647 || rslt == -2147483648)
			return (0);
		rslt = (rslt * 10) + str[i] - '0';
		i++;
	}
	return (rslt * n);
}

int	check_args(t_var *var, int ac)
{
	if (var->nb_ph <= 0 || var->timetodie <= 0 || var->timetosleep <= 0
		|| (ac == 6 && var->nb_ph_must_eat <= 0 ))
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
	if (check_args(var, ac))
	{
		mutex_clear(var, 2);
		free(var);
		printf("\033[0;31mArguments Error\033[0m\n");
		return (1);
	}
	return (0);
}
