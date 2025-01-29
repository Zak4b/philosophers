/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:50:48 by asene             #+#    #+#             */
/*   Updated: 2025/01/29 15:55:39 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# define USAGE "Usage: %s <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [meal_goal]\n"

typedef struct s_vars
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_goal;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	struct s_philo	**philos;
	long			start_time;
}	t_vars;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meal_count;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_vars			*vars;
}	t_philo;

int		ft_atoi(const char *nptr);
long	get_time(void);
void	free_all(t_vars *vars);

void	*philo_routine(void *arg);
t_philo	*new_philo(t_vars *vars, int id);

#endif