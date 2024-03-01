/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:29:42 by truello           #+#    #+#             */
/*   Updated: 2024/03/01 12:46:20 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

enum e_philo_state
{
	TAKEN_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DEAD
};

typedef struct s_philo
{
	long long	last_meal_time;
	long long	sleep_start_time;
}	t_philo;

typedef struct s_vars
{
	int	philo_amt;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;

}	t_vars;

#endif
