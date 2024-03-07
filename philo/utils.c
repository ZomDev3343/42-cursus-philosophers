/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truello <truello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:39:44 by truello           #+#    #+#             */
/*   Updated: 2024/03/07 14:55:06 by truello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	long int		r;
	unsigned char	minus_count;

	i = 0;
	r = 0;
	minus_count = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus_count = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	if (minus_count == 1)
		r *= -1;
	return ((int) r);
}

void	*ft_calloc(size_t size, size_t count)
{
	void	*res;

	res = malloc(size * count);
	if (!res)
		return (NULL);
	memset(res, 0, size * count);
	return (res);
}

void	ft_free(void *to_free)
{
	if (to_free)
		free(to_free);
}

void	free_vars(t_vars *vars)
{
	ft_free(vars->philos);
	ft_free(vars->threads);
	ft_free(vars->infos);
	ft_free(vars->forks);
	ft_free(vars->philos_mtx);
	ft_free(vars);
}
