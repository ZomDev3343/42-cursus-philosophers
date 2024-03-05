/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:10:50 by truello           #+#    #+#             */
/*   Updated: 2024/03/05 13:31:50 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *buf)
{
	t_philo	*philo;

	philo = (t_philo *) buf;
	if (philo->last_meal_time == -1)
		philo->last_meal_time = timestamp();
	return (NULL);
}

void	change_state(t_philo *philo, enum e_philo_state newstate)
{
	long long	ts;

	if (philo->state == newstate)
		return ;
	ts = timestamp();
	philo->state = newstate;
	if (newstate == TAKEN_FORK)
		printf("%lld %d has taken a fork\n", ts, philo->id);
	else if (newstate == EATING)
		printf("%lld %d is eating\n", ts, philo->id);
	else if (newstate == SLEEPING)
		printf("%lld %d is sleeping\n", ts, philo->id);
	else if (newstate == THINKING)
		printf("%lld %d is thinking\n", ts, philo->id);
	else
		printf("%lld %d is dead\n", ts, philo->id);
}

void	take_fork(t_philo *philo)
{
	MTX_LOCK(philo->forks + (philo->id - 1));
	if (philo->infos->philo_amt > 1)
	{
		if (philo->id == philo->infos->philo_amt)
			MTX_LOCK(philo->forks);
		else
			MTX_LOCK(philo->forks + philo->id);
	}
}

int	is_one_philo_dead(t_philo *philosophers, int amount)
{
	while (amount-- >= 0)
	{
		if ((int)(timestamp() - philosophers[amount].last_meal_time)
			> philosophers->infos->time_to_die)
			return (TRUE);
	}
	return (FALSE);
}
