/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:58:44 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/21 22:12:05 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo, t_rules *rules)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		if (philo->rules->number_of_philosophers == 1)
		{
			while (!is_someone_dead(rules))
				usleep(100);
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

static void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = current_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	precise_sleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_sleep(philo->rules->time_to_sleep);
	print_status(philo, "is thinking");
	if (philo->rules->number_of_philosophers % 2 != 0)
		precise_sleep(philo->rules->time_to_eat / 3);
}

int	is_someone_dead(t_rules *rules)
{
	int	status;

	pthread_mutex_lock(&rules->death_lock);
	status = rules->someone_died;
	pthread_mutex_unlock(&rules->death_lock);
	return (status);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_rules	*rules;

	philo = (t_philo *)arg;
	rules = philo->rules;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_someone_dead(rules))
	{
		if (is_someone_dead(rules))
			break ;
		take_forks(philo, rules);
		if (philo->rules->number_of_philosophers == 1)
			return (NULL);
		if (is_someone_dead(rules))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
