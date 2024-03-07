/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:10:50 by truello           #+#    #+#             */
/*   Updated: 2024/03/07 11:44:01 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *buf)
{
	t_philo	*philo;

	philo = (t_philo *) buf;
	if (philo->last_meal_time.tv_sec == 0)
	{
		MTX_LOCK(philo->philos_mtx + philo->id - 1);
		philo->last_meal_time = timestamp();
		MTX_UNLOCK(philo->philos_mtx + philo->id - 1);
	}
	while (!philo->must_stop)
		philo_take_fork(philo);
	return (NULL);
}

void	change_state(t_philo *philo, enum e_philo_state newstate)
{
	struct timeval	ts;

	if (philo->state == newstate)
		return ;
	ts = timestamp();
	MTX_LOCK(philo->philos_mtx + philo->id - 1);
	philo->state = newstate;
	MTX_UNLOCK(philo->philos_mtx + philo->id - 1);
	if (newstate == TAKEN_FORK)
		printf("%ld%03d %d has taken a fork\n",
			ts.tv_sec, ts.tv_usec / 1000, philo->id);
	else if (newstate == EATING)
		printf("%ld%03d %d is eating\n", ts.tv_sec,
			ts.tv_usec / 1000, philo->id);
	else if (newstate == SLEEPING)
		printf("%ld%03d %d is sleeping\n",
			ts.tv_sec, ts.tv_usec / 1000, philo->id);
	else if (newstate == THINKING)
		printf("%ld%03d %d is thinking\n",
			ts.tv_sec, ts.tv_usec / 1000, philo->id);
	else
		printf("%ld%03d %d died\n", ts.tv_sec, ts.tv_usec / 1000, philo->id);
}

void	philo_take_fork(t_philo *philo)
{
	MTX_LOCK(philo->forks + (philo->id - 1));
	if (philo->must_stop)
		return (MTX_UNLOCK(philo->forks + (philo->id - 1)), (void) 0);
	if (philo->infos->philo_amt > 1)
	{
		MTX_LOCK(philo->forks
			+ (philo->id * (philo->id != philo->infos->philo_amt)));
		if (philo->must_stop)
			return (MTX_UNLOCK(philo->forks
					+ (philo->id * (philo->id != philo->infos->philo_amt))),
				(void) 0);
	}
	change_state(philo, TAKEN_FORK);
	philo_eat(philo);
}

static void	put_fork(t_philo *philo)
{
	MTX_UNLOCK(philo->forks + (philo->id - 1));
	if (philo->infos->philo_amt > 1)
		MTX_UNLOCK(philo->forks
			+ (philo->id * (philo->id != philo->infos->philo_amt)));
}

void	philo_eat(t_philo *philo)
{
	if (philo->must_stop)
		return (MTX_UNLOCK(philo->forks + (philo->id - 1)),
			MTX_UNLOCK(philo->forks + (philo->id
					* (philo->id != philo->infos->philo_amt))), (void) 0);
	change_state(philo, EATING);
	MTX_LOCK(philo->philos_mtx + philo->id - 1);
	philo->last_meal_time = timestamp();
	MTX_UNLOCK(philo->philos_mtx + philo->id - 1);
	usleep(philo->infos->time_to_eat * 1000);
	MTX_LOCK(philo->philos_mtx + philo->id - 1);
	philo->last_meal_time = timestamp();
	philo->times_eaten++;
	MTX_UNLOCK(philo->philos_mtx + philo->id - 1);
	put_fork(philo);
	if (philo->must_stop)
		return ;
	philo_sleep(philo);
}
