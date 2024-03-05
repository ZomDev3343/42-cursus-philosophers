/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:29:42 by truello           #+#    #+#             */
/*   Updated: 2024/03/05 15:31:02 by truello          ###   ########.fr       */
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

typedef struct s_infos
{
	int			philo_amt;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_times;
}	t_infos;

typedef struct s_philo
{
	pthread_mutex_t		*forks;
	int					id;
	t_infos				*infos;
	struct timeval		last_meal_time;
	int					must_stop;
	struct timeval		sleep_start_time;
	enum e_philo_state	state;
	int					times_eaten;
}	t_philo;

/**
 * @param philo_amt Number of philosophers around the table
*/
typedef struct s_vars
{
	pthread_mutex_t	*forks;
	t_infos			*infos;
	t_philo			*philos;
	pthread_t		*threads;
}	t_vars;

#endif
