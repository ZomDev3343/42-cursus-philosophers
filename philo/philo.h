/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:11:29 by truello           #+#    #+#             */
/*   Updated: 2024/02/27 16:41:15 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define PHILO_USAGE "Usage : <philo_amount> <time_to_die> <time_to_eat> \
				<time_to_sleep> [amount_of_philo_eating]"

int			ft_atoi(const char *str);
long long	timestamp(void);

#endif
