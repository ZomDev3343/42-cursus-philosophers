/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:56:23 by truello           #+#    #+#             */
/*   Updated: 2024/03/05 15:40:43 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	struct timeval	sleep_start_time;

	if (philo->must_stop)
		return ;
	change_state(philo, SLEEPING);
	sleep_start_time = timestamp();
	while (get_time_diff(timestamp(), sleep_start_time)
		<= philo->infos->time_to_sleep)
		;
	if (philo->must_stop)
		return ;
	change_state(philo, THINKING);
}

int	is_philo_dead(t_philo *philo)
{
	return (get_time_diff(timestamp(), philo->last_meal_time)
		> philo->infos->time_to_die);
}
