/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:53:12 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/19 02:03:06 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_rules *rules)
{
	int	i;

	rules->forks = malloc(sizeof(pthread_mutex_t)
			* rules->number_of_philosophers);
	if (!rules->forks)
		return (1);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->print_lock, NULL))
		return (1);
	return (0);
}

t_philo	*init_philosophers(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * rules->number_of_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = current_timestamp();
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		philos[i].rules = rules;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[(i + 1)
			% rules->number_of_philosophers];
		i++;
	}
	return (philos);
}

void	destroy_mutexes(t_rules *rules, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&rules->print_lock);
}
