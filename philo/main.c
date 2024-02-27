/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:11:10 by truello           #+#    #+#             */
/*   Updated: 2024/02/27 16:45:16 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_infos
{
	int	philo_amt;
	int	ttd;
	int	tte;
	int	tts;
	int	philo_eat_amt;
}	t_infos;

typedef struct s_mutexes
{
	pthread_mutex_t	init_mtx;
}	t_mutexes;

static void	philosophers(int ac, char **av)
{

}

int	main(int ac, char **av)
{
	if (ac < 5)
		printf(PHILO_USAGE);
	else
		philosophers(ac, av);
	return (0);
}
