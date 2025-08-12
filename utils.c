/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:48:27 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/21 20:48:49 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_timestamp(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}

void	precise_sleep(long time_in_ms)
{
	long	start;

	start = current_timestamp();
	while ((current_timestamp() - start) < time_in_ms)
		usleep(500);
}

static char	*get_color(char *msg)
{
	if (!msg)
		return ("\033[0m");
	if (msg[0] == 'i' && msg[1] == 's' && msg[3] == 'e')
		return ("\033[32m");
	if (msg[0] == 'i' && msg[1] == 's' && msg[3] == 's')
		return ("\033[34m");
	if (msg[0] == 'i' && msg[1] == 's' && msg[3] == 't')
		return ("\033[33m");
	if (msg[0] == 'h' && msg[1] == 'a')
		return ("\033[36m");
	if (msg[0] == 'd')
		return ("\033[31m");
	return ("\033[0m");
}

void	print_status(t_philo *philo, char *msg)
{
	long	timestamp;
	char	*color;
	int		dead;

	pthread_mutex_lock(&philo->rules->death_lock);
	dead = philo->rules->someone_died;
	pthread_mutex_unlock(&philo->rules->death_lock);
	if (dead)
		return ;
	pthread_mutex_lock(&philo->rules->print_lock);
	timestamp = current_timestamp() - philo->rules->start_time;
	color = get_color(msg);
	printf("%s%ld %d %s\033[0m\n", color, timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print_lock);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (sign == 1 && result > 2147483647)
			return (-1);
		if (sign == -1 && - result < -2147483648)
			return (0);
		i++;
	}
	return ((int)(result * sign));
}
