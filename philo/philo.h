/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:11:29 by truello           #+#    #+#             */
/*   Updated: 2024/03/04 15:34:56 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include "philo_struct.h"

# define TRUE 1
# define FALSE 0

# define THD_CREATE pthread_create
# define THD_DETACH pthread_detach

# define MTX_INIT pthread_mutex_init
# define MTX_LOCK pthread_mutex_lock
# define MTX_UNLOCK pthread_mutex_unlock

/* Utils */

int			ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
void		*ft_calloc(size_t size, size_t count);
void		ft_free(void *to_free);
void		free_vars(t_vars *vars);

/* Philosophers Control */

void		*routine(void *buf);
void		change_state(t_philo *philo, enum e_philo_state newstate);
void		take_fork(t_philo *philo);
int			is_one_philo_dead(t_philo *philosophers, int amount);

/* Manager */

void		*manager_loop(void *buf);

/* Time */

long long	timestamp(void);

#endif
