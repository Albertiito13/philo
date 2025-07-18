/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 22:51:11 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/18 23:03:27 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	count_total_args(int argc, char **argv)
{
	int		i;
	int		count;
	char	**temp;
	int		j;

	i = 1;
	count = 0;
	while (i < argc)
	{
		temp = ft_split(argv[i], ' ');
		if (!temp)
			return (-1);
		j = 0;
		while (temp[j])
		{
			count++;
			j++;
		}
		free_split(temp);
		i++;
	}
	return (count);
}

static int	copy_split_into_final(char **dest, char *arg, int index)
{
	char	**temp;
	int		j;

	temp = ft_split(arg, ' ');
	if (!temp)
		return (-1);
	j = 0;
	while (temp[j])
	{
		dest[index++] = temp[j];
		j++;
	}
	free(temp);
	return (index);
}

char	**flatten_args(int argc, char **argv)
{
	char	**final;
	int		total;
	int		i;
	int		k;

	total = count_total_args(argc, argv);
	if (total < 0)
		return (NULL);
	final = malloc(sizeof(char *) * (total + 1));
	if (!final)
		return (NULL);
	i = 1;
	k = 0;
	while (i < argc)
	{
		k = copy_split_into_final(final, argv[i], k);
		if (k < 0)
			return (NULL);
		i++;
	}
	final[k] = NULL;
	return (final);
}
