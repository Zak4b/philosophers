/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:02:53 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 00:43:47 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;

	if (!nptr)
		return (0);
	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
		result = result * 10 + (*(nptr++) - '0');
	return ((int)result * sign);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	free_all(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_count)
	{
		pthread_join(vars->philos[i]->thread, NULL);
		free(vars->philos[i++]);
	}
	free(vars->forks);
	free(vars->philos);
	pthread_mutex_destroy(&vars->meal_goal_mutex);
	pthread_mutex_destroy(&vars->stop_mutex);
	pthread_mutex_destroy(&vars->print_mutex);
}
