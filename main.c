/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:54:29 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/21 18:07:01 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_numeric_argument(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static int	parse_args(int argc, char **argv, t_rules *rules)
{
	int	i;

	if (argc != 4 && argc != 5)
		return (1);
	i = 0;
	while (i < argc)
		if (!is_numeric_argument(argv[i++]))
			return (1);
	rules->number_of_philosophers = ft_atoi(argv[0]);
	rules->time_to_die = ft_atoi(argv[1]);
	rules->time_to_eat = ft_atoi(argv[2]);
	rules->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		rules->must_eat_count = ft_atoi(argv[4]);
	else
		rules->must_eat_count = -1;
	if (rules->number_of_philosophers <= 0
		|| rules->time_to_die <= 59
		|| rules->time_to_eat <= 59
		|| rules->time_to_sleep <= 59
		|| (argc == 5 && rules->must_eat_count <= 0))
		return (1);
	rules->someone_died = 0;
	rules->start_time = current_timestamp();
	return (0);
}

static void	start_threads(t_philo *philos, t_rules *rules)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, monitor, philos);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < rules->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		ac;
	char	**args;
	t_rules	rules;
	t_philo	*philos;

	args = flatten_args(argc, argv);
	if (!args)
		return (printf("Error: malloc failed\n"), 1);
	ac = 0;
	while (args[ac])
		ac++;
	if (parse_args(ac, args, &rules))
		return (printf("Error: invalid arguments\n"), free_split(args), 1);
	if (init_mutexes(&rules))
		return (printf("Error: mutex init failed\n"), 1);
	philos = init_philosophers(&rules);
	if (!philos)
		return (printf("Error: philos init failed\n"), 1);
	start_threads(philos, &rules);
	destroy_mutexes(&rules, philos);
	(free(philos), free(rules.forks), free_split(args));
	return (0);
}
