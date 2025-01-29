/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:18:40 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 20:51:15 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_print(philo, "is eating");
	sleep_ms(philo->vars->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	sleep_ms(philo->vars->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	int		stop;
	t_philo	*philo;

	philo = (t_philo *)arg;
	stop = 0;
	if (philo->vars->philo_count == 1)
	{
		philo_print(philo, "has taken a fork");
		return (NULL);
	}
	while (!stop)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_print(philo, "is thinking");
		pthread_mutex_lock(&philo->vars->stop_mutex);
		stop = philo->vars->stop;
		pthread_mutex_unlock(&philo->vars->stop_mutex);
	}
	return (NULL);
}

t_philo	*new_philo(t_vars *vars, int id)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	p->id = id;
	p->last_meal = vars->start_time;
	p->meal_count = 0;
	p->vars = vars;
	p->left_fork = &vars->forks[id];
	p->right_fork = &vars->forks[(id + 1) % vars->philo_count];
	pthread_mutex_init(&p->meal_mutex, NULL);
	pthread_create(&p->thread, NULL, philo_routine, p);
	return (p);
}
