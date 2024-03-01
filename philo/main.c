/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:27:08 by truello           #+#    #+#             */
/*   Updated: 2024/03/01 19:15:22 by tohma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_vars(t_vars *vars)
{
	free(vars->philos);
}

static int	check_args(int ac, char **av)
{
	int	i;
	int	n;

	i = -1;
	while (++i < ac)
	{
		n = ft_atoi(av[i]);
		if (!ft_strcmp(av[ac], "0") && n == 0)
			return (FALSE);
	}
	return (TRUE);
}

static int	setup_vars(t_vars **vars, int ac, char **av)
{
	*vars = (t_vars *) ft_calloc(sizeof(t_vars), 1);
	if (!*vars)
		return (FALSE);
	(*vars)->philo_amt = ft_atoi(av[1]);
	(*vars)->time_to_die = ft_atoi(av[2]);
	(*vars)->time_to_eat = ft_atoi(av[3]);
	(*vars)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*vars)->philo_amt = ft_atoi(av[5]);
	(*vars)->philos = ft_calloc(sizeof(t_philo), (*vars)->philo_amt);
	(*vars)->threads = ft_calloc(sizeof(pthread_t), (*vars)->philo_amt);
	if (!(*vars)->philos || !(*vars)->threads)
		return (ft_free((*vars)->philos), ft_free((*vars)->threads), FALSE);
	return (TRUE);
}

static void	init_philo(int ac, char **av)
{
	t_vars	*vars;

	if (!check_args(ac, av) || !setup_vars(&vars, ac, av))
		return (printf("Initialization error!\n"), (void) 0);
}

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6)
		init_philo(ac, av);
	else
		printf("Usage : ./philosopher <philo_amount> <time_to_die> <time_to_eat> \
<time_to_sleep> [amount_of_philo_eating]\n");
	return (0);
}
