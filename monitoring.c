/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:15:58 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 20:50:53 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->meal_mutex);
	dead = get_time() > philo->last_meal + philo->vars->time_to_die;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (dead);
}

int	check_meals(t_vars *vars, t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->meal_mutex);
	result = philo->meal_count >= vars->meal_goal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (result);
}

void	monitor(t_vars *vars)
{
	int	i;
	int	meals_ok;

	while (1)
	{
		usleep(100);
		i = 0;
		meals_ok = 0;
		while (i < vars->philo_count)
		{
			if (check_death(vars->philos[i]))
				return (philo_print(vars->philos[i], "\033[31mdied\033[0m"));
			if (!check_meals(vars, vars->philos[i]))
				meals_ok = 0;
			i++;
		}
		if (meals_ok)
			return ;
	}
}
