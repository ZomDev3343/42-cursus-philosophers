/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:01:20 by truello           #+#    #+#             */
/*   Updated: 2024/03/04 15:35:00 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manager_loop(void *buf)
{
	int		i;
	int		loop;
	t_vars	*vars;

	loop = TRUE;
	vars = (t_vars *) buf;
	while (loop)
	{
		i = -1;
		if (is_one_philo_dead(vars->philos, vars->infos->philo_amt))
		{
			while (++i < vars->infos->philo_amt)
				vars->philos->must_stop = TRUE;
			loop = FALSE;
		}
	}
	return (NULL);
}
