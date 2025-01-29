/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 00:18:40 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 16:02:18 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, char *msg)
{
	long	time;

	time = get_time();
	pthread_mutex_lock(&philo->vars->print_mutex);
	printf("% 10ld0 Philo %d %s\n", time - philo->vars->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->vars->print_mutex);
}

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
	philo->last_meal = get_time();
	philo->meal_count++;
	philo_print(philo, "is eating");
	usleep(philo->vars->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	usleep(philo->vars->time_to_sleep * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_print(philo, "is thinking");
		// pthread_mutex_lock(&philo->vars->stop_mutex);
		// philo->vars->stop = 1;
		// pthread_mutex_unlock(&philo->vars->stop_mutex);
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