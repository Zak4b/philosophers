/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:50:45 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 00:40:47 by asene            ###   ########.fr       */
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
	pthread_mutex_init(&vars->meal_goal_mutex, NULL);
	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->philo_count);
	i = 0;
	while (i < vars->philo_count)
		pthread_mutex_init(&vars->forks[i++], NULL);
	i = 0;
	while (i < vars->philo_count)
	{
		vars->philos[i] = new_philo(vars, i);
		i++;
	}
	vars->start_time = get_time();
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		stop;

	if (argc < 5 || argc > 6)
		return (printf(USAGE, argv[0]), EXIT_FAILURE);
	init_vars(&vars, argc, argv);
	stop = 0;
	while (stop == 0)
	{
		usleep(100);
		pthread_mutex_lock(&vars.stop_mutex);
		stop = vars.stop;
		pthread_mutex_unlock(&vars.stop_mutex);
	}
	free_all(&vars);
	return (EXIT_SUCCESS);
}
