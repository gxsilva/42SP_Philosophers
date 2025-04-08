/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:03 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/08 18:44:44 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		message(char *str, t_philo *philo);
void		input_checker(char **argv);
uint64_t	get_time(t_data *philo_s);

void	message(char *str, t_philo *philo)
{
	uint64_t	time;

	time = get_time(philo->data) - philo->data->start_time;
	if (ft_strcmp(str, DIED) == 0)
	{
		sem_wait(philo->data->write);
		printf("%lu %d %s\n", time, philo->id, str);
		return ;
	}
	else
	{
		sem_wait(philo->data->write);
		printf("%lu %d %s\n", time, philo->id, str);
		sem_post(philo->data->write);
	}
}

uint64_t	get_time(t_data *philo_s)
{
	struct timeval	tv;
	uint64_t		cast_time;

	if (gettimeofday(&tv, NULL))
	{
		free_philo(philo_s);
		terminate_with_error(FAILED_GET_TIME, -3);
	}
	cast_time = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (cast_time);
}

void	input_checker(char **argv)
{
	int		x;
	int		y;

	x = 1;
	while (argv[++x])
	{
		y = -1;
		while (argv[x][++y])
		{
			if (argv[x][y] < 48 || argv[x][y] > 57)
				terminate_with_error(INVALID_FORMAT, -1);
		}
	}
}
