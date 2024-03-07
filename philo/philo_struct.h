/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:29:42 by truello           #+#    #+#             */
/*   Updated: 2024/03/07 14:42:42 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCT_H
# define PHILO_STRUCT_H

/* Every steps a philosphers follows during the sim. */
enum e_philo_state
{
	TAKEN_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DEAD
};

/**
 * @param must_eat_times How many times does philo. has to eat [0-~] 0=no limit
 * @param philo_amt How many philosophers
 * @param time_to_die How long (in ms) to die
 * @param time_to_eat How long (in ms) to finish eating
 * @param time_to_sleep How long (in ms) to wake up after sleeping
*/
typedef struct s_infos
{
	int			must_eat_times;
	int			philo_amt;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
}	t_infos;

/**
 * @param forks Mutex list representing the forks
 * @param id Number representing the philosopher [1-~]
 * @param infos Contains all the infos given at the start
 * @param last_meal_time Timestamp of philosopher's last meal
 * @param must_stop Does any philosophers died, or stopping condition fulfilled
 * @param philos_mtx Mutexes to avoid data races when modifing philosophers
 * @param state Current state (e.g enum s_infos)
 * @param times_eaten How many times the philo. ate
*/
typedef struct s_philo
{
	pthread_mutex_t		*forks;
	int					id;
	t_infos				*infos;
	struct timeval		last_meal_time;
	int					must_stop;
	pthread_mutex_t		*philos_mtx;
	enum e_philo_state	state;
	int					times_eaten;
}	t_philo;

/**
 * @param forks Mutex list representing the forks
 * @param infos Contains all the infos given at the start
 * @param philos Every philosophers in the simulation
 * @param philos_mtx Mutexes to avoid data races when modifing philosophers
 * @param threads All the threads linked to philosophers
*/
typedef struct s_vars
{
	pthread_mutex_t	*forks;
	t_infos			*infos;
	t_philo			*philos;
	pthread_mutex_t	*philos_mtx;
	pthread_t		*threads;
}	t_vars;

#endif
