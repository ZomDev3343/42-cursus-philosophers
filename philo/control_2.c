/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:56:23 by truello           #+#    #+#             */
/*   Updated: 2024/03/07 13:31:46 by tohma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	MTX_LOCK(philo->philos_mtx + (philo->id - 1));
	if (philo->must_stop)
		return (MTX_UNLOCK(philo->philos_mtx + (philo->id - 1)), (void) 0);
	MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
	change_state(philo, SLEEPING);
	usleep(philo->infos->time_to_sleep * 1000);
	MTX_LOCK(philo->philos_mtx + (philo->id - 1));
	if (philo->must_stop)
		return (MTX_UNLOCK(philo->philos_mtx + (philo->id - 1)), (void) 0);
	MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
	change_state(philo, THINKING);
}

int	is_philo_dead(t_philo *philo)
{
	return (get_time_diff(timestamp(), philo->last_meal_time)
		> philo->infos->time_to_die);
}
