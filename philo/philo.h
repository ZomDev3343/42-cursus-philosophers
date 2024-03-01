/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:11:29 by truello           #+#    #+#             */
/*   Updated: 2024/03/01 12:21:04 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define PHILO_USAGE "Usage : <philo_amount> <time_to_die> <time_to_eat> \
<time_to_sleep> [amount_of_philo_eating]"

# define PHILO_TAKEN_FORK "%ld %d has taken a fork\n"
# define PHILO_EATING "%ld %d is eating\n"
# define PHILO_SLEEPING "%ld %d is sleeping\n"
# define PHILO_THINKING "%ld %d is thinking\n"
# define PHILO_DEAD "%ld %d is dead\n"

int			ft_atoi(const char *str);
long long	timestamp(void);

#endif
