/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:18:40 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 00:45:52 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo philo;

	philo = *(t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo.vars->stop_mutex);
		philo.vars->stop = 1;
		pthread_mutex_unlock(&philo.vars->stop_mutex);
		return (NULL);
	}
}

t_philo	*new_philo(t_vars *vars, int id)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	p->id = id;
	p->last_meal = vars->start_time;
	p->vars = vars;
	p->left_fork = vars->forks[id];
	p->right_fork = vars->forks[(id + 1) % vars->philo_count];
	pthread_create(&p->thread, NULL, philo_routine, p);
	return (p);
}