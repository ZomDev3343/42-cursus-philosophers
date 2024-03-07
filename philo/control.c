/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:10:50 by truello           #+#    #+#             */
/*   Updated: 2024/03/07 14:17:40 by tohma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *buf)
{
	t_philo	*philo;

	philo = (t_philo *) buf;
	MTX_LOCK(philo->philos_mtx + (philo->id - 1));
	if (philo->last_meal_time.tv_sec == 0)
		philo->last_meal_time = timestamp();
	while (!philo->must_stop)
	{
		MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
		philo_take_fork(philo);
		MTX_LOCK(philo->philos_mtx + (philo->id - 1));
	}
	MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
	return (NULL);
}

void	change_state(t_philo *philo, enum e_philo_state newstate)
{
	struct timeval	ts;
	int				philo_id;

	ts = timestamp();
	MTX_LOCK(philo->philos_mtx + (philo->id - 1));
	philo->state = newstate;
	philo_id = philo->id;
	MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
	MTX_LOCK(philo->philos_mtx + philo->infos->philo_amt);
	if (newstate == TAKEN_FORK)
		printf("%ld%03ld %d has taken a fork\n",
			ts.tv_sec, ts.tv_usec / 1000, philo_id);
	else if (newstate == EATING)
		printf("%ld%03ld %d is eating\n", ts.tv_sec,
			ts.tv_usec / 1000, philo_id);
	else if (newstate == SLEEPING)
		printf("%ld%03ld %d is sleeping\n",
			ts.tv_sec, ts.tv_usec / 1000, philo_id);
	else if (newstate == THINKING)
		printf("%ld%03ld %d is thinking\n",
			ts.tv_sec, ts.tv_usec / 1000, philo_id);
	else
		printf("%ld%03ld %d died\n", ts.tv_sec, ts.tv_usec / 1000, philo_id);
	MTX_UNLOCK(philo->philos_mtx + philo->infos->philo_amt);
}

void	philo_take_fork(t_philo *philo)
{
	MTX_LOCK(philo->forks + (philo->id - 1));
	MTX_LOCK(philo->philos_mtx + (philo->id - 1));
	if (philo->must_stop)
		return (MTX_UNLOCK(philo->philos_mtx + (philo->id - 1)),
			MTX_UNLOCK(philo->forks + (philo->id - 1)), (void) 0);
	MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
	if (philo->infos->philo_amt > 1)
	{
		MTX_LOCK(philo->forks
			+ (philo->id * (philo->id != philo->infos->philo_amt)));
		MTX_LOCK(philo->philos_mtx + (philo->id - 1));
		if (philo->must_stop)
			return (MTX_UNLOCK(philo->philos_mtx + (philo->id - 1)),
				MTX_UNLOCK(philo->forks
					+ (philo->id * (philo->id != philo->infos->philo_amt))),
				MTX_UNLOCK(philo->forks + (philo->id - 1)),
				(void) 0);
		MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
	}
	change_state(philo, TAKEN_FORK);
	philo_eat(philo);
}

static void	put_fork(t_philo *philo)
{
	if (philo->infos->philo_amt > 1)
		MTX_UNLOCK(philo->forks
			+ (philo->id * (philo->id != philo->infos->philo_amt)));
	MTX_UNLOCK(philo->forks + (philo->id - 1));
}

void	philo_eat(t_philo *philo)
{
	MTX_LOCK(philo->philos_mtx + (philo->id - 1));
	if (philo->must_stop)
		return (MTX_UNLOCK(philo->philos_mtx + (philo->id - 1)),
			MTX_UNLOCK(philo->forks + (philo->id - 1)),
			MTX_UNLOCK(philo->forks + (philo->id
					* (philo->id != philo->infos->philo_amt))), (void) 0);
	MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
	change_state(philo, EATING);
	MTX_LOCK(philo->philos_mtx + philo->id - 1);
	philo->last_meal_time = timestamp();
	MTX_UNLOCK(philo->philos_mtx + philo->id - 1);
	usleep(philo->infos->time_to_eat * 1000);
	MTX_LOCK(philo->philos_mtx + (philo->id - 1));
	philo->last_meal_time = timestamp();
	philo->times_eaten++;
	MTX_UNLOCK(philo->philos_mtx + (philo->id - 1));
	put_fork(philo);
	if (philo->must_stop)
		return ;
	philo_sleep(philo);
}
