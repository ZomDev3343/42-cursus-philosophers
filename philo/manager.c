/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:01:20 by truello           #+#    #+#             */
/*   Updated: 2024/03/06 17:36:11 by tohma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*is_one_philo_dead(t_philo *philosophers, int amount)
{
	int	time_diff;

	while (--amount >= 0)
	{
		time_diff = get_time_diff(timestamp(),
				philosophers[amount].last_meal_time);
		if (time_diff > philosophers->infos->time_to_die
			&& philosophers[amount].state != EATING
			&& philosophers[amount].last_meal_time.tv_sec > 0)
			return (philosophers + amount);
	}
	return (NULL);
}

static int	do_philos_ate_enough(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->infos->must_eat_times == 0)
		return (FALSE);
	while (++i < philo->infos->philo_amt)
		if (philo[i].times_eaten < philo->infos->must_eat_times)
			return (FALSE);
	return (TRUE);
}

static void	stop_philos(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < vars->infos->philo_amt)
	{
		MTX_LOCK(vars->philos_mtx + i);
		vars->philos[i].must_stop = TRUE;
		MTX_UNLOCK(vars->philos_mtx + i);
	}
}

void	*manager_loop(void *buf)
{
	int		loop;
	t_vars	*vars;
	t_philo	*dead;

	loop = TRUE;
	vars = (t_vars *) buf;
	while (loop)
	{
		dead = is_one_philo_dead(vars->philos, vars->infos->philo_amt);
		if (dead)
		{
			change_state(dead, DEAD);
			stop_philos(vars);
			loop = FALSE;
		}
		if (do_philos_ate_enough(vars->philos))
		{
			stop_philos(vars);
			loop = FALSE;
		}
	}
	return (NULL);
}
