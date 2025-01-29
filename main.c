/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:50:45 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 19:57:51 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_vars(t_vars *vars, int argc, char **argv)
{
	int	i;

	vars->philo_count = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		vars->meal_goal = ft_atoi(argv[5]);
	else
		vars->meal_goal = -1;
	vars->stop = 0;
	vars->philos = malloc(sizeof(t_philo) * vars->philo_count);
	pthread_mutex_init(&vars->stop_mutex, NULL);
	pthread_mutex_init(&vars->print_mutex, NULL);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philo_count);
	i = 0;
	while (i < vars->philo_count)
		pthread_mutex_init(&vars->forks[i++], NULL);
	vars->start_time = get_time();
	i = 0;
	while (i < vars->philo_count)
	{
		vars->philos[i] = new_philo(vars, i);
		i++;
	}
}


int		check_death(t_philo *philo)
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

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc < 5 || argc > 6)
		return (printf(USAGE, argv[0]), EXIT_FAILURE);
	init_vars(&vars, argc, argv);
	monitor(&vars);
	pthread_mutex_lock(&vars.stop_mutex);
	vars.stop = 1;
	pthread_mutex_unlock(&vars.stop_mutex);
	free_all(&vars);
	return (EXIT_SUCCESS);
}
