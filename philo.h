/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:43:56 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/19 02:03:13 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_rules
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				someone_died;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_t		thread;
	t_rules			*rules;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

// utils.c
long	current_timestamp(void);
void	precise_sleep(long time_in_ms);
void	print_status(t_philo *philo, char *msg);
int		ft_atoi(const char *str);
char	**ft_split(const char *str, char sep);
void	free_split(char **split);
char	**flatten_args(int argc, char **argv);

// init.c
int		init_mutexes(t_rules *rules);
t_philo	*init_philosophers(t_rules *rules);
void	destroy_mutexes(t_rules *rules, t_philo *philos);

// routine.c
void	*routine(void *arg);

// monitor.c
void	*monitor(void *arg);

#endif
