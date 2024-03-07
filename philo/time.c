/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:38:32 by truello           #+#    #+#             */
/*   Updated: 2024/03/07 14:42:06 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval	timestamp(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return (tval);
}

/**
 * @brief Get the duration (in ms) between two moments
 *
 * @param from Most recent moment
 * @param to Less recent moment
 * @return int Duration in ms
 */
int	get_time_diff(struct timeval from, struct timeval to)
{
	long long	diff;

	diff = (from.tv_sec - to.tv_sec) * 1000;
	diff += (from.tv_usec - to.tv_usec) / 1000;
	return (diff);
}
