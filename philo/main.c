/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:27:08 by truello           #+#    #+#             */
/*   Updated: 2024/03/01 12:29:21 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int ac, char **av)
{

}

static void	init_philo()
{

}

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6)
		init_philo();
	else
		printf(PHILO_USAGE);
	return (0);
}
