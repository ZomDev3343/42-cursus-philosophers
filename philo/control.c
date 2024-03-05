/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:10:50 by truello           #+#    #+#             */
/*   Updated: 2024/03/05 16:25:37 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *buf)
{
	t_philo	*philo;

	philo = (t_philo *) buf;
	if (philo->last_meal_time.tv_sec == 0)
		philo->last_meal_time = timestamp();
	while (!philo->must_stop
		|| (philo->infos->must_eat_times > 0
			&& philo->times_eaten < philo->infos->must_eat_times))
	{
		philo_take_fork(philo);
	}
	return (NULL);
}

void	change_state(t_philo *philo, enum e_philo_state newstate)
{
	struct timeval	ts;

	if (philo->state == newstate)
		return ;
	ts = timestamp();
	philo->state = newstate;
	if (newstate == TAKEN_FORK)
		printf("%ld%d %d has taken a fork\n", ts.tv_sec, ts.tv_usec, philo->id);
	else if (newstate == EATING)
		printf("%ld%d %d is eating\n", ts.tv_sec, ts.tv_usec, philo->id);
	else if (newstate == SLEEPING)
		printf("%ld%d %d is sleeping\n", ts.tv_sec, ts.tv_usec, philo->id);
	else if (newstate == THINKING)
		printf("%ld%d %d is thinking\n", ts.tv_sec, ts.tv_usec, philo->id);
	else
		printf("%ld%d %d is dead\n", ts.tv_sec, ts.tv_usec, philo->id);
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
	struct timeval	start_eating_time;

	start_eating_time = timestamp();
	if (philo->must_stop)
		return ;
	change_state(philo, EATING);
	philo->last_meal_time = timestamp();
	while (get_time_diff(timestamp(), start_eating_time)
		<= philo->infos->time_to_eat)
		;
	philo->last_meal_time = timestamp();
	philo->times_eaten++;
	put_fork(philo);
	if (philo->must_stop)
		return ;
	philo_sleep(philo);
}
