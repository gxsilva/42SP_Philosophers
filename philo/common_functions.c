/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:45:18 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/19 01:39:21 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		message(char *str, t_philo *philo);
uint64_t	get_time(t_data *philo_s);
void		input_checker(int argc, char **argv);

void	message(char *str, t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time(philo->data) - philo->data->start_time;
	if (ft_strcmp(str, DIED) == 0 && philo->data->dead == 0)
	{
		printf("%lu %d %s\n", time, philo->id + 1, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%lu %d %s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->write);
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

void	input_checker(int argc, char **argv)
{
	int		x;
	int		y;

	x = 1;
	y = 1;
	while (argv[x])
	{
		y = 0;
		while (argv[x][y])
		{
			if (argv[x][y] == ' ')
				(void)argc;
			else if (argv[x][y] < 48 || argv[x][y] > 57)
			{
				printf("%c | %d\n", argv[x][y], argv[x][y]);
				terminate_with_error(INVALID_FORMAT, -1);
			}
			y++;
		}
		x++;
	}
}
