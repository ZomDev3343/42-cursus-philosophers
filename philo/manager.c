/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:01:20 by truello           #+#    #+#             */
/*   Updated: 2024/03/05 16:24:01 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*is_one_philo_dead(t_philo *philosophers, int amount)
{
	int	time_diff;

	time_diff = get_time_diff(timestamp(),
			philosophers[amount - 1].last_meal_time);
	while (amount-- >= 0)
	{
		if (time_diff > philosophers->infos->time_to_die)
			return (philosophers + amount);
	}
	return (NULL);
}

void	*manager_loop(void *buf)
{
	int		i;
	int		loop;
	t_vars	*vars;
	t_philo	*dead;

	loop = TRUE;
	vars = (t_vars *) buf;
	while (loop)
	{
		i = -1;
		dead = is_one_philo_dead(vars->philos, vars->infos->philo_amt);
		if (dead)
		{
			change_state(dead, DEAD);
			while (++i < vars->infos->philo_amt)
				vars->philos->must_stop = TRUE;
			loop = FALSE;
		}
	}
	return (NULL);
}
