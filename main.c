/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:50:45 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 20:49:25 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_vars *vars)
{
	int	i;

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philo_count);
	i = 0;
	while (i < vars->philo_count)
		pthread_mutex_init(&vars->forks[i++], NULL);
}

void	init_philos(t_vars *vars)
{
	int	i;

	vars->philos = malloc(sizeof(t_philo) * vars->philo_count);
	i = 0;
	while (i < vars->philo_count)
	{
		vars->philos[i] = new_philo(vars, i);
		i++;
	}
}

int	init_vars(t_vars *vars, int argc, char **argv)
{
	if (parse_int(argv[1], &vars->philo_count)
		|| parse_int(argv[2], &vars->time_to_die)
		|| parse_int(argv[3], &vars->time_to_eat)
		|| parse_int(argv[4], &vars->time_to_sleep))
		return (0);
	if (argc == 6)
	{
		if (parse_int(argv[5], &vars->meal_goal))
			return (0);
	}
	else
		vars->meal_goal = -1;
	vars->stop = 0;
	pthread_mutex_init(&vars->stop_mutex, NULL);
	pthread_mutex_init(&vars->print_mutex, NULL);
	vars->start_time = get_time();
	init_forks(vars);
	init_philos(vars);
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc < 5 || argc > 6)
		return (printf(USAGE, argv[0]), EXIT_FAILURE);
	if (!init_vars(&vars, argc, argv))
		return (printf("Error, Invalid argument\n"), EXIT_FAILURE);
	monitor(&vars);
	pthread_mutex_lock(&vars.stop_mutex);
	vars.stop = 1;
	pthread_mutex_unlock(&vars.stop_mutex);
	free_all(&vars);
	return (EXIT_SUCCESS);
}
