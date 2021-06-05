/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semphore.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moharras <moharras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:51:10 by moharras          #+#    #+#             */
/*   Updated: 2021/06/05 16:06:56 by moharras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosopher.h"

void	creat_semaphore(t_var *var)
{
	sem_unlink(CHOPST);
	var->chopsticks = sem_open(CHOPST, O_CREAT, 600, var->nb_ph);
	sem_unlink(MUT);
	var->mut = sem_open(MUT, O_CREAT, 600, 1);
	sem_unlink(PRINT);
	var->print_lock = sem_open(PRINT, O_CREAT, 600, 1);
	sem_unlink(EAT);
	var->sem_eat = sem_open(EAT, O_CREAT, 600, 0);
}

void	clear_all(t_var *var)
{
	int	i;

	sem_unlink(CHOPST);
	sem_unlink(MUT);
	sem_unlink(PRINT);
	i = -1;
	while (++i < var->nb_ph)
		kill (var->pid[i], SIGKILL);
	free(var->pid);
	free(var);
}
