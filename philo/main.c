/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tohma <tohma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:27:08 by truello           #+#    #+#             */
/*   Updated: 2024/03/06 17:25:20 by tohma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int ac, char **av)
{
	int	i;
	int	n;

	i = 0;
	while (++i < ac)
	{
		n = ft_atoi(av[i]);
		if (!ft_strcmp(av[i], "0") && n == 0)
			return (FALSE);
	}
	return (TRUE);
}

static void	init_vars(t_vars *vars)
{
	int			i;

	i = -1;
	while (++i < vars->infos->philo_amt)
	{
		MTX_INIT(vars->forks + i, NULL);
		MTX_INIT(vars->philos_mtx + i, NULL);
	}
	i = -1;
	while (++i < vars->infos->philo_amt)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].state = THINKING;
		vars->philos[i].infos = vars->infos;
		vars->philos[i].forks = vars->forks;
		vars->philos[i].philos_mtx = vars->philos_mtx;
		THD_CREATE(vars->threads + i, NULL, &routine, vars->philos + i);
	}
	THD_CREATE(vars->threads + vars->infos->philo_amt, NULL,
		&manager_loop, vars);
}

static int	setup_vars(t_vars **vars, int ac, char **av)
{
	*vars = (t_vars *) ft_calloc(sizeof(t_vars), 1);
	if (!*vars)
		return (FALSE);
	(*vars)->infos = ft_calloc(sizeof(t_infos), 1);
	if (!(*vars)->infos)
		return (free(vars), FALSE);
	(*vars)->infos->philo_amt = ft_atoi(av[1]);
	(*vars)->infos->time_to_die = ft_atoi(av[2]);
	(*vars)->infos->time_to_eat = ft_atoi(av[3]);
	(*vars)->infos->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*vars)->infos->must_eat_times = ft_atoi(av[5]);
	(*vars)->philos = ft_calloc(sizeof(t_philo), (*vars)->infos->philo_amt);
	(*vars)->forks = ft_calloc(sizeof(pthread_mutex_t),
			(*vars)->infos->philo_amt);
	(*vars)->philos_mtx = ft_calloc(sizeof(pthread_mutex_t),
			(*vars)->infos->philo_amt);
	(*vars)->threads = ft_calloc(sizeof(pthread_t),
			(*vars)->infos->philo_amt + 1);
	if (!(*vars)->philos || !(*vars)->threads || !(*vars)->forks
		|| !(*vars)->philos_mtx)
		return (free_vars(*vars), FALSE);
	return (TRUE);
}

static void	start_philo(int ac, char **av)
{
	t_vars	*vars;
	int		i;

	i = -1;
	if (!check_args(ac, av) || !setup_vars(&vars, ac, av))
		return (printf("Initialization error!\n"), (void) 0);
	init_vars(vars);
	while (++i < vars->infos->philo_amt + 1)
		THD_JOIN(vars->threads[i], NULL);
	i = -1;
	while (++i < vars->infos->philo_amt)
	{
		MTX_DESTROY(vars->forks + i);
		MTX_DESTROY(vars->philos_mtx + i);
	}
	free_vars(vars);
}

int	main(int ac, char **av)
{
	if (ac >= 5 && ac <= 6)
		start_philo(ac, av);
	else
		printf("Usage : ./philosopher <philo_amount> <time_to_die> <time_to_eat> \
<time_to_sleep> [amount_of_philo_eating]\n");
	return (0);
}
