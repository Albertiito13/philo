/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:05:43 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/04 16:30:19 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_philo *philo)
{
	long	now;

	now = current_timestamp();
	if ((now - philo->last_meal_time) > philo->rules->time_to_die)
	{
		pthread_mutex_lock(&philo->rules->print_lock);
		if (!philo->rules->someone_died)
		{
			printf("%ld %d died\n",
				now - philo->rules->start_time, philo->id);
			philo->rules->someone_died = 1;
		}
		pthread_mutex_unlock(&philo->rules->print_lock);
		return (1);
	}
	return (0);
}

static int	all_satisfied(t_philo *philos)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < philos[0].rules->number_of_philosophers)
	{
		if (philos[i].meals_eaten >= philos[0].rules->must_eat_count
			&& philos[0].rules->must_eat_count != -1)
			full++;
		i++;
	}
	if (full == philos[0].rules->number_of_philosophers)
		return (1);
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_rules	*rules;
	int		i;

	philos = (t_philo *)arg;
	rules = philos[0].rules;
	while (!rules->someone_died)
	{
		i = 0;
		while (i < rules->number_of_philosophers)
		{
			if (check_death(&philos[i]))
				return (NULL);
			i++;
		}
		if (all_satisfied(philos))
		{
			pthread_mutex_lock(&rules->print_lock);
			rules->someone_died = 1;
			pthread_mutex_unlock(&rules->print_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
