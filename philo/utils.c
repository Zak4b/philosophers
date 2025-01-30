/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 20:02:53 by asene             #+#    #+#             */
/*   Updated: 2025/01/30 11:28:26 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_int(const char *nptr, int *result)
{
	if (!nptr || !result)
		return (EXIT_FAILURE);
	*result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*(nptr++) == '-')
			return (EXIT_FAILURE);
	while (*nptr >= '0' && *nptr <= '9')
	{
		*result = *result * 10 + (*(nptr++) - '0');
		if (*result > __INT_MAX__)
			return (EXIT_FAILURE);
	}
	if (*nptr)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleep_ms(int duration)
{
	long	start;

	start = get_time();
	while (get_time() < start + duration)
		usleep(500);
}

void	free_all(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->philo_count)
	{
		pthread_join(vars->philos[i]->thread, NULL);
		pthread_mutex_destroy(&vars->philos[i]->meal_mutex);
		free(vars->philos[i++]);
	}
	free(vars->forks);
	free(vars->philos);
	pthread_mutex_destroy(&vars->stop_mutex);
	pthread_mutex_destroy(&vars->print_mutex);
}

void	philo_print(t_philo *philo, char *msg)
{
	int		stop;
	long	time;

	time = get_time();
	pthread_mutex_lock(&philo->vars->stop_mutex);
	stop = philo->vars->stop;
	pthread_mutex_unlock(&philo->vars->stop_mutex);
	if (stop)
		return ;
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("%ld %d %s\n", time, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}
