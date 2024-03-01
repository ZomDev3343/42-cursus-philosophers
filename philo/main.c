/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:11:10 by truello           #+#    #+#             */
/*   Updated: 2024/03/01 12:25:46 by truello          ###   ########.fr       */
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
	pthread_mutex_t	*init_mtx;
	pthread_mutex_t	*forks;
}	t_mutexes;

typedef struct s_vars
{
	t_infos		infos;
	t_mutexes	*mutexes;
	pthread_t	*threads;
	int			threads_ready;
}	t_vars;

enum	e_philo_state
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct s_philosopher
{
	t_vars				*vars;
	int					id;
	enum e_philo_state	state;
}	t_philo;

static void	free_vars(t_vars *vars)
{
	free(vars->mutexes);
	free(vars->threads);
}

static void	init_mutexes(t_vars *vars)
{
	int	i;

	i = -1;
	pthread_mutex_init(vars->mutexes->init_mtx, NULL);
	vars->mutexes->forks = malloc(sizeof(pthread_mutex_t) * vars->infos.philo_amt);
	if (!vars->mutexes->forks)
		return ;
	while (++i < vars->infos.philo_amt)
		pthread_mutex_init(vars->mutexes->forks + i, NULL);
}

static int	init_vars(t_vars *vars, int ac, char **av)
{
	vars->infos = get_infos(ac, av);
	vars->mutexes = (t_mutexes *) malloc(sizeof(t_mutexes));
	vars->threads = (pthread_t *) malloc(sizeof(pthread_t) * vars->infos.philo_amt);
	if (!vars->threads || !vars->mutexes)
		return (0);
	init_mutexes(vars);
	vars->threads_ready = 0;
	return (1);
}

static int	check_args(int ac, char **av)
{
	long	n;

	while (--ac > 0)
	{
		n = ft_atoi(av[ac]);
		if ((n == 0 && (av[ac][0] != '0' && av[ac][1] != '\0'))
			|| n < 0)
			return (0);
	}
	return (1);
}

static t_infos	get_infos(int ac, char **av)
{
	t_infos	res;

	res.philo_amt = ft_atoi(av[1]);
	res.ttd = ft_atoi(av[2]);
	res.tte = ft_atoi(av[3]);
	res.tts = ft_atoi(av[4]);
	if (ac == 6)
		res.philo_eat_amt = ft_atoi(av[5]);
	return (res);
}

static void	change_state(t_philo *philo, enum e_philo_state new_state)
{
	long long	ts;

	if (new_state == philo->state)
		return ;
	ts = timestamp();
	philo->state = new_state;
	if (philo->state == TAKEN_FORK)
		printf(PHILO_TAKEN_FORK, ts, philo->id);
	else if (philo->state == EATING)
		printf(PHILO_EATING, ts, philo->id);
	else if (philo->state == SLEEPING)
		printf(PHILO_SLEEPING, ts, philo->id);
	else if (philo->state == THINKING)
		printf(PHILO_THINKING, ts, philo->id);
	else if (philo->state == DEAD)
		printf(PHILO_DEAD, ts, philo->id);
}

static void	routine(t_philo *philo)
{

}

static void	philosophers(int ac, char **av)
{
	t_vars	vars;
	t_philo	*philo;
	int		i;

	if (!check_args(ac, av) || !init_vars(&vars, ac, av))
		return ;
	philo = (t_philo *) malloc(sizeof(t_philo) * vars.infos.philo_amt);
	if (!philo)
		return (free_vars(&vars));
	i = -1;
	while (++i < vars.infos.philo_amt)
	{
		philo[i].vars = &vars;
		philo[i].id = i;
		philo[i].state = THINKING;
		pthread_create(vars.threads + i, NULL, &routine, philo + i);
	}
	i = -1;
	while (++i < vars.infos.philo_amt)
		pthread_join(vars.threads + i, NULL);
}

int	main(int ac, char **av)
{
	if (ac < 5)
		printf(PHILO_USAGE);
	else
		philosophers(ac, av);
	return (0);
}
