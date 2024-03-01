/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:11:29 by truello           #+#    #+#             */
/*   Updated: 2024/03/01 19:12:11 by tohma            ###   ########.fr       */
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

# define PHILO_TAKEN_FORK "%ld %d has taken a fork\n"
# define PHILO_EATING "%ld %d is eating\n"
# define PHILO_SLEEPING "%ld %d is sleeping\n"
# define PHILO_THINKING "%ld %d is thinking\n"
# define PHILO_DEAD "%ld %d is dead\n"

int			ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
void		*ft_calloc(size_t size, size_t count);
void		ft_free(void *to_free);
long long	timestamp(void);

#endif
