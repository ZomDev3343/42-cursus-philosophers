/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:38:32 by truello           #+#    #+#             */
/*   Updated: 2024/03/05 16:23:32 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval	timestamp(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return (tval);
}

int	get_time_diff(struct timeval from, struct timeval to)
{
	long long	diff;

	diff = (from.tv_sec - to.tv_sec) * 1000;
	diff += (from.tv_usec - to.tv_usec) / 1000;
	return (diff);
}
