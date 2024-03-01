/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:29:42 by truello           #+#    #+#             */
/*   Updated: 2024/03/01 19:11:49 by tohma            ###   ########.fr       */
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

/**
 * @param philo_amt Number of philosophers around the table
*/
typedef struct s_vars
{
	int			philo_amt;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_times;
	pthread_t	*threads;
	t_philo		*philos;
}	t_vars;

#endif
